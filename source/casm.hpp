#ifndef CASM_HPP

#define CASM_HPP

#include <cstddef>
#include <type_traits>
#include <cstdint>
#include <ciso646>
#include <utility>
#include <array>
#include <vector>
#include <limits>
#include <optional>
#include <cassert>
#include <tuple>
#include <stdexcept>
#include <set>
#include <map>
#include <cmath>
#include <cstring>

#if defined(_WIN32)
#define CASM_WINDOWS
#endif

#ifdef CASM_WINDOWS
#include <windows.h>
#else
#include <sys/mman.h>
#endif

namespace casm::details
{
    class base_label
    {
    public:
        using id_t = std::size_t;

        constexpr explicit base_label(id_t id) noexcept
            : id_{ id }
        { }

        constexpr auto id() const noexcept
        {
            return this->id_;
        }

    private:
        id_t id_;
    };

    template<class t>
    inline constexpr const auto is_label_v{ std::is_base_of_v<base_label, std::decay_t<t>> };

    using numeric_label = base_label;

    class crc32
    {
    public:
        using hash_t = std::uint32_t;

        constexpr explicit crc32(char const* const str, std::size_t size) noexcept
            : value_{ 0 xor 0xffffffff }
        {
            for (std::size_t char_n = 0; char_n < size; ++ char_n)
            {
                this->value_ = crc32::table[str[char_n] xor (this->value_ & 0xff)] xor (this->value_ >> 8);
            }

            this->value_ xor_eq 0xffffffff;
        }

        template<std::size_t size>
        constexpr explicit crc32(const char(&str)[size]) noexcept
            : crc32{ str, size - 1 }
        { };

        constexpr operator hash_t() const noexcept
        {
            return this->value_;
        }

    private:
        static constexpr const hash_t table[]
        {
            0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419,
            0x706af48f, 0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4,
            0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07,
            0x90bf1d91, 0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
            0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7, 0x136c9856,
            0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
            0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4,
            0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
            0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3,
            0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac, 0x51de003a,
            0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599,
            0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
            0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190,
            0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f,
            0x9fbfe4a5, 0xe8b8d433, 0x7807c9a2, 0x0f00f934, 0x9609a88e,
            0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
            0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed,
            0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
            0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3,
            0xfbd44c65, 0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
            0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a,
            0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5,
            0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa, 0xbe0b1010,
            0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
            0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17,
            0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6,
            0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615,
            0x73dc1683, 0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
            0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1, 0xf00f9344,
            0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
            0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a,
            0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
            0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1,
            0xa6bc5767, 0x3fb506dd, 0x48b2364b, 0xd80d2bda, 0xaf0a1b4c,
            0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef,
            0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
            0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe,
            0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31,
            0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c,
            0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
            0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b,
            0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
            0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1,
            0x18b74777, 0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
            0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45, 0xa00ae278,
            0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7,
            0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc, 0x40df0b66,
            0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
            0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605,
            0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8,
            0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b,
            0x2d02ef8d
        };

        hash_t value_;
    };

    class crc32_label
        : public base_label
    {
    public:
        constexpr explicit crc32_label(char const* const str, std::size_t size) noexcept
            : base_label{ crc32{ str, size } }
        { }

        template<std::size_t size>
        constexpr explicit crc32_label(const char(&str)[size]) noexcept
            : base_label{ crc32{ str } }
        { };
    };

    enum class sizesof_oper
    {
        _8,
        _16,
        _32,
        _48,
        _64,
        _80,
        _128,
        sreg,
        st,
        mm,
        xmm,
        cr,
        dr
    };

    template<sizesof_oper sizeof_oper>
    class base_oper
    { };

    using oper8_t = base_oper<sizesof_oper::_8>;

    template<class t>
    inline constexpr const auto is_oper8_v{ std::is_base_of_v<oper8_t, t> };

    using oper16_t = base_oper<sizesof_oper::_16>;

    template<class t>
    inline constexpr const auto is_oper16_v{ std::is_base_of_v<oper16_t, t> };

    using oper32_t = base_oper<sizesof_oper::_32>;

    template<class t>
    inline constexpr const auto is_oper32_v{ std::is_base_of_v<oper32_t, t> };

    using oper48_t = base_oper<sizesof_oper::_48>;
    using oper64_t = base_oper<sizesof_oper::_64>;

    template<class t>
    inline constexpr const auto is_oper64_v{ std::is_base_of_v<oper64_t, t> };

    using oper80_t = base_oper<sizesof_oper::_80>;
    using oper128_t = base_oper<sizesof_oper::_128>;

    template<class t>
    inline constexpr const auto is_oper128_v{ std::is_base_of_v<oper128_t, t> };

    using sreg_oper_t = base_oper<sizesof_oper::sreg>;
    using st_oper_t = base_oper<sizesof_oper::st>;
    using mm_oper_t = base_oper<sizesof_oper::mm>;
    using xmm_oper_t = base_oper<sizesof_oper::xmm>;
    using cr_oper_t = base_oper<sizesof_oper::cr>;
    using dr_oper_t = base_oper<sizesof_oper::dr>;

    template<class oper0_t, class oper1_t>
    class is_same_oper_size
    {
        template<sizesof_oper sizeof_oper>
        static constexpr std::true_type impl(base_oper<sizeof_oper>&&, base_oper<sizeof_oper>&&) noexcept;

        static constexpr std::false_type impl(...) noexcept;

    public:
        static constexpr const auto value{ decltype(impl(std::declval<std::decay_t<oper0_t>>(), std::declval<std::decay_t<oper1_t>>()))::value };
    };

    template<class oper0_t, class oper1_t>
    inline constexpr const auto is_same_oper_size_v{ is_same_oper_size<oper0_t, oper1_t>::value };

    using r_n_t = std::uint8_t;

    template<class e>
    constexpr auto e2n(e value) noexcept
    {
        return static_cast<std::underlying_type_t<e>>(value);
    }

    template<class base_oper_t>
    class base_r
        : public base_oper_t
    {
    public:
        template<class names_t>
        constexpr explicit base_r(names_t name) noexcept
            : n_{ e2n(name) }
        { }

        constexpr auto n() const noexcept
        {
            return this->n_;
        }

    private:
        r_n_t n_;
    };

    template<class t>
    class is_r
    {
        template<class base_oper_t>
        static constexpr std::true_type impl(base_r<base_oper_t>&&) noexcept;

        static constexpr std::false_type impl(...) noexcept;

    public:
        static constexpr const auto value{ decltype(impl(std::declval<std::decay_t<t>>()))::value };
    };

    template<class t>
    inline constexpr const auto is_r_v{ is_r<t>::value };

    using base_r8 = base_r<oper8_t>;

    template<class t>
    inline constexpr const auto is_r8_v{ std::is_base_of_v<base_r8, std::decay_t<t>> };

    class r8l
        : public base_r8
    {
    public:
        enum class names
            : r_n_t
        {
            al, cl, dl, bl
        };

        constexpr r8l(names name) noexcept
            : base_r8{ name }
        { }
    };

    class al_t
        : public r8l
    {
    public:
        constexpr al_t() noexcept
            : r8l{ r8l::names::al }
        { }
    };

    class cl_t
        : public r8l
    {
    public:
        constexpr cl_t() noexcept
            : r8l{ r8l::names::cl }
        { }
    };

    class r8h
        : public base_r8
    {
    public:
        enum class names
            : r_n_t
        {
            ah = 4, ch, dh, bh
        };

        constexpr r8h(names name) noexcept
            : base_r8{ name }
        { }
    };

    template<class t>
    inline constexpr const auto is_r8h_v{ std::is_base_of_v<r8h, std::decay_t<t>> };

#if defined(_WIN64) or defined(__x86_64__)
#define CASM_X64
#else
#define CASM_X32
#endif

#ifdef CASM_X64
    class rb
        : public base_r8
    {
    public:
        enum class names
            : r_n_t
        {
            r8b, r9b, r10b, r11b, r12b, r13b, r14b, r15b
        };

        constexpr rb(names name) noexcept
            : base_r8{ name }
        { }
    };

    class rl
        : public base_r8
    {
    public:
        enum class names
            : r_n_t
        {
            spl = 4, bpl, sil, dil
        };

        constexpr rl(names name) noexcept
            : base_r8{ name }
        { }
    };
#endif

    using base_r16 = base_r<oper16_t>;

    template<class t>
    inline constexpr const auto is_r16_v{ std::is_base_of_v<base_r16, std::decay_t<t>> };

    class r16
        : public base_r16
    {
    public:
        enum class names
            : r_n_t
        {
            ax, cx, dx, bx, sp, bp, si, di
        };

        constexpr r16(names name) noexcept
            : base_r16{ name }
        { }
    };

    class ax_t
        : public r16
    {
    public:
        constexpr ax_t() noexcept
            : r16{ r16::names::ax }
        { }
    };

    class dx_t
        : public r16
    {
    public:
        constexpr dx_t() noexcept
            : r16{ r16::names::dx }
        { }
    };

    class sp_t
        : public r16
    {
    public:
        constexpr sp_t() noexcept
            : r16{ r16::names::sp }
        { }
    };

    class bp_t
        : public r16
    {
    public:
        constexpr bp_t() noexcept
            : r16{ r16::names::bp }
        { }
    };

#ifdef CASM_X64
    class rw
        : public base_r16
    {
    public:
        enum class names
            : r_n_t
        {
            r8w, r9w, r10w, r11w, r12w, r13w, r14w, r15w
        };

        constexpr rw(names name) noexcept
            : base_r16{ name }
        { }
    };
#endif

    using base_r32 = base_r<oper32_t>;

    template<class t>
    inline constexpr const auto is_r32_v{ std::is_base_of_v<base_r32, std::decay_t<t>> };

    template<class t>
    inline constexpr const auto is_r16_32_v{ is_r16_v<t> or is_r32_v<t> };

    class r32
        : public base_r32
    {
    public:
        enum class names
            : r_n_t
        {
            eax, ecx, edx, ebx, esp, ebp, esi, edi, eip, eiz
        };

        constexpr r32(names name) noexcept
            : base_r32{ name }
        { }
    };

    class eax_t
        : public r32
    {
    public:
        constexpr eax_t() noexcept
            : r32{ r32::names::eax }
        { }
    };

    class esp_t
        : public r32
    {
    public:
        constexpr esp_t() noexcept
            : r32{ r32::names::esp }
        { }
    };

    class ebp_t
        : public r32
    {
    public:
        constexpr ebp_t() noexcept
            : r32{ r32::names::ebp }
        { }
    };

    class eip_t
        : public r32
    {
    public:
        constexpr eip_t() noexcept
            : r32{ r32::names::eip }
        { }
    };

    class eiz_t
        : public r32
    {
    public:
        constexpr eiz_t() noexcept
            : r32{ r32::names::eiz }
        { }
    };

#ifdef CASM_X64
    class rd
        : public base_r32
    {
    public:
        enum class names
            : r_n_t
        {
            r8d, r9d, r10d, r11d, r12d, r13d, r14d, r15d
        };

        constexpr rd(names name) noexcept
            : base_r32{ name }
        { }
    };

    class r13d_t
        : public rd
    {
    public:
        constexpr r13d_t() noexcept
            : rd{ rd::names::r13d }
        { }
    };

    using base_r64 = base_r<oper64_t>;

    template<class t>
    inline constexpr const auto is_r64_v{ std::is_base_of_v<base_r64, std::decay_t<t>> };
#endif

    template<class t>
    inline constexpr const auto is_r32_64_v
    {
        is_r32_v<t>
#ifdef CASM_X64
        or is_r64_v<t>
#endif
    };

    template<class t>
    inline constexpr const auto is_r16_32_64_v
    {
        is_r16_32_v<t>
#ifdef CASM_X64
        or is_r64_v<t>
#endif
    };

    template<class t>
    inline constexpr const auto is_r16_64_v
    {
        is_r16_v<t>
#ifdef CASM_X64
        or is_r64_v<t>
#endif
    };

    template<class t>
    inline constexpr const auto is_addressing_r_v
    {
        is_r32_v<t>
#ifdef CASM_X64
        or is_r64_v<t>
#endif
    };

#ifdef CASM_X64
    class r64
        : public base_r64
    {
    public:
        enum class names
            : r_n_t
        {
            rax, rcx, rdx, rbx, rsp, rbp, rsi, rdi, rip, riz
        };

        constexpr r64(names name) noexcept
            : base_r64{ name }
        { }
    };

    class rax_t
        : public r64
    {
    public:
        constexpr rax_t() noexcept
            : r64{ r64::names::rax }
        { }
    };

    class rsp_t
        : public r64
    {
    public:
        constexpr rsp_t() noexcept
            : r64{ r64::names::rsp }
        { }
    };

    class rbp_t
        : public r64
    {
    public:
        constexpr rbp_t() noexcept
            : r64{ r64::names::rbp }
        { }
    };

    class rip_t
        : public r64
    {
    public:
        constexpr rip_t() noexcept
            : r64{ r64::names::rip }
        { }
    };

    class riz_t
        : public r64
    {
    public:
        constexpr riz_t() noexcept
            : r64{ r64::names::riz }
        { }
    };
#endif

    template<class t, class... ts>
    inline constexpr const auto is_any_of_v{ std::disjunction_v<std::is_same<std::decay_t<t>, std::decay_t<ts>>...> };

    template<class t>
    inline constexpr const auto is_ax_eax_rax_v
    {
        is_any_of_v<
            t
            , ax_t
            , eax_t
#ifdef CASM_X64
            , rax_t
#endif
        >
    };

    template<class t>
    inline constexpr const auto is_addressing_sp_v
    {
        is_any_of_v<
            t
            , esp_t
#ifdef CASM_X64
            , rsp_t
#endif
        >
    };

#ifdef CASM_X64
    class rq
        : public base_r64
    {
    public:
        enum class names
            : r_n_t
        {
            r8, r9, r10, r11, r12, r13, r14, r15
        };

        constexpr rq(names name) noexcept
            : base_r64{ name }
        { }
    };

    class r13_t
        : public rq
    {
    public:
        constexpr r13_t() noexcept
            : rq{ rq::names::r13 }
        { }
    };
#endif

    template<class t>
    inline constexpr const auto is_addressing_bp_v
    {
        is_any_of_v<
            t
            , ebp_t
#ifdef CASM_X64
            , rbp_t
            , r13d_t
            , r13_t
#endif
        >
    };

    class st
        : public base_r<st_oper_t>
    {
    public:
        enum class names
            : r_n_t
        {
            st0, st1, st2, st3, st4, st5, st6, st7
        };

        constexpr st(names name) noexcept
            : base_r<st_oper_t>{ name }
        { }
    };

    template<class t>
    inline constexpr const auto is_st_v{ std::is_same_v<std::decay_t<t>, st> };

    class st0_t
        : public st
    {
    public:
        constexpr st0_t() noexcept
            : st{ st::names::st0 }
        { }
    };

    class mm
        : public base_r<mm_oper_t>
    {
    public:
        enum class names
            : r_n_t
        {
            mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7
        };

        constexpr mm(names name) noexcept
            : base_r<mm_oper_t>{ name }
        { }
    };

    using base_xmm = base_r<xmm_oper_t>;

    template<class t>
    inline constexpr const auto is_xmm_v{ std::is_base_of_v<base_xmm, std::decay_t<t>> };

    class xmm
        : public base_xmm
    {
    public:
        enum class names
            : r_n_t
        {
            xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7
        };

        constexpr xmm(names name) noexcept
            : base_xmm{ name }
        { }
    };

#ifdef CASM_X64
    class extended_xmm
        : public base_xmm
    {
    public:
        enum class names
            : r_n_t
        {
            xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15
        };

        constexpr extended_xmm(names name) noexcept
            : base_xmm{ name }
        { }
    };
#endif

    class cr
        : public base_r<cr_oper_t>
    {
    public:
        enum class names
            : r_n_t
        {
            cr0, cr1, cr2, cr3, cr4, cr5, cr6, cr7
        };

        constexpr cr(names name) noexcept
            : base_r<cr_oper_t>{ name }
        { }
    };

    class dr
        : public base_r<dr_oper_t>
    {
    public:
        enum class names
            : r_n_t
        {
            dr0, dr1, dr2, dr3, dr4, dr5, dr6, dr7
        };

        constexpr dr(names name) noexcept
            : base_r<dr_oper_t>{ name }
        { }
    };

    using imm8_t = std::int8_t;

    template<class t>
    inline constexpr const auto is_imm8_v{ std::is_same_v<std::decay_t<t>, imm8_t> };

    using imm16_t = std::int16_t;

    using imm32_t = std::int32_t;

    template<class t>
    inline constexpr const auto is_imm32_v{ std::is_same_v<std::decay_t<t>, imm32_t> };

    template<class t>
    inline constexpr const auto is_imm16_32_v{ std::is_same_v<std::decay_t<t>, imm16_t> or is_imm32_v<t> };

    using imm64_t = std::int64_t;

    template<class t>
    inline constexpr const auto is_imm_v{ is_any_of_v<t, imm8_t, imm16_t, imm32_t, imm64_t> };

#ifdef CASM_X32
    using no_r_t = eiz_t;
#else
    using no_r_t = riz_t;
#endif

    using no_base_t = no_r_t;

    using no_index_t = no_r_t;

    template<class t>
    inline constexpr const auto no_index_v{ std::is_same_v<std::decay_t<t>, no_index_t> };

    struct no_scale_t
    { };

    template<class t>
    inline constexpr const auto no_scale_v{ std::is_same_v<std::decay_t<t>, no_scale_t> };

    enum class scales
        : std::uint8_t
    {
        _2 = 2,
        _4 = 4,
        _8 = 8
    };

    struct no_displacement_t
    { };

    struct no_segment_prefix_t
    { };

    template<class base_t, class index_t, class scale_t, class displacement_t, class segment_prefix_t>
    class address
    {
        static_assert(is_addressing_r_v<base_t> and is_addressing_r_v<index_t>);

        static_assert(is_same_oper_size_v<base_t, std::conditional_t<no_index_v<index_t>, base_t, index_t>>);

    public:
        constexpr address(base_t base, segment_prefix_t segment_prefix = segment_prefix_t{}) noexcept
            : base_{ base }
            , segment_prefix_{ segment_prefix }
        { }

        constexpr address(displacement_t displacement, segment_prefix_t segment_prefix = segment_prefix_t{}) noexcept
            : displacement_{ displacement }
            , segment_prefix_{ segment_prefix }
        { }

        constexpr address(base_t base, index_t index) noexcept
            : base_{ base }
            , index_{ index }
        { }

        constexpr address(base_t base, scale_t scale) noexcept
            : base_{ base }
            , scale_{ scale }
        { }

        constexpr address(base_t base, displacement_t displacement) noexcept
            : base_{ base }
            , displacement_{ displacement }
        { }

        constexpr address(base_t base, index_t index, scale_t scale) noexcept
            : base_{ base }
            , index_{ index }
            , scale_{ scale }
        { }

        constexpr address(base_t base, index_t index, displacement_t displacement) noexcept
            : base_{ base }
            , index_{ index }
            , displacement_{ displacement }
        { }

        constexpr address(base_t base, index_t index, scale_t scale, displacement_t displacement, segment_prefix_t segment_prefix) noexcept
            : base_{ base }
            , index_{ index }
            , scale_{ scale }
            , displacement_{ displacement }
            , segment_prefix_{ segment_prefix }
        { }

        constexpr auto base() const noexcept
        {
            return this->base_;
        }

        constexpr auto index() const noexcept
        {
            return this->index_;
        }

        constexpr auto scale() const noexcept
        {
            return this->scale_;
        }

        constexpr auto displacement() const noexcept
        {
            return this->displacement_;
        }

        constexpr auto segment_prefix() const noexcept
        {
            return this->segment_prefix_;
        }

    private:
        base_t base_;
        index_t index_;
        scale_t scale_;
        segment_prefix_t segment_prefix_;
        displacement_t displacement_;
    };

    template<class>
    struct is_address
        : std::false_type
    { };

    template<class... ts>
    struct is_address<address<ts...>>
        : std::true_type
    { };

    template<class t>
    inline constexpr const auto is_address_v{ is_address<std::decay_t<t>>::value };

    template<class base_t, class index_t, std::enable_if_t<is_addressing_r_v<base_t> and is_addressing_r_v<index_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) operator+(base_t base, index_t index) noexcept
    {
        return address<base_t, index_t, no_scale_t, no_displacement_t, no_segment_prefix_t>{ base, index };
    }

    template<class base_t, std::enable_if_t<is_addressing_r_v<base_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) operator*(base_t base, std::uint32_t scale) noexcept
    {
        return address<base_t, no_index_t, scales, no_displacement_t, no_segment_prefix_t>{ base, static_cast<scales>(scale) };
    }

    template<class base_t, class displacement_t, std::enable_if_t<is_addressing_r_v<base_t> and is_imm_v<displacement_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) operator+(base_t base, displacement_t displacement) noexcept
    {
        return address<base_t, no_index_t, no_scale_t, displacement_t, no_segment_prefix_t>{ base, displacement };
    }

    template<class base_t, template<class...> class address_t, class... address_ts, std::enable_if_t<is_address_v<address_t<address_ts...>> and is_addressing_r_v<base_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) operator+(base_t base, address_t<address_ts...>&& addr) noexcept
    {
        return address{ base, addr.base(), addr.scale(), addr.displacement(), addr.segment_prefix() };
    }

    template<class base_t, class index_t, class scale_t, class segment_prefix_t, class displacement_t, std::enable_if_t<is_imm_v<displacement_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) operator+(address<base_t, index_t, scale_t, no_displacement_t, segment_prefix_t>&& addr, displacement_t displacement) noexcept
    {
        return address<base_t, index_t, scale_t, displacement_t, segment_prefix_t>{ addr.base(), addr.index(), addr.scale(), displacement, addr.segment_prefix() };
    }

    using byte_t = std::uint8_t;

    class sreg
        : public base_r<sreg_oper_t>
    {
    public:
        enum class names
            : r_n_t
        {
            es, cs, ss, ds, fs, gs
        };

        constexpr sreg(names name, byte_t prefix) noexcept
            : base_r{ name }
            , prefix_{ prefix }
        { }

        template<class base_t, std::enable_if_t<is_addressing_r_v<base_t>, std::nullptr_t> = nullptr>
        constexpr decltype(auto) operator()(base_t base) const noexcept
        {
            return address<base_t, no_index_t, no_scale_t, no_displacement_t, byte_t>{ base, this->prefix_ };
        }

        template<class displacement_t, std::enable_if_t<is_imm_v<displacement_t>, std::nullptr_t> = nullptr>
        constexpr decltype(auto) operator()(displacement_t displacement) const noexcept
        {
            return address<no_base_t, no_index_t, no_scale_t, displacement_t, byte_t>{ displacement, this->prefix_ };
        }

        template<template<class...> class address_t, class... address_ts, std::enable_if_t<is_address_v<address_t<address_ts...>>, std::nullptr_t> = nullptr>
        constexpr decltype(auto) operator()(address_t<address_ts...>&& addr) const noexcept
        {
            return address{ addr.base(), addr.index(), addr.scale(), addr.displacement(), this->prefix_ };
        }

    private:
        byte_t prefix_;
    };

    class es_t
        : public sreg
    {
    public:
        constexpr es_t() noexcept
            : sreg{ sreg::names::es, 0x26 }
        { }
    };

    class cs_t
        : public sreg
    {
    public:
        constexpr cs_t() noexcept
            : sreg{ sreg::names::cs, 0x2e }
        { }
    };

    class ss_t
        : public sreg
    {
    public:
        constexpr ss_t() noexcept
            : sreg{ sreg::names::ss, 0x36 }
        { }
    };

    class ds_t
        : public sreg
    {
    public:
        constexpr ds_t() noexcept
            : sreg{ sreg::names::ds, 0x3e }
        { }
    };

    class fs_t
        : public sreg
    {
    public:
        constexpr fs_t() noexcept
            : sreg{ sreg::names::fs, 0x64 }
        { }
    };

    class gs_t
        : public sreg
    {
    public:
        constexpr gs_t() noexcept
            : sreg{ sreg::names::gs, 0x65 }
        { }
    };

    template<class base_oper_t, class... address_ts>
    class base_m
        : public base_oper_t
    {
    public:
        constexpr base_m(address<address_ts...> addr) noexcept
            : addr_{ std::move(addr) }
        { }

        constexpr auto const& addr() const& noexcept
        {
            return this->addr_;
        }

    private:
        address<address_ts...> addr_;
    };

    template<class>
    struct is_m
        : std::false_type
    { };

    template<class base_oper_t, class... address_ts>
    struct is_m<base_m<base_oper_t, address_ts...>>
        : std::true_type
    { };

    template<class t>
    inline constexpr const auto is_m_v{ is_m<std::decay_t<t>>::value };

    template<class base_oper_t, class t>
    class is_mz_impl
    {
        template<class... address_ts>
        static constexpr std::true_type impl(base_m<base_oper_t, address_ts...>&&) noexcept;

        static constexpr std::false_type impl(...) noexcept;

    public:
        static constexpr const auto value{ decltype(impl(std::declval<std::decay_t<t>>()))::value };
    };

    template<class base_oper_t, class t>
    inline constexpr const auto is_mz_impl_v{ is_mz_impl<base_oper_t, t>::value };

    template<class t>
    inline constexpr const auto is_m8_v{ is_mz_impl_v<oper8_t, t> };

    template<class t>
    inline constexpr const auto is_m16_v{ is_mz_impl_v<oper16_t, t> };

    template<class t>
    inline constexpr const auto is_m32_v{ is_mz_impl_v<oper32_t, t> };

    template<class t>
    inline constexpr const auto is_m16_32_v{ is_m16_v<t> or is_m32_v<t> };

    template<class t>
    inline constexpr const auto is_m48_v{ is_mz_impl_v<oper48_t, t> };

    template<class t>
    inline constexpr const auto is_m16_48_v{ is_m16_v<t> or is_m48_v<t> };

    template<class t>
    inline constexpr const auto is_m64_v{ is_mz_impl_v<oper64_t, t> };

    template<class t>
    inline constexpr const auto is_m16_32_64_v{ is_m16_32_v<t> or is_m64_v<t> };

    template<class t>
    inline constexpr const auto is_m16_64_v{ is_m16_v<t> or is_m64_v<t> };

    template<class t>
    inline constexpr const auto is_m32_64_v{ is_m32_v<t> or is_m64_v<t> };

    template<class t>
    inline constexpr const auto is_m80_v{ is_mz_impl_v<oper80_t, t> };

    template<class t>
    inline constexpr const auto is_m128_v{ is_mz_impl_v<oper128_t, t> };

    template<class t>
    inline constexpr const auto is_rm8_v{ is_r8_v<t> or is_m8_v<t> };

    template<class t>
    inline constexpr const auto is_rm16_v{ is_r16_v<t> or is_m16_v<t> };

    template<class t>
    inline constexpr const auto is_rm32_v{ is_r32_v<t> or is_m32_v<t> };

    template<class t>
    inline constexpr const auto is_rm16_32_v{ is_r16_32_v<t> or is_m16_32_v<t> };

    template<class t>
    inline constexpr const auto is_rm64_v
    {
#ifdef CASM_X64
        is_r64_v<t> or
#endif
        is_m64_v<t>
    };

    template<class t>
    inline constexpr const auto is_rm32_64_v{ is_r32_64_v<t> or is_m32_64_v<t> };

    template<class t>
    inline constexpr const auto is_rm16_32_64_v{ is_r16_32_64_v<t> or is_m16_32_64_v<t> };

    template<class t>
    inline constexpr const auto is_stm32_v{ is_st_v<t> or is_m32_v<t> };

    template<class t>
    inline constexpr const auto is_mmm64_v{ std::is_same_v<std::decay_t<t>, mm> or is_m64_v<t> };

    template<class t>
    inline constexpr const auto is_xmmm32_v{ is_xmm_v<t> or is_m32_v<t> };

    template<class t>
    inline constexpr const auto is_xmmm64_v{ is_xmm_v<t> or is_m64_v<t> };

    template<class t>
    inline constexpr const auto is_xmmm128_v{ is_xmm_v<t> or is_m128_v<t> };

    template<class base_oper_t>
    class base_ptr
    {
    public:
        template<class base_t, std::enable_if_t<is_addressing_r_v<base_t>, std::nullptr_t> = nullptr>
        constexpr decltype(auto) operator[](base_t r) const noexcept
        {
            return base_m<base_oper_t, base_t, no_index_t, no_scale_t, no_displacement_t, no_segment_prefix_t>{ r };
        }

        constexpr decltype(auto) operator[](imm32_t displacement) const noexcept
        {
            return base_m<base_oper_t, no_base_t, no_index_t, no_scale_t, imm32_t, no_segment_prefix_t>{ displacement };
        }

#ifdef CASM_X32
        template<class t>
        constexpr decltype(auto) operator[](t const* const value) const noexcept
        {
            return base_m<base_oper_t, no_base_t, no_index_t, no_scale_t, imm32_t, no_segment_prefix_t>{ reinterpret_cast<details::imm32_t>(value) };
        }
#endif

        template<template<class...> class address_t, class... address_ts, std::enable_if_t<is_address_v<address_t<address_ts...>>, std::nullptr_t> = nullptr>
        constexpr decltype(auto) operator[](address_t<address_ts...>&& addr) const noexcept
        {
            return base_m<base_oper_t, address_ts...>{ std::forward<address_t<address_ts...>>(addr) };
        }
    };

    template<std::size_t size>
    using static_bytecode = std::array<byte_t, size>;

    template<class>
    struct is_static_bytecode
        : std::false_type
    { };

    template<std::size_t size>
    struct is_static_bytecode<static_bytecode<size>>
        : std::true_type
    { };

    template<class... bytes_t>
    constexpr decltype(auto) make_static_bytecode(bytes_t... bytes) noexcept
    {
        return static_bytecode<sizeof...(bytes_t)>{ static_cast<byte_t>(bytes)... };
    }

    template<std::size_t... indexes>
    constexpr decltype(auto) static_bytecode_cat(byte_t byte, static_bytecode<sizeof...(indexes)> const& bytecode, std::index_sequence<indexes...>) noexcept
    {
        return make_static_bytecode(byte, bytecode[indexes]...);
    }

    template<std::size_t size>
    constexpr decltype(auto) operator+(byte_t byte, static_bytecode<size> const& bytecode) noexcept
    {
        return static_bytecode_cat(byte, bytecode, std::make_index_sequence<size>{});
    }

    template<std::size_t... indexes>
    constexpr decltype(auto) static_bytecode_cat(static_bytecode<sizeof...(indexes)> const& bytecode, byte_t byte, std::index_sequence<indexes...>) noexcept
    {
        return make_static_bytecode(bytecode[indexes]..., byte);
    }

    template<std::size_t size>
    constexpr decltype(auto) operator+(static_bytecode<size> const& bytecode, byte_t byte) noexcept
    {
        return static_bytecode_cat(bytecode, byte, std::make_index_sequence<size>{});
    }

    template<std::size_t... indexes0, std::size_t... indexes1>
    constexpr decltype(auto) static_bytecode_cat(static_bytecode<sizeof...(indexes0)> const& bytecode0, static_bytecode<sizeof...(indexes1)> const& bytecode1, std::index_sequence<indexes0...>, std::index_sequence<indexes1...>) noexcept
    {
        return make_static_bytecode(bytecode0[indexes0]..., bytecode1[indexes1]...);
    }

    template<std::size_t size0, std::size_t size1>
    constexpr decltype(auto) operator+(static_bytecode<size0> const& bytecode0, static_bytecode<size1> const& bytecode1) noexcept
    {
        return static_bytecode_cat(bytecode0, bytecode1, std::make_index_sequence<size0>{}, std::make_index_sequence<size1>{});
    }

    template<class t, std::size_t... indexes>
    constexpr decltype(auto) to_static_bytecode_impl(t&& v, std::index_sequence<indexes...>) noexcept
    {
        return make_static_bytecode(reinterpret_cast<byte_t const* const>(&v)[indexes]...);
    }

    template<class t>
    constexpr decltype(auto) to_static_bytecode(t&& v) noexcept
    {
        return to_static_bytecode_impl(std::forward<t>(v), std::make_index_sequence<sizeof(t)>{});
    }

    using null_static_bytecode_t = static_bytecode<0>;

    inline constexpr const null_static_bytecode_t null_static_bytecode{};

    using dynamic_bytecode_t = std::vector<byte_t>;

    template<class t>
    inline constexpr const auto is_bytecode_v{ is_static_bytecode<std::decay_t<t>>::value or std::is_same_v<std::decay_t<t>, dynamic_bytecode_t> };

    template<class bytecode_t>
    class instruct
    {
        static_assert(is_bytecode_v<bytecode_t>);

    public:
        constexpr explicit instruct(bytecode_t&& bytecode) noexcept
            : bytecode_{ std::forward<bytecode_t>(bytecode) }
        { }

        constexpr auto const& bytecode() const& noexcept
        {
            return this->bytecode_;
        }

    private:
        bytecode_t bytecode_;
    };

    template<class>
    struct is_instruct
        : std::false_type
    { };

    template<class bytecode_t>
    struct is_instruct<instruct<bytecode_t>>
        : std::true_type
    { };

    template<class t>
    inline constexpr const auto is_instruct_v{ is_instruct<std::decay_t<t>>::value };

    class rel_instruct
    {
    public:
        rel_instruct(base_label target_label, dynamic_bytecode_t(*rel8_instruct)(imm8_t), dynamic_bytecode_t(*rel32_instruct)(imm32_t)) noexcept
            : target_label_{ target_label }
            , rel_{ 0 }
            , rel8_instruct_{ rel8_instruct }
            , rel32_instruct_{ rel32_instruct }
        {
            size_ = this->operator()(imm32_t{ (std::numeric_limits<imm32_t>::max)() }).size();
        }

        rel_instruct(base_label target_label, dynamic_bytecode_t(*rel32_instruct)(imm32_t)) noexcept
            : target_label_{ target_label }
            , rel_{ 0 }
            , rel8_instruct_{ std::nullopt }
            , rel32_instruct_{ rel32_instruct }
        {
            size_ = this->operator()(imm32_t{ (std::numeric_limits<imm32_t>::max)() }).size();
        }

        rel_instruct(base_label target_label, dynamic_bytecode_t(*rel8_instruct)(imm8_t)) noexcept
            : target_label_{ target_label }
            , rel_{ 0 }
            , rel8_instruct_{ rel8_instruct }
            , rel32_instruct_{ std::nullopt }
        {
            size_ = this->operator()(imm8_t{ (std::numeric_limits<imm8_t>::max)() }).size();
        }

        auto size() const noexcept
        {
            return this->size_;
        }

        void resize(std::size_t size) noexcept
        {
            this->size_ = size;
        }

        auto target_label() const noexcept
        {
            return this->target_label_;
        }

        auto rel() const noexcept
        {
            return this->rel_;
        }

        auto& rel() noexcept
        {
            return this->rel_;
        }

        dynamic_bytecode_t operator()(imm8_t imm) const noexcept
        {
            if (this->rel8_instruct_.has_value())
            {
                return this->rel8_instruct_.value()(imm);
            }
            else
            {
                return this->operator()(details::imm32_t{ static_cast<details::imm32_t>(imm) });
            }

        }

        dynamic_bytecode_t operator()(imm32_t imm) const noexcept
        {
            if (this->rel32_instruct_.has_value())
            {
                return this->rel32_instruct_.value()(imm);
            }
            else
            {
                return this->operator()(details::imm8_t{ static_cast<details::imm8_t>(imm) });
            }
        }

    private:
        std::size_t size_;

        base_label target_label_;

        imm32_t rel_;

        std::optional<dynamic_bytecode_t(*)(imm8_t)> rel8_instruct_;
        std::optional<dynamic_bytecode_t(*)(imm32_t)> rel32_instruct_;
    };

    template<class t>
    inline constexpr const auto is_rel_instruct_v{ std::is_same_v<std::decay_t<t>, rel_instruct> };

    template<class t, std::enable_if_t<is_imm16_32_v<t>, std::nullptr_t> = nullptr>
    decltype(auto) make_rel_instruct_bytecode(dynamic_bytecode_t&& opcode, t imm) noexcept
    {
        dynamic_bytecode_t bytecode;

        std::copy(opcode.cbegin(), opcode.cend(), std::back_inserter(bytecode));

        auto imm_static_bytecode = to_static_bytecode(imm);
        std::copy(imm_static_bytecode.cbegin(), imm_static_bytecode.cend(), std::back_inserter(bytecode));

        return bytecode;
    }

    template<class base_oper_t, class base_t, class index_t, class scale_t, class displacement_t, class segment_prefix_t>
    constexpr decltype(auto) make_segment_prefix(base_m<base_oper_t, base_t, index_t, scale_t, displacement_t, segment_prefix_t> const& m) noexcept
    {
        if constexpr (!std::is_same_v<segment_prefix_t, no_segment_prefix_t>)
        {
            return make_static_bytecode(m.addr().segment_prefix());
        }
        else
        {
            return null_static_bytecode;
        }
    }

    constexpr decltype(auto) make_segment_prefix(...) noexcept
    {
        return null_static_bytecode;
    }

    template<class t>
    constexpr decltype(auto) make_oper_size_prefix(t) noexcept
    {
        if constexpr (is_oper16_v<t> or is_xmm_v<t> or is_oper128_v<t>)
        {
            return make_static_bytecode(0x66);
        }
        else
        {
            return null_static_bytecode;
        }
    }


#ifdef CASM_X64
    template<class base_oper_t, class base_t, class... address_ts>
    constexpr decltype(auto) make_address_size_prefix(base_m<base_oper_t, base_t, address_ts...> const&) noexcept
    {
        if constexpr (is_r32_v<base_t>)
        {
            return make_static_bytecode(0x67);
        }
        else
        {
            return null_static_bytecode;
        }
    }
#endif

    constexpr decltype(auto) make_address_size_prefix(...) noexcept
    {
        return null_static_bytecode;
    }

    template<class t>
    inline constexpr const auto is_extended_v
    {
#ifdef CASM_X64
        std::is_base_of_v<rb, std::decay_t<t>>
        or std::is_base_of_v<rw, std::decay_t<t>>
        or std::is_base_of_v<rd, std::decay_t<t>>
        or std::is_base_of_v<rq, std::decay_t<t>>
        or std::is_base_of_v<extended_xmm, std::decay_t<t>>
#else
        false
#endif
    };

    template<class t>
    inline constexpr const auto is_rex_oper_v
    {
#ifdef CASM_X64
        is_oper64_v<t>
        or is_oper128_v<t>
        or is_extended_v<t>
        or std::is_base_of_v<rl, std::decay_t<t>>
#else
        false
#endif
    };

#ifdef CASM_X64
    class rex
    {
    public:
        constexpr rex(bool w, bool r, bool x, bool b) noexcept
        {
            this->byte_ or_eq w << e2n(addrof_bits::w);
            this->byte_ or_eq r << e2n(addrof_bits::r);
            this->byte_ or_eq x << e2n(addrof_bits::x);
            this->byte_ or_eq b << e2n(addrof_bits::b);
        }

        constexpr operator byte_t() const noexcept
        {
            return this->byte_;
        }

    private:
        enum class addrof_bits
            : std::uint8_t
        {
            b,
            x,
            r,
            w
        };

        byte_t byte_{ 0x40 };
    };

    template<class base_oper_t, class base_t, class index_t, class scale_t, class... address_ts, class oper1_t, std::enable_if_t<is_oper64_v<base_oper_t> or is_extended_v<base_t> or is_extended_v<index_t> or is_rex_oper_v<oper1_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_rex(base_m<base_oper_t, base_t, index_t, scale_t, address_ts...> const&, oper1_t) noexcept
    {
        return rex
        {
            is_oper64_v<oper1_t> or is_oper64_v<base_oper_t>,
            is_extended_v<oper1_t>,
            is_extended_v<index_t> or (no_index_v<index_t> and !no_scale_v<scale_t> and is_extended_v<base_t>),
            (is_extended_v<base_t> and !no_index_v<index_t>) or (no_index_v<index_t> and no_scale_v<scale_t> and is_extended_v<base_t>)
        };
    }

    template<class base_oper_t, class base_t, class index_t, class scale_t, class... address_ts, std::enable_if_t<is_extended_v<base_t> or is_extended_v<index_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_rex(base_m<base_oper_t, base_t, index_t, scale_t, address_ts...> const&) noexcept
    {
        return rex
        {
            is_oper64_v<base_oper_t> or is_oper128_v<base_oper_t>,
            false,
            is_extended_v<index_t> or (no_index_v<index_t> and !no_scale_v<scale_t> and is_extended_v<base_t>),
            (is_extended_v<base_t> and !no_index_v<index_t>) or (no_index_v<index_t> and no_scale_v<scale_t> and is_extended_v<base_t>)
        };
    }

    template<class r0_t, class oper1_t, std::enable_if_t<(is_rex_oper_v<r0_t> or is_rex_oper_v<oper1_t>), std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_rex(r0_t, oper1_t) noexcept
    {
        static_assert((!is_r8h_v<r0_t>) and (!is_r8h_v<oper1_t>));

        return rex{ is_oper64_v<r0_t> or is_oper64_v<oper1_t>, is_extended_v<oper1_t>, false, is_extended_v<r0_t> };
    };

    template<class r_t, std::enable_if_t<is_rex_oper_v<r_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_rex(r_t) noexcept
    {
        static_assert(!is_r8h_v<r_t>);

        return rex{ is_oper64_v<r_t> or is_oper128_v<r_t>, false, false, is_extended_v<r_t> };
    };
#endif

    constexpr decltype(auto) make_rex(...) noexcept
    {
        return null_static_bytecode;
    }

#ifdef CASM_X64
    template<class base_oper_t, class base_t, class index_t, class scale_t, class... address_ts, class oper1_t, std::enable_if_t<is_extended_v<base_t> or is_extended_v<index_t> or is_rex_oper_v<oper1_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_rex_w(base_m<base_oper_t, base_t, index_t, scale_t, address_ts...> const&, oper1_t) noexcept
    {
        return rex
        {
            is_oper64_v<oper1_t>,
            is_extended_v<oper1_t>,
            is_extended_v<index_t> or (no_index_v<index_t> and !no_scale_v<scale_t> and is_extended_v<base_t>),
            (is_extended_v<base_t> and !no_index_v<index_t>) or (no_index_v<index_t> and no_scale_v<scale_t> and is_extended_v<base_t>)
        };
    }

    template<class base_oper_t, class base_t, class index_t, class scale_t, class... address_ts, std::enable_if_t<is_extended_v<base_t> or is_extended_v<index_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_rex_w(base_m<base_oper_t, base_t, index_t, scale_t, address_ts...> const&) noexcept
    {
        return rex
        {
            false,
            false,
            is_extended_v<index_t> or (no_index_v<index_t> and !no_scale_v<scale_t> and is_extended_v<base_t>),
            (is_extended_v<base_t> and !no_index_v<index_t>) or (no_index_v<index_t> and no_scale_v<scale_t> and is_extended_v<base_t>)
        };
    }

    template<class oper0_t, class oper1_t, std::enable_if_t<(is_rex_oper_v<oper0_t> or is_rex_oper_v<oper1_t>) and !is_m_v<oper0_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_rex_w(oper0_t, oper1_t) noexcept
    {
        return rex{ is_oper64_v<oper1_t>, is_extended_v<oper1_t>, false, is_extended_v<oper0_t> };
    }

    template<class oper_t, std::enable_if_t<(is_extended_v<oper_t>) and !is_m_v<oper_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_rex_w(oper_t) noexcept
    {
        return rex{ false, false, false, is_extended_v<oper_t> };
    }
#endif

    constexpr decltype(auto) make_rex_w(...) noexcept
    {
        return null_static_bytecode;
    }

    using bit_field_t = std::uint8_t;

    class modrm
    {
    public:
        constexpr modrm(bit_field_t mod, bit_field_t rm, bit_field_t reg) noexcept
            : mod_{ mod }, rm_{ rm }, reg_{ reg }
        { }

        constexpr operator byte_t() const noexcept
        {
            return static_cast<byte_t>((this->mod_ << e2n(addrof_bits::mod)) bitor (this->rm_ << e2n(addrof_bits::rm)) bitor (this->reg_ << e2n(addrof_bits::reg)));
        }

    private:
        enum class sizeof_bits
            : std::uint8_t
        {
            mod = 2,
            reg,
            rm = 3,
        };

        enum class addrof_bits
            : std::uint8_t
        {
            rm,
            reg = rm + e2n(sizeof_bits::rm),
            mod = reg + e2n(sizeof_bits::reg)
        };

        bit_field_t mod_ : e2n(sizeof_bits::mod);
        bit_field_t reg_ : e2n(sizeof_bits::reg);
        bit_field_t rm_ : e2n(sizeof_bits::rm);
    };

    class reg_bits
    {
    public:
        constexpr reg_bits(bit_field_t value) noexcept
            : value_{ value }
        { }

        constexpr auto value() const noexcept
        {
            return this->value_;
        }

    private:
        bit_field_t value_;
    };

    template<class oper0_t, class t, std::enable_if_t<is_r_v<oper0_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(oper0_t r0, t r) noexcept
    {
        if constexpr (is_r_v<t>)
        {
            return modrm{ 0b11, r0.n(), r.n() };
        }
        else if constexpr (std::is_same_v<t, reg_bits>)
        {
            return modrm{ 0b11, r0.n(), r.value() };
        }
    }

    template<class t>
    constexpr bit_field_t get_mod(t imm) noexcept
    {
        if constexpr (is_imm_v<t>)
        {
            if constexpr (is_imm8_v<t>)
            {
                return 0b01;
            }
            else
            {
                return 0b10;
            }
        }
        else
        {
            return 0b00;
        }
    }

    template<class oper_t>
    constexpr bit_field_t get_reg(oper_t r) noexcept
    {
        if constexpr (is_r_v<oper_t>)
        {
            return r.n();
        }
        else if constexpr (std::is_same_v<std::decay_t<oper_t>, reg_bits>)
        {
            return r.value();
        }
        else
        {
            return 0b000;
        }
    }

    template<class scale_t>
    constexpr bit_field_t get_ss(scale_t scale) noexcept
    {
        if constexpr (std::is_same_v<scale_t, scales>)
        {
            return scale == scales::_2 ? 0b01 : scale == scales::_4 ? 0b10 : 0b11;
        }
        else if constexpr (no_scale_v<scale_t>)
        {
            return 0b00;
        }
    }

    template<class oper_t>
    constexpr bit_field_t get_index(oper_t r) noexcept
    {
        if constexpr (is_r_v<oper_t>)
        {
            return r.n();
        }
        else if constexpr (std::is_same_v<oper_t, no_r_t>)
        {
            return 0b100;
        }
    }

    template<class oper_t>
    constexpr decltype(auto) get_displacement_bytecode(oper_t oper) noexcept
    {
        if constexpr (is_imm_v<oper_t>)
        {
            return to_static_bytecode(oper);
        }
        else
        {
            return null_static_bytecode;
        }
    }

    // base + displacement
    template<class base_oper_t, class base_t, class displacement_t, class segment_prefix_t, class oper1_t, std::enable_if_t<!is_addressing_sp_v<base_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, no_index_t, no_scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        return details::make_static_bytecode(modrm{ get_mod(m.addr().displacement()), m.addr().base().n(), get_reg(oper1) }) + get_displacement_bytecode(m.addr().displacement());
    }

    class sib
    {
    public:
        constexpr sib(bit_field_t ss, bit_field_t index, bit_field_t base) noexcept
            : ss_{ ss }, index_{ index }, base_{ base }
        { }

        constexpr operator byte_t() const noexcept
        {
            return static_cast<byte_t>((this->ss_ << e2n(addrof_bits::ss)) bitor (this->index_ << e2n(addrof_bits::index)) bitor (this->base_ << e2n(addrof_bits::base)));
        }

    private:
        enum class sizeof_bits
            : std::uint8_t
        {
            ss = 2,
            index,
            base = 3,
        };

        enum class addrof_bits
            : std::uint8_t
        {
            base,
            index = base + e2n(sizeof_bits::base),
            ss = index + e2n(sizeof_bits::index)
        };

        bit_field_t ss_ : e2n(sizeof_bits::ss);
        bit_field_t index_ : e2n(sizeof_bits::index);
        bit_field_t base_ : e2n(sizeof_bits::base);
    };

    // base + index + displacement
    template<class base_oper_t, class base_t, class index_t, class displacement_t, class segment_prefix_t, class oper1_t, std::enable_if_t<!is_addressing_sp_v<base_t> and !is_addressing_sp_v<index_t> and !is_addressing_bp_v<base_t> and !is_addressing_bp_v<index_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, index_t, no_scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        return details::make_static_bytecode(modrm{ get_mod(m.addr().displacement()), 0b100, get_reg(oper1) }, sib{ 0b00, get_index(m.addr().index()), m.addr().base().n() }) + get_displacement_bytecode(m.addr().displacement());
    }

#ifdef CASM_X64
    // (eip or rip) + displacement
    template<class base_oper_t, class base_t, class segment_prefix_t, class oper1_t, std::enable_if_t<std::is_same_v<base_t, eip_t> or std::is_same_v<base_t, rip_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, no_index_t, no_scale_t, imm32_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        return details::make_static_bytecode(modrm{ 0b00, 0b101, get_reg(oper1) }) + get_displacement_bytecode(m.addr().displacement());
    }
#endif

    // displacement
    template<class base_oper_t, class displacement_t, class segment_prefix_t, class oper1_t>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, no_base_t, no_index_t, no_scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
#ifdef CASM_X64
        return details::make_static_bytecode(modrm{ 0b00, 0b100, get_reg(oper1) }, sib{ 0b00, 0b100, 0b101 }) + get_displacement_bytecode(m.addr().displacement());
#elif defined(CASM_X32)
        return modrm{ 0b00, 0b101, oper1.n() } + to_bytecode(m.addr().displacement());
#endif
    }

    // displacement
    template<class base_oper_t, class displacement_t, class segment_prefix_t>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, no_base_t, no_index_t, no_scale_t, displacement_t, segment_prefix_t> const& m, reg_bits bits) noexcept
    {
#ifdef CASM_X64
        return details::make_static_bytecode(modrm{ 0b00, 0b100, bits.value() }, sib{ 0b00, 0b100, 0b101 }) + get_displacement_bytecode(m.addr().displacement());
#elif defined(CASM_X32)
        return modrm{ 0b00, 0b101, 0b101 } + to_static_bytecode(m.addr().displacement());
#endif
    }

    // ebp or rbp
    template<class base_oper_t, class base_t, class segment_prefix_t, class oper1_t, std::enable_if_t<is_addressing_bp_v<base_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, no_index_t, no_scale_t, no_displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        return details::make_static_bytecode(modrm{ 0b01, m.addr().base().n(), get_reg(oper1) }, 0x00);
    }

    template<class...>
    constexpr bool always_false_t = false;

    template<class base_oper_t, class rs_t, class segment_prefix_t, class oper1_t, std::enable_if_t<is_addressing_sp_v<rs_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, rs_t, rs_t, no_scale_t, no_displacement_t, segment_prefix_t> const& m, oper1_t) noexcept
    {
        static_assert(always_false_t<rs_t>, "2 sp registers");
    }

    template<class displacement_t, std::enable_if_t<is_imm_v<displacement_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) get_displacement_bytecode32(displacement_t displacement) noexcept
    {
        return to_static_bytecode(imm32_t{ displacement.value() });
    }

    constexpr decltype(auto) get_displacement_bytecode32(no_displacement_t) noexcept
    {
        return to_static_bytecode(imm32_t{ 0x00 });
    }

    // base * scale + (no displacement or displacement8)
    template<class base_oper_t, class base_t, class scale_t, class displacement_t, class segment_prefix_t, class oper1_t, std::enable_if_t<!is_addressing_bp_v<base_t> and (std::is_same_v<std::decay_t<displacement_t>, no_displacement_t> or std::is_same_v<displacement_t, imm8_t>), std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, no_index_t, scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        static_assert(!is_addressing_sp_v<base_t>);

        return details::make_static_bytecode(modrm{ 0b00, 0b100, get_reg(oper1) }, sib{ get_ss(m.addr().scale()), get_index(m.addr().base()), 0b101 }) + get_displacement_bytecode32(m.addr().displacement());
    }

    // base * scale + displacement32
    template<class base_oper_t, class base_t, class scale_t, class displacement_t, class segment_prefix_t, class oper1_t, std::enable_if_t<is_imm32_v<displacement_t> and !is_addressing_bp_v<base_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, no_index_t, scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        static_assert(!is_addressing_sp_v<base_t>);

        return details::make_static_bytecode(modrm{ 0b00, 0b100, get_reg(oper1) }, sib{ get_ss(m.addr().scale()), get_index(m.addr().base()), 0b101 }) + get_displacement_bytecode(m.addr().displacement());
    }

    // base + index * scale + displacement
    template<class base_oper_t, class base_t, class index_t, class scale_t, class displacement_t, class segment_prefix_t, class oper1_t, std::enable_if_t<!is_addressing_sp_v<base_t> and !is_addressing_sp_v<index_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, index_t, scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        return details::make_static_bytecode(modrm{ get_mod(m.addr().displacement()), 0b100, get_reg(oper1) }, sib{ get_ss(m.addr().scale()), m.addr().index().n(), m.addr().base().n() }) + get_displacement_bytecode(m.addr().displacement());
    }

    // (esp or rsp) + displacement
    template<class base_oper_t, class base_t, class displacement_t, class segment_prefix_t, class oper1_t, std::enable_if_t<is_addressing_sp_v<base_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, no_index_t, no_scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        return details::make_static_bytecode(modrm{ get_mod(m.addr().displacement()), 0b100, get_reg(oper1) }, sib{ 0b00, 0b100, 0b100 }) + get_displacement_bytecode(m.addr().displacement());
    }

    // base + (esp or rsp) + displacemnt
    template<class base_oper_t, class base_t, class index_t, class scale_t, class displacement_t, class segment_prefix_t, class oper1_t, std::enable_if_t<is_addressing_sp_v<index_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, index_t, scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        static_assert(std::is_same_v<scale_t, no_scale_t>, "bad sp scale");

        return details::make_static_bytecode(modrm{ get_mod(m.addr().displacement()), 0b100, get_reg(oper1) }, sib{ 0b00, m.addr().base().n(), 0b100 }) + get_displacement_bytecode(m.addr().displacement());
    }

    // (esp or rsp) + index + displacemnt
    template<class base_oper_t, class base_t, class index_t, class scale_t, class displacement_t, class segment_prefix_t, class oper1_t, std::enable_if_t<is_addressing_sp_v<base_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, index_t, scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        static_assert((!is_addressing_sp_v<index_t>) and (!std::is_same_v<index_t, no_index_t>), "bad sp addressing");

        return details::make_static_bytecode(modrm{ get_mod(m.addr().displacement()), 0b100, get_reg(oper1) }, sib{ get_ss(m.addr().scale()), m.addr().index().n(), m.addr().base().n() }) + get_displacement_bytecode(m.addr().displacement());
    }

    // (ebp or rbp) + index * scale
    template<class base_oper_t, class base_t, class index_t, class scale_t, class segment_prefix_t, class oper1_t, std::enable_if_t<is_addressing_bp_v<base_t> and !no_index_v<index_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, index_t, scale_t, no_displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        return details::make_static_bytecode(modrm{ 0b01, 0b100, get_reg(oper1) }, sib{ get_ss(m.addr().scale()), m.addr().index().n(), m.addr().base().n() }, 0x00);
    }

    // (r13d or r13) * scale + displacement
    template<class base_oper_t, class base_t, class scale_t, class displacement_t, class segment_prefix_t, class oper1_t, std::enable_if_t<is_addressing_bp_v<base_t> and is_extended_v<base_t>, std::nullptr_t> = nullptr>
    constexpr decltype(auto) make_modrm_sib(base_m<base_oper_t, base_t, no_index_t, scale_t, displacement_t, segment_prefix_t> const& m, oper1_t oper1) noexcept
    {
        return details::make_static_bytecode(modrm{ 0b00, 0b100, get_reg(oper1) }, sib{ get_ss(m.addr().scale()), 0b101, 0b101 }) + get_displacement_bytecode32(m.addr().displacement());
    }

    template<class oper_t>
    constexpr decltype(auto) make_imm(oper_t oper) noexcept
    {
        if constexpr (is_imm_v<oper_t>)
        {
            return to_static_bytecode(oper);
        }
        else
        {
            return null_static_bytecode;
        }
    }

    template<class imm_t, class oper_t>
    constexpr decltype(auto) make_imm(imm_t imm, oper_t oper) noexcept
    {
        if constexpr (is_oper8_v<oper_t>)
        {
            return to_static_bytecode(static_cast<imm8_t>(imm));
        }
        else if constexpr (is_oper16_v<oper_t>)
        {
            return to_static_bytecode(static_cast<imm16_t>(imm));
        }
        else if constexpr (is_oper32_v<oper_t>)
        {
            return to_static_bytecode(imm32_t{ imm });
        }
        else if constexpr (is_oper64_v<oper_t>)
        {
            return to_static_bytecode(static_cast<imm32_t>(imm));
        }
        else
        {
            return null_static_bytecode;
        }
    }

    template<std::size_t n>
    struct visit_impl
    {
        template <typename tuple_t, typename f_t>
        static constexpr void visit(tuple_t&& tuple, std::size_t index, f_t&& f)
        {
            if (n - 1 == index)
                std::forward<f_t>(f)(std::get<n - 1>(std::forward<tuple_t>(tuple)));
            else
                visit_impl<n - 1>::visit(std::forward<tuple_t>(tuple), index, std::forward<f_t>(f));
        }
    };

    template<>
    struct visit_impl<0>
    {
        template <typename tuple_t, typename f_t>
        static constexpr void visit(tuple_t, std::size_t, f_t)
        {
            throw std::out_of_range("index out of range");
        }
    };

    template<typename f_t, typename... ts>
    constexpr void visit_at(const std::tuple<ts...>& t, std::size_t index, f_t&& f)
    {
        visit_impl<sizeof...(ts)>::visit(t, index, std::forward<f_t>(f));
    }

    template <typename f_t, typename... ts>
    constexpr void visit_at(std::tuple<ts...>& tuple, std::size_t index, f_t&& f)
    {
        visit_impl<sizeof...(ts)>::visit(tuple, index, std::forward<f_t>(f));
    }

    template <template<typename...> class tuple_t, typename f_t, typename... ts>
    constexpr void visit_at(tuple_t<ts...>&& tuple, std::size_t index, f_t&& f)
    {
        visit_impl<sizeof...(ts)>::visit(std::forward<tuple_t>(tuple), index, std::forward<f_t>(f));
    }
}

namespace casm
{
    constexpr decltype(auto) operator "" _l(unsigned long long id) noexcept
    {
        return details::numeric_label{ static_cast<details::numeric_label::id_t>(id) };
    }

    constexpr decltype(auto) operator "" _l(char const* const str, std::size_t size) noexcept
    {
        return details::crc32_label{ str, size };
    }

    constexpr decltype(auto) operator "" _b(unsigned long long value) noexcept
    {
        return static_cast<details::imm8_t>(value);
    }

    constexpr decltype(auto) operator "" _w(unsigned long long value) noexcept
    {
        return static_cast<details::imm16_t>(value);
    }

    constexpr decltype(auto) operator "" _d(unsigned long long value) noexcept
    {
        return static_cast<details::imm32_t>(value);
    }

    constexpr decltype(auto) operator "" _q(unsigned long long value) noexcept
    {
        return static_cast<details::imm64_t>(value);
    }

    inline constexpr const details::al_t al;
    inline constexpr const details::cl_t cl;
    inline constexpr const details::r8l dl{ details::r8l::names::dl };
    inline constexpr const details::r8l bl{ details::r8l::names::bl };

    inline constexpr const details::r8h ah{ details::r8h::names::ah };
    inline constexpr const details::r8h ch{ details::r8h::names::ch };
    inline constexpr const details::r8h dh{ details::r8h::names::dh };
    inline constexpr const details::r8h bh{ details::r8h::names::bh };

#ifdef CASM_X64
    inline constexpr const details::rb r8b{ details::rb::names::r8b };
    inline constexpr const details::rb r9b{ details::rb::names::r9b };
    inline constexpr const details::rb r10b{ details::rb::names::r10b };
    inline constexpr const details::rb r11b{ details::rb::names::r11b };
    inline constexpr const details::rb r12b{ details::rb::names::r12b };
    inline constexpr const details::rb r13b{ details::rb::names::r13b };
    inline constexpr const details::rb r14b{ details::rb::names::r14b };
    inline constexpr const details::rb r15b{ details::rb::names::r15b };

    inline constexpr const details::rl spl{ details::rl::names::spl };
    inline constexpr const details::rl bpl{ details::rl::names::bpl };
    inline constexpr const details::rl sil{ details::rl::names::sil };
    inline constexpr const details::rl dil{ details::rl::names::dil };
#endif

    inline constexpr const details::ax_t ax;
    inline constexpr const details::r16 cx{ details::r16::names::cx };
    inline constexpr const details::dx_t dx;
    inline constexpr const details::r16 bx{ details::r16::names::bx };
    inline constexpr const details::sp_t sp;
    inline constexpr const details::bp_t bp;
    inline constexpr const details::r16 si{ details::r16::names::si };
    inline constexpr const details::r16 di{ details::r16::names::di };

#ifdef CASM_X64
    inline constexpr const details::rw r8w{ details::rw::names::r8w };
    inline constexpr const details::rw r9w{ details::rw::names::r9w };
    inline constexpr const details::rw r10w{ details::rw::names::r10w };
    inline constexpr const details::rw r11w{ details::rw::names::r11w };
    inline constexpr const details::rw r12w{ details::rw::names::r12w };
    inline constexpr const details::rw r13w{ details::rw::names::r13w };
    inline constexpr const details::rw r14w{ details::rw::names::r14w };
    inline constexpr const details::rw r15w{ details::rw::names::r15w };
#endif

    inline constexpr const details::eax_t eax;
    inline constexpr const details::r32 ecx{ details::r32::names::ecx };
    inline constexpr const details::r32 edx{ details::r32::names::edx };
    inline constexpr const details::r32 ebx{ details::r32::names::ebx };
    inline constexpr const details::esp_t esp;
    inline constexpr const details::ebp_t ebp;
    inline constexpr const details::eip_t eip;
    inline constexpr const details::r32 esi{ details::r32::names::esi };
    inline constexpr const details::r32 edi{ details::r32::names::edi };

#ifdef CASM_X64
    inline constexpr const details::rd r8d{ details::rd::names::r8d };
    inline constexpr const details::rd r9d{ details::rd::names::r9d };
    inline constexpr const details::rd r10d{ details::rd::names::r10d };
    inline constexpr const details::rd r11d{ details::rd::names::r11d };
    inline constexpr const details::rd r12d{ details::rd::names::r12d };
    inline constexpr const details::r13d_t r13d;
    inline constexpr const details::rd r14d{ details::rd::names::r14d };
    inline constexpr const details::rd r15d{ details::rd::names::r15d };

    inline constexpr const details::rax_t rax;
    inline constexpr const details::r64 rcx{ details::r64::names::rcx };
    inline constexpr const details::r64 rdx{ details::r64::names::rdx };
    inline constexpr const details::r64 rbx{ details::r64::names::rbx };
    inline constexpr const details::rsp_t rsp;
    inline constexpr const details::rbp_t rbp;
    inline constexpr const details::rip_t rip;
    inline constexpr const details::r64 rsi{ details::r64::names::rsi };
    inline constexpr const details::r64 rdi{ details::r64::names::rdi };

    inline constexpr const details::rq r8{ details::rq::names::r8 };
    inline constexpr const details::rq r9{ details::rq::names::r9 };
    inline constexpr const details::rq r10{ details::rq::names::r10 };
    inline constexpr const details::rq r11{ details::rq::names::r11 };
    inline constexpr const details::rq r12{ details::rq::names::r12 };
    inline constexpr const details::r13_t r13;
    inline constexpr const details::rq r14{ details::rq::names::r14 };
    inline constexpr const details::rq r15{ details::rq::names::r15 };
#endif

    inline constexpr const details::es_t es;
    inline constexpr const details::cs_t cs;
    inline constexpr const details::ss_t ss;
    inline constexpr const details::ds_t ds;
    inline constexpr const details::fs_t fs;
    inline constexpr const details::gs_t gs;

    inline constexpr const details::st0_t st0;
    inline constexpr const details::st st1{ details::st::names::st1 };
    inline constexpr const details::st st2{ details::st::names::st2 };
    inline constexpr const details::st st3{ details::st::names::st3 };
    inline constexpr const details::st st4{ details::st::names::st4 };
    inline constexpr const details::st st5{ details::st::names::st5 };
    inline constexpr const details::st st6{ details::st::names::st6 };
    inline constexpr const details::st st7{ details::st::names::st7 };

    inline constexpr const details::mm mm0{ details::mm::names::mm0 };
    inline constexpr const details::mm mm1{ details::mm::names::mm1 };
    inline constexpr const details::mm mm2{ details::mm::names::mm2 };
    inline constexpr const details::mm mm3{ details::mm::names::mm3 };
    inline constexpr const details::mm mm4{ details::mm::names::mm4 };
    inline constexpr const details::mm mm5{ details::mm::names::mm5 };
    inline constexpr const details::mm mm6{ details::mm::names::mm6 };
    inline constexpr const details::mm mm7{ details::mm::names::mm7 };

    inline constexpr const details::xmm xmm0{ details::xmm::names::xmm0 };
    inline constexpr const details::xmm xmm1{ details::xmm::names::xmm1 };
    inline constexpr const details::xmm xmm2{ details::xmm::names::xmm2 };
    inline constexpr const details::xmm xmm3{ details::xmm::names::xmm3 };
    inline constexpr const details::xmm xmm4{ details::xmm::names::xmm4 };
    inline constexpr const details::xmm xmm5{ details::xmm::names::xmm5 };
    inline constexpr const details::xmm xmm6{ details::xmm::names::xmm6 };
    inline constexpr const details::xmm xmm7{ details::xmm::names::xmm7 };

#ifdef CASM_X64
    inline constexpr const details::extended_xmm xmm8{ details::extended_xmm::names::xmm8 };
    inline constexpr const details::extended_xmm xmm9{ details::extended_xmm::names::xmm9 };
    inline constexpr const details::extended_xmm xmm10{ details::extended_xmm::names::xmm10 };
    inline constexpr const details::extended_xmm xmm11{ details::extended_xmm::names::xmm11 };
    inline constexpr const details::extended_xmm xmm12{ details::extended_xmm::names::xmm12 };
    inline constexpr const details::extended_xmm xmm13{ details::extended_xmm::names::xmm13 };
    inline constexpr const details::extended_xmm xmm14{ details::extended_xmm::names::xmm14 };
    inline constexpr const details::extended_xmm xmm15{ details::extended_xmm::names::xmm15 };
#endif

    inline constexpr const details::cr cr0{ details::cr::names::cr0 };
    inline constexpr const details::cr cr1{ details::cr::names::cr1 };
    inline constexpr const details::cr cr2{ details::cr::names::cr2 };
    inline constexpr const details::cr cr3{ details::cr::names::cr3 };
    inline constexpr const details::cr cr4{ details::cr::names::cr4 };
    inline constexpr const details::cr cr5{ details::cr::names::cr5 };
    inline constexpr const details::cr cr6{ details::cr::names::cr6 };
    inline constexpr const details::cr cr7{ details::cr::names::cr7 };

    inline constexpr const details::dr dr0{ details::dr::names::dr0 };
    inline constexpr const details::dr dr1{ details::dr::names::dr1 };
    inline constexpr const details::dr dr2{ details::dr::names::dr2 };
    inline constexpr const details::dr dr3{ details::dr::names::dr3 };
    inline constexpr const details::dr dr4{ details::dr::names::dr4 };
    inline constexpr const details::dr dr5{ details::dr::names::dr5 };
    inline constexpr const details::dr dr6{ details::dr::names::dr6 };
    inline constexpr const details::dr dr7{ details::dr::names::dr7 };

    inline constexpr const details::base_ptr<details::oper8_t> byte_ptr;
    inline constexpr const auto ptr = byte_ptr;
    inline constexpr const details::base_ptr<details::oper16_t> word;
    inline constexpr const details::base_ptr<details::oper32_t> dword;
    inline constexpr const details::base_ptr<details::oper48_t> fword;
    inline constexpr const details::base_ptr<details::oper64_t> qword;
    inline constexpr const details::base_ptr<details::oper80_t> tword;
    inline constexpr const details::base_ptr<details::oper128_t> oword;

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) add(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x00) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) add(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x01) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) add(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x02) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) add(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x03) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) add(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x04) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_ax_eax_rax_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) add(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x05) + make_imm(oper1, oper0) }; }

#ifdef CASM_X32
    constexpr decltype(auto) push(details::es_t) noexcept { return details::instruct{ details::make_static_bytecode(0x06) }; }

    constexpr decltype(auto) pop(details::es_t) noexcept { return details::instruct{ details::make_static_bytecode(0x07) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) or_(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x08) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) or_(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x09) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) or_(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) or_(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0b) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) or_(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0c) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_ax_eax_rax_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) or_(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0d) + make_imm(oper1, oper0) }; }

#ifdef CASM_X32
    constexpr decltype(auto) push(details::cs_t) noexcept { return details::instruct{ details::make_static_bytecode(0x0e) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) adc(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x10) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) adc(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x11) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) adc(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x12) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) adc(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x13) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) adc(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x14) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_ax_eax_rax_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) adc(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x15) + make_imm(oper1, oper0) }; }

#ifdef CASM_X32
    constexpr decltype(auto) push(details::ss_t) noexcept { return details::instruct{ details::make_static_bytecode(0x16) }; }

    constexpr decltype(auto) pop(details::ss_t) noexcept { return details::instruct{ details::make_static_bytecode(0x17) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sbb(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x18) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sbb(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x19) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sbb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x1a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sbb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x1b) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) sbb(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x1c) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_ax_eax_rax_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sbb(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x1d) + make_imm(oper1, oper0) }; }

#ifdef CASM_X32
    constexpr decltype(auto) push(details::ds_t) noexcept { return details::instruct{ details::make_static_bytecode(0x1e) }; }

    constexpr decltype(auto) pop(details::ds_t) noexcept { return details::instruct{ details::make_static_bytecode(0x1f) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) and_(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x20) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) and_(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x21) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) and_(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x22) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) and_(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x23) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) and_(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x24) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_ax_eax_rax_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) and_(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x25) + make_imm(oper1, oper0) }; }

#ifdef CASM_X32
    constexpr decltype(auto) daa() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x27) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sub(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x28) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sub(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x29) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sub(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x2a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sub(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x2b) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) sub(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x2c) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_ax_eax_rax_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sub(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x2d) + make_imm(oper1, oper0) }; }

#ifdef CASM_X32
    constexpr decltype(auto) das() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x2f) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xor_(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x30) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xor_(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x31) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xor_(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x32) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xor_(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x33) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) xor_(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x34) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_ax_eax_rax_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xor_(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x35) + make_imm(oper1, oper0) }; }

#ifdef CASM_X32
    constexpr decltype(auto) aaa() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x37) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmp(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x38) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmp(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x39) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmp(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x3a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmp(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x3b) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) cmp(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x3c) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_ax_eax_rax_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmp(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x3d) + make_imm(oper1, oper0) }; }

#ifdef CASM_X32
    constexpr decltype(auto) aas() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x3f) }; }

    template<class oper0_t, std::enable_if_t<details::is_r16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) inc(oper0_t r) noexcept { using namespace details; auto opcode = make_static_bytecode(0x40); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_oper_size_prefix(r) + opcode }; }

    template<class oper0_t, std::enable_if_t<details::is_r16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) dec(oper0_t r) noexcept { using namespace details; auto opcode = make_static_bytecode(0x48); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_oper_size_prefix(r) + opcode }; }

    template<class oper0_t, std::enable_if_t<details::is_r16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) push(oper0_t r) noexcept { using namespace details; auto opcode = make_static_bytecode(0x50); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_oper_size_prefix(r) + opcode }; }

    template<class oper0_t, std::enable_if_t<details::is_r16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pop(oper0_t r) noexcept { using namespace details; auto opcode = make_static_bytecode(0x58); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_oper_size_prefix(r) + opcode }; }

    constexpr decltype(auto) pusha() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x60) }; }

    constexpr decltype(auto) pushad() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x60) }; }

    constexpr decltype(auto) popa() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x61) }; }

    constexpr decltype(auto) popad() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x61) }; }
#endif

#ifdef CASM_X64
    template<class oper0_t, std::enable_if_t<details::is_r16_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) push(oper0_t r) noexcept { using namespace details; auto opcode = make_static_bytecode(0x50); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_oper_size_prefix(r) + make_rex_w(r) + opcode }; }

    template<class oper0_t, std::enable_if_t<details::is_r16_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pop(oper0_t r) noexcept { using namespace details; auto opcode = make_static_bytecode(0x58); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_oper_size_prefix(r) + make_rex_w(r) + opcode }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_rm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movsxd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x63) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, std::enable_if_t<details::is_imm32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) push(oper0_t oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0x68) + make_imm(oper0) }; }

    template<class oper0_t, class oper1_t, class oper2_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_rm16_32_64_v<oper1_t> and details::is_imm16_32_v<oper2_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) imul(oper0_t oper0, oper1_t const& oper1, oper2_t oper2) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x69) + make_modrm_sib(oper1, oper0) + make_imm(oper2, oper0) }; }

    constexpr decltype(auto) push(details::imm8_t imm) noexcept { using namespace details; return instruct{ make_static_bytecode(0x6a) + make_imm(imm) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_rm16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) imul(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x6b) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    constexpr decltype(auto) ins() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x6c) }; }

    constexpr decltype(auto) insb() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x6c) }; }

    constexpr decltype(auto) insw() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x66, 0x6d) }; }

    constexpr decltype(auto) insd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x6d) }; }

    constexpr decltype(auto) outsb() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x6e) }; }

    constexpr decltype(auto) outsw() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x66, 0x6f) }; }

    constexpr decltype(auto) outsd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x6f) }; }

    inline decltype(auto) jo(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x70, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jno(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x71, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jb(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x72, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jnae(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x72, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jc(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x72, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jnb(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x73, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jae(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x73, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jnc(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x73, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jz(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x74, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) je(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x74, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jnz(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x75, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jne(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x75, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jbe(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x76, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jna(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x76, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jnbe(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x77, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) ja(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x77, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) js(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x78, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jns(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x79, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jp(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7a, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jpe(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7a, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jnp(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7b, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jpo(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7b, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jl(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7c, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jnge(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7c, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jnl(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7d, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jge(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7d, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jle(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7e, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jng(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7e, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jnle(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7f, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jg(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0x7f, static_cast<details::byte_t>(rel) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) add(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x80) + make_modrm_sib(oper0, reg_bits{ 0 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) or_(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x80) + make_modrm_sib(oper0, reg_bits{ 1 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) adc(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x80) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sbb(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x80) + make_modrm_sib(oper0, reg_bits{ 3 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) and_(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x80) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sub(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x80) + make_modrm_sib(oper0, reg_bits{ 5 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xor_(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x80) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmp(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x80) + make_modrm_sib(oper0, reg_bits{ 7 }) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and (!details::is_ax_eax_rax_v<oper0_t>) and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) add(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x81) + make_modrm_sib(oper0, reg_bits{ 0 }) + make_imm(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and (!details::is_ax_eax_rax_v<oper0_t>) and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) or_(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x81) + make_modrm_sib(oper0, reg_bits{ 1 }) + make_imm(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and (!details::is_ax_eax_rax_v<oper0_t>) and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) adc(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x81) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and (!details::is_ax_eax_rax_v<oper0_t>) and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sbb(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x81) + make_modrm_sib(oper0, reg_bits{ 3 }) + make_imm(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and (!details::is_ax_eax_rax_v<oper0_t>) and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) and_(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x81) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and (!details::is_ax_eax_rax_v<oper0_t>) and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sub(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x81) + make_modrm_sib(oper0, reg_bits{ 5 }) + make_imm(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and (!details::is_ax_eax_rax_v<oper0_t>) and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xor_(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x81) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and (!details::is_ax_eax_rax_v<oper0_t>) and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmp(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x81) + make_modrm_sib(oper0, reg_bits{ 7 }) + make_imm(oper1, oper0) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) add(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x83) + make_modrm_sib(oper0, reg_bits{ 0 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) or_(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x83) + make_modrm_sib(oper0, reg_bits{ 1 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) adc(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x83) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sbb(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x83) + make_modrm_sib(oper0, reg_bits{ 3 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) and_(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x83) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sub(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x83) + make_modrm_sib(oper0, reg_bits{ 5 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xor_(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x83) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmp(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x83) + make_modrm_sib(oper0, reg_bits{ 7 }) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) test(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x84) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) test(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x85) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xchg(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_rex(oper0, oper1) + make_static_bytecode(0x86) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xchg(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x86) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xchg(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x87) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x88) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x89) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r8_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x8a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x8b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t const& oper0, details::sreg oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x8c) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t oper0, details::sreg oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x8c) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lea(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x8d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_rm16_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(details::sreg oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1) + make_static_bytecode(0x8e) + make_modrm_sib(oper1, oper0) }; }

#ifdef CASM_X32
    template<class oper0_t, std::enable_if_t<details::is_m16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pop(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0x8f) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }
#endif

#ifdef CASM_X64
    template<class oper0_t, std::enable_if_t<details::is_m16_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pop(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0x8f) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_ax_eax_rax_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xchg(oper0_t r, oper1_t) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); auto opcode = make_static_bytecode(0x90); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_oper_size_prefix(r) + make_rex(r) + opcode }; }

    constexpr decltype(auto) nop() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x90) }; }

    constexpr decltype(auto) pause_() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf3, 0x90) }; }

    constexpr decltype(auto) cbw() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x66, 0x98) }; }

    constexpr decltype(auto) cwde() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x98) }; }

#ifdef CASM_X64
    constexpr decltype(auto) cdqe() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x48, 0x98) }; }
#endif

    constexpr decltype(auto) cwd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x66, 0x99) }; }

    constexpr decltype(auto) cdq() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x99) }; }

#ifdef CASM_X64
    constexpr decltype(auto) cqo() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x48, 0x99) }; }
#endif

    constexpr decltype(auto) fwait() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9b) }; }

    constexpr decltype(auto) wait() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9b) }; }

    constexpr decltype(auto) pushf() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9c) }; }

    constexpr decltype(auto) pushfq() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9c) }; }

    constexpr decltype(auto) popf() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9d) }; }

    constexpr decltype(auto) popfq() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9d) }; }

    constexpr decltype(auto) sahf() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9e) }; }

    constexpr decltype(auto) lahf() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9f) }; }

    constexpr decltype(auto) movsb() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xa4) }; }

    constexpr decltype(auto) movsw() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x66, 0xa5) }; }

    constexpr decltype(auto) movsd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xa5) }; }

#ifdef CASM_X64
    constexpr decltype(auto) movsq() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x48, 0xa5) }; }
#endif

    constexpr decltype(auto) cmpsb() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xa6) }; }

    constexpr decltype(auto) cmpsw() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x66, 0xa7) }; }

    constexpr decltype(auto) cmpsd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xa7) }; }

#ifdef CASM_X64
    constexpr decltype(auto) cmpsq() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x48, 0xa7) }; }
#endif

    constexpr decltype(auto) test(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0xa8) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_ax_eax_rax_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) test(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xa9) + make_imm(oper1, oper0) }; }

    constexpr decltype(auto) stosb() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xaa) }; }

    constexpr decltype(auto) stosw() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x66, 0xab) }; }

    constexpr decltype(auto) stosd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xab) }; }

#ifdef CASM_X64
    constexpr decltype(auto) stosq() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x48, 0xab) }; }
#endif

    constexpr decltype(auto) lodsb() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xac) }; }

    constexpr decltype(auto) lodsw() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x66, 0xad) }; }

    constexpr decltype(auto) lodsd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xad) }; }

#ifdef CASM_X64
    constexpr decltype(auto) lodsq() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x48, 0xad) }; }
#endif

    constexpr decltype(auto) scasb() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xae) }; }

    constexpr decltype(auto) scasw() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x66, 0xaf) }; }

    constexpr decltype(auto) scasd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xaf) }; }

#ifdef CASM_X64
    constexpr decltype(auto) scasq() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x48, 0xaf) }; }
#endif

    template<class oper0_t, std::enable_if_t<details::is_r8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t r, details::imm8_t oper1) noexcept { using namespace details; auto opcode = make_static_bytecode(0xb0); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_rex(r) + opcode + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_v<oper0_t> and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t r, oper1_t oper1) noexcept { using namespace details; auto opcode = make_static_bytecode(0xb8); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_oper_size_prefix(r) + make_rex(r) + opcode + make_imm(oper1, r) }; }

#ifdef CASM_X64
    template<class oper0_t, std::enable_if_t<details::is_r64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t r, details::imm64_t oper1) noexcept { using namespace details; auto opcode = make_static_bytecode(0xb8); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_rex(r) + opcode + to_static_bytecode(oper1) }; }

    template<class oper0_t, class t, std::enable_if_t<details::is_r64_v<oper0_t> and !details::is_m_v<t> and !details::is_r_v<t> and !details::is_imm_v<t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t r, t const& ref) noexcept { using namespace details; auto opcode = make_static_bytecode(0xb8); opcode.at(opcode.size() - 1) += r.n(); return instruct{ make_rex(r) + opcode + to_static_bytecode(ref) }; }
#endif

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rol(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc0) + make_modrm_sib(oper0, reg_bits{ 0 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ror(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc0) + make_modrm_sib(oper0, reg_bits{ 1 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcl(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc0) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcr(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc0) + make_modrm_sib(oper0, reg_bits{ 3 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shl(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc0) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sal(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc0) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shr(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc0) + make_modrm_sib(oper0, reg_bits{ 5 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sar(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc0) + make_modrm_sib(oper0, reg_bits{ 7 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rol(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc1) + make_modrm_sib(oper0, reg_bits{ 0 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ror(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc1) + make_modrm_sib(oper0, reg_bits{ 1 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcl(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc1) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcr(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc1) + make_modrm_sib(oper0, reg_bits{ 3 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shl(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc1) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sal(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc1) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shr(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc1) + make_modrm_sib(oper0, reg_bits{ 5 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sar(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc1) + make_modrm_sib(oper0, reg_bits{ 7 }) + make_imm(oper1) }; }

    constexpr decltype(auto) retn(details::imm16_t oper) noexcept { using namespace details; return instruct{ make_static_bytecode(0xc2) + make_imm(oper) }; }

    constexpr decltype(auto) ret() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xc3) }; }

#ifdef CASM_X32
    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_v<oper0_t> and details::is_m16_48_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) les(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xc4) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_v<oper0_t> and details::is_m16_48_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lds(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xc5) + make_modrm_sib(oper1, oper0) }; }
#endif

    template<class oper0_t, std::enable_if_t<details::is_m8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc6) + make_modrm_sib(oper0, reg_bits{ 0 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t const& oper0, details::imm32_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xc7) + make_modrm_sib(oper0, reg_bits{ 0 }) + make_imm(oper1, oper0) }; }

    constexpr decltype(auto) enter(details::imm16_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0xc8) + make_imm(oper0) + make_imm(oper1) }; }

    constexpr decltype(auto) leave() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xc9) }; }

    constexpr decltype(auto) retf(details::imm16_t oper) noexcept { using namespace details; return instruct{ make_static_bytecode(0xca) + make_imm(oper) }; }

    constexpr decltype(auto) retf() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xcb) }; }

    constexpr decltype(auto) int3() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xcc) }; }

    constexpr decltype(auto) int_(details::imm8_t imm) noexcept { using namespace details; return instruct{ make_static_bytecode(0xcd) + make_imm(imm) }; }

#ifdef CASM_X32
    constexpr decltype(auto) into() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xce) }; }
#endif

    constexpr decltype(auto) iret() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xcf) }; }

    constexpr decltype(auto) iretd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xcf) }; }

#ifdef CASM_X64
    constexpr decltype(auto) iretq() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x48, 0xcf) }; }
#endif

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rol(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd0) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ror(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd0) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcl(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd0) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd0) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shl(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd0) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sal(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd0) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd0) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sar(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd0) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rol(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd1) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ror(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd1) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcl(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd1) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd1) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shl(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd1) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sal(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd1) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd1) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sar(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd1) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rol(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd2) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ror(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd2) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcl(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd2) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcr(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd2) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shl(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd2) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sal(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd2) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shr(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd2) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sar(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd2) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rol(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd3) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ror(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd3) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcl(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd3) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcr(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd3) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shl(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd3) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sal(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd3) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shr(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd3) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sar(oper0_t const& oper0, details::cl_t) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd3) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

#ifdef CASM_X32
    constexpr decltype(auto) aam() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd4, 0x0a) }; }

    constexpr decltype(auto) aam(details::imm8_t imm) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd4) + make_imm(imm) }; }

    constexpr decltype(auto) amx(details::imm8_t imm) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd4) + make_imm(imm) }; }

    constexpr decltype(auto) aad() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd5, 0x0a) }; }

    constexpr decltype(auto) aad(details::imm8_t imm) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd4) + make_imm(imm) }; }

    constexpr decltype(auto) adx(details::imm8_t imm) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd4) + make_imm(imm) }; }

    constexpr decltype(auto) salc() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd6) }; }

    constexpr decltype(auto) setalc() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd6) }; }
#endif

    constexpr decltype(auto) xlat() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd7) }; }

    constexpr decltype(auto) xlatb() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd7) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fadd(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) fadd(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) fadd(details::st0_t, details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fmul(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    constexpr decltype(auto) fmul(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    constexpr decltype(auto) fmul(details::st0_t, details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_stm32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fcom(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    constexpr decltype(auto) fcom() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd8, 0xd1) }; }

    template<class oper0_t, std::enable_if_t<details::is_stm32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fcomp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    constexpr decltype(auto) fcomp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd8, 0xd9) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fsub(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) fsub(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) fsub(details::st0_t, details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fsubr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fsubr(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fsubr(details::st0_t, details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fdiv(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    constexpr decltype(auto) fdiv(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    constexpr decltype(auto) fdiv(details::st0_t, details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fdivr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    constexpr decltype(auto) fdivr(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    constexpr decltype(auto) fdivr(details::st0_t, details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd8) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_stm32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fld(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) fxch(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    constexpr decltype(auto) fxch() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xc9) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fst(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    constexpr decltype(auto) fnop() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xd0) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fstp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fldenv(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) fchs() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xe0) }; }

    constexpr decltype(auto) fabs() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xe1) }; }

    constexpr decltype(auto) ftst() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xe4) }; }

    constexpr decltype(auto) fxam() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xe5) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fldcw(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fld1() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xe8) }; }

    constexpr decltype(auto) fldl2t() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xe9) }; }

    constexpr decltype(auto) fldl2e() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xea) }; }

    constexpr decltype(auto) fldpi() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xeb) }; }

    constexpr decltype(auto) fldlg2() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xec) }; }

    constexpr decltype(auto) fldln2() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xed) }; }

    constexpr decltype(auto) fldz() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xee) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fnstenv(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fstenv(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + 0x9b + make_rex(oper0) + make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    constexpr decltype(auto) f2xm1() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf0) }; }

    constexpr decltype(auto) fyl2x() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf1) }; }

    constexpr decltype(auto) fptan() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf2) }; }

    constexpr decltype(auto) fpatan() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf3) }; }

    constexpr decltype(auto) fxtract() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf4) }; }

    constexpr decltype(auto) fprem1() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf5) }; }

    constexpr decltype(auto) fdecstp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf6) }; }

    constexpr decltype(auto) fincstp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf7) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fnstcw(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fstcw(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0x9b) + make_rex(oper0) + make_static_bytecode(0xd9) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    constexpr decltype(auto) fprem() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf8) }; }

    constexpr decltype(auto) fyl2xp1() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xf9) }; }

    constexpr decltype(auto) fsqrt() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xfa) }; }

    constexpr decltype(auto) fsincos() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xfb) }; }

    constexpr decltype(auto) frndint() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xfc) }; }

    constexpr decltype(auto) fscale() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xfd) }; }

    constexpr decltype(auto) fsin() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xfe) }; }

    constexpr decltype(auto) fcos() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xd9, 0xff) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fiadd(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) fcmovb(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fimul(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    constexpr decltype(auto) fcmove(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ficom(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    constexpr decltype(auto) fcmovbe(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ficomp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    constexpr decltype(auto) fcmovu(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fisub(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fisubr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fucompp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xda, 0xe9) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fidiv(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fidivr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xda) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fild(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) fcmovnb(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fisttp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    constexpr decltype(auto) fcmovne(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fist(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    constexpr decltype(auto) fcmovnbe(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fistp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    constexpr decltype(auto) fcmovnu(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    constexpr decltype(auto) fneni() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xdb, 0xe0) }; }

    constexpr decltype(auto) fndisi() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xdb, 0xe1) }; }

    constexpr decltype(auto) fnclex() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xdb, 0xe2) }; }

    constexpr decltype(auto) fclex() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9b, 0xdb, 0xe2) }; }

    constexpr decltype(auto) fninit() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xdb, 0xe3) }; }

    constexpr decltype(auto) finit() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x9b, 0xdb, 0xe3) }; }

    template<class oper0_t, std::enable_if_t<details::is_m80_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fld(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fucomi(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fcomi(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m80_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fstp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdb) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fadd(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) fadd(details::st oper0, details::st0_t) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fmul(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    constexpr decltype(auto) fmul(details::st oper0, details::st0_t) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fcom(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fcomp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fsub(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) fsubr(details::st oper0, details::st0_t) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fsubr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fsub(details::st oper0, details::st0_t) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fdiv(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    constexpr decltype(auto) fdivr(details::st oper0, details::st0_t) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fdivr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    constexpr decltype(auto) fdiv(details::st oper0, details::st0_t) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdc) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fld(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) ffree(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fisttp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fst(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    constexpr decltype(auto) fst(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_st_v<oper0_t> or details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fstp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) frstor(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) fucom(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) fucom() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xdd, 0xe1) }; }

    constexpr decltype(auto) fucomp(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fucomp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xdd, 0xe9) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fnsave(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fsave(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + 0x9b + make_rex(oper0) + make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fnstsw(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fstsw(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0x9b) + make_rex(oper0) + make_static_bytecode(0xdd) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fiadd(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) faddp(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) faddp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xde, 0xc1) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fimul(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    constexpr decltype(auto) fmulp(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    constexpr decltype(auto) fmulp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xde, 0xc9) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ficom(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ficomp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    constexpr decltype(auto) fcompp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xde, 0xd9) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fisub(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) fsubrp(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) fsubrp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xde, 0xe1) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fisubr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fsubp(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fsubp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xde, 0xe9) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fidiv(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    constexpr decltype(auto) fdivrp(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    constexpr decltype(auto) fdivrp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xde, 0xf1) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fidivr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    constexpr decltype(auto) fdivp(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xde) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    constexpr decltype(auto) fdivp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xde, 0xf9) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fild(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) ffreep(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fisttp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fist(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fistp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m80_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fbld(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) fnstsw(details::ax_t) noexcept { return details::instruct{ details::make_static_bytecode(0xdf, 0xe0) }; }

    constexpr decltype(auto) fstsw(details::ax_t) noexcept { return details::instruct{ details::make_static_bytecode(0x9b, 0xdf, 0xe0) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fild(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) fucomip(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m80_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fbstp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    constexpr decltype(auto) fcomip(details::st oper0) noexcept { using namespace details; return instruct{ make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fistp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xdf) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    inline decltype(auto) loopnz(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0xe0, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) loopne(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0xe0, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) loopz(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0xe1, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) loope(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0xe1, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) loop(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0xe2, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jecxz(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0xe3, static_cast<details::byte_t>(rel) }; }

    inline decltype(auto) jrcxz(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0xe3, static_cast<details::byte_t>(rel) }; }

    constexpr decltype(auto) in(details::al_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0xe4) + make_imm(oper1) }; }

    constexpr decltype(auto) in(details::eax_t, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0xe5) + make_imm(oper1) }; }

    constexpr decltype(auto) out(details::imm8_t oper0, details::al_t) noexcept { using namespace details; return instruct{ make_static_bytecode(0xe6) + make_imm(oper0) }; }

    constexpr decltype(auto) out(details::imm8_t oper0, details::eax_t) noexcept { using namespace details; return instruct{ make_static_bytecode(0xe7) + make_imm(oper0) }; }

    inline decltype(auto) call(details::imm32_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0xe8 }, imm); }

    inline decltype(auto) jmp(details::imm32_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0xe9 }, imm); }

#ifdef CASM_X32
    template<class oper0_t, std::enable_if_t<details::is_m16_48_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) jmp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0xea) + make_modrm_sib(oper0) }; }
#endif

    inline decltype(auto) jmp(details::imm8_t rel) noexcept { return details::dynamic_bytecode_t{ 0xeb, static_cast<details::byte_t>(rel) }; }

    constexpr decltype(auto) in(details::al_t, details::dx_t) noexcept { return details::instruct{ details::make_static_bytecode(0xec) }; }

    constexpr decltype(auto) in(details::eax_t, details::dx_t) noexcept { return details::instruct{ details::make_static_bytecode(0xed) }; }

    constexpr decltype(auto) out(details::dx_t, details::al_t) noexcept { return details::instruct{ details::make_static_bytecode(0xee) }; }

    constexpr decltype(auto) out(details::dx_t, details::eax_t) noexcept { return details::instruct{ details::make_static_bytecode(0xef) }; }

    constexpr decltype(auto) lock() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf0) }; }

    constexpr decltype(auto) int1() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf1) }; }

    constexpr decltype(auto) icebp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf1) }; }

    constexpr decltype(auto) repnz() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf2) }; }

    constexpr decltype(auto) repne() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf2) }; }

    constexpr decltype(auto) repz() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf3) }; }

    constexpr decltype(auto) repe() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf3) }; }

    constexpr decltype(auto) rep() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf3) }; }

    constexpr decltype(auto) hlt() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf4) }; }

    constexpr decltype(auto) cmc() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf5) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) test(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf6) + make_modrm_sib(oper0, reg_bits{ 0 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) not_(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf6) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) neg(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf6) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mul(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf6) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) imul(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf6) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) div(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf6) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) idiv(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf6) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and (!details::is_ax_eax_rax_v<oper0_t>) and details::is_imm16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) test(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf7) + make_modrm_sib(oper0, reg_bits{ 0 }) + make_imm(oper1, oper0) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) not_(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf7) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) neg(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf7) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mul(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf7) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) imul(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf7) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) div(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf7) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) idiv(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xf7) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    constexpr decltype(auto) clc() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf8) }; }

    constexpr decltype(auto) stc() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xf9) }; }

    constexpr decltype(auto) cli() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xfa) }; }

    constexpr decltype(auto) sti() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xfb) }; }

    constexpr decltype(auto) cld() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xfc) }; }

    constexpr decltype(auto) std_() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0xfd) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) inc(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xfe) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) dec(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xfe) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

#ifdef CASM_X32
    template<class oper0_t, std::enable_if_t<details::is_m16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) inc(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }
#endif

#ifdef CASM_X64
    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) inc(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }
#endif

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) dec(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) call(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

#ifdef CASM_X64
    template<class oper0_t, std::enable_if_t<details::is_rm64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) call(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }
#endif

    template<class oper0_t, std::enable_if_t<details::is_m48_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) call(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

#ifdef CASM_X32
    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) jmp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }
#endif

#ifdef CASM_X64
    template<class oper0_t, std::enable_if_t<details::is_rm64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) jmp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }
#endif

    template<class oper0_t, std::enable_if_t<details::is_m48_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) jmp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

#ifdef CASM_X32
    template<class oper0_t, std::enable_if_t<details::is_m16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) push(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }
#endif

#ifdef CASM_X64
    template<class oper0_t, std::enable_if_t<details::is_m16_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) push(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0xff) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }
#endif

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sldt(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x00) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_r16_32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sldt(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x00) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) str(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x00) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) str(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x00) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lldt(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x00) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ltr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x00) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) verr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x00) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) verw(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x00) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sgdt(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x01) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) vmcall() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xc1) }; }

    constexpr decltype(auto) vmlaunch() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xc2) }; }

    constexpr decltype(auto) vmresume() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xc3) }; }

    constexpr decltype(auto) vmxoff() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xc4) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sidt(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x01) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    constexpr decltype(auto) monitor() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xc8) }; }

    constexpr decltype(auto) mwait() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xc9) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lgdt(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x01) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    constexpr decltype(auto) xgetbv() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xd0) }; }

    constexpr decltype(auto) xsetbv() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xd1) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lidt(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x01) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) smsw(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x01) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) smsw(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x01) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lmsw(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x01) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) invlpg(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x01) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

#ifdef CASM_X64
    constexpr decltype(auto) swapgs() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xf8) }; }
#endif

    constexpr decltype(auto) rdtscp() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x01, 0xf9) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lar(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x02) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_r16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lar(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x02) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lsl(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x03) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_r16_32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lsl(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x03) + make_modrm_sib(oper1, oper0) }; }

#ifdef CASM_X64
    constexpr decltype(auto) syscall_() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x05) }; }
#endif

    constexpr decltype(auto) clts() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x06) }; }

    constexpr decltype(auto) sysret() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x07) }; }

    constexpr decltype(auto) invd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x08) }; }

    constexpr decltype(auto) wbinvd() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x09) }; }

    constexpr decltype(auto) ud2() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x0b) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movups(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x10) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x10) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movupd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x10) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x10) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m128_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movups(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0x11) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m32_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movss(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0xf3) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x11) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m128_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movupd(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex_w(oper0, oper1) + make_static_bytecode(0x0f, 0x11) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movsd(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0xf2) + make_rex_w(oper0, oper1) + make_static_bytecode(0x0f, 0x11) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movhlps(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x12) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movlps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x12) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movlpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x12) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movddup(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x12) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movsldup(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x12) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movlps(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0x13) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movlpd(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0x13) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) unpcklps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x14) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) unpcklpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x14) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) unpckhps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x15) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) unpckhpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x15) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movlhps(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x16) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movhps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x16) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movhpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x16) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movshdup(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x16) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movhps(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0x17) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movhpd(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0x17) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_m8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) prefetchnta(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x18) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) prefetcht0(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x18) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) prefetcht1(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x18) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) prefetcht2(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x18) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) nop(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x1f) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

#ifdef CASM_X64
    template<class oper0_t, std::enable_if_t<details::is_r64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t oper0, details::cr oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x20) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_r64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t oper0, details::dr oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x21) + make_modrm_sib(oper0, oper1) }; }

    template<class oper1_t, std::enable_if_t<details::is_r64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(details::cr oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x22) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_r64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(details::dr oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x23) + make_modrm_sib(oper1, oper0) }; }
#endif

#ifdef CASM_X32
    template<class oper0_t, std::enable_if_t<details::is_r32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t oper0, details::cr oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x20) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_r32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(oper0_t oper0, details::dr oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x21) + make_modrm_sib(oper0, oper1) }; }

    template<class oper1_t, std::enable_if_t<details::is_r32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(details::cr oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x22) + make_modrm_sib(oper0, oper1) }; }

    template<class oper1_t, std::enable_if_t<details::is_r32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mov(details::dr oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x23) + make_modrm_sib(oper0, oper1) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movaps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x28) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movapd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x28) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m128_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movaps(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex_w(oper0, oper1) + make_static_bytecode(0x0f, 0x29) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m128_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movapd(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0x29) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtpi2ps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x2a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_rm32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtsi2ss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x2a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtpi2pd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x2a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_rm32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtsi2sd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x2a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m128_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movntps(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_rex_w(oper0, oper1) + make_address_size_prefix(oper0) + make_static_bytecode(0x0f, 0x2b) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m128_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movntpd(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex_w(oper0, oper1) + make_static_bytecode(0x0f, 0x2b) + make_modrm_sib(oper0, oper1) }; }

    template<class oper1_t, std::enable_if_t<details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvttps2pi(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x2c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvttss2si(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x2c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvttpd2pi(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1) + make_static_bytecode(0x0f, 0x2c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvttsd2si(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0xf2) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x2c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvttsd2si(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x2c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtps2pi(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x2d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtss2si(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x2d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtpd2pi(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1) + make_static_bytecode(0x0f, 0x2d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtsd2si(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x2d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ucomiss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1) + make_static_bytecode(0x0f, 0x2e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ucomisd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x2e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) comiss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1) + make_static_bytecode(0x0f, 0x2f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) comisd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x2f) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) wrmsr() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x30) }; }

    constexpr decltype(auto) rdtsc() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x31) }; }

    constexpr decltype(auto) rdmsr() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x32) }; }

    constexpr decltype(auto) rdpmc() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x33) }; }

    constexpr decltype(auto) sysenter() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x34) }; }

    constexpr decltype(auto) sysexit() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x35) }; }

    constexpr decltype(auto) getsec() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x37) }; }

#ifdef CASM_X32
    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pshufb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x00) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pshufb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x00) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phaddw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x01) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phaddw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x01) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phaddd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x02) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phaddd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x02) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phaddsw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x03) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phaddsw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x03) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaddubsw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x04) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaddubsw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x04) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phsubw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x05) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phsubw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x05) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phsubd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x06) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phsubd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x06) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phsubsw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x07) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phsubsw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x07) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psignb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x08) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psignb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x08) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psignw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x09) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psignw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x09) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psignd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x0a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psignd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x0a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmulhrsw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x0b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmulhrsw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x0b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pblendvb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x10) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) blendvps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x14) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) blendvpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x15) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ptest(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x17) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pabsb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x1c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pabsb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x1c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pabsw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x1d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pabsw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x1d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pabsd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x1e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pabsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x1e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovsxbw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x20) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovsxbd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x21) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m16_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovsxbq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x22) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovsxwd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x23) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovsxwq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x24) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovsxdq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x25) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmuldq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x28) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpeqq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x29) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movntdqa(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x38, 0x2a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) packusdw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x2b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovzxbw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x38, 0x30) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovzxbd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x38, 0x31) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m16_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovzxbq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x38, 0x32) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovzxwd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_static_bytecode(0x66, 0x0f, 0x38, 0x33) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovzxwq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x34) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovzxdq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x35) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpgtq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x37) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pminsb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x38) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pminsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x39) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pminuw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x3a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pminud(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x3b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaxsb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x3c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaxsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x3d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaxuw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x3e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaxud(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x3f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmulld(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x40) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) phminposuw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x41) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_v<oper0_t> and details::is_m128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) invept(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x80) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_v<oper0_t> and details::is_m128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) invvpid(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x81) + make_modrm_sib(oper1, oper0) }; }
#endif

#ifdef CASM_X64
    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r64_v<oper0_t> and details::is_m128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) invept(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x80) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r64_v<oper0_t> and details::is_m128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) invvpid(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x38, 0x81) + make_modrm_sib(oper1, oper0) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movbe(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x38, 0xf0) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_rm8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) crc32(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x38, 0xf0) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movbe(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x38, 0xf1) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_rm16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) crc32(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x38, 0xf1) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) roundps(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x08) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) roundpd(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x09) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) roundss(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x0a) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) roundsd(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x0b) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) blendps(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x0c) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) blendpd(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x0d) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pblendw(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x0e) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) palignr(details::mm oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1) + make_static_bytecode(0x0f, 0x3a, 0x0f) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) palignr(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x0f) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m8_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pextrb(oper0_t const& oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_oper_size_prefix(oper1) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x3a, 0x14) + make_modrm_sib(oper0, oper1) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pextrb(oper0_t oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper1) + make_static_bytecode(0x0f, 0x3a, 0x14) + make_modrm_sib(oper0, oper1) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm32_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pextrd(oper0_t const& oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_oper_size_prefix(oper1) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x3a, 0x16) + make_modrm_sib(oper0, oper1) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pextrq(oper0_t const& oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_oper_size_prefix(oper1) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x3a, 0x16) + make_modrm_sib(oper0, oper1) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm32_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) extractps(oper0_t const& oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_oper_size_prefix(oper1) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x3a, 0x17) + make_modrm_sib(oper0, oper1) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pinsrb(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x20) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_r32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pinsrb(oper0_t oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x20) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) insertps(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x21) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) insertps(oper0_t oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x21) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_rm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pinsrd(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0x66) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x22) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_rm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pinsrq(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x22) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) dpps(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x40) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) dppd(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x41) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mpsadbw(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x42) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpestrm(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x60) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpestri(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x61) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpistrm(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x62) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpistri(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x3a, 0x63) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovo(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x40) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovno(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x41) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x42) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovnae(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x42) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovc(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x42) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovnb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x43) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovae(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x43) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovnc(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x43) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovz(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x44) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmove(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x44) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovnz(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x45) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovne(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x45) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovbe(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x46) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovna(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x46) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovnbe(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x47) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmova(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x47) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovs(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x48) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovns(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x49) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovp(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovpe(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovnp(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovpo(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovl(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovnge(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovnl(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovge(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovle(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovng(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovnle(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmovg(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x4f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movmskps(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_rex(oper0) + make_static_bytecode(0x0f, 0x50) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movmskpd(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper1) + make_rex(oper0) + make_static_bytecode(0x0f, 0x50) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sqrtps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x51) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sqrtss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x51) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sqrtpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1, oper0) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x51) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sqrtsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x51) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rsqrtps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x52) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rsqrtss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x52) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcpps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x53) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) rcpss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x53) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) andps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x54) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) andpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x54) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) andnps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x55) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) andnpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x55) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) orps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x56) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) orpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x56) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xorps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x57) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xorpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x57) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) addps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x58) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) addss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x58) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) addpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x58) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) addsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x58) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mulps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x59) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mulss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x59) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mulpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x59) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) mulsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x59) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtps2pd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtpd2ps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtss2sd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x5a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtsd2ss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtdq2ps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtps2dq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvttps2dq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_static_bytecode(0xf3) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) subps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) subss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x5c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) subpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) subsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) minps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) minss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x5d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) minpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) minsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) divps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) divss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x5e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) divpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) divsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) maxps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) maxss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x5f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) maxpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) maxsd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x5f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpcklbw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x60) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpcklbw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x60) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpcklwd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x61) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpcklwd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x61) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpckldq(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x62) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpckldq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x62) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) packsswb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x63) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) packsswb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x63) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpgtb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x64) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpgtb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x64) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpgtw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x65) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpgtw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x65) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpgtd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x66) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpgtd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x66) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) packuswb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x67) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) packuswb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x67) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpckhbw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x68) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpckhbw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x68) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpckhwd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x69) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpckhwd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x69) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpckhdq(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x6a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpckhdq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x6a) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) packssdw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x6b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) packssdw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x6b) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpcklqdq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x6c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) punpckhqdq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x6d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_rm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1) + make_static_bytecode(0x0f, 0x6e) + make_modrm_sib(oper1, oper0) }; }

#ifdef CASM_X64
    template<class oper1_t, std::enable_if_t<details::is_r64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movq(details::mm oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_rex(oper1) + make_static_bytecode(0x0f, 0x6e) + make_modrm_sib(oper1, oper0) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_rm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_oper_size_prefix(oper0) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x6e) + make_modrm_sib(oper1, oper0) }; }

#ifdef CASM_X64
    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_r64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movq(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0x6e) + make_modrm_sib(oper1, oper0) }; }
#endif

    constexpr decltype(auto) movq(details::mm oper0, details::mm oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x6f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_m64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movq(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x6f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movdqa(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x6f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movdqu(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x6f) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pshufw(details::mm oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1) + make_static_bytecode(0x0f, 0x70) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pshuflw(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x70) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pshufhw(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x70) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pshufd(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x70) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    constexpr decltype(auto) psrlw(details::mm oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x71) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrlw(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x71) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    constexpr decltype(auto) psraw(details::mm oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x71) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psraw(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x71) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    constexpr decltype(auto) psllw(details::mm oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x71) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psllw(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x71) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1) }; }

    constexpr decltype(auto) psrld(details::mm oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x72) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrld(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x72) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    constexpr decltype(auto) psrad(details::mm oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x72) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrad(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x72) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    constexpr decltype(auto) pslld(details::mm oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x72) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pslld(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x72) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1) }; }

    constexpr decltype(auto) psrlq(details::mm oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x73) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrlq(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x73) + make_modrm_sib(oper0, reg_bits{ 2 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrldq(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x73) + make_modrm_sib(oper0, reg_bits{ 3 }) + make_imm(oper1) }; }

    constexpr decltype(auto) psllq(details::mm oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0x73) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psllq(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x73) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pslldq(oper0_t oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0x0f, 0x73) + make_modrm_sib(oper0, reg_bits{ 7 }) + make_imm(oper1) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpeqb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x74) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpeqb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x74) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpeqw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x75) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpeqw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x75) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpeqd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x76) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pcmpeqd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x76) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) emms() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0x77) }; }

#ifdef CASM_X32
    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m32_v<oper0_t> and details::is_r32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) vmread(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0x0f, 0x78) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_v<oper0_t> and details::is_rm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) vmwrite(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x79) + make_modrm_sib(oper1, oper0) }; }
#endif

#ifdef CASM_X64
    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm64_v<oper0_t> and details::is_r64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) vmread(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0x0f, 0x78) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r64_v<oper0_t> and details::is_rm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) vmwrite(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0x79) + make_modrm_sib(oper1, oper0) }; }
#endif

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) haddpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x7c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) haddps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x7c) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) hsubpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x7d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) hsubps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x7d) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movd(oper0_t const& oper0, details::mm oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x7e) + make_modrm_sib(oper0, oper1) }; }

#ifdef CASM_X64
    template<class oper0_t, std::enable_if_t<details::is_r64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movq(oper0_t const& oper0, details::mm oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x7e) + make_modrm_sib(oper0, oper1) }; }
#endif

#ifdef CASM_X64
    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movq(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper1) + make_static_bytecode(0x0f, 0x7e) + make_modrm_sib(oper0, oper1) }; }
#endif

#undef CASM_X32
#undef CASM_X64

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm32_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movd(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_oper_size_prefix(oper1) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0x7e) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0x7e) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movq(oper0_t const& oper0, details::mm oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_rex_w(oper0, oper1) + make_address_size_prefix(oper0) + make_static_bytecode(0x0f, 0x7f) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m128_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movdqa(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0x66) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0x7f) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m128_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movdqu(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0xf3) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0x7f) + make_modrm_sib(oper0, oper1) }; }


    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jo(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x80 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jno(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x81 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jb(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x82 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jnae(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x82 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jc(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x82 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jnb(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x83 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jae(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x83 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jnc(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x83 }, imm); }

    inline decltype(auto) jz(details::imm32_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x84 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) je(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x84 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jnz(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x85 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jne(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x85 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jbe(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x86 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jna(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x86 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jnbe(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x87 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) ja(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x87 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) js(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x88 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jns(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x89 }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jp(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8a }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jpe(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8a }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jnp(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8b }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jpo(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8b }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jl(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8c }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jnge(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8c }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jnl(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8d }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jge(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8d }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jle(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8e }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jng(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8e }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jnle(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8f }, imm); }

    template<class oper_t, std::enable_if_t<details::is_imm16_32_v<oper_t>, std::nullptr_t> = nullptr> inline decltype(auto) jg(oper_t imm) noexcept { return details::make_rel_instruct_bytecode(details::dynamic_bytecode_t{ 0x0f, 0x8f }, imm); }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) seto(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x90) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setno(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x91) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setb(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x92) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setnae(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x92) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setc(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x92) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setnb(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x93) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setae(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x93) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setnc(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x93) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setz(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x94) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sete(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x94) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setnz(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x95) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setne(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x95) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setbe(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x96) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setna(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x96) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setnbe(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x97) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) seta(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x97) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) sets(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x98) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setns(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x99) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9a) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setpe(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9a) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setnp(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9b) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setpo(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9b) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setl(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9c) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setnge(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9c) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setnl(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9d) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setge(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9d) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setle(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9e) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setng(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9e) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setnle(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9f) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) setg(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0x9f) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    constexpr decltype(auto) push(details::fs_t) noexcept { return details::instruct{ details::make_static_bytecode(0x0f, 0xa0) }; }

    constexpr decltype(auto) pop(details::fs_t) noexcept { return details::instruct{ details::make_static_bytecode(0x0f, 0xa1) }; }

    constexpr decltype(auto) cpuid() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0xa2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) bt(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xa3) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shld(oper0_t const& oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xa4) + make_modrm_sib(oper0, oper1) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shld(oper0_t const& oper0, oper1_t oper1, details::cl_t) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xa5) + make_modrm_sib(oper0, oper1) }; }

    constexpr decltype(auto) push(details::gs_t) noexcept { return details::instruct{ details::make_static_bytecode(0x0f, 0xa8) }; }

    constexpr decltype(auto) pop(details::gs_t) noexcept { return details::instruct{ details::make_static_bytecode(0x0f, 0xa9) }; }

    constexpr decltype(auto) rsm() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0xaa) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) bts(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xab) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shrd(oper0_t const& oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xac) + make_modrm_sib(oper0, oper1) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shrd(oper0_t const& oper0, oper1_t oper1, details::cl_t) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xad) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fxsave(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xae) + make_modrm_sib(oper0, reg_bits{ 0 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) fxrstor(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0xae) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) ldmxcsr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xae) + make_modrm_sib(oper0, reg_bits{ 2 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) stmxcsr(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xae) + make_modrm_sib(oper0, reg_bits{ 3 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xsave(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xae) + make_modrm_sib(oper0, reg_bits{ 4 }) }; }

    constexpr decltype(auto) lfence() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0xae) }; }

    template<class oper0_t, std::enable_if_t<details::is_m_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xrstor(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xae) + make_modrm_sib(oper0, reg_bits{ 5 }) }; }

    constexpr decltype(auto) mfence() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0xae) }; }

    constexpr decltype(auto) sfence() noexcept { using namespace details; return details::instruct{ details::make_static_bytecode(0x0f, 0xae) }; }

    template<class oper0_t, std::enable_if_t<details::is_m8_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) clflush(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xae) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) imul(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xaf) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmpxchg(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xb0) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmpxchg(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xb1) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lss(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xb2) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) btr(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xb3) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lfs(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xb4) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lgs(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xb5) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_rm8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movzx(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xb6) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_v<oper0_t> and details::is_rm16_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movzx(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xb7) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) popcnt(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xb8) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) bt(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xba) + make_modrm_sib(oper0, reg_bits{ 4 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) bts(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xba) + make_modrm_sib(oper0, reg_bits{ 5 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) btr(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xba) + make_modrm_sib(oper0, reg_bits{ 6 }) + make_imm(oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) btc(oper0_t const& oper0, details::imm8_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xba) + make_modrm_sib(oper0, reg_bits{ 7 }) + make_imm(oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) btc(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xbb) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) bsf(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xbc) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_m16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) bsr(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xbd) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_64_v<oper0_t> and details::is_rm8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movsx(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xbe) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r16_32_v<oper0_t> and details::is_rm16_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movsx(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xbf) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm8_v<oper0_t> and details::is_r8_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xadd(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xc0) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_rm16_32_64_v<oper0_t> and details::is_r16_32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) xadd(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_oper_size_prefix(oper1) + make_address_size_prefix(oper0) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xc1) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmpps(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xc2) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmpss(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xc2) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmppd(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xc2) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmpsd(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xc2) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m32_64_v<oper0_t> and details::is_r32_64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movnti(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; static_assert(is_same_oper_size_v<oper0_t, oper1_t>); return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_oper_size_prefix(oper1) + make_rex(oper0, oper1) + make_static_bytecode(0x0f, 0xc3) + make_modrm_sib(oper0, oper1) }; }

    template<class oper1_t, std::enable_if_t<details::is_r32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pinsrw(details::mm oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_rex(oper1) + make_static_bytecode(0x0f, 0xc4) + make_modrm_sib(oper0, oper1) + make_imm(oper2) }; }

    template<class oper1_t, std::enable_if_t<details::is_m16_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pinsrw(details::mm oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_rex(oper1) + make_static_bytecode(0x0f, 0xc4) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_r32_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pinsrw(oper0_t oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper1, oper0) + make_static_bytecode(0x0f, 0xc4) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m16_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pinsrw(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_rex(oper1) + make_static_bytecode(0x0f, 0xc4) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, std::enable_if_t<details::is_r32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pextrw(oper0_t oper0, details::mm oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_rex(oper0) + make_static_bytecode(0x0f, 0xc5) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pextrw(oper0_t oper0, oper1_t oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper1) + make_rex(oper0) + make_static_bytecode(0x0f, 0xc5) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shufps(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xc6) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) shufpd(oper0_t oper0, oper1_t const& oper1, details::imm8_t oper2) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xc6) + make_modrm_sib(oper1, oper0) + make_imm(oper2) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmpxchg8b(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xc7) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m128_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cmpxchg16b(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xc7) + make_modrm_sib(oper0, reg_bits{ 1 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) vmptrld(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xc7) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) vmclear(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xc7) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) vmxon(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_static_bytecode(0xf3) + make_rex(oper0) + make_static_bytecode(0x0f, 0xc7) + make_modrm_sib(oper0, reg_bits{ 6 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) vmptrst(oper0_t const& oper0) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex(oper0) + make_static_bytecode(0x0f, 0xc7) + make_modrm_sib(oper0, reg_bits{ 7 }) }; }

    template<class oper0_t, std::enable_if_t<details::is_r32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) bswap(oper0_t r) noexcept { using namespace details; auto opcode = make_static_bytecode(0x0f, 0xc8); opcode.at(opcode.size() - 1) += r.n(); return instruct{ std::move(opcode) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) addsubpd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd0) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) addsubps(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd0) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrlw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xd1) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrlw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd1) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrld(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xd2) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrld(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd2) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrlq(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xd3) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrlq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd3) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddq(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xd4) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd4) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmullw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xd5) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmullw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd5) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m64_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movq(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_oper_size_prefix(oper1) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0xd6) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, std::enable_if_t<details::is_xmm_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movq2dq(oper0_t oper0, details::mm oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper0) + make_static_bytecode(0xf3) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0xd6) + make_modrm_sib(oper0, oper1) }; }

    template<class oper1_t, std::enable_if_t<details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movdq2q(details::mm oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd6) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, std::enable_if_t<details::is_r32_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovmskb(oper0_t oper0, details::mm oper1) noexcept { using namespace details; return instruct{ make_rex(oper0) + make_static_bytecode(0x0f, 0xd7) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_r32_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmovmskb(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_oper_size_prefix(oper1) + make_rex(oper1) + make_static_bytecode(0x0f, 0xd7) + make_modrm_sib(oper0, oper1) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubusb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xd8) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubusb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd8) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubusw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xd9) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubusw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xd9) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pminub(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xda) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pminub(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xda) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pand(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xdb) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pand(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xdb) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddusb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xdc) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddusb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xdc) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddusw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xdd) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddusw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xdd) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaxub(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xde) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaxub(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xde) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pandn(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xdf) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pandn(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xdf) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pavgb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xe0) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pavgb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe0) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psraw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xe1) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psraw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe1) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrad(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xe2) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psrad(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe2) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pavgw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xe3) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pavgw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe3) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmulhuw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xe4) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmulhuw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe4) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmulhw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xe5) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmulhw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe5) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtpd2dq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe6) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvttpd2dq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe6) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) cvtdq2pd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf3) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe6) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, std::enable_if_t<details::is_m64_v<oper0_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movntq(oper0_t const& oper0, details::mm oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_rex_w(oper0) + make_static_bytecode(0x0f, 0xe7) + make_modrm_sib(oper0, oper1) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_m128_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) movntdq(oper0_t const& oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper0) + make_address_size_prefix(oper0) + make_oper_size_prefix(oper1) + make_rex_w(oper0, oper1) + make_static_bytecode(0x0f, 0xe7) + make_modrm_sib(oper0, oper1) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubsb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xe8) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubsb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe8) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubsw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xe9) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubsw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xe9) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pminsw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xea) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pminsw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xea) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) por(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xeb) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) por(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xeb) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddsb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xec) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddsb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xec) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddsw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xed) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddsw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xed) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaxsw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xee) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaxsw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xee) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pxor(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xef) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pxor(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xef) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_m128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) lddqu(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_address_size_prefix(oper1) + make_static_bytecode(0xf2) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf0) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psllw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xf1) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psllw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf1) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pslld(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xf2) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pslld(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf2) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psllq(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xf3) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psllq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf3) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmuludq(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xf4) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmuludq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf4) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaddwd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xf5) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) pmaddwd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf5) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psadbw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xf6) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psadbw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf6) + make_modrm_sib(oper1, oper0) }; }

    constexpr decltype(auto) maskmovq(details::mm oper0, details::mm oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x0f, 0xf7) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmm_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) maskmovdqu(oper0_t oper0, oper1_t oper1) noexcept { using namespace details; return instruct{ make_static_bytecode(0x66) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf7) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xf8) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf8) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xf9) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xf9) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xfa) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xfa) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubq(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xfb) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) psubq(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xfb) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddb(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xfc) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddb(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xfc) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddw(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xfd) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddw(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xfd) + make_modrm_sib(oper1, oper0) }; }

    template<class oper1_t, std::enable_if_t<details::is_mmm64_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddd(details::mm oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_static_bytecode(0x0f, 0xfe) + make_modrm_sib(oper1, oper0) }; }

    template<class oper0_t, class oper1_t, std::enable_if_t<details::is_xmm_v<oper0_t> and details::is_xmmm128_v<oper1_t>, std::nullptr_t> = nullptr> constexpr decltype(auto) paddd(oper0_t oper0, oper1_t const& oper1) noexcept { using namespace details; return instruct{ make_segment_prefix(oper1) + make_oper_size_prefix(oper0) + make_address_size_prefix(oper1) + make_rex_w(oper1, oper0) + make_static_bytecode(0x0f, 0xfe) + make_modrm_sib(oper1, oper0) }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jo(t label) noexcept { return details::rel_instruct{ label, &jo, &jo }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jno(t label) noexcept { return details::rel_instruct{ label, &jno, &jno }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jb(t label) noexcept { return details::rel_instruct{ label, &jb, &jb }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jnae(t label) noexcept { return details::rel_instruct{ label, &jnae, &jnae }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jc(t label) noexcept { return details::rel_instruct{ label, &jc, &jc }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jnb(t label) noexcept { return details::rel_instruct{ label, &jnb, &jnb }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jae(t label) noexcept { return details::rel_instruct{ label, &jae, &jae }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jnc(t label) noexcept { return details::rel_instruct{ label, &jnc, &jnc }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jz(t label) noexcept { return details::rel_instruct{ label, &jz, &jz }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) je(t label) noexcept { return details::rel_instruct{ label, &je, &je }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jnz(t label) noexcept { return details::rel_instruct{ label, &jnz, &jnz }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jne(t label) noexcept { return details::rel_instruct{ label, &jne, &jne }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jbe(t label) noexcept { return details::rel_instruct{ label, &jbe, &jbe }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jna(t label) noexcept { return details::rel_instruct{ label, &jna, &jna }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jnbe(t label) noexcept { return details::rel_instruct{ label, &jnbe, &jnbe }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) ja(t label) noexcept { return details::rel_instruct{ label, &ja, &ja }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) js(t label) noexcept { return details::rel_instruct{ label, &js, &js }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jns(t label) noexcept { return details::rel_instruct{ label, &jns, &jns }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jp(t label) noexcept { return details::rel_instruct{ label, &jp, &jp }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jpe(t label) noexcept { return details::rel_instruct{ label, &jpe, &jpe }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jnp(t label) noexcept { return details::rel_instruct{ label, &jnp, &jnp }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jpo(t label) noexcept { return details::rel_instruct{ label, &jpo, &jpo }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jl(t label) noexcept { return details::rel_instruct{ label, &jl, &jl }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jnge(t label) noexcept { return details::rel_instruct{ label, &jnge, &jnge }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jnl(t label) noexcept { return details::rel_instruct{ label, &jnl, &jnl }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jge(t label) noexcept { return details::rel_instruct{ label, &jge, &jge }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jle(t label) noexcept { return details::rel_instruct{ label, &jle, &jle }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jng(t label) noexcept { return details::rel_instruct{ label, &jng, &jng }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jnle(t label) noexcept { return details::rel_instruct{ label, &jnle, &jnle }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jg(t label) noexcept { return details::rel_instruct{ label, &jg, &jg }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) jmp(t label) noexcept { return details::rel_instruct{ label, &jmp, &jmp }; }

    template<typename t, std::enable_if_t<details::is_label_v<t>, std::nullptr_t> = nullptr>  decltype(auto) call(t label) noexcept { return details::rel_instruct{ label, &call }; }

    class assembler
    {
    public:
        using bytecode_t = std::vector<details::byte_t>;

    private:
        class mnemonic_code
        {
        public:
            template<class... ts>
            constexpr mnemonic_code(std::tuple<ts...>&& mnemonics) noexcept
            {
                for (std::size_t i = 0; i < std::tuple_size_v<std::decay_t<decltype(mnemonics)>>; ++ i)
                {
                    details::visit_at(mnemonics, i, [i, this](auto&& mnemonic) mutable
                        {
                            if constexpr (details::is_label_v<decltype(mnemonic)>)
                            {
                                this->label_by_id_.emplace(mnemonic.id(), this->label_by_address_.emplace(this->size_).first);
                            }
                            else if constexpr (details::is_instruct_v<decltype(mnemonic)>)
                            {
                                this->size_ += mnemonic.bytecode().size();
                            }
                            else if constexpr (details::is_rel_instruct_v<decltype(mnemonic)>)
                            {
                                this->size_ += mnemonic.size();

                                this->rel_instruction_by_address_.emplace(this->size_, &mnemonic);
                            }
                        });
                }
            }

            auto& label_by_address() noexcept
            {
                return this->label_by_address_;
            }

            auto& label_by_id() noexcept
            {
                return this->label_by_id_;
            }

            auto& rel_instruction_by_address() noexcept
            {
                return this->rel_instruction_by_address_;
            }

            auto size() const noexcept
            {
                return this->size_;
            }

            void resize(std::size_t size) noexcept
            {
                this->size_ = size;
            }

        private:
            using code_address_t = std::size_t;

            std::set<code_address_t> label_by_address_;
            std::map<details::base_label::id_t, decltype(label_by_address_)::iterator> label_by_id_;

            std::map<code_address_t, details::rel_instruct*> rel_instruction_by_address_;

            std::size_t size_;
        };

        static constexpr const std::size_t pass_n = 2;

        void transcode_rel_instructions(mnemonic_code& code) const
        {
            if (code.rel_instruction_by_address().empty())
            {
                return;
            }

            for (std::size_t pass_counter = 0; pass_counter < pass_n; ++ pass_counter)
            {
                for (auto i = code.rel_instruction_by_address().begin(); i not_eq code.rel_instruction_by_address().end();)
                {
                    std::size_t last_size = i->second->size();

                    auto label_id = i->second->target_label().id();

                    details::imm32_t rel{ static_cast<details::imm32_t>(*code.label_by_id().at(label_id) - i->first) };

                    std::size_t new_size;

                    if (std::abs(rel) > (std::numeric_limits<details::imm8_t>::max)())
                    {
                        new_size = i->second->operator()(details::imm32_t{ rel }).size();
                    }
                    else
                    {
                        new_size = i->second->operator()(static_cast<details::imm8_t>(rel)).size();
                    }

                    i->second->resize(new_size);

                    i->second->rel() = rel;

                    auto difference = last_size - new_size;

                    for (auto next_label_iterator = code.label_by_address().lower_bound(i->first); next_label_iterator not_eq code.label_by_address().end(); ++ next_label_iterator)
                    {
                        auto new_label_address = code.label_by_address().extract(next_label_iterator);
                        new_label_address.value() -= difference;
                        code.label_by_address().insert(std::move(new_label_address));
                    }

                    for (auto next_instruction_iterator = code.rel_instruction_by_address().lower_bound(i->first); next_instruction_iterator not_eq code.rel_instruction_by_address().end();)
                    {
                        ++ i;
                        auto new_instruction_address = code.rel_instruction_by_address().extract(next_instruction_iterator ++);
                        new_instruction_address.key() -= difference;
                        code.rel_instruction_by_address().insert(std::move(new_instruction_address));
                    }

                    code.resize(code.size() - difference);
                }
            }
        }

    public:
        template<template<class...> class tuple_t, class... ts>
        constexpr assembler(tuple_t<ts...>&& mnemonics) noexcept
        {
            mnemonic_code code{ std::forward<tuple_t<ts...>>(mnemonics) };

            this->transcode_rel_instructions(code);

            auto rel_instruction_iterator = code.rel_instruction_by_address().begin();

            for (std::size_t i = 0; i < std::tuple_size_v<std::decay_t<decltype(mnemonics)>>; ++ i)
            {
                details::visit_at(mnemonics, i, [i, this, &rel_instruction_iterator](auto&& mnemonic) mutable
                    {
                        if constexpr (details::is_instruct_v<decltype(mnemonic)>)
                        {
                            std::copy(mnemonic.bytecode().begin(), mnemonic.bytecode().end(), std::back_inserter(this->bytecode()));
                        }
                        else if constexpr (details::is_rel_instruct_v<decltype(mnemonic)>)
                        {
                            if (std::abs(rel_instruction_iterator->second->rel()) > (std::numeric_limits<details::imm8_t>::max)())
                            {
                                auto rel_instruction_bytecode = rel_instruction_iterator->second->operator()(details::imm32_t{ rel_instruction_iterator->second->rel() });
                                std::copy(rel_instruction_bytecode.begin(), rel_instruction_bytecode.end(), std::back_inserter(this->bytecode()));
                            }
                            else
                            {
                                auto rel_instruction_bytecode = rel_instruction_iterator->second->operator()(static_cast<details::imm8_t>(rel_instruction_iterator->second->rel()));
                                std::copy(rel_instruction_bytecode.begin(), rel_instruction_bytecode.end(), std::back_inserter(this->bytecode()));
                            }

                            ++ rel_instruction_iterator;
                        }
                    });
            }
        }

        template<class... ts>
        assembler(ts&&... vs) noexcept
            : assembler{ std::tuple{ std::forward<ts>(vs)... } }
        { }

        auto& bytecode() & noexcept
        {
            return this->bytecode_;
        }

        auto const& bytecode() const& noexcept
        {
            return this->bytecode_;
        }

        auto&& bytecode() && noexcept
        {
            return std::move(this->bytecode_);
        }

        bytecode_t bytecode_;
    };

#ifndef __APPLE__
    class f
    {
    public:
        template<class bytecode_t, std::enable_if_t<details::is_bytecode_v<bytecode_t>, std::nullptr_t> = nullptr>
        f(bytecode_t&& bytecode)
        {
            this->size_ = bytecode.size();

#ifdef CASM_WINDOWS
            this->pointer_ = VirtualAlloc(NULL, this->size_, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
#else
            this->pointer_ = mmap(NULL, this->size_, PROT_EXEC bitor PROT_READ bitor PROT_WRITE, MAP_PRIVATE bitor MAP_ANONYMOUS, 0, 0);
#endif

            if (this->pointer_ not_eq nullptr)
            {
                std::memcpy(this->pointer_, bytecode.data(), this->size_);
            }
            else
            {
                throw std::bad_alloc{};
            }
        }

        template<class... ts>
        f(ts&&... vs)
            : f{ assembler{ std::tuple{ std::forward<ts>(vs)..., ret() } }.bytecode() }
        { }

        void operator()() const noexcept
        {
            reinterpret_cast<void(*)()>(this->pointer_)();
        }

        ~f() noexcept
        {
#ifdef CASM_WINDOWS
            VirtualFree(this->pointer_, 0, MEM_RELEASE);
#else
            munmap(this->pointer_, this->size_);
#endif

#undef CASM_WINDOWS
        }

    private:
        void* pointer_;
        std::size_t size_;
    };
#endif
}

#endif