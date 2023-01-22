#include "casm.hpp"

#include <gtest/gtest.h>

#include <cstring>

using namespace casm;

extern "C" void nasm_add_rm8_r8_instruction();

TEST(NASMBytecode, add_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			add(dl, ah),
			add(r9b, al),
			add(al, r11b),
			add(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			add(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			add(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			add(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			add(byte_ptr [rdx + rdx * 8], al),
			add(byte_ptr [rdx + rdx * 8], spl),
			add(byte_ptr [r11 + rdx * 8], dil),
			add(byte_ptr [edx + r11d * 8], r8b),
			add(byte_ptr [r11d], bl),
			add(byte_ptr [rdx], bpl),
			add(byte_ptr [r11d * 4], bl),
			add(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_add_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_add_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, add_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			add(dx, ax),
			add(edx, eax),
			add(rdx, rax),
			add(word[ebx * 4], dx),
			add(dword[ebx * 4], edx),
			add(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_add_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_add_r8_rm8_instruction();

TEST(NASMBytecode, add_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			add(al, dl),
			add(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_add_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_add_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, add_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			add(cx, word[r11 + rbx]),
			add(ebx, dword[r11 + rbx]),
			add(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_add_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_add_al_imm8_instruction();

TEST(NASMBytecode, add_al_imm8_instruction_test)
{
	const auto casm_bytecode{ add(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_add_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_add_ax_eax_rax_imm16_32_instruction();

TEST(NASMBytecode, add_ax_eax_rax_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			add(ax, 0x8888_w),
			add(eax, 0x88888888_d),
			add(rax, 0x88888888_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_add_ax_eax_rax_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_or_rm8_r8_instruction();

TEST(NASMBytecode, or_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			or_(dl, ah),
			or_(r9b, al),
			or_(al, r11b),
			or_(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			or_(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			or_(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			or_(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			or_(byte_ptr [rdx + rdx * 8], al),
			or_(byte_ptr [rdx + rdx * 8], spl),
			or_(byte_ptr [r11 + rdx * 8], dil),
			or_(byte_ptr [edx + r11d * 8], r8b),
			or_(byte_ptr [r11d], bl),
			or_(byte_ptr [rdx], bpl),
			or_(byte_ptr [r11d * 4], bl),
			or_(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_or_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_or_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, or_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			or_(dx, ax),
			or_(edx, eax),
			or_(rdx, rax),
			or_(word[ebx * 4], dx),
			or_(dword[ebx * 4], edx),
			or_(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_or_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_or_r8_rm8_instruction();

TEST(NASMBytecode, or_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			or_(al, dl),
			or_(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_or_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_or_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, or_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			or_(cx, word[r11 + rbx]),
			or_(ebx, dword[r11 + rbx]),
			or_(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_or_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_or_al_imm8_instruction();

TEST(NASMBytecode, or_al_imm8_instruction_test)
{
	const auto casm_bytecode{ or_(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_or_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_or_ax_eax_rax_imm16_32_instruction();

TEST(NASMBytecode, or_ax_eax_rax_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			or_(ax, 0x8888_w),
			or_(eax, 0x88888888_d),
			or_(rax, 0x88888888_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_or_ax_eax_rax_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_adc_rm8_r8_instruction();

TEST(NASMBytecode, adc_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			adc(dl, ah),
			adc(r9b, al),
			adc(al, r11b),
			adc(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			adc(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			adc(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			adc(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			adc(byte_ptr [rdx + rdx * 8], al),
			adc(byte_ptr [rdx + rdx * 8], spl),
			adc(byte_ptr [r11 + rdx * 8], dil),
			adc(byte_ptr [edx + r11d * 8], r8b),
			adc(byte_ptr [r11d], bl),
			adc(byte_ptr [rdx], bpl),
			adc(byte_ptr [r11d * 4], bl),
			adc(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_adc_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_adc_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, adc_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			adc(dx, ax),
			adc(edx, eax),
			adc(rdx, rax),
			adc(word[ebx * 4], dx),
			adc(dword[ebx * 4], edx),
			adc(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_adc_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_adc_r8_rm8_instruction();

TEST(NASMBytecode, adc_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			adc(al, dl),
			adc(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_adc_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_adc_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, adc_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			adc(cx, word[r11 + rbx]),
			adc(ebx, dword[r11 + rbx]),
			adc(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_adc_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_adc_al_imm8_instruction();

TEST(NASMBytecode, adc_al_imm8_instruction_test)
{
	const auto casm_bytecode{ adc(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_adc_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_adc_ax_eax_rax_imm16_32_instruction();

TEST(NASMBytecode, adc_ax_eax_rax_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			adc(ax, 0x8888_w),
			adc(eax, 0x88888888_d),
			adc(rax, 0x88888888_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_adc_ax_eax_rax_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sbb_rm8_r8_instruction();

TEST(NASMBytecode, sbb_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sbb(dl, ah),
			sbb(r9b, al),
			sbb(al, r11b),
			sbb(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			sbb(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			sbb(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			sbb(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			sbb(byte_ptr [rdx + rdx * 8], al),
			sbb(byte_ptr [rdx + rdx * 8], spl),
			sbb(byte_ptr [r11 + rdx * 8], dil),
			sbb(byte_ptr [edx + r11d * 8], r8b),
			sbb(byte_ptr [r11d], bl),
			sbb(byte_ptr [rdx], bpl),
			sbb(byte_ptr [r11d * 4], bl),
			sbb(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sbb_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sbb_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, sbb_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sbb(dx, ax),
			sbb(edx, eax),
			sbb(rdx, rax),
			sbb(word[ebx * 4], dx),
			sbb(dword[ebx * 4], edx),
			sbb(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sbb_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sbb_r8_rm8_instruction();

TEST(NASMBytecode, sbb_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sbb(al, dl),
			sbb(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sbb_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sbb_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, sbb_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sbb(cx, word[r11 + rbx]),
			sbb(ebx, dword[r11 + rbx]),
			sbb(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sbb_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sbb_al_imm8_instruction();

TEST(NASMBytecode, sbb_al_imm8_instruction_test)
{
	const auto casm_bytecode{ sbb(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sbb_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sbb_ax_eax_rax_imm16_32_instruction();

TEST(NASMBytecode, sbb_ax_eax_rax_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sbb(ax, 0x8888_w),
			sbb(eax, 0x88888888_d),
			sbb(rax, 0x88888888_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sbb_ax_eax_rax_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_and_rm8_r8_instruction();

TEST(NASMBytecode, and_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			and_(dl, ah),
			and_(r9b, al),
			and_(al, r11b),
			and_(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			and_(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			and_(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			and_(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			and_(byte_ptr [rdx + rdx * 8], al),
			and_(byte_ptr [rdx + rdx * 8], spl),
			and_(byte_ptr [r11 + rdx * 8], dil),
			and_(byte_ptr [edx + r11d * 8], r8b),
			and_(byte_ptr [r11d], bl),
			and_(byte_ptr [rdx], bpl),
			and_(byte_ptr [r11d * 4], bl),
			and_(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_and_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_and_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, and_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			and_(dx, ax),
			and_(edx, eax),
			and_(rdx, rax),
			and_(word[ebx * 4], dx),
			and_(dword[ebx * 4], edx),
			and_(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_and_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_and_r8_rm8_instruction();

TEST(NASMBytecode, and_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			and_(al, dl),
			and_(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_and_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_and_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, and_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			and_(cx, word[r11 + rbx]),
			and_(ebx, dword[r11 + rbx]),
			and_(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_and_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_and_al_imm8_instruction();

TEST(NASMBytecode, and_al_imm8_instruction_test)
{
	const auto casm_bytecode{ and_(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_and_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_and_ax_eax_rax_imm16_32_instruction();

TEST(NASMBytecode, and_ax_eax_rax_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			and_(ax, 0x8888_w),
			and_(eax, 0x88888888_d),
			and_(rax, 0x88888888_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_and_ax_eax_rax_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sub_rm8_r8_instruction();

TEST(NASMBytecode, sub_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sub(dl, ah),
			sub(r9b, al),
			sub(al, r11b),
			sub(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			sub(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			sub(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			sub(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			sub(byte_ptr [rdx + rdx * 8], al),
			sub(byte_ptr [rdx + rdx * 8], spl),
			sub(byte_ptr [r11 + rdx * 8], dil),
			sub(byte_ptr [edx + r11d * 8], r8b),
			sub(byte_ptr [r11d], bl),
			sub(byte_ptr [rdx], bpl),
			sub(byte_ptr [r11d * 4], bl),
			sub(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sub_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sub_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, sub_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sub(dx, ax),
			sub(edx, eax),
			sub(rdx, rax),
			sub(word[ebx * 4], dx),
			sub(dword[ebx * 4], edx),
			sub(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sub_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sub_r8_rm8_instruction();

TEST(NASMBytecode, sub_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sub(al, dl),
			sub(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sub_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sub_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, sub_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sub(cx, word[r11 + rbx]),
			sub(ebx, dword[r11 + rbx]),
			sub(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sub_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sub_al_imm8_instruction();

TEST(NASMBytecode, sub_al_imm8_instruction_test)
{
	const auto casm_bytecode{ sub(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sub_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sub_ax_eax_rax_imm16_32_instruction();

TEST(NASMBytecode, sub_ax_eax_rax_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sub(ax, 0x8888_w),
			sub(eax, 0x88888888_d),
			sub(rax, 0x88888888_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sub_ax_eax_rax_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xor_rm8_r8_instruction();

TEST(NASMBytecode, xor_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xor_(dl, ah),
			xor_(r9b, al),
			xor_(al, r11b),
			xor_(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			xor_(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			xor_(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			xor_(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			xor_(byte_ptr [rdx + rdx * 8], al),
			xor_(byte_ptr [rdx + rdx * 8], spl),
			xor_(byte_ptr [r11 + rdx * 8], dil),
			xor_(byte_ptr [edx + r11d * 8], r8b),
			xor_(byte_ptr [r11d], bl),
			xor_(byte_ptr [rdx], bpl),
			xor_(byte_ptr [r11d * 4], bl),
			xor_(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xor_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xor_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, xor_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xor_(dx, ax),
			xor_(edx, eax),
			xor_(rdx, rax),
			xor_(word[ebx * 4], dx),
			xor_(dword[ebx * 4], edx),
			xor_(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xor_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xor_r8_rm8_instruction();

TEST(NASMBytecode, xor_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xor_(al, dl),
			xor_(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xor_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xor_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, xor_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xor_(cx, word[r11 + rbx]),
			xor_(ebx, dword[r11 + rbx]),
			xor_(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xor_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xor_al_imm8_instruction();

TEST(NASMBytecode, xor_al_imm8_instruction_test)
{
	const auto casm_bytecode{ xor_(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xor_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xor_ax_eax_rax_imm16_32_instruction();

TEST(NASMBytecode, xor_ax_eax_rax_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xor_(ax, 0x8888_w),
			xor_(eax, 0x88888888_d),
			xor_(rax, 0x88888888_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xor_ax_eax_rax_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmp_rm8_r8_instruction();

TEST(NASMBytecode, cmp_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmp(dl, ah),
			cmp(r9b, al),
			cmp(al, r11b),
			cmp(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			cmp(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			cmp(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			cmp(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			cmp(byte_ptr [rdx + rdx * 8], al),
			cmp(byte_ptr [rdx + rdx * 8], spl),
			cmp(byte_ptr [r11 + rdx * 8], dil),
			cmp(byte_ptr [edx + r11d * 8], r8b),
			cmp(byte_ptr [r11d], bl),
			cmp(byte_ptr [rdx], bpl),
			cmp(byte_ptr [r11d * 4], bl),
			cmp(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmp_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmp_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, cmp_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmp(dx, ax),
			cmp(edx, eax),
			cmp(rdx, rax),
			cmp(word[ebx * 4], dx),
			cmp(dword[ebx * 4], edx),
			cmp(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmp_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmp_r8_rm8_instruction();

TEST(NASMBytecode, cmp_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmp(al, dl),
			cmp(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmp_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmp_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmp_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmp(cx, word[r11 + rbx]),
			cmp(ebx, dword[r11 + rbx]),
			cmp(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmp_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmp_al_imm8_instruction();

TEST(NASMBytecode, cmp_al_imm8_instruction_test)
{
	const auto casm_bytecode{ cmp(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmp_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmp_ax_eax_rax_imm16_32_instruction();

TEST(NASMBytecode, cmp_ax_eax_rax_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmp(ax, 0x8888_w),
			cmp(eax, 0x88888888_d),
			cmp(rax, 0x88888888_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmp_ax_eax_rax_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_push_r16_64_instruction_by_register();

TEST(NASMBytecode, push_r16_64_instruction_by_register_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			push(ax),
			push(cx),
			push(dx),
			push(bx),
			push(sp),
			push(bp),
			push(si),
			push(di),
			push(rax),
			push(rcx),
			push(rdx),
			push(rbx),
			push(rsp),
			push(rbp),
			push(rsi),
			push(rdi),
			push(r8),
			push(r12)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_push_r16_64_instruction_by_register), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pop_r16_64_instruction_by_register();

TEST(NASMBytecode, pop_r16_64_instruction_by_register_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pop(ax),
			pop(cx),
			pop(dx),
			pop(bx),
			pop(sp),
			pop(bp),
			pop(si),
			pop(di),
			pop(rax),
			pop(rcx),
			pop(rdx),
			pop(rbx),
			pop(rsp),
			pop(rbp),
			pop(rsi),
			pop(rdi),
			pop(r8),
			pop(r12)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pop_r16_64_instruction_by_register), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsxd_r32_64_rm32_instruction();

TEST(NASMBytecode, movsxd_r32_64_rm32_instruction_test)
{
	const auto casm_bytecode{ movsxd(rdx, ecx).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsxd_r32_64_rm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_push_imm32_instruction();

TEST(NASMBytecode, push_imm32_instruction_test)
{
	const auto casm_bytecode{ push(0x11113333_d).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_push_imm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_imul_r16_32_64_rm16_32_64_imm16_32_instruction();

TEST(NASMBytecode, imul_r16_32_64_rm16_32_64_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			imul(bx, cx, 0x44_b),
			imul(ebx, ecx, 0x4444_d),
			imul(rbx, rcx, 0x44444444_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_imul_r16_32_64_rm16_32_64_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_push_imm8_instruction();

TEST(NASMBytecode, push_imm8_instruction_test)
{
	const auto casm_bytecode{ push(0x11_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_push_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_imul_r16_32_64_rm16_32_64_imm8_instruction();

TEST(NASMBytecode, imul_r16_32_64_rm16_32_64_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			imul(bx, cx, 0x44_b),
			imul(ebx, ecx, 0x44_b),
			imul(rbx, rcx, 0x44_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_imul_r16_32_64_rm16_32_64_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ins_no_operands_instruction();

TEST(NASMBytecode, ins_no_operands_instruction_test)
{
	const auto casm_bytecode{ ins().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ins_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_insb_no_operands_instruction();

TEST(NASMBytecode, insb_no_operands_instruction_test)
{
	const auto casm_bytecode{ insb().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_insb_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_insw_no_operands_instruction();

TEST(NASMBytecode, insw_no_operands_instruction_test)
{
	const auto casm_bytecode{ insw().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_insw_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_insd_no_operands_instruction();

TEST(NASMBytecode, insd_no_operands_instruction_test)
{
	const auto casm_bytecode{ insd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_insd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_outsb_no_operands_instruction();

TEST(NASMBytecode, outsb_no_operands_instruction_test)
{
	const auto casm_bytecode{ outsb().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_outsb_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_outsw_no_operands_instruction();

TEST(NASMBytecode, outsw_no_operands_instruction_test)
{
	const auto casm_bytecode{ outsw().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_outsw_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_outsd_no_operands_instruction();

TEST(NASMBytecode, outsd_no_operands_instruction_test)
{
	const auto casm_bytecode{ outsd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_outsd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_add_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, add_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			add(byte_ptr [ebx], 11_b),
			add(dl, 11_b),
			add(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_add_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_or_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, or_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			or_(byte_ptr [ebx], 11_b),
			or_(dl, 11_b),
			or_(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_or_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_adc_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, adc_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			adc(byte_ptr [ebx], 11_b),
			adc(dl, 11_b),
			adc(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_adc_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sbb_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, sbb_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sbb(byte_ptr [ebx], 11_b),
			sbb(dl, 11_b),
			sbb(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sbb_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_and_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, and_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			and_(byte_ptr [ebx], 11_b),
			and_(dl, 11_b),
			and_(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_and_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sub_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, sub_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sub(byte_ptr [ebx], 11_b),
			sub(dl, 11_b),
			sub(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sub_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xor_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, xor_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xor_(byte_ptr [ebx], 11_b),
			xor_(dl, 11_b),
			xor_(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xor_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmp_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, cmp_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmp(byte_ptr [ebx], 11_b),
			cmp(dl, 11_b),
			cmp(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmp_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_add_rm16_32_imm16_32_instruction_by_number();

TEST(NASMBytecode, add_rm16_32_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			add(dx, 0x1111_w),
			add(edx, 0x113333_d),
			add(word[ebx * 4], 0x1111_w),
			add(dword[ebx * 4], 0x113333_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_add_rm16_32_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_or_rm16_32_imm16_32_instruction_by_number();

TEST(NASMBytecode, or_rm16_32_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			or_(dx, 0x1111_w),
			or_(edx, 0x113333_d),
			or_(word[ebx * 4], 0x1111_w),
			or_(dword[ebx * 4], 0x113333_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_or_rm16_32_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_adc_rm16_32_imm16_32_instruction_by_number();

TEST(NASMBytecode, adc_rm16_32_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			adc(dx, 0x1111_w),
			adc(edx, 0x113333_d),
			adc(word[ebx * 4], 0x1111_w),
			adc(dword[ebx * 4], 0x113333_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_adc_rm16_32_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sbb_rm16_32_imm16_32_instruction_by_number();

TEST(NASMBytecode, sbb_rm16_32_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sbb(dx, 0x1111_w),
			sbb(edx, 0x113333_d),
			sbb(word[ebx * 4], 0x1111_w),
			sbb(dword[ebx * 4], 0x113333_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sbb_rm16_32_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_and_rm16_32_imm16_32_instruction_by_number();

TEST(NASMBytecode, and_rm16_32_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			and_(dx, 0x1111_w),
			and_(edx, 0x113333_d),
			and_(word[ebx * 4], 0x1111_w),
			and_(dword[ebx * 4], 0x113333_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_and_rm16_32_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sub_rm16_32_imm16_32_instruction_by_number();

TEST(NASMBytecode, sub_rm16_32_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sub(dx, 0x1111_w),
			sub(edx, 0x113333_d),
			sub(word[ebx * 4], 0x1111_w),
			sub(dword[ebx * 4], 0x113333_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sub_rm16_32_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xor_rm16_32_imm16_32_instruction_by_number();

TEST(NASMBytecode, xor_rm16_32_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xor_(dx, 0x1111_w),
			xor_(edx, 0x113333_d),
			xor_(word[ebx * 4], 0x1111_w),
			xor_(dword[ebx * 4], 0x113333_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xor_rm16_32_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmp_rm16_32_imm16_32_instruction_by_number();

TEST(NASMBytecode, cmp_rm16_32_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmp(dx, 0x1111_w),
			cmp(edx, 0x113333_d),
			cmp(word[ebx * 4], 0x1111_w),
			cmp(dword[ebx * 4], 0x113333_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmp_rm16_32_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_add_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, add_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			add(dx, 0x11_b),
			add(edx, 0x11_b),
			add(word[ebx * 4], 0x11_b),
			add(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_add_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_or_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, or_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			or_(dx, 0x11_b),
			or_(edx, 0x11_b),
			or_(word[ebx * 4], 0x11_b),
			or_(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_or_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_adc_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, adc_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			adc(dx, 0x11_b),
			adc(edx, 0x11_b),
			adc(word[ebx * 4], 0x11_b),
			adc(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_adc_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sbb_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, sbb_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sbb(dx, 0x11_b),
			sbb(edx, 0x11_b),
			sbb(word[ebx * 4], 0x11_b),
			sbb(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sbb_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_and_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, and_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			and_(dx, 0x11_b),
			and_(edx, 0x11_b),
			and_(word[ebx * 4], 0x11_b),
			and_(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_and_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sub_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, sub_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sub(dx, 0x11_b),
			sub(edx, 0x11_b),
			sub(word[ebx * 4], 0x11_b),
			sub(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sub_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xor_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, xor_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xor_(dx, 0x11_b),
			xor_(edx, 0x11_b),
			xor_(word[ebx * 4], 0x11_b),
			xor_(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xor_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmp_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, cmp_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmp(dx, 0x11_b),
			cmp(edx, 0x11_b),
			cmp(word[ebx * 4], 0x11_b),
			cmp(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmp_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_test_rm8_r8_instruction();

TEST(NASMBytecode, test_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			test(dl, ah),
			test(r9b, al),
			test(al, r11b),
			test(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			test(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			test(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			test(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			test(byte_ptr [rdx + rdx * 8], al),
			test(byte_ptr [rdx + rdx * 8], spl),
			test(byte_ptr [r11 + rdx * 8], dil),
			test(byte_ptr [edx + r11d * 8], r8b),
			test(byte_ptr [r11d], bl),
			test(byte_ptr [rdx], bpl),
			test(byte_ptr [r11d * 4], bl),
			test(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_test_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_test_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, test_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			test(dx, ax),
			test(edx, eax),
			test(rdx, rax),
			test(word[ebx * 4], dx),
			test(dword[ebx * 4], edx),
			test(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_test_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xchg_r8_rm8_instruction();

TEST(NASMBytecode, xchg_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xchg(al, dl),
			xchg(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xchg_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xchg_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, xchg_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xchg(cx, word[r11 + rbx]),
			xchg(ebx, dword[r11 + rbx]),
			xchg(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xchg_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_rm8_r8_instruction();

TEST(NASMBytecode, mov_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(dl, ah),
			mov(r9b, al),
			mov(al, r11b),
			mov(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			mov(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			mov(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			mov(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			mov(byte_ptr [rdx + rdx * 8], al),
			mov(byte_ptr [rdx + rdx * 8], spl),
			mov(byte_ptr [r11 + rdx * 8], dil),
			mov(byte_ptr [edx + r11d * 8], r8b),
			mov(byte_ptr [r11d], bl),
			mov(byte_ptr [rdx], bpl),
			mov(byte_ptr [r11d * 4], bl),
			mov(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, mov_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(dx, ax),
			mov(edx, eax),
			mov(rdx, rax),
			mov(word[ebx * 4], dx),
			mov(dword[ebx * 4], edx),
			mov(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_r8_rm8_instruction();

TEST(NASMBytecode, mov_r8_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(al, dl),
			mov(dl, byte_ptr [rax + rax * 8 + 0x11111111_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_r8_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, mov_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(cx, word[r11 + rbx]),
			mov(ebx, dword[r11 + rbx]),
			mov(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_m16_sreg_instruction();

TEST(NASMBytecode, mov_m16_sreg_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(word[r11 + rbx * 8], gs),
			mov(word[r11 + rbx * 8], ds)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_m16_sreg_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_r16_32_64_sreg_instruction();

TEST(NASMBytecode, mov_r16_32_64_sreg_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(dx, ds),
			mov(edx, fs),
			mov(rdx, ss)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_r16_32_64_sreg_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lea_r16_32_64_m_instruction();

TEST(NASMBytecode, lea_r16_32_64_m_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lea(dx, ptr[r14d]),
			lea(edx, ptr[r14d]),
			lea(rdx, ptr[r14d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lea_r16_32_64_m_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_sreg_rm16_instruction();

TEST(NASMBytecode, mov_sreg_rm16_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(es, word [0x321_d]),
			mov(ds, ax)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_sreg_rm16_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pop_m16_64_instruction_by_number();

TEST(NASMBytecode, pop_m16_64_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pop(word[r11 + rbx * 8]),
			pop(qword[r11 + rbx * 8])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pop_m16_64_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xchg_r16_32_64_ax_eax_rax_instruction_by_register();

TEST(NASMBytecode, xchg_r16_32_64_ax_eax_rax_instruction_by_register_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xchg(dx, ax),
			xchg(edx, eax),
			xchg(rdx, rax)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xchg_r16_32_64_ax_eax_rax_instruction_by_register), casm_bytecode.size()) == 0);
};

extern "C" void nasm_nop_no_operands_instruction();

TEST(NASMBytecode, nop_no_operands_instruction_test)
{
	const auto casm_bytecode{ nop().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_nop_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pause_no_operands_instruction();

TEST(NASMBytecode, pause_no_operands_instruction_test)
{
	const auto casm_bytecode{ pause_().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pause_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cbw_no_operands_instruction();

TEST(NASMBytecode, cbw_no_operands_instruction_test)
{
	const auto casm_bytecode{ cbw().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cbw_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cwde_no_operands_instruction();

TEST(NASMBytecode, cwde_no_operands_instruction_test)
{
	const auto casm_bytecode{ cwde().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cwde_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cdqe_no_operands_instruction();

TEST(NASMBytecode, cdqe_no_operands_instruction_test)
{
	const auto casm_bytecode{ cdqe().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cdqe_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cwd_no_operands_instruction();

TEST(NASMBytecode, cwd_no_operands_instruction_test)
{
	const auto casm_bytecode{ cwd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cwd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cdq_no_operands_instruction();

TEST(NASMBytecode, cdq_no_operands_instruction_test)
{
	const auto casm_bytecode{ cdq().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cdq_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cqo_no_operands_instruction();

TEST(NASMBytecode, cqo_no_operands_instruction_test)
{
	const auto casm_bytecode{ cqo().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cqo_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fwait_no_operands_instruction();

TEST(NASMBytecode, fwait_no_operands_instruction_test)
{
	const auto casm_bytecode{ fwait().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fwait_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_wait_no_operands_instruction();

TEST(NASMBytecode, wait_no_operands_instruction_test)
{
	const auto casm_bytecode{ wait().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_wait_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pushf_no_operands_instruction();

TEST(NASMBytecode, pushf_no_operands_instruction_test)
{
	const auto casm_bytecode{ pushf().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pushf_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pushfq_no_operands_instruction();

TEST(NASMBytecode, pushfq_no_operands_instruction_test)
{
	const auto casm_bytecode{ pushfq().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pushfq_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_popf_no_operands_instruction();

TEST(NASMBytecode, popf_no_operands_instruction_test)
{
	const auto casm_bytecode{ popf().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_popf_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_popfq_no_operands_instruction();

TEST(NASMBytecode, popfq_no_operands_instruction_test)
{
	const auto casm_bytecode{ popfq().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_popfq_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sahf_no_operands_instruction();

TEST(NASMBytecode, sahf_no_operands_instruction_test)
{
	const auto casm_bytecode{ sahf().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sahf_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lahf_no_operands_instruction();

TEST(NASMBytecode, lahf_no_operands_instruction_test)
{
	const auto casm_bytecode{ lahf().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lahf_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsb_no_operands_instruction();

TEST(NASMBytecode, movsb_no_operands_instruction_test)
{
	const auto casm_bytecode{ movsb().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsb_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsw_no_operands_instruction();

TEST(NASMBytecode, movsw_no_operands_instruction_test)
{
	const auto casm_bytecode{ movsw().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsw_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsd_no_operands_instruction();

TEST(NASMBytecode, movsd_no_operands_instruction_test)
{
	const auto casm_bytecode{ movsd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsq_no_operands_instruction();

TEST(NASMBytecode, movsq_no_operands_instruction_test)
{
	const auto casm_bytecode{ movsq().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsq_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpsb_no_operands_instruction();

TEST(NASMBytecode, cmpsb_no_operands_instruction_test)
{
	const auto casm_bytecode{ cmpsb().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpsb_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpsw_no_operands_instruction();

TEST(NASMBytecode, cmpsw_no_operands_instruction_test)
{
	const auto casm_bytecode{ cmpsw().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpsw_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpsd_no_operands_instruction();

TEST(NASMBytecode, cmpsd_no_operands_instruction_test)
{
	const auto casm_bytecode{ cmpsd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpsd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpsq_no_operands_instruction();

TEST(NASMBytecode, cmpsq_no_operands_instruction_test)
{
	const auto casm_bytecode{ cmpsq().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpsq_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_test_al_imm8_instruction();

TEST(NASMBytecode, test_al_imm8_instruction_test)
{
	const auto casm_bytecode{ test(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_test_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_test_ax_eax_rax_imm16_32_instruction();

TEST(NASMBytecode, test_ax_eax_rax_imm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			test(ax, 0x8888_w),
			test(eax, 0x88888888_d),
			test(rax, 0x88888888_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_test_ax_eax_rax_imm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_stosb_no_operands_instruction();

TEST(NASMBytecode, stosb_no_operands_instruction_test)
{
	const auto casm_bytecode{ stosb().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_stosb_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_stosw_no_operands_instruction();

TEST(NASMBytecode, stosw_no_operands_instruction_test)
{
	const auto casm_bytecode{ stosw().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_stosw_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_stosd_no_operands_instruction();

TEST(NASMBytecode, stosd_no_operands_instruction_test)
{
	const auto casm_bytecode{ stosd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_stosd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_stosq_no_operands_instruction();

TEST(NASMBytecode, stosq_no_operands_instruction_test)
{
	const auto casm_bytecode{ stosq().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_stosq_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lodsb_no_operands_instruction();

TEST(NASMBytecode, lodsb_no_operands_instruction_test)
{
	const auto casm_bytecode{ lodsb().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lodsb_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lodsw_no_operands_instruction();

TEST(NASMBytecode, lodsw_no_operands_instruction_test)
{
	const auto casm_bytecode{ lodsw().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lodsw_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lodsd_no_operands_instruction();

TEST(NASMBytecode, lodsd_no_operands_instruction_test)
{
	const auto casm_bytecode{ lodsd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lodsd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lodsq_no_operands_instruction();

TEST(NASMBytecode, lodsq_no_operands_instruction_test)
{
	const auto casm_bytecode{ lodsq().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lodsq_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_scasb_no_operands_instruction();

TEST(NASMBytecode, scasb_no_operands_instruction_test)
{
	const auto casm_bytecode{ scasb().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_scasb_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_scasw_no_operands_instruction();

TEST(NASMBytecode, scasw_no_operands_instruction_test)
{
	const auto casm_bytecode{ scasw().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_scasw_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_scasd_no_operands_instruction();

TEST(NASMBytecode, scasd_no_operands_instruction_test)
{
	const auto casm_bytecode{ scasd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_scasd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_scasq_no_operands_instruction();

TEST(NASMBytecode, scasq_no_operands_instruction_test)
{
	const auto casm_bytecode{ scasq().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_scasq_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_r8_imm8_instruction_by_register();

TEST(NASMBytecode, mov_r8_imm8_instruction_by_register_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(al, 11_b),
			mov(cl, 11_b),
			mov(dl, 11_b),
			mov(bl, 11_b),
			mov(ah, 11_b),
			mov(ch, 11_b),
			mov(dh, 11_b),
			mov(bh, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_r8_imm8_instruction_by_register), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_r16_32_64_imm16_32_64_instruction_by_register();

TEST(NASMBytecode, mov_r16_32_64_imm16_32_64_instruction_by_register_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(dx, 0x1111_w),
			mov(edx, 0x11111111_d),
			mov(rdx, 0x111111111111_q)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_r16_32_64_imm16_32_64_instruction_by_register), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rol_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, rol_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rol(byte_ptr [ebx], 11_b),
			rol(dl, 11_b),
			rol(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rol_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ror_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, ror_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			ror(byte_ptr [ebx], 11_b),
			ror(dl, 11_b),
			ror(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ror_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcl_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, rcl_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcl(byte_ptr [ebx], 11_b),
			rcl(dl, 11_b),
			rcl(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcl_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcr_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, rcr_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcr(byte_ptr [ebx], 11_b),
			rcr(dl, 11_b),
			rcr(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcr_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shl_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, shl_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shl(byte_ptr [ebx], 11_b),
			shl(dl, 11_b),
			shl(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shl_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sal_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, sal_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sal(byte_ptr [ebx], 11_b),
			sal(dl, 11_b),
			sal(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sal_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shr_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, shr_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shr(byte_ptr [ebx], 11_b),
			shr(dl, 11_b),
			shr(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shr_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sar_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, sar_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sar(byte_ptr [ebx], 11_b),
			sar(dl, 11_b),
			sar(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sar_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rol_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, rol_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rol(dx, 0x11_b),
			rol(edx, 0x11_b),
			rol(word[ebx * 4], 0x11_b),
			rol(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rol_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ror_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, ror_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			ror(dx, 0x11_b),
			ror(edx, 0x11_b),
			ror(word[ebx * 4], 0x11_b),
			ror(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ror_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcl_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, rcl_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcl(dx, 0x11_b),
			rcl(edx, 0x11_b),
			rcl(word[ebx * 4], 0x11_b),
			rcl(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcl_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcr_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, rcr_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcr(dx, 0x11_b),
			rcr(edx, 0x11_b),
			rcr(word[ebx * 4], 0x11_b),
			rcr(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcr_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shl_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, shl_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shl(dx, 0x11_b),
			shl(edx, 0x11_b),
			shl(word[ebx * 4], 0x11_b),
			shl(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shl_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sal_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, sal_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sal(dx, 0x11_b),
			sal(edx, 0x11_b),
			sal(word[ebx * 4], 0x11_b),
			sal(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sal_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shr_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, shr_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shr(dx, 0x11_b),
			shr(edx, 0x11_b),
			shr(word[ebx * 4], 0x11_b),
			shr(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shr_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sar_rm16_32_imm8_instruction_by_number();

TEST(NASMBytecode, sar_rm16_32_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sar(dx, 0x11_b),
			sar(edx, 0x11_b),
			sar(word[ebx * 4], 0x11_b),
			sar(dword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sar_rm16_32_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_retn_imm16_instruction();

TEST(NASMBytecode, retn_imm16_instruction_test)
{
	const auto casm_bytecode{ retn(0x1111_w).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_retn_imm16_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ret_no_operands_instruction();

TEST(NASMBytecode, ret_no_operands_instruction_test)
{
	const auto casm_bytecode{ ret().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ret_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_m8_imm8_instruction_by_number();

TEST(NASMBytecode, mov_m8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ mov(byte_ptr [r11 + rax], 0x11_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_m8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_m16_32_64_imm16_32_instruction_by_number();

TEST(NASMBytecode, mov_m16_32_64_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mov(word[r11 + rbx * 8], 0x8888),
			mov(word[r11 + rbx * 8], 0x8888),
			mov(word[r11 + rbx * 8], 0x8888),
			mov(dword[r11 + rbx * 8], 0x88888888),
			mov(qword[r11 + rbx * 8], 0x88888888)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_m16_32_64_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_leave_no_operands_instruction();

TEST(NASMBytecode, leave_no_operands_instruction_test)
{
	const auto casm_bytecode{ leave().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_leave_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_retf_imm16_instruction();

TEST(NASMBytecode, retf_imm16_instruction_test)
{
	const auto casm_bytecode{ retf(0x1111_w).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_retf_imm16_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_retf_no_operands_instruction();

TEST(NASMBytecode, retf_no_operands_instruction_test)
{
	const auto casm_bytecode{ retf().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_retf_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_int3_no_operands_instruction();

TEST(NASMBytecode, int3_no_operands_instruction_test)
{
	const auto casm_bytecode{ int3().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_int3_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_int_imm8_instruction();

TEST(NASMBytecode, int_imm8_instruction_test)
{
	const auto casm_bytecode{ int_(0x11_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_int_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_iret_no_operands_instruction();

TEST(NASMBytecode, iret_no_operands_instruction_test)
{
	const auto casm_bytecode{ iret().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_iret_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_iretd_no_operands_instruction();

TEST(NASMBytecode, iretd_no_operands_instruction_test)
{
	const auto casm_bytecode{ iretd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_iretd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_iretq_no_operands_instruction();

TEST(NASMBytecode, iretq_no_operands_instruction_test)
{
	const auto casm_bytecode{ iretq().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_iretq_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rol_rm8_cl_instruction_by_number();

TEST(NASMBytecode, rol_rm8_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rol(byte_ptr [ebx], cl),
			rol(bl, cl),
			rol(al, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rol_rm8_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ror_rm8_cl_instruction_by_number();

TEST(NASMBytecode, ror_rm8_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			ror(byte_ptr [ebx], cl),
			ror(bl, cl),
			ror(al, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ror_rm8_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcl_rm8_cl_instruction_by_number();

TEST(NASMBytecode, rcl_rm8_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcl(byte_ptr [ebx], cl),
			rcl(bl, cl),
			rcl(al, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcl_rm8_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcr_rm8_cl_instruction_by_number();

TEST(NASMBytecode, rcr_rm8_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcr(byte_ptr [ebx], cl),
			rcr(bl, cl),
			rcr(al, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcr_rm8_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shl_rm8_cl_instruction_by_number();

TEST(NASMBytecode, shl_rm8_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shl(byte_ptr [ebx], cl),
			shl(bl, cl),
			shl(al, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shl_rm8_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sal_rm8_cl_instruction_by_number();

TEST(NASMBytecode, sal_rm8_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sal(byte_ptr [ebx], cl),
			sal(bl, cl),
			sal(al, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sal_rm8_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shr_rm8_cl_instruction_by_number();

TEST(NASMBytecode, shr_rm8_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shr(byte_ptr [ebx], cl),
			shr(bl, cl),
			shr(al, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shr_rm8_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sar_rm8_cl_instruction_by_number();

TEST(NASMBytecode, sar_rm8_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sar(byte_ptr [ebx], cl),
			sar(bl, cl),
			sar(al, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sar_rm8_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rol_rm16_32_64_cl_instruction_by_number();

TEST(NASMBytecode, rol_rm16_32_64_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rol(dx, cl),
			rol(edx, cl),
			rol(rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rol_rm16_32_64_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ror_rm16_32_64_cl_instruction_by_number();

TEST(NASMBytecode, ror_rm16_32_64_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			ror(dx, cl),
			ror(edx, cl),
			ror(rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ror_rm16_32_64_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcl_rm16_32_64_cl_instruction_by_number();

TEST(NASMBytecode, rcl_rm16_32_64_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcl(dx, cl),
			rcl(edx, cl),
			rcl(rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcl_rm16_32_64_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcr_rm16_32_64_cl_instruction_by_number();

TEST(NASMBytecode, rcr_rm16_32_64_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcr(dx, cl),
			rcr(edx, cl),
			rcr(rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcr_rm16_32_64_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shl_rm16_32_64_cl_instruction_by_number();

TEST(NASMBytecode, shl_rm16_32_64_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shl(dx, cl),
			shl(edx, cl),
			shl(rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shl_rm16_32_64_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sal_rm16_32_64_cl_instruction_by_number();

TEST(NASMBytecode, sal_rm16_32_64_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sal(dx, cl),
			sal(edx, cl),
			sal(rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sal_rm16_32_64_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shr_rm16_32_64_cl_instruction_by_number();

TEST(NASMBytecode, shr_rm16_32_64_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shr(dx, cl),
			shr(edx, cl),
			shr(rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shr_rm16_32_64_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sar_rm16_32_64_cl_instruction_by_number();

TEST(NASMBytecode, sar_rm16_32_64_cl_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sar(dx, cl),
			sar(edx, cl),
			sar(rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sar_rm16_32_64_cl_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xlat_no_operands_instruction();

TEST(NASMBytecode, xlat_no_operands_instruction_test)
{
	const auto casm_bytecode{ xlat().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xlat_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xlatb_no_operands_instruction();

TEST(NASMBytecode, xlatb_no_operands_instruction_test)
{
	const auto casm_bytecode{ xlatb().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xlatb_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fadd_m32_instruction_by_number();

TEST(NASMBytecode, fadd_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fadd(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fadd_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fadd_sti_instruction_by_number();

TEST(NASMBytecode, fadd_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fadd(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fadd_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fadd_st_sti_instruction_by_number();

TEST(NASMBytecode, fadd_st_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fadd(st0, st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fadd_st_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fmul_m32_instruction_by_number();

TEST(NASMBytecode, fmul_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fmul(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fmul_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fmul_sti_instruction_by_number();

TEST(NASMBytecode, fmul_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fmul(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fmul_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fmul_st_sti_instruction_by_number();

TEST(NASMBytecode, fmul_st_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fmul(st0, st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fmul_st_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcom_stm32_instruction_by_number();

TEST(NASMBytecode, fcom_stm32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fcom(st6),
			fcom(dword[rdx])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcom_stm32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcom_no_operands_instruction();

TEST(NASMBytecode, fcom_no_operands_instruction_test)
{
	const auto casm_bytecode{ fcom().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcom_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcomp_stm32_instruction_by_number();

TEST(NASMBytecode, fcomp_stm32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fcomp(st6),
			fcomp(dword[rdx])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcomp_stm32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcomp_no_operands_instruction();

TEST(NASMBytecode, fcomp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fcomp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcomp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsub_m32_instruction_by_number();

TEST(NASMBytecode, fsub_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fsub(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsub_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsub_sti_instruction_by_number();

TEST(NASMBytecode, fsub_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fsub(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsub_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsub_st_sti_instruction_by_number();

TEST(NASMBytecode, fsub_st_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fsub(st0, st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsub_st_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsubr_m32_instruction_by_number();

TEST(NASMBytecode, fsubr_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fsubr(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsubr_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsubr_sti_instruction_by_number();

TEST(NASMBytecode, fsubr_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fsubr(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsubr_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsubr_st_sti_instruction_by_number();

TEST(NASMBytecode, fsubr_st_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fsubr(st0, st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsubr_st_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdiv_m32_instruction_by_number();

TEST(NASMBytecode, fdiv_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fdiv(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdiv_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdiv_sti_instruction_by_number();

TEST(NASMBytecode, fdiv_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fdiv(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdiv_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdiv_st_sti_instruction_by_number();

TEST(NASMBytecode, fdiv_st_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fdiv(st0, st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdiv_st_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdivr_m32_instruction_by_number();

TEST(NASMBytecode, fdivr_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fdivr(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdivr_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdivr_sti_instruction_by_number();

TEST(NASMBytecode, fdivr_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fdivr(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdivr_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdivr_st_sti_instruction_by_number();

TEST(NASMBytecode, fdivr_st_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fdivr(st0, st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdivr_st_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fld_stm32_instruction_by_number();

TEST(NASMBytecode, fld_stm32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fld(st6),
			fld(dword[rdx])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fld_stm32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fxch_sti_instruction_by_number();

TEST(NASMBytecode, fxch_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fxch(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fxch_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fxch_no_operands_instruction();

TEST(NASMBytecode, fxch_no_operands_instruction_test)
{
	const auto casm_bytecode{ fxch().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fxch_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fst_m32_instruction_by_number();

TEST(NASMBytecode, fst_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fst(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fst_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fnop_no_operands_instruction();

TEST(NASMBytecode, fnop_no_operands_instruction_test)
{
	const auto casm_bytecode{ fnop().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fnop_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fstp_m32_instruction_by_number();

TEST(NASMBytecode, fstp_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fstp(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fstp_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fldenv_m_instruction_by_number();

TEST(NASMBytecode, fldenv_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fldenv(ptr[0x11223344]),
			fldenv(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fldenv_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fchs_no_operands_instruction();

TEST(NASMBytecode, fchs_no_operands_instruction_test)
{
	const auto casm_bytecode{ fchs().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fchs_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fabs_no_operands_instruction();

TEST(NASMBytecode, fabs_no_operands_instruction_test)
{
	const auto casm_bytecode{ fabs().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fabs_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ftst_no_operands_instruction();

TEST(NASMBytecode, ftst_no_operands_instruction_test)
{
	const auto casm_bytecode{ ftst().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ftst_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fxam_no_operands_instruction();

TEST(NASMBytecode, fxam_no_operands_instruction_test)
{
	const auto casm_bytecode{ fxam().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fxam_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fldcw_m16_instruction_by_number();

TEST(NASMBytecode, fldcw_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fldcw(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fldcw_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fld1_no_operands_instruction();

TEST(NASMBytecode, fld1_no_operands_instruction_test)
{
	const auto casm_bytecode{ fld1().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fld1_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fldl2t_no_operands_instruction();

TEST(NASMBytecode, fldl2t_no_operands_instruction_test)
{
	const auto casm_bytecode{ fldl2t().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fldl2t_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fldl2e_no_operands_instruction();

TEST(NASMBytecode, fldl2e_no_operands_instruction_test)
{
	const auto casm_bytecode{ fldl2e().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fldl2e_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fldpi_no_operands_instruction();

TEST(NASMBytecode, fldpi_no_operands_instruction_test)
{
	const auto casm_bytecode{ fldpi().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fldpi_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fldlg2_no_operands_instruction();

TEST(NASMBytecode, fldlg2_no_operands_instruction_test)
{
	const auto casm_bytecode{ fldlg2().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fldlg2_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fldln2_no_operands_instruction();

TEST(NASMBytecode, fldln2_no_operands_instruction_test)
{
	const auto casm_bytecode{ fldln2().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fldln2_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fldz_no_operands_instruction();

TEST(NASMBytecode, fldz_no_operands_instruction_test)
{
	const auto casm_bytecode{ fldz().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fldz_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fnstenv_m_instruction_by_number();

TEST(NASMBytecode, fnstenv_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fnstenv(ptr[0x11223344]),
			fnstenv(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fnstenv_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fstenv_m_instruction_by_number();

TEST(NASMBytecode, fstenv_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fstenv(ptr[0x11223344]),
			fstenv(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fstenv_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_f2xm1_no_operands_instruction();

TEST(NASMBytecode, f2xm1_no_operands_instruction_test)
{
	const auto casm_bytecode{ f2xm1().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_f2xm1_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fyl2x_no_operands_instruction();

TEST(NASMBytecode, fyl2x_no_operands_instruction_test)
{
	const auto casm_bytecode{ fyl2x().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fyl2x_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fptan_no_operands_instruction();

TEST(NASMBytecode, fptan_no_operands_instruction_test)
{
	const auto casm_bytecode{ fptan().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fptan_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fpatan_no_operands_instruction();

TEST(NASMBytecode, fpatan_no_operands_instruction_test)
{
	const auto casm_bytecode{ fpatan().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fpatan_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fxtract_no_operands_instruction();

TEST(NASMBytecode, fxtract_no_operands_instruction_test)
{
	const auto casm_bytecode{ fxtract().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fxtract_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fprem1_no_operands_instruction();

TEST(NASMBytecode, fprem1_no_operands_instruction_test)
{
	const auto casm_bytecode{ fprem1().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fprem1_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdecstp_no_operands_instruction();

TEST(NASMBytecode, fdecstp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fdecstp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdecstp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fincstp_no_operands_instruction();

TEST(NASMBytecode, fincstp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fincstp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fincstp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fnstcw_m16_instruction_by_number();

TEST(NASMBytecode, fnstcw_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fnstcw(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fnstcw_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fstcw_m16_instruction_by_number();

TEST(NASMBytecode, fstcw_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fstcw(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fstcw_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fprem_no_operands_instruction();

TEST(NASMBytecode, fprem_no_operands_instruction_test)
{
	const auto casm_bytecode{ fprem().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fprem_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fyl2xp1_no_operands_instruction();

TEST(NASMBytecode, fyl2xp1_no_operands_instruction_test)
{
	const auto casm_bytecode{ fyl2xp1().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fyl2xp1_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsqrt_no_operands_instruction();

TEST(NASMBytecode, fsqrt_no_operands_instruction_test)
{
	const auto casm_bytecode{ fsqrt().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsqrt_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsincos_no_operands_instruction();

TEST(NASMBytecode, fsincos_no_operands_instruction_test)
{
	const auto casm_bytecode{ fsincos().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsincos_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_frndint_no_operands_instruction();

TEST(NASMBytecode, frndint_no_operands_instruction_test)
{
	const auto casm_bytecode{ frndint().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_frndint_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fscale_no_operands_instruction();

TEST(NASMBytecode, fscale_no_operands_instruction_test)
{
	const auto casm_bytecode{ fscale().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fscale_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsin_no_operands_instruction();

TEST(NASMBytecode, fsin_no_operands_instruction_test)
{
	const auto casm_bytecode{ fsin().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsin_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcos_no_operands_instruction();

TEST(NASMBytecode, fcos_no_operands_instruction_test)
{
	const auto casm_bytecode{ fcos().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcos_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fiadd_m32_instruction_by_number();

TEST(NASMBytecode, fiadd_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fiadd(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fiadd_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcmovb_sti_instruction_by_number();

TEST(NASMBytecode, fcmovb_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcmovb(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcmovb_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fimul_m32_instruction_by_number();

TEST(NASMBytecode, fimul_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fimul(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fimul_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcmove_sti_instruction_by_number();

TEST(NASMBytecode, fcmove_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcmove(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcmove_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ficom_m32_instruction_by_number();

TEST(NASMBytecode, ficom_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ ficom(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ficom_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcmovbe_sti_instruction_by_number();

TEST(NASMBytecode, fcmovbe_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcmovbe(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcmovbe_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ficomp_m32_instruction_by_number();

TEST(NASMBytecode, ficomp_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ ficomp(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ficomp_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcmovu_sti_instruction_by_number();

TEST(NASMBytecode, fcmovu_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcmovu(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcmovu_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fisub_m32_instruction_by_number();

TEST(NASMBytecode, fisub_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fisub(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fisub_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fisubr_m32_instruction_by_number();

TEST(NASMBytecode, fisubr_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fisubr(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fisubr_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fucompp_no_operands_instruction();

TEST(NASMBytecode, fucompp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fucompp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fucompp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fidiv_m32_instruction_by_number();

TEST(NASMBytecode, fidiv_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fidiv(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fidiv_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fidivr_m32_instruction_by_number();

TEST(NASMBytecode, fidivr_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fidivr(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fidivr_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fild_m32_instruction_by_number();

TEST(NASMBytecode, fild_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fild(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fild_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcmovnb_sti_instruction_by_number();

TEST(NASMBytecode, fcmovnb_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcmovnb(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcmovnb_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fisttp_m32_instruction_by_number();

TEST(NASMBytecode, fisttp_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fisttp(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fisttp_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcmovne_sti_instruction_by_number();

TEST(NASMBytecode, fcmovne_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcmovne(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcmovne_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fist_m32_instruction_by_number();

TEST(NASMBytecode, fist_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fist(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fist_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcmovnbe_sti_instruction_by_number();

TEST(NASMBytecode, fcmovnbe_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcmovnbe(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcmovnbe_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fistp_m32_instruction_by_number();

TEST(NASMBytecode, fistp_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ fistp(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fistp_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcmovnu_sti_instruction_by_number();

TEST(NASMBytecode, fcmovnu_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcmovnu(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcmovnu_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fneni_no_operands_instruction();

TEST(NASMBytecode, fneni_no_operands_instruction_test)
{
	const auto casm_bytecode{ fneni().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fneni_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fndisi_no_operands_instruction();

TEST(NASMBytecode, fndisi_no_operands_instruction_test)
{
	const auto casm_bytecode{ fndisi().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fndisi_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fnclex_no_operands_instruction();

TEST(NASMBytecode, fnclex_no_operands_instruction_test)
{
	const auto casm_bytecode{ fnclex().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fnclex_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fclex_no_operands_instruction();

TEST(NASMBytecode, fclex_no_operands_instruction_test)
{
	const auto casm_bytecode{ fclex().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fclex_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fninit_no_operands_instruction();

TEST(NASMBytecode, fninit_no_operands_instruction_test)
{
	const auto casm_bytecode{ fninit().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fninit_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_finit_no_operands_instruction();

TEST(NASMBytecode, finit_no_operands_instruction_test)
{
	const auto casm_bytecode{ finit().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_finit_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fld_m80_instruction_by_number();

TEST(NASMBytecode, fld_m80_instruction_by_number_test)
{
	const auto casm_bytecode{ fld(tword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fld_m80_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fucomi_sti_instruction_by_number();

TEST(NASMBytecode, fucomi_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fucomi(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fucomi_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcomi_sti_instruction_by_number();

TEST(NASMBytecode, fcomi_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcomi(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcomi_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fstp_m80_instruction_by_number();

TEST(NASMBytecode, fstp_m80_instruction_by_number_test)
{
	const auto casm_bytecode{ fstp(tword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fstp_m80_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fadd_sti_st_instruction_by_number();

TEST(NASMBytecode, fadd_sti_st_instruction_by_number_test)
{
	const auto casm_bytecode{ fadd(st6, st0).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fadd_sti_st_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fmul_sti_st_instruction_by_number();

TEST(NASMBytecode, fmul_sti_st_instruction_by_number_test)
{
	const auto casm_bytecode{ fmul(st6, st0).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fmul_sti_st_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsubr_sti_st_instruction_by_number();

TEST(NASMBytecode, fsubr_sti_st_instruction_by_number_test)
{
	const auto casm_bytecode{ fsubr(st6, st0).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsubr_sti_st_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsub_sti_st_instruction_by_number();

TEST(NASMBytecode, fsub_sti_st_instruction_by_number_test)
{
	const auto casm_bytecode{ fsub(st6, st0).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsub_sti_st_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdivr_sti_st_instruction_by_number();

TEST(NASMBytecode, fdivr_sti_st_instruction_by_number_test)
{
	const auto casm_bytecode{ fdivr(st6, st0).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdivr_sti_st_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdiv_sti_st_instruction_by_number();

TEST(NASMBytecode, fdiv_sti_st_instruction_by_number_test)
{
	const auto casm_bytecode{ fdiv(st6, st0).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdiv_sti_st_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ffree_sti_instruction_by_number();

TEST(NASMBytecode, ffree_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ ffree(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ffree_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fst_sti_instruction_by_number();

TEST(NASMBytecode, fst_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fst(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fst_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fstp_stm64_instruction_by_number();

TEST(NASMBytecode, fstp_stm64_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fstp(st6),
			fstp(qword[rdx])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fstp_stm64_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_frstor_m_instruction_by_number();

TEST(NASMBytecode, frstor_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			frstor(ptr[0x11223344]),
			frstor(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_frstor_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fucom_sti_instruction_by_number();

TEST(NASMBytecode, fucom_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fucom(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fucom_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fucom_no_operands_instruction();

TEST(NASMBytecode, fucom_no_operands_instruction_test)
{
	const auto casm_bytecode{ fucom().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fucom_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fucomp_sti_instruction_by_number();

TEST(NASMBytecode, fucomp_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fucomp(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fucomp_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fucomp_no_operands_instruction();

TEST(NASMBytecode, fucomp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fucomp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fucomp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fnsave_m_instruction_by_number();

TEST(NASMBytecode, fnsave_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fnsave(ptr[0x11223344]),
			fnsave(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fnsave_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsave_m_instruction_by_number();

TEST(NASMBytecode, fsave_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fsave(ptr[0x11223344]),
			fsave(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsave_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fnstsw_m16_instruction_by_number();

TEST(NASMBytecode, fnstsw_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fnstsw(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fnstsw_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fstsw_m16_instruction_by_number();

TEST(NASMBytecode, fstsw_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fstsw(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fstsw_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fiadd_m16_instruction_by_number();

TEST(NASMBytecode, fiadd_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fiadd(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fiadd_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_faddp_sti_instruction_by_number();

TEST(NASMBytecode, faddp_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ faddp(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_faddp_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_faddp_no_operands_instruction();

TEST(NASMBytecode, faddp_no_operands_instruction_test)
{
	const auto casm_bytecode{ faddp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_faddp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fimul_m16_instruction_by_number();

TEST(NASMBytecode, fimul_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fimul(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fimul_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fmulp_sti_instruction_by_number();

TEST(NASMBytecode, fmulp_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fmulp(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fmulp_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fmulp_no_operands_instruction();

TEST(NASMBytecode, fmulp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fmulp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fmulp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ficom_m16_instruction_by_number();

TEST(NASMBytecode, ficom_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ ficom(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ficom_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ficomp_m16_instruction_by_number();

TEST(NASMBytecode, ficomp_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ ficomp(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ficomp_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcompp_no_operands_instruction();

TEST(NASMBytecode, fcompp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fcompp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcompp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fisub_m16_instruction_by_number();

TEST(NASMBytecode, fisub_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fisub(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fisub_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsubrp_sti_instruction_by_number();

TEST(NASMBytecode, fsubrp_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fsubrp(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsubrp_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsubrp_no_operands_instruction();

TEST(NASMBytecode, fsubrp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fsubrp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsubrp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fisubr_m16_instruction_by_number();

TEST(NASMBytecode, fisubr_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fisubr(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fisubr_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsubp_sti_instruction_by_number();

TEST(NASMBytecode, fsubp_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fsubp(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsubp_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fsubp_no_operands_instruction();

TEST(NASMBytecode, fsubp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fsubp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fsubp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fidiv_m16_instruction_by_number();

TEST(NASMBytecode, fidiv_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fidiv(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fidiv_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdivrp_sti_instruction_by_number();

TEST(NASMBytecode, fdivrp_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fdivrp(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdivrp_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdivrp_no_operands_instruction();

TEST(NASMBytecode, fdivrp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fdivrp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdivrp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fidivr_m16_instruction_by_number();

TEST(NASMBytecode, fidivr_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fidivr(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fidivr_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdivp_sti_instruction_by_number();

TEST(NASMBytecode, fdivp_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fdivp(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdivp_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fdivp_no_operands_instruction();

TEST(NASMBytecode, fdivp_no_operands_instruction_test)
{
	const auto casm_bytecode{ fdivp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fdivp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fild_m16_instruction_by_number();

TEST(NASMBytecode, fild_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fild(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fild_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ffreep_sti_instruction_by_number();

TEST(NASMBytecode, ffreep_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ ffreep(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ffreep_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fisttp_m16_instruction_by_number();

TEST(NASMBytecode, fisttp_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fisttp(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fisttp_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fist_m16_instruction_by_number();

TEST(NASMBytecode, fist_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fist(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fist_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fistp_m16_instruction_by_number();

TEST(NASMBytecode, fistp_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ fistp(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fistp_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fbld_m80_instruction_by_number();

TEST(NASMBytecode, fbld_m80_instruction_by_number_test)
{
	const auto casm_bytecode{ fbld(tword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fbld_m80_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fnstsw_ax_instruction();

TEST(NASMBytecode, fnstsw_ax_instruction_test)
{
	const auto casm_bytecode{ fnstsw(ax).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fnstsw_ax_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fstsw_ax_instruction();

TEST(NASMBytecode, fstsw_ax_instruction_test)
{
	const auto casm_bytecode{ fstsw(ax).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fstsw_ax_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fucomip_sti_instruction_by_number();

TEST(NASMBytecode, fucomip_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fucomip(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fucomip_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fbstp_m80_instruction_by_number();

TEST(NASMBytecode, fbstp_m80_instruction_by_number_test)
{
	const auto casm_bytecode{ fbstp(tword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fbstp_m80_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fcomip_sti_instruction_by_number();

TEST(NASMBytecode, fcomip_sti_instruction_by_number_test)
{
	const auto casm_bytecode{ fcomip(st6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fcomip_sti_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_in_al_imm8_instruction();

TEST(NASMBytecode, in_al_imm8_instruction_test)
{
	const auto casm_bytecode{ in(al, 0x40).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_in_al_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_in_eax_imm8_instruction();

TEST(NASMBytecode, in_eax_imm8_instruction_test)
{
	const auto casm_bytecode{ in(eax, 0x88_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_in_eax_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_out_imm8_al_instruction();

TEST(NASMBytecode, out_imm8_al_instruction_test)
{
	const auto casm_bytecode{ out(0x11_b, al).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_out_imm8_al_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_out_imm8_eax_instruction();

TEST(NASMBytecode, out_imm8_eax_instruction_test)
{
	const auto casm_bytecode{ out(0x11_b, eax).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_out_imm8_eax_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_in_al_dx_instruction();

TEST(NASMBytecode, in_al_dx_instruction_test)
{
	const auto casm_bytecode{ in(al, dx).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_in_al_dx_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_in_eax_dx_instruction();

TEST(NASMBytecode, in_eax_dx_instruction_test)
{
	const auto casm_bytecode{ in(eax, dx).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_in_eax_dx_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_out_dx_al_instruction();

TEST(NASMBytecode, out_dx_al_instruction_test)
{
	const auto casm_bytecode{ out(dx, al).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_out_dx_al_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_out_dx_eax_instruction();

TEST(NASMBytecode, out_dx_eax_instruction_test)
{
	const auto casm_bytecode{ out(dx, eax).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_out_dx_eax_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lock_no_operands_instruction();

TEST(NASMBytecode, lock_no_operands_instruction_test)
{
	const auto casm_bytecode{ lock().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lock_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_int1_no_operands_instruction();

TEST(NASMBytecode, int1_no_operands_instruction_test)
{
	const auto casm_bytecode{ int1().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_int1_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_icebp_no_operands_instruction();

TEST(NASMBytecode, icebp_no_operands_instruction_test)
{
	const auto casm_bytecode{ icebp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_icebp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_repnz_no_operands_instruction();

TEST(NASMBytecode, repnz_no_operands_instruction_test)
{
	const auto casm_bytecode{ repnz().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_repnz_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_repne_no_operands_instruction();

TEST(NASMBytecode, repne_no_operands_instruction_test)
{
	const auto casm_bytecode{ repne().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_repne_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_repz_no_operands_instruction();

TEST(NASMBytecode, repz_no_operands_instruction_test)
{
	const auto casm_bytecode{ repz().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_repz_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_repe_no_operands_instruction();

TEST(NASMBytecode, repe_no_operands_instruction_test)
{
	const auto casm_bytecode{ repe().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_repe_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rep_no_operands_instruction();

TEST(NASMBytecode, rep_no_operands_instruction_test)
{
	const auto casm_bytecode{ rep().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rep_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_hlt_no_operands_instruction();

TEST(NASMBytecode, hlt_no_operands_instruction_test)
{
	const auto casm_bytecode{ hlt().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_hlt_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmc_no_operands_instruction();

TEST(NASMBytecode, cmc_no_operands_instruction_test)
{
	const auto casm_bytecode{ cmc().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmc_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_test_rm8_imm8_instruction_by_number();

TEST(NASMBytecode, test_rm8_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			test(byte_ptr [ebx], 11_b),
			test(dl, 11_b),
			test(al, 11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_test_rm8_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_test_rm16_32_64_imm16_32_instruction_by_number();

TEST(NASMBytecode, test_rm16_32_64_imm16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			test(dx, 0x1111_w),
			test(edx, 0x111122_d),
			test(rdx, 0x111122_d),
			test(word[ebx * 4], 0x1111_w),
			test(dword[ebx * 4], 0x111122_d),
			test(qword[ebx * 4], 0x111122_d)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_test_rm16_32_64_imm16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_clc_no_operands_instruction();

TEST(NASMBytecode, clc_no_operands_instruction_test)
{
	const auto casm_bytecode{ clc().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_clc_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_stc_no_operands_instruction();

TEST(NASMBytecode, stc_no_operands_instruction_test)
{
	const auto casm_bytecode{ stc().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_stc_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cli_no_operands_instruction();

TEST(NASMBytecode, cli_no_operands_instruction_test)
{
	const auto casm_bytecode{ cli().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cli_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sti_no_operands_instruction();

TEST(NASMBytecode, sti_no_operands_instruction_test)
{
	const auto casm_bytecode{ sti().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sti_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cld_no_operands_instruction();

TEST(NASMBytecode, cld_no_operands_instruction_test)
{
	const auto casm_bytecode{ cld().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cld_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_std_no_operands_instruction();

TEST(NASMBytecode, std_no_operands_instruction_test)
{
	const auto casm_bytecode{ std_().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_std_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_call_rm64_instruction_by_number();

TEST(NASMBytecode, call_rm64_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			call(rdx),
			call(qword[ebx * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_call_rm64_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_jmp_rm64_instruction_by_number();

TEST(NASMBytecode, jmp_rm64_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			jmp(rdx),
			jmp(qword[ebx * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_jmp_rm64_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_push_m16_64_instruction_by_number();

TEST(NASMBytecode, push_m16_64_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			push(word[r11 + rbx * 8]),
			push(qword[r11 + rbx * 8])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_push_m16_64_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sldt_m16_instruction_by_number();

TEST(NASMBytecode, sldt_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ sldt(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sldt_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sldt_r16_32_instruction_by_number();

TEST(NASMBytecode, sldt_r16_32_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sldt(dx),
			sldt(edx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sldt_r16_32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_str_m16_instruction_by_number();

TEST(NASMBytecode, str_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ str(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_str_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_str_r16_32_64_instruction_by_number();

TEST(NASMBytecode, str_r16_32_64_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			str(dx),
			str(edx),
			str(rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_str_r16_32_64_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lldt_rm16_instruction_by_number();

TEST(NASMBytecode, lldt_rm16_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lldt(dx),
			lldt(word[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lldt_rm16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ltr_rm16_instruction_by_number();

TEST(NASMBytecode, ltr_rm16_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			ltr(dx),
			ltr(word[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ltr_rm16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_verr_rm16_instruction_by_number();

TEST(NASMBytecode, verr_rm16_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			verr(dx),
			verr(word[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_verr_rm16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_verw_rm16_instruction_by_number();

TEST(NASMBytecode, verw_rm16_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			verw(dx),
			verw(word[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_verw_rm16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sgdt_m_instruction_by_number();

TEST(NASMBytecode, sgdt_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sgdt(ptr[0x11223344]),
			sgdt(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sgdt_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_vmcall_no_operands_instruction();

TEST(NASMBytecode, vmcall_no_operands_instruction_test)
{
	const auto casm_bytecode{ vmcall().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_vmcall_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_vmlaunch_no_operands_instruction();

TEST(NASMBytecode, vmlaunch_no_operands_instruction_test)
{
	const auto casm_bytecode{ vmlaunch().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_vmlaunch_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_vmresume_no_operands_instruction();

TEST(NASMBytecode, vmresume_no_operands_instruction_test)
{
	const auto casm_bytecode{ vmresume().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_vmresume_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_vmxoff_no_operands_instruction();

TEST(NASMBytecode, vmxoff_no_operands_instruction_test)
{
	const auto casm_bytecode{ vmxoff().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_vmxoff_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sidt_m_instruction_by_number();

TEST(NASMBytecode, sidt_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sidt(ptr[0x11223344]),
			sidt(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sidt_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_monitor_no_operands_instruction();

TEST(NASMBytecode, monitor_no_operands_instruction_test)
{
	const auto casm_bytecode{ monitor().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_monitor_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mwait_no_operands_instruction();

TEST(NASMBytecode, mwait_no_operands_instruction_test)
{
	const auto casm_bytecode{ mwait().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mwait_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lgdt_m_instruction_by_number();

TEST(NASMBytecode, lgdt_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lgdt(ptr[0x11223344]),
			lgdt(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lgdt_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xgetbv_no_operands_instruction();

TEST(NASMBytecode, xgetbv_no_operands_instruction_test)
{
	const auto casm_bytecode{ xgetbv().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xgetbv_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xsetbv_no_operands_instruction();

TEST(NASMBytecode, xsetbv_no_operands_instruction_test)
{
	const auto casm_bytecode{ xsetbv().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xsetbv_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lidt_m_instruction_by_number();

TEST(NASMBytecode, lidt_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lidt(ptr[0x11223344]),
			lidt(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lidt_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_smsw_m16_instruction_by_number();

TEST(NASMBytecode, smsw_m16_instruction_by_number_test)
{
	const auto casm_bytecode{ smsw(word[r11 + rbx * 8]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_smsw_m16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_smsw_r16_32_64_instruction_by_number();

TEST(NASMBytecode, smsw_r16_32_64_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			smsw(dx),
			smsw(edx),
			smsw(rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_smsw_r16_32_64_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lmsw_rm16_instruction_by_number();

TEST(NASMBytecode, lmsw_rm16_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lmsw(dx),
			lmsw(word[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lmsw_rm16_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_invlpg_m_instruction_by_number();

TEST(NASMBytecode, invlpg_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			invlpg(ptr[0x11223344]),
			invlpg(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_invlpg_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_swapgs_no_operands_instruction();

TEST(NASMBytecode, swapgs_no_operands_instruction_test)
{
	const auto casm_bytecode{ swapgs().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_swapgs_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rdtscp_no_operands_instruction();

TEST(NASMBytecode, rdtscp_no_operands_instruction_test)
{
	const auto casm_bytecode{ rdtscp().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rdtscp_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lar_r16_32_64_m16_instruction();

TEST(NASMBytecode, lar_r16_32_64_m16_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lar(dx, word[r11 + rax + 0x11_b]),
			lar(edx, word[r11 + rax + 0x112233_d]),
			lar(rdx, word[r11 + rax + 0x11_b])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lar_r16_32_64_m16_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lar_r16_32_64_r16_32_instruction();

TEST(NASMBytecode, lar_r16_32_64_r16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lar(dx, ax),
			lar(edx, eax),
			lar(rdx, eax)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lar_r16_32_64_r16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lsl_r16_32_64_m16_instruction();

TEST(NASMBytecode, lsl_r16_32_64_m16_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lsl(dx, word[r11 + rax + 0x11_b]),
			lsl(edx, word[r11 + rax + 0x112233_d]),
			lsl(rdx, word[r11 + rax + 0x11_b])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lsl_r16_32_64_m16_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lsl_r16_32_64_r16_32_instruction();

TEST(NASMBytecode, lsl_r16_32_64_r16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lsl(dx, ax),
			lsl(edx, eax),
			lsl(rdx, eax)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lsl_r16_32_64_r16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_syscall_no_operands_instruction();

TEST(NASMBytecode, syscall_no_operands_instruction_test)
{
	const auto casm_bytecode{ syscall_().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_syscall_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_clts_no_operands_instruction();

TEST(NASMBytecode, clts_no_operands_instruction_test)
{
	const auto casm_bytecode{ clts().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_clts_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sysret_no_operands_instruction();

TEST(NASMBytecode, sysret_no_operands_instruction_test)
{
	const auto casm_bytecode{ sysret().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sysret_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_invd_no_operands_instruction();

TEST(NASMBytecode, invd_no_operands_instruction_test)
{
	const auto casm_bytecode{ invd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_invd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_wbinvd_no_operands_instruction();

TEST(NASMBytecode, wbinvd_no_operands_instruction_test)
{
	const auto casm_bytecode{ wbinvd().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_wbinvd_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ud2_no_operands_instruction();

TEST(NASMBytecode, ud2_no_operands_instruction_test)
{
	const auto casm_bytecode{ ud2().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ud2_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movups_xmm_xmmm128_instruction();

TEST(NASMBytecode, movups_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movups(xmm13, oword[r12 + rax]),
			movups(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movups_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movss_xmm_xmmm32_instruction();

TEST(NASMBytecode, movss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movss(xmm4, dword[r12 + rax]),
			movss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movupd_xmm_xmmm128_instruction();

TEST(NASMBytecode, movupd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movupd(xmm13, oword[r12 + rax]),
			movupd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movupd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsd_xmm_xmmm64_instruction();

TEST(NASMBytecode, movsd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movsd(xmm12, qword[r12 + rax]),
			movsd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movups_xmmm128_xmm_instruction();

TEST(NASMBytecode, movups_xmmm128_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movups(xmm2, xmm6),
			movups(oword[rbp + rcx * 2], xmm6),
			movups(oword[r10 + rbp + 0x80_d], xmm6),
			movups(oword[rbp + 0x8012333_d], xmm6),
			movups(oword[rbp + 0x80_d], xmm6),
			movups(oword[rbp + 0xff_b], xmm6),
			movups(oword[rbp + 0xff_d], xmm6)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movups_xmmm128_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movss_xmmm32_xmm_instruction();

TEST(NASMBytecode, movss_xmmm32_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movss(xmm2, xmm6),
			movss(dword[esp + ecx * 2], xmm6)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movss_xmmm32_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movupd_xmmm128_xmm_instruction();

TEST(NASMBytecode, movupd_xmmm128_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movupd(xmm2, xmm6),
			movupd(oword[rbp + rcx * 2], xmm6),
			movupd(oword[r10 + rbp + 0x80_d], xmm6),
			movupd(oword[rbp + 0x8012333_d], xmm6),
			movupd(oword[rbp + 0x80_d], xmm6),
			movupd(oword[rbp + 0xff_b], xmm6),
			movupd(oword[rbp + 0xff_d], xmm6)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movupd_xmmm128_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsd_xmmm64_xmm_instruction();

TEST(NASMBytecode, movsd_xmmm64_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movsd(xmm2, xmm6),
			movsd(qword[r13 + r11], xmm6)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsd_xmmm64_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movhlps_xmm_xmm_instruction();

TEST(NASMBytecode, movhlps_xmm_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movhlps(xmm4, xmm12),
			movhlps(xmm12, xmm4)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movhlps_xmm_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movlps_xmm_m64_instruction();

TEST(NASMBytecode, movlps_xmm_m64_instruction_test)
{
	const auto casm_bytecode{ movlps(xmm13, qword[r13d]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movlps_xmm_m64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movlpd_xmm_m64_instruction();

TEST(NASMBytecode, movlpd_xmm_m64_instruction_test)
{
	const auto casm_bytecode{ movlpd(xmm13, qword[r13d]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movlpd_xmm_m64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movddup_xmm_xmmm64_instruction();

TEST(NASMBytecode, movddup_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movddup(xmm12, qword[r12 + rax]),
			movddup(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movddup_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsldup_xmm_xmmm64_instruction();

TEST(NASMBytecode, movsldup_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movsldup(xmm12, qword[r12 + rax]),
			movsldup(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsldup_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movlps_m64_xmm_instruction();

TEST(NASMBytecode, movlps_m64_xmm_instruction_test)
{
	const auto casm_bytecode{ movlps(qword[r11 + rax], xmm2).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movlps_m64_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movlpd_m64_xmm_instruction();

TEST(NASMBytecode, movlpd_m64_xmm_instruction_test)
{
	const auto casm_bytecode{ movlpd(qword[r11 + rax], xmm2).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movlpd_m64_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_unpcklps_xmm_xmmm64_instruction();

TEST(NASMBytecode, unpcklps_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			unpcklps(xmm12, qword[r12 + rax]),
			unpcklps(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_unpcklps_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_unpcklpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, unpcklpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			unpcklpd(xmm13, oword[r12 + rax]),
			unpcklpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_unpcklpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_unpckhps_xmm_xmmm64_instruction();

TEST(NASMBytecode, unpckhps_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			unpckhps(xmm12, qword[r12 + rax]),
			unpckhps(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_unpckhps_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_unpckhpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, unpckhpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			unpckhpd(xmm13, oword[r12 + rax]),
			unpckhpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_unpckhpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movlhps_xmm_xmm_instruction();

TEST(NASMBytecode, movlhps_xmm_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movlhps(xmm4, xmm12),
			movlhps(xmm12, xmm4)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movlhps_xmm_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movhps_xmm_m64_instruction();

TEST(NASMBytecode, movhps_xmm_m64_instruction_test)
{
	const auto casm_bytecode{ movhps(xmm13, qword[r13d]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movhps_xmm_m64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movhpd_xmm_m64_instruction();

TEST(NASMBytecode, movhpd_xmm_m64_instruction_test)
{
	const auto casm_bytecode{ movhpd(xmm13, qword[r13d]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movhpd_xmm_m64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movshdup_xmm_xmmm64_instruction();

TEST(NASMBytecode, movshdup_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movshdup(xmm12, qword[r12 + rax]),
			movshdup(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movshdup_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movhps_m64_xmm_instruction();

TEST(NASMBytecode, movhps_m64_xmm_instruction_test)
{
	const auto casm_bytecode{ movhps(qword[r11 + rax], xmm2).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movhps_m64_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movhpd_m64_xmm_instruction();

TEST(NASMBytecode, movhpd_m64_xmm_instruction_test)
{
	const auto casm_bytecode{ movhpd(qword[r11 + rax], xmm2).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movhpd_m64_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_prefetchnta_m8_instruction_by_number();

TEST(NASMBytecode, prefetchnta_m8_instruction_by_number_test)
{
	const auto casm_bytecode{ prefetchnta(byte_ptr [r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_prefetchnta_m8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_prefetcht0_m8_instruction_by_number();

TEST(NASMBytecode, prefetcht0_m8_instruction_by_number_test)
{
	const auto casm_bytecode{ prefetcht0(byte_ptr [r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_prefetcht0_m8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_prefetcht1_m8_instruction_by_number();

TEST(NASMBytecode, prefetcht1_m8_instruction_by_number_test)
{
	const auto casm_bytecode{ prefetcht1(byte_ptr [r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_prefetcht1_m8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_prefetcht2_m8_instruction_by_number();

TEST(NASMBytecode, prefetcht2_m8_instruction_by_number_test)
{
	const auto casm_bytecode{ prefetcht2(byte_ptr [r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_prefetcht2_m8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_nop_rm16_32_instruction();

TEST(NASMBytecode, nop_rm16_32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			nop(dx),
			nop(edx),
			nop(word[ebx * 4]),
			nop(dword[ebx * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_nop_rm16_32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_r64_crn_instruction();

TEST(NASMBytecode, mov_r64_crn_instruction_test)
{
	const auto casm_bytecode{ mov(rdx, cr0).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_r64_crn_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_r64_drn_instruction();

TEST(NASMBytecode, mov_r64_drn_instruction_test)
{
	const auto casm_bytecode{ mov(rax, dr0).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_r64_drn_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_crn_r64_instruction();

TEST(NASMBytecode, mov_crn_r64_instruction_test)
{
	const auto casm_bytecode{ mov(cr0, rcx).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_crn_r64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mov_drn_r64_instruction();

TEST(NASMBytecode, mov_drn_r64_instruction_test)
{
	const auto casm_bytecode{ mov(dr0, rcx).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mov_drn_r64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movaps_xmm_xmmm128_instruction();

TEST(NASMBytecode, movaps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movaps(xmm13, oword[r12 + rax]),
			movaps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movaps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movapd_xmm_xmmm128_instruction();

TEST(NASMBytecode, movapd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movapd(xmm13, oword[r12 + rax]),
			movapd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movapd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movaps_xmmm128_xmm_instruction();

TEST(NASMBytecode, movaps_xmmm128_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movaps(xmm2, xmm6),
			movaps(oword[rbp + rcx * 2], xmm6),
			movaps(oword[r10 + rbp + 0x80_d], xmm6),
			movaps(oword[rbp + 0x8012333_d], xmm6),
			movaps(oword[rbp + 0x80_d], xmm6),
			movaps(oword[rbp + 0xff_b], xmm6),
			movaps(oword[rbp + 0xff_d], xmm6)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movaps_xmmm128_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movapd_xmmm128_xmm_instruction();

TEST(NASMBytecode, movapd_xmmm128_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movapd(xmm2, xmm6),
			movapd(oword[rbp + rcx * 2], xmm6),
			movapd(oword[r10 + rbp + 0x80_d], xmm6),
			movapd(oword[rbp + 0x8012333_d], xmm6),
			movapd(oword[rbp + 0x80_d], xmm6),
			movapd(oword[rbp + 0xff_b], xmm6),
			movapd(oword[rbp + 0xff_d], xmm6)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movapd_xmmm128_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtpi2ps_xmm_mmm64_instruction();

TEST(NASMBytecode, cvtpi2ps_xmm_mmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtpi2ps(xmm15, qword[eax * 4]),
			cvtpi2ps(xmm15, mm5)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtpi2ps_xmm_mmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtsi2ss_xmm_rm32_64_instruction();

TEST(NASMBytecode, cvtsi2ss_xmm_rm32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtsi2ss(xmm15, dword[r13d]),
			cvtsi2ss(xmm3, qword[r13 + r13])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtsi2ss_xmm_rm32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtpi2pd_xmm_mmm64_instruction();

TEST(NASMBytecode, cvtpi2pd_xmm_mmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtpi2pd(xmm15, qword[eax * 4]),
			cvtpi2pd(xmm15, mm5)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtpi2pd_xmm_mmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtsi2sd_xmm_rm32_64_instruction();

TEST(NASMBytecode, cvtsi2sd_xmm_rm32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtsi2sd(xmm15, dword[r13d]),
			cvtsi2sd(xmm3, qword[r13 + r13])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtsi2sd_xmm_rm32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movntps_m128_xmm_instruction();

TEST(NASMBytecode, movntps_m128_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movntps(oword[gs(0x8888888)], xmm2),
			movntps(oword[r11 + rdx * 8], xmm8)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movntps_m128_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movntpd_m128_xmm_instruction();

TEST(NASMBytecode, movntpd_m128_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movntpd(oword[gs(0x8888888)], xmm2),
			movntpd(oword[r11 + rdx * 8], xmm8)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movntpd_m128_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvttps2pi_mm_xmmm64_instruction();

TEST(NASMBytecode, cvttps2pi_mm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvttps2pi(mm2, xmm3),
			cvttps2pi(mm6, qword[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvttps2pi_mm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvttss2si_r32_64_xmmm32_instruction();

TEST(NASMBytecode, cvttss2si_r32_64_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvttss2si(edx, xmm2),
			cvttss2si(edx, dword [ebp + 0x12_b]),
			cvttss2si(rdx, xmm2),
			cvttss2si(rdx, dword [ebp + 0x12_b])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvttss2si_r32_64_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvttpd2pi_mm_xmmm128_instruction();

TEST(NASMBytecode, cvttpd2pi_mm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvttpd2pi(mm2, xmm3),
			cvttpd2pi(mm6, oword[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvttpd2pi_mm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvttsd2si_r32_64_xmmm64_instruction();

TEST(NASMBytecode, cvttsd2si_r32_64_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvttsd2si(edx, xmm2),
			cvttsd2si(edx, qword [rcx + r15 + 0x1212_d]),
			cvttsd2si(rdx, xmm2),
			cvttsd2si(rdx, qword [rcx + r15 + 0x1212_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvttsd2si_r32_64_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtps2pi_mm_xmmm64_instruction();

TEST(NASMBytecode, cvtps2pi_mm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtps2pi(mm2, xmm3),
			cvtps2pi(mm6, qword[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtps2pi_mm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtss2si_r32_64_xmmm32_instruction();

TEST(NASMBytecode, cvtss2si_r32_64_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtss2si(edx, xmm2),
			cvtss2si(edx, dword [ebp + 0x12_b]),
			cvtss2si(rdx, xmm2),
			cvtss2si(rdx, dword [ebp + 0x12_b])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtss2si_r32_64_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtpd2pi_mm_xmmm128_instruction();

TEST(NASMBytecode, cvtpd2pi_mm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtpd2pi(mm2, xmm3),
			cvtpd2pi(mm6, oword[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtpd2pi_mm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtsd2si_r32_64_xmmm64_instruction();

TEST(NASMBytecode, cvtsd2si_r32_64_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtsd2si(edx, xmm2),
			cvtsd2si(edx, qword [rcx + r15 + 0x1212_d]),
			cvtsd2si(rdx, xmm2),
			cvtsd2si(rdx, qword [rcx + r15 + 0x1212_d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtsd2si_r32_64_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ucomiss_xmm_xmmm32_instruction();

TEST(NASMBytecode, ucomiss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			ucomiss(xmm4, dword[r12 + rax]),
			ucomiss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ucomiss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ucomisd_xmm_xmmm64_instruction();

TEST(NASMBytecode, ucomisd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			ucomisd(xmm12, qword[r12 + rax]),
			ucomisd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ucomisd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_comiss_xmm_xmmm32_instruction();

TEST(NASMBytecode, comiss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			comiss(xmm4, dword[r12 + rax]),
			comiss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_comiss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_comisd_xmm_xmmm64_instruction();

TEST(NASMBytecode, comisd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			comisd(xmm12, qword[r12 + rax]),
			comisd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_comisd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_wrmsr_no_operands_instruction();

TEST(NASMBytecode, wrmsr_no_operands_instruction_test)
{
	const auto casm_bytecode{ wrmsr().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_wrmsr_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rdtsc_no_operands_instruction();

TEST(NASMBytecode, rdtsc_no_operands_instruction_test)
{
	const auto casm_bytecode{ rdtsc().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rdtsc_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rdmsr_no_operands_instruction();

TEST(NASMBytecode, rdmsr_no_operands_instruction_test)
{
	const auto casm_bytecode{ rdmsr().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rdmsr_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rdpmc_no_operands_instruction();

TEST(NASMBytecode, rdpmc_no_operands_instruction_test)
{
	const auto casm_bytecode{ rdpmc().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rdpmc_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sysenter_no_operands_instruction();

TEST(NASMBytecode, sysenter_no_operands_instruction_test)
{
	const auto casm_bytecode{ sysenter().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sysenter_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sysexit_no_operands_instruction();

TEST(NASMBytecode, sysexit_no_operands_instruction_test)
{
	const auto casm_bytecode{ sysexit().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sysexit_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_getsec_no_operands_instruction();

TEST(NASMBytecode, getsec_no_operands_instruction_test)
{
	const auto casm_bytecode{ getsec().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_getsec_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_invept_r64_m128_instruction();

TEST(NASMBytecode, invept_r64_m128_instruction_test)
{
	const auto casm_bytecode{ invept(rax, oword [0x11223344_d]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_invept_r64_m128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_invvpid_r64_m128_instruction();

TEST(NASMBytecode, invvpid_r64_m128_instruction_test)
{
	const auto casm_bytecode{ invvpid(rax, oword [0x11223344_d]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_invvpid_r64_m128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movbe_r16_32_64_m16_32_64_instruction();

TEST(NASMBytecode, movbe_r16_32_64_m16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movbe(dx, word[r11 + rax]),
			movbe(edx, dword[r11 + rax]),
			movbe(rdx, qword[r11 + rax])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movbe_r16_32_64_m16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_crc32_r32_64_rm8_instruction();

TEST(NASMBytecode, crc32_r32_64_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			crc32(edx, cl),
			crc32(edx, byte_ptr [rcx]),
			crc32(rdx, cl),
			crc32(rdx, byte_ptr [rcx])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_crc32_r32_64_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movbe_m16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, movbe_m16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movbe(word[r11 + rbx * 8], dx),
			movbe(dword[r11 + rbx * 8], eax),
			movbe(qword[r11 + rbx * 8], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movbe_m16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_crc32_r32_64_rm16_32_64_instruction();

TEST(NASMBytecode, crc32_r32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			crc32(edx, cx),
			crc32(edx, ecx),
			crc32(rdx, rcx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_crc32_r32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_roundps_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, roundps_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			roundps(xmm4, oword[r12 + rax], 4_b),
			roundps(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_roundps_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_roundpd_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, roundpd_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			roundpd(xmm4, oword[r12 + rax], 4_b),
			roundpd(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_roundpd_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_roundss_xmm_xmmm32_imm8_instruction();

TEST(NASMBytecode, roundss_xmm_xmmm32_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			roundss(xmm4, dword[r12 + rax], 4_b),
			roundss(xmm2, xmm3, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_roundss_xmm_xmmm32_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_roundsd_xmm_xmmm64_imm8_instruction();

TEST(NASMBytecode, roundsd_xmm_xmmm64_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			roundsd(xmm14, qword[r12 + rax], 4_b),
			roundsd(xmm2, xmm11, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_roundsd_xmm_xmmm64_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_blendps_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, blendps_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			blendps(xmm4, oword[r12 + rax], 4_b),
			blendps(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_blendps_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_blendpd_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, blendpd_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			blendpd(xmm4, oword[r12 + rax], 4_b),
			blendpd(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_blendpd_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pblendw_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, pblendw_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pblendw(xmm4, oword[r12 + rax], 4_b),
			pblendw(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pblendw_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_palignr_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, palignr_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			palignr(xmm4, oword[r12 + rax], 4_b),
			palignr(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_palignr_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pextrb_m8_xmm_imm8_instruction();

TEST(NASMBytecode, pextrb_m8_xmm_imm8_instruction_test)
{
	const auto casm_bytecode{ pextrb(byte_ptr [r11 + rax], xmm6, 0x11_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pextrb_m8_xmm_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pextrb_r32_64_xmm_imm8_instruction();

TEST(NASMBytecode, pextrb_r32_64_xmm_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pextrb(edx, xmm2, 12_b),
			pextrb(rdx, xmm7, 12_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pextrb_r32_64_xmm_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pextrd_rm32_xmm_imm8_instruction();

TEST(NASMBytecode, pextrd_rm32_xmm_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pextrd(edx, xmm5, 0x55_b),
			pextrd(dword[ebx * 4], xmm5, 0x55_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pextrd_rm32_xmm_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pextrq_rm64_xmm_imm8_instruction();

TEST(NASMBytecode, pextrq_rm64_xmm_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pextrq(rdx, xmm6, 0x11_b),
			pextrq(qword[ebx * 4], xmm6, 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pextrq_rm64_xmm_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_extractps_rm32_xmm_imm8_instruction();

TEST(NASMBytecode, extractps_rm32_xmm_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			extractps(edx, xmm5, 0x55_b),
			extractps(dword[ebx * 4], xmm5, 0x55_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_extractps_rm32_xmm_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pinsrb_xmm_m8_imm8_instruction();

TEST(NASMBytecode, pinsrb_xmm_m8_imm8_instruction_test)
{
	const auto casm_bytecode{ pinsrb(xmm12, byte_ptr [rsp + 0x45_b], 0x17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pinsrb_xmm_m8_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pinsrb_xmm_r32_imm8_instruction();

TEST(NASMBytecode, pinsrb_xmm_r32_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pinsrb(xmm15, ecx, 4_b),
			pinsrb(xmm3, r13d, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pinsrb_xmm_r32_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_insertps_xmm_m32_imm8_instruction();

TEST(NASMBytecode, insertps_xmm_m32_imm8_instruction_test)
{
	const auto casm_bytecode{ insertps(xmm8, dword[r13d * 4], 0x17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_insertps_xmm_m32_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_insertps_xmm_xmm_imm8_instruction();

TEST(NASMBytecode, insertps_xmm_xmm_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			insertps(xmm4, xmm12, 4),
			insertps(xmm12, xmm4, 4)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_insertps_xmm_xmm_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_dpps_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, dpps_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			dpps(xmm4, oword[r12 + rax], 4_b),
			dpps(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_dpps_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_dppd_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, dppd_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			dppd(xmm4, oword[r12 + rax], 4_b),
			dppd(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_dppd_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mpsadbw_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, mpsadbw_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mpsadbw(xmm4, oword[r12 + rax], 4_b),
			mpsadbw(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mpsadbw_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpestrm_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, pcmpestrm_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpestrm(xmm4, oword[r12 + rax], 4_b),
			pcmpestrm(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpestrm_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpestri_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, pcmpestri_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpestri(xmm4, oword[r12 + rax], 4_b),
			pcmpestri(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpestri_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpistrm_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, pcmpistrm_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpistrm(xmm4, oword[r12 + rax], 4_b),
			pcmpistrm(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpistrm_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpistri_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, pcmpistri_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpistri(xmm4, oword[r12 + rax], 4_b),
			pcmpistri(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpistri_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovo_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovo_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovo(cx, word[r11 + rbx]),
			cmovo(ebx, dword[r11 + rbx]),
			cmovo(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovo_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovno_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovno_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovno(cx, word[r11 + rbx]),
			cmovno(ebx, dword[r11 + rbx]),
			cmovno(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovno_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovb_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovb_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovb(cx, word[r11 + rbx]),
			cmovb(ebx, dword[r11 + rbx]),
			cmovb(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovb_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovnae_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovnae_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovnae(cx, word[r11 + rbx]),
			cmovnae(ebx, dword[r11 + rbx]),
			cmovnae(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovnae_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovc_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovc_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovc(cx, word[r11 + rbx]),
			cmovc(ebx, dword[r11 + rbx]),
			cmovc(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovc_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovnb_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovnb_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovnb(cx, word[r11 + rbx]),
			cmovnb(ebx, dword[r11 + rbx]),
			cmovnb(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovnb_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovae_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovae_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovae(cx, word[r11 + rbx]),
			cmovae(ebx, dword[r11 + rbx]),
			cmovae(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovae_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovnc_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovnc_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovnc(cx, word[r11 + rbx]),
			cmovnc(ebx, dword[r11 + rbx]),
			cmovnc(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovnc_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovz_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovz_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovz(cx, word[r11 + rbx]),
			cmovz(ebx, dword[r11 + rbx]),
			cmovz(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovz_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmove_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmove_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmove(cx, word[r11 + rbx]),
			cmove(ebx, dword[r11 + rbx]),
			cmove(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmove_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovnz_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovnz_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovnz(cx, word[r11 + rbx]),
			cmovnz(ebx, dword[r11 + rbx]),
			cmovnz(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovnz_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovne_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovne_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovne(cx, word[r11 + rbx]),
			cmovne(ebx, dword[r11 + rbx]),
			cmovne(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovne_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovbe_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovbe_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovbe(cx, word[r11 + rbx]),
			cmovbe(ebx, dword[r11 + rbx]),
			cmovbe(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovbe_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovna_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovna_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovna(cx, word[r11 + rbx]),
			cmovna(ebx, dword[r11 + rbx]),
			cmovna(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovna_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovnbe_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovnbe_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovnbe(cx, word[r11 + rbx]),
			cmovnbe(ebx, dword[r11 + rbx]),
			cmovnbe(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovnbe_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmova_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmova_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmova(cx, word[r11 + rbx]),
			cmova(ebx, dword[r11 + rbx]),
			cmova(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmova_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovs_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovs_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovs(cx, word[r11 + rbx]),
			cmovs(ebx, dword[r11 + rbx]),
			cmovs(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovs_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovns_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovns_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovns(cx, word[r11 + rbx]),
			cmovns(ebx, dword[r11 + rbx]),
			cmovns(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovns_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovp_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovp_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovp(cx, word[r11 + rbx]),
			cmovp(ebx, dword[r11 + rbx]),
			cmovp(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovp_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovpe_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovpe_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovpe(cx, word[r11 + rbx]),
			cmovpe(ebx, dword[r11 + rbx]),
			cmovpe(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovpe_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovnp_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovnp_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovnp(cx, word[r11 + rbx]),
			cmovnp(ebx, dword[r11 + rbx]),
			cmovnp(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovnp_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovpo_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovpo_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovpo(cx, word[r11 + rbx]),
			cmovpo(ebx, dword[r11 + rbx]),
			cmovpo(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovpo_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovl_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovl_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovl(cx, word[r11 + rbx]),
			cmovl(ebx, dword[r11 + rbx]),
			cmovl(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovl_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovnge_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovnge_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovnge(cx, word[r11 + rbx]),
			cmovnge(ebx, dword[r11 + rbx]),
			cmovnge(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovnge_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovnl_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovnl_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovnl(cx, word[r11 + rbx]),
			cmovnl(ebx, dword[r11 + rbx]),
			cmovnl(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovnl_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovge_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovge_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovge(cx, word[r11 + rbx]),
			cmovge(ebx, dword[r11 + rbx]),
			cmovge(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovge_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovle_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovle_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovle(cx, word[r11 + rbx]),
			cmovle(ebx, dword[r11 + rbx]),
			cmovle(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovle_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovng_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovng_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovng(cx, word[r11 + rbx]),
			cmovng(ebx, dword[r11 + rbx]),
			cmovng(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovng_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovnle_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovnle_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovnle(cx, word[r11 + rbx]),
			cmovnle(ebx, dword[r11 + rbx]),
			cmovnle(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovnle_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmovg_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, cmovg_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmovg(cx, word[r11 + rbx]),
			cmovg(ebx, dword[r11 + rbx]),
			cmovg(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmovg_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movmskps_r32_64_xmm_instruction();

TEST(NASMBytecode, movmskps_r32_64_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movmskps(edx, xmm2),
			movmskps(rdx, xmm7)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movmskps_r32_64_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movmskpd_r32_64_xmm_instruction();

TEST(NASMBytecode, movmskpd_r32_64_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movmskpd(edx, xmm2),
			movmskpd(rdx, xmm7)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movmskpd_r32_64_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sqrtps_xmm_xmmm128_instruction();

TEST(NASMBytecode, sqrtps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sqrtps(xmm13, oword[r12 + rax]),
			sqrtps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sqrtps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sqrtss_xmm_xmmm32_instruction();

TEST(NASMBytecode, sqrtss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sqrtss(xmm4, dword[r12 + rax]),
			sqrtss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sqrtss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sqrtpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, sqrtpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sqrtpd(xmm13, oword[r12 + rax]),
			sqrtpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sqrtpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sqrtsd_xmm_xmmm64_instruction();

TEST(NASMBytecode, sqrtsd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			sqrtsd(xmm12, qword[r12 + rax]),
			sqrtsd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sqrtsd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rsqrtps_xmm_xmmm128_instruction();

TEST(NASMBytecode, rsqrtps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rsqrtps(xmm13, oword[r12 + rax]),
			rsqrtps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rsqrtps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rsqrtss_xmm_xmmm32_instruction();

TEST(NASMBytecode, rsqrtss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rsqrtss(xmm4, dword[r12 + rax]),
			rsqrtss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rsqrtss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcpps_xmm_xmmm128_instruction();

TEST(NASMBytecode, rcpps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcpps(xmm13, oword[r12 + rax]),
			rcpps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcpps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rcpss_xmm_xmmm32_instruction();

TEST(NASMBytecode, rcpss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			rcpss(xmm4, dword[r12 + rax]),
			rcpss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rcpss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_andps_xmm_xmmm128_instruction();

TEST(NASMBytecode, andps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			andps(xmm13, oword[r12 + rax]),
			andps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_andps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_andpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, andpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			andpd(xmm13, oword[r12 + rax]),
			andpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_andpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_andnps_xmm_xmmm128_instruction();

TEST(NASMBytecode, andnps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			andnps(xmm13, oword[r12 + rax]),
			andnps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_andnps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_andnpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, andnpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			andnpd(xmm13, oword[r12 + rax]),
			andnpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_andnpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_orps_xmm_xmmm128_instruction();

TEST(NASMBytecode, orps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			orps(xmm13, oword[r12 + rax]),
			orps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_orps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_orpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, orpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			orpd(xmm13, oword[r12 + rax]),
			orpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_orpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xorps_xmm_xmmm128_instruction();

TEST(NASMBytecode, xorps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xorps(xmm13, oword[r12 + rax]),
			xorps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xorps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xorpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, xorpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xorpd(xmm13, oword[r12 + rax]),
			xorpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xorpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_addps_xmm_xmmm128_instruction();

TEST(NASMBytecode, addps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			addps(xmm13, oword[r12 + rax]),
			addps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_addps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_addss_xmm_xmmm32_instruction();

TEST(NASMBytecode, addss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			addss(xmm4, dword[r12 + rax]),
			addss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_addss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_addpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, addpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			addpd(xmm13, oword[r12 + rax]),
			addpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_addpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_addsd_xmm_xmmm64_instruction();

TEST(NASMBytecode, addsd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			addsd(xmm12, qword[r12 + rax]),
			addsd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_addsd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mulps_xmm_xmmm128_instruction();

TEST(NASMBytecode, mulps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mulps(xmm13, oword[r12 + rax]),
			mulps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mulps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mulss_xmm_xmmm32_instruction();

TEST(NASMBytecode, mulss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mulss(xmm4, dword[r12 + rax]),
			mulss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mulss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mulpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, mulpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mulpd(xmm13, oword[r12 + rax]),
			mulpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mulpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mulsd_xmm_xmmm64_instruction();

TEST(NASMBytecode, mulsd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			mulsd(xmm12, qword[r12 + rax]),
			mulsd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mulsd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtps2pd_xmm_xmmm128_instruction();

TEST(NASMBytecode, cvtps2pd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtps2pd(xmm13, oword[r12 + rax]),
			cvtps2pd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtps2pd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtpd2ps_xmm_xmmm128_instruction();

TEST(NASMBytecode, cvtpd2ps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtpd2ps(xmm13, oword[r12 + rax]),
			cvtpd2ps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtpd2ps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtss2sd_xmm_xmmm32_instruction();

TEST(NASMBytecode, cvtss2sd_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtss2sd(xmm4, dword[r12 + rax]),
			cvtss2sd(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtss2sd_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtsd2ss_xmm_xmmm64_instruction();

TEST(NASMBytecode, cvtsd2ss_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtsd2ss(xmm12, qword[r12 + rax]),
			cvtsd2ss(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtsd2ss_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtdq2ps_xmm_xmmm128_instruction();

TEST(NASMBytecode, cvtdq2ps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtdq2ps(xmm13, oword[r12 + rax]),
			cvtdq2ps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtdq2ps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtps2dq_xmm_xmmm128_instruction();

TEST(NASMBytecode, cvtps2dq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtps2dq(xmm13, oword[r12 + rax]),
			cvtps2dq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtps2dq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvttps2dq_xmm_xmmm128_instruction();

TEST(NASMBytecode, cvttps2dq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvttps2dq(xmm13, oword[r12 + rax]),
			cvttps2dq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvttps2dq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_subps_xmm_xmmm128_instruction();

TEST(NASMBytecode, subps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			subps(xmm13, oword[r12 + rax]),
			subps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_subps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_subss_xmm_xmmm32_instruction();

TEST(NASMBytecode, subss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			subss(xmm4, dword[r12 + rax]),
			subss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_subss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_subpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, subpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			subpd(xmm13, oword[r12 + rax]),
			subpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_subpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_subsd_xmm_xmmm64_instruction();

TEST(NASMBytecode, subsd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			subsd(xmm12, qword[r12 + rax]),
			subsd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_subsd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_minps_xmm_xmmm128_instruction();

TEST(NASMBytecode, minps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			minps(xmm13, oword[r12 + rax]),
			minps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_minps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_minss_xmm_xmmm32_instruction();

TEST(NASMBytecode, minss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			minss(xmm4, dword[r12 + rax]),
			minss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_minss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_minpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, minpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			minpd(xmm13, oword[r12 + rax]),
			minpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_minpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_minsd_xmm_xmmm64_instruction();

TEST(NASMBytecode, minsd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			minsd(xmm12, qword[r12 + rax]),
			minsd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_minsd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_divps_xmm_xmmm128_instruction();

TEST(NASMBytecode, divps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			divps(xmm13, oword[r12 + rax]),
			divps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_divps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_divss_xmm_xmmm32_instruction();

TEST(NASMBytecode, divss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			divss(xmm4, dword[r12 + rax]),
			divss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_divss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_divpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, divpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			divpd(xmm13, oword[r12 + rax]),
			divpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_divpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_divsd_xmm_xmmm64_instruction();

TEST(NASMBytecode, divsd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			divsd(xmm12, qword[r12 + rax]),
			divsd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_divsd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_maxps_xmm_xmmm128_instruction();

TEST(NASMBytecode, maxps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			maxps(xmm13, oword[r12 + rax]),
			maxps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_maxps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_maxss_xmm_xmmm32_instruction();

TEST(NASMBytecode, maxss_xmm_xmmm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			maxss(xmm4, dword[r12 + rax]),
			maxss(xmm2, xmm9)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_maxss_xmm_xmmm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_maxpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, maxpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			maxpd(xmm13, oword[r12 + rax]),
			maxpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_maxpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_maxsd_xmm_xmmm64_instruction();

TEST(NASMBytecode, maxsd_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			maxsd(xmm12, qword[r12 + rax]),
			maxsd(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_maxsd_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_punpcklbw_xmm_xmmm128_instruction();

TEST(NASMBytecode, punpcklbw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			punpcklbw(xmm13, oword[r12 + rax]),
			punpcklbw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_punpcklbw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_punpcklwd_xmm_xmmm128_instruction();

TEST(NASMBytecode, punpcklwd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			punpcklwd(xmm13, oword[r12 + rax]),
			punpcklwd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_punpcklwd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_punpckldq_xmm_xmmm128_instruction();

TEST(NASMBytecode, punpckldq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			punpckldq(xmm13, oword[r12 + rax]),
			punpckldq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_punpckldq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_packsswb_xmm_xmmm128_instruction();

TEST(NASMBytecode, packsswb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			packsswb(xmm13, oword[r12 + rax]),
			packsswb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_packsswb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpgtb_xmm_xmmm128_instruction();

TEST(NASMBytecode, pcmpgtb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpgtb(xmm13, oword[r12 + rax]),
			pcmpgtb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpgtb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpgtw_xmm_xmmm128_instruction();

TEST(NASMBytecode, pcmpgtw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpgtw(xmm13, oword[r12 + rax]),
			pcmpgtw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpgtw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpgtd_xmm_xmmm128_instruction();

TEST(NASMBytecode, pcmpgtd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpgtd(xmm13, oword[r12 + rax]),
			pcmpgtd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpgtd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_packuswb_xmm_xmmm128_instruction();

TEST(NASMBytecode, packuswb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			packuswb(xmm13, oword[r12 + rax]),
			packuswb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_packuswb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_punpckhbw_xmm_xmmm128_instruction();

TEST(NASMBytecode, punpckhbw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			punpckhbw(xmm13, oword[r12 + rax]),
			punpckhbw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_punpckhbw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_punpckhwd_xmm_xmmm128_instruction();

TEST(NASMBytecode, punpckhwd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			punpckhwd(xmm13, oword[r12 + rax]),
			punpckhwd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_punpckhwd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_punpckhdq_xmm_xmmm128_instruction();

TEST(NASMBytecode, punpckhdq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			punpckhdq(xmm13, oword[r12 + rax]),
			punpckhdq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_punpckhdq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_packssdw_xmm_xmmm128_instruction();

TEST(NASMBytecode, packssdw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			packssdw(xmm13, oword[r12 + rax]),
			packssdw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_packssdw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_punpcklqdq_xmm_xmmm128_instruction();

TEST(NASMBytecode, punpcklqdq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			punpcklqdq(xmm13, oword[r12 + rax]),
			punpcklqdq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_punpcklqdq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_punpckhqdq_xmm_xmmm128_instruction();

TEST(NASMBytecode, punpckhqdq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			punpckhqdq(xmm13, oword[r12 + rax]),
			punpckhqdq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_punpckhqdq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movd_mm_rm32_instruction();

TEST(NASMBytecode, movd_mm_rm32_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movd(mm2, edx),
			movd(mm6, dword[r11 + rax * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movd_mm_rm32_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movq_mm_r64_instruction();

TEST(NASMBytecode, movq_mm_r64_instruction_test)
{
	const auto casm_bytecode{ movq(mm2, rdx).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movq_mm_r64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movq_xmm_r64_instruction();

TEST(NASMBytecode, movq_xmm_r64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movq(xmm15, qword [eax + r11d]),
			movq(xmm3, r14)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movq_xmm_r64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movq_mm_mm_instruction();

TEST(NASMBytecode, movq_mm_mm_instruction_test)
{
	const auto casm_bytecode{ movq(mm2, mm3).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movq_mm_mm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movq_mm_m64_instruction();

TEST(NASMBytecode, movq_mm_m64_instruction_test)
{
	const auto casm_bytecode{ movq(mm2, qword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movq_mm_m64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movdqa_xmm_xmmm128_instruction();

TEST(NASMBytecode, movdqa_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movdqa(xmm13, oword[r12 + rax]),
			movdqa(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movdqa_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movdqu_xmm_xmmm128_instruction();

TEST(NASMBytecode, movdqu_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movdqu(xmm13, oword[r12 + rax]),
			movdqu(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movdqu_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pshuflw_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, pshuflw_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pshuflw(xmm4, oword[r12 + rax], 4_b),
			pshuflw(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pshuflw_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pshufhw_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, pshufhw_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pshufhw(xmm4, oword[r12 + rax], 4_b),
			pshufhw(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pshufhw_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pshufd_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, pshufd_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pshufd(xmm4, oword[r12 + rax], 4_b),
			pshufd(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pshufd_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrlw_mm_imm8_instruction_by_number();

TEST(NASMBytecode, psrlw_mm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psrlw(mm2, 0x11).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrlw_mm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrlw_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, psrlw_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psrlw(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrlw_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psraw_mm_imm8_instruction_by_number();

TEST(NASMBytecode, psraw_mm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psraw(mm2, 0x11).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psraw_mm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psraw_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, psraw_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psraw(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psraw_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psllw_mm_imm8_instruction_by_number();

TEST(NASMBytecode, psllw_mm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psllw(mm2, 0x11).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psllw_mm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psllw_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, psllw_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psllw(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psllw_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrld_mm_imm8_instruction_by_number();

TEST(NASMBytecode, psrld_mm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psrld(mm2, 0x11).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrld_mm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrld_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, psrld_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psrld(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrld_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrad_mm_imm8_instruction_by_number();

TEST(NASMBytecode, psrad_mm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psrad(mm2, 0x11).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrad_mm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrad_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, psrad_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psrad(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrad_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pslld_mm_imm8_instruction_by_number();

TEST(NASMBytecode, pslld_mm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ pslld(mm2, 0x11).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pslld_mm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pslld_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, pslld_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ pslld(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pslld_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrlq_mm_imm8_instruction_by_number();

TEST(NASMBytecode, psrlq_mm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psrlq(mm2, 0x11).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrlq_mm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrlq_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, psrlq_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psrlq(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrlq_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrldq_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, psrldq_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psrldq(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrldq_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psllq_mm_imm8_instruction_by_number();

TEST(NASMBytecode, psllq_mm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psllq(mm2, 0x11).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psllq_mm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psllq_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, psllq_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ psllq(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psllq_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pslldq_xmm_imm8_instruction_by_number();

TEST(NASMBytecode, pslldq_xmm_imm8_instruction_by_number_test)
{
	const auto casm_bytecode{ pslldq(xmm2, 17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pslldq_xmm_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpeqb_xmm_xmmm128_instruction();

TEST(NASMBytecode, pcmpeqb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpeqb(xmm13, oword[r12 + rax]),
			pcmpeqb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpeqb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpeqw_xmm_xmmm128_instruction();

TEST(NASMBytecode, pcmpeqw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpeqw(xmm13, oword[r12 + rax]),
			pcmpeqw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpeqw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pcmpeqd_xmm_xmmm128_instruction();

TEST(NASMBytecode, pcmpeqd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pcmpeqd(xmm13, oword[r12 + rax]),
			pcmpeqd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pcmpeqd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_emms_no_operands_instruction();

TEST(NASMBytecode, emms_no_operands_instruction_test)
{
	const auto casm_bytecode{ emms().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_emms_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_vmread_rm64_r64_instruction();

TEST(NASMBytecode, vmread_rm64_r64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			vmread(rdx, rax),
			vmread(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_vmread_rm64_r64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_vmwrite_r64_rm64_instruction();

TEST(NASMBytecode, vmwrite_r64_rm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			vmwrite(rax, rdx),
			vmwrite(rax, qword[rdx + rdx * 8])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_vmwrite_r64_rm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_haddpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, haddpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			haddpd(xmm13, oword[r12 + rax]),
			haddpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_haddpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_haddps_xmm_xmmm128_instruction();

TEST(NASMBytecode, haddps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			haddps(xmm13, oword[r12 + rax]),
			haddps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_haddps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_hsubpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, hsubpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			hsubpd(xmm13, oword[r12 + rax]),
			hsubpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_hsubpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_hsubps_xmm_xmmm128_instruction();

TEST(NASMBytecode, hsubps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			hsubps(xmm13, oword[r12 + rax]),
			hsubps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_hsubps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movd_rm32_mm_instruction();

TEST(NASMBytecode, movd_rm32_mm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movd(edx, mm5),
			movd(dword[r11 + rax * 4], mm5)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movd_rm32_mm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movq_rm64_mm_instruction();

TEST(NASMBytecode, movq_rm64_mm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movq(rdx, mm5),
			movq(qword[ebx * 4], mm5)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movq_rm64_mm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movd_rm32_xmm_instruction();

TEST(NASMBytecode, movd_rm32_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movd(edx, xmm5),
			movd(dword[ebx * 4], xmm5)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movd_rm32_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movq_xmm_xmmm64_instruction();

TEST(NASMBytecode, movq_xmm_xmmm64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movq(xmm12, qword[r12 + rax]),
			movq(xmm11, xmm3)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movq_xmm_xmmm64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movq_mmm64_mm_instruction();

TEST(NASMBytecode, movq_mmm64_mm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movq(qword[r11 + rax], mm6),
			movq(mm2, mm6)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movq_mmm64_mm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movdqa_xmmm128_xmm_instruction();

TEST(NASMBytecode, movdqa_xmmm128_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movdqa(xmm2, xmm6),
			movdqa(oword[rbp + rcx * 2], xmm6),
			movdqa(oword[r10 + rbp + 0x80_d], xmm6),
			movdqa(oword[rbp + 0x8012333_d], xmm6),
			movdqa(oword[rbp + 0x80_d], xmm6),
			movdqa(oword[rbp + 0xff_b], xmm6),
			movdqa(oword[rbp + 0xff_d], xmm6)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movdqa_xmmm128_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movdqu_xmmm128_xmm_instruction();

TEST(NASMBytecode, movdqu_xmmm128_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movdqu(xmm2, xmm6),
			movdqu(oword[rbp + rcx * 2], xmm6),
			movdqu(oword[r10 + rbp + 0x80_d], xmm6),
			movdqu(oword[rbp + 0x8012333_d], xmm6),
			movdqu(oword[rbp + 0x80_d], xmm6),
			movdqu(oword[rbp + 0xff_b], xmm6),
			movdqu(oword[rbp + 0xff_d], xmm6)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movdqu_xmmm128_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_push_fs_instruction();

TEST(NASMBytecode, push_fs_instruction_test)
{
	const auto casm_bytecode{ push(fs).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_push_fs_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pop_fs_instruction();

TEST(NASMBytecode, pop_fs_instruction_test)
{
	const auto casm_bytecode{ pop(fs).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pop_fs_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cpuid_no_operands_instruction();

TEST(NASMBytecode, cpuid_no_operands_instruction_test)
{
	const auto casm_bytecode{ cpuid().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cpuid_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_bt_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, bt_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			bt(dx, ax),
			bt(edx, eax),
			bt(rdx, rax),
			bt(word[ebx * 4], dx),
			bt(dword[ebx * 4], edx),
			bt(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_bt_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shld_rm16_32_64_r16_32_64_imm8_instruction();

TEST(NASMBytecode, shld_rm16_32_64_r16_32_64_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shld(dx, ax, 0x11_b),
			shld(edx, eax, 0x11_b),
			shld(rdx, rax, 0x11_b),
			shld(word[ebx * 4], dx, 0x11_b),
			shld(dword[ebx * 4], edx, 0x11_b),
			shld(qword[ebx * 4], rdx, 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shld_rm16_32_64_r16_32_64_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shld_rm16_32_64_r16_32_64_cl_instruction();

TEST(NASMBytecode, shld_rm16_32_64_r16_32_64_cl_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shld(dx, ax, cl),
			shld(edx, eax, cl),
			shld(rdx, rax, cl),
			shld(word[ebx * 4], dx, cl),
			shld(dword[ebx * 4], edx, cl),
			shld(qword[ebx * 4], rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shld_rm16_32_64_r16_32_64_cl_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_push_gs_instruction();

TEST(NASMBytecode, push_gs_instruction_test)
{
	const auto casm_bytecode{ push(gs).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_push_gs_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pop_gs_instruction();

TEST(NASMBytecode, pop_gs_instruction_test)
{
	const auto casm_bytecode{ pop(gs).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pop_gs_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_rsm_no_operands_instruction();

TEST(NASMBytecode, rsm_no_operands_instruction_test)
{
	const auto casm_bytecode{ rsm().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_rsm_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_bts_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, bts_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			bts(dx, ax),
			bts(edx, eax),
			bts(rdx, rax),
			bts(word[ebx * 4], dx),
			bts(dword[ebx * 4], edx),
			bts(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_bts_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shrd_rm16_32_64_r16_32_64_imm8_instruction();

TEST(NASMBytecode, shrd_rm16_32_64_r16_32_64_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shrd(dx, ax, 0x11_b),
			shrd(edx, eax, 0x11_b),
			shrd(rdx, rax, 0x11_b),
			shrd(word[ebx * 4], dx, 0x11_b),
			shrd(dword[ebx * 4], edx, 0x11_b),
			shrd(qword[ebx * 4], rdx, 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shrd_rm16_32_64_r16_32_64_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shrd_rm16_32_64_r16_32_64_cl_instruction();

TEST(NASMBytecode, shrd_rm16_32_64_r16_32_64_cl_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shrd(dx, ax, cl),
			shrd(edx, eax, cl),
			shrd(rdx, rax, cl),
			shrd(word[ebx * 4], dx, cl),
			shrd(dword[ebx * 4], edx, cl),
			shrd(qword[ebx * 4], rdx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shrd_rm16_32_64_r16_32_64_cl_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fxsave_m_instruction_by_number();

TEST(NASMBytecode, fxsave_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fxsave(ptr[0x11223344]),
			fxsave(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fxsave_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_fxrstor_m_instruction_by_number();

TEST(NASMBytecode, fxrstor_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			fxrstor(ptr[0x11223344]),
			fxrstor(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_fxrstor_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_ldmxcsr_m32_instruction_by_number();

TEST(NASMBytecode, ldmxcsr_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ ldmxcsr(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_ldmxcsr_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_stmxcsr_m32_instruction_by_number();

TEST(NASMBytecode, stmxcsr_m32_instruction_by_number_test)
{
	const auto casm_bytecode{ stmxcsr(dword[r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_stmxcsr_m32_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xsave_m_instruction_by_number();

TEST(NASMBytecode, xsave_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xsave(ptr[0x11223344]),
			xsave(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xsave_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lfence_no_operands_instruction();

TEST(NASMBytecode, lfence_no_operands_instruction_test)
{
	const auto casm_bytecode{ lfence().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lfence_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xrstor_m_instruction_by_number();

TEST(NASMBytecode, xrstor_m_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xrstor(ptr[0x11223344]),
			xrstor(ptr[rbx + r12 * 4])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xrstor_m_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_mfence_no_operands_instruction();

TEST(NASMBytecode, mfence_no_operands_instruction_test)
{
	const auto casm_bytecode{ mfence().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_mfence_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_sfence_no_operands_instruction();

TEST(NASMBytecode, sfence_no_operands_instruction_test)
{
	const auto casm_bytecode{ sfence().bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_sfence_no_operands_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_clflush_m8_instruction_by_number();

TEST(NASMBytecode, clflush_m8_instruction_by_number_test)
{
	const auto casm_bytecode{ clflush(byte_ptr [r11 + rax]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_clflush_m8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_imul_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, imul_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			imul(cx, word[r11 + rbx]),
			imul(ebx, dword[r11 + rbx]),
			imul(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_imul_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpxchg_rm8_r8_instruction();

TEST(NASMBytecode, cmpxchg_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmpxchg(dl, ah),
			cmpxchg(r9b, al),
			cmpxchg(al, r11b),
			cmpxchg(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			cmpxchg(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			cmpxchg(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			cmpxchg(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			cmpxchg(byte_ptr [rdx + rdx * 8], al),
			cmpxchg(byte_ptr [rdx + rdx * 8], spl),
			cmpxchg(byte_ptr [r11 + rdx * 8], dil),
			cmpxchg(byte_ptr [edx + r11d * 8], r8b),
			cmpxchg(byte_ptr [r11d], bl),
			cmpxchg(byte_ptr [rdx], bpl),
			cmpxchg(byte_ptr [r11d * 4], bl),
			cmpxchg(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpxchg_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpxchg_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, cmpxchg_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmpxchg(dx, ax),
			cmpxchg(edx, eax),
			cmpxchg(rdx, rax),
			cmpxchg(word[ebx * 4], dx),
			cmpxchg(dword[ebx * 4], edx),
			cmpxchg(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpxchg_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lss_r16_32_64_m_instruction();

TEST(NASMBytecode, lss_r16_32_64_m_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lss(dx, ptr[r14d]),
			lss(edx, ptr[r14d]),
			lss(rdx, ptr[r14d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lss_r16_32_64_m_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_btr_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, btr_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			btr(dx, ax),
			btr(edx, eax),
			btr(rdx, rax),
			btr(word[ebx * 4], dx),
			btr(dword[ebx * 4], edx),
			btr(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_btr_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lfs_r16_32_64_m_instruction();

TEST(NASMBytecode, lfs_r16_32_64_m_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lfs(dx, ptr[r14d]),
			lfs(edx, ptr[r14d]),
			lfs(rdx, ptr[r14d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lfs_r16_32_64_m_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lgs_r16_32_64_m_instruction();

TEST(NASMBytecode, lgs_r16_32_64_m_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			lgs(dx, ptr[r14d]),
			lgs(edx, ptr[r14d]),
			lgs(rdx, ptr[r14d])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lgs_r16_32_64_m_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movzx_r16_32_64_rm8_instruction();

TEST(NASMBytecode, movzx_r16_32_64_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movzx(dx, byte_ptr [eax]),
			movzx(edx, byte_ptr [r11 + rbx]),
			movzx(rdx, byte_ptr [r8d]),
			movzx(dx, al),
			movzx(edx, al),
			movzx(rdx, al)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movzx_r16_32_64_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movzx_r16_32_rm16_instruction();

TEST(NASMBytecode, movzx_r16_32_rm16_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movzx(ebx, dx),
			movzx(edx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movzx_r16_32_rm16_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_popcnt_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, popcnt_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			popcnt(cx, word[r11 + rbx]),
			popcnt(ebx, dword[r11 + rbx]),
			popcnt(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_popcnt_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_bt_rm16_32_64_imm8_instruction_by_number();

TEST(NASMBytecode, bt_rm16_32_64_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			bt(dx, 0x11_b),
			bt(edx, 0x11_b),
			bt(rdx, 0x11_b),
			bt(word[ebx * 4], 0x11_b),
			bt(dword[ebx * 4], 0x11_b),
			bt(qword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_bt_rm16_32_64_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_bts_rm16_32_64_imm8_instruction_by_number();

TEST(NASMBytecode, bts_rm16_32_64_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			bts(dx, 0x11_b),
			bts(edx, 0x11_b),
			bts(rdx, 0x11_b),
			bts(word[ebx * 4], 0x11_b),
			bts(dword[ebx * 4], 0x11_b),
			bts(qword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_bts_rm16_32_64_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_btr_rm16_32_64_imm8_instruction_by_number();

TEST(NASMBytecode, btr_rm16_32_64_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			btr(dx, 0x11_b),
			btr(edx, 0x11_b),
			btr(rdx, 0x11_b),
			btr(word[ebx * 4], 0x11_b),
			btr(dword[ebx * 4], 0x11_b),
			btr(qword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_btr_rm16_32_64_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_btc_rm16_32_64_imm8_instruction_by_number();

TEST(NASMBytecode, btc_rm16_32_64_imm8_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			btc(dx, 0x11_b),
			btc(edx, 0x11_b),
			btc(rdx, 0x11_b),
			btc(word[ebx * 4], 0x11_b),
			btc(dword[ebx * 4], 0x11_b),
			btc(qword[ebx * 4], 0x11_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_btc_rm16_32_64_imm8_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_btc_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, btc_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			btc(dx, ax),
			btc(edx, eax),
			btc(rdx, rax),
			btc(word[ebx * 4], dx),
			btc(dword[ebx * 4], edx),
			btc(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_btc_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_bsf_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, bsf_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			bsf(cx, word[r11 + rbx]),
			bsf(ebx, dword[r11 + rbx]),
			bsf(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_bsf_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_bsr_r16_32_64_rm16_32_64_instruction();

TEST(NASMBytecode, bsr_r16_32_64_rm16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			bsr(cx, word[r11 + rbx]),
			bsr(ebx, dword[r11 + rbx]),
			bsr(rax, qword[r12])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_bsr_r16_32_64_rm16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsx_r16_32_64_rm8_instruction();

TEST(NASMBytecode, movsx_r16_32_64_rm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movsx(dx, byte_ptr [eax]),
			movsx(edx, byte_ptr [r11 + rbx]),
			movsx(rdx, byte_ptr [r8d]),
			movsx(dx, al),
			movsx(edx, al),
			movsx(rdx, al)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsx_r16_32_64_rm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movsx_r16_32_rm16_instruction();

TEST(NASMBytecode, movsx_r16_32_rm16_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movsx(ebx, dx),
			movsx(edx, cl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movsx_r16_32_rm16_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xadd_rm8_r8_instruction();

TEST(NASMBytecode, xadd_rm8_r8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xadd(dl, ah),
			xadd(r9b, al),
			xadd(al, r11b),
			xadd(byte_ptr [rdx + rdx * 8 + 0x1122], al),
			xadd(byte_ptr [rdx + rdx * 8 + 0x1122], spl),
			xadd(byte_ptr [r11 + rdx * 8 + 0x1122], dil),
			xadd(byte_ptr [edx + r11d * 8 + 0x1122], r8b),
			xadd(byte_ptr [rdx + rdx * 8], al),
			xadd(byte_ptr [rdx + rdx * 8], spl),
			xadd(byte_ptr [r11 + rdx * 8], dil),
			xadd(byte_ptr [edx + r11d * 8], r8b),
			xadd(byte_ptr [r11d], bl),
			xadd(byte_ptr [rdx], bpl),
			xadd(byte_ptr [r11d * 4], bl),
			xadd(byte_ptr [rdx * 4], bpl)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xadd_rm8_r8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_xadd_rm16_32_64_r16_32_64_instruction();

TEST(NASMBytecode, xadd_rm16_32_64_r16_32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			xadd(dx, ax),
			xadd(edx, eax),
			xadd(rdx, rax),
			xadd(word[ebx * 4], dx),
			xadd(dword[ebx * 4], edx),
			xadd(qword[ebx * 4], rdx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_xadd_rm16_32_64_r16_32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpps_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, cmpps_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmpps(xmm4, oword[r12 + rax], 4_b),
			cmpps(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpps_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpss_xmm_xmmm32_imm8_instruction();

TEST(NASMBytecode, cmpss_xmm_xmmm32_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmpss(xmm4, dword[r12 + rax], 4_b),
			cmpss(xmm2, xmm3, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpss_xmm_xmmm32_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmppd_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, cmppd_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmppd(xmm4, oword[r12 + rax], 4_b),
			cmppd(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmppd_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpsd_xmm_xmmm64_imm8_instruction();

TEST(NASMBytecode, cmpsd_xmm_xmmm64_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmpsd(xmm14, qword[r12 + rax], 4_b),
			cmpsd(xmm2, xmm11, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpsd_xmm_xmmm64_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movnti_m32_64_r32_64_instruction();

TEST(NASMBytecode, movnti_m32_64_r32_64_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movnti(dword[r11 + rbx * 8 + 0x818181], r13d),
			movnti(qword[r11 + rbx * 4 + 0x11_b], rcx)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movnti_m32_64_r32_64_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pinsrw_mm_r32_imm8_instruction();

TEST(NASMBytecode, pinsrw_mm_r32_imm8_instruction_test)
{
	const auto casm_bytecode{ pinsrw(mm2, edx, 0x11).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pinsrw_mm_r32_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pinsrw_mm_m16_imm8_instruction();

TEST(NASMBytecode, pinsrw_mm_m16_imm8_instruction_test)
{
	const auto casm_bytecode{ pinsrw(mm2, word[r11 + rax], 0x11_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pinsrw_mm_m16_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pinsrw_xmm_r32_imm8_instruction();

TEST(NASMBytecode, pinsrw_xmm_r32_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pinsrw(xmm15, ecx, 4_b),
			pinsrw(xmm3, r13d, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pinsrw_xmm_r32_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pinsrw_xmm_m16_imm8_instruction();

TEST(NASMBytecode, pinsrw_xmm_m16_imm8_instruction_test)
{
	const auto casm_bytecode{ pinsrw(xmm2, word[0x11223344_d], 0x17_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pinsrw_xmm_m16_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pextrw_r32_mm_imm8_instruction();

TEST(NASMBytecode, pextrw_r32_mm_imm8_instruction_test)
{
	const auto casm_bytecode{ pextrw(edx, mm6, 0x11_b).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pextrw_r32_mm_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pextrw_r32_64_xmm_imm8_instruction();

TEST(NASMBytecode, pextrw_r32_64_xmm_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pextrw(edx, xmm2, 12_b),
			pextrw(rdx, xmm7, 12_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pextrw_r32_64_xmm_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shufps_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, shufps_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shufps(xmm4, oword[r12 + rax], 4_b),
			shufps(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shufps_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_shufpd_xmm_xmmm128_imm8_instruction();

TEST(NASMBytecode, shufpd_xmm_xmmm128_imm8_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			shufpd(xmm4, oword[r12 + rax], 4_b),
			shufpd(xmm9, xmm8, 4_b)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_shufpd_xmm_xmmm128_imm8_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cmpxchg16b_m128_instruction_by_number();

TEST(NASMBytecode, cmpxchg16b_m128_instruction_by_number_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cmpxchg16b(oword[0x88888888]),
			cmpxchg16b(oword[r11 + rdx * 8]),
			cmpxchg16b(oword[ecx + r13d * 8])
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cmpxchg16b_m128_instruction_by_number), casm_bytecode.size()) == 0);
};

extern "C" void nasm_bswap_r32_instruction_by_register();

TEST(NASMBytecode, bswap_r32_instruction_by_register_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			bswap(eax),
			bswap(ecx),
			bswap(edx),
			bswap(ebx),
			bswap(esp),
			bswap(ebp),
			bswap(esi),
			bswap(edi)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_bswap_r32_instruction_by_register), casm_bytecode.size()) == 0);
};

extern "C" void nasm_addsubpd_xmm_xmmm128_instruction();

TEST(NASMBytecode, addsubpd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			addsubpd(xmm13, oword[r12 + rax]),
			addsubpd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_addsubpd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_addsubps_xmm_xmmm128_instruction();

TEST(NASMBytecode, addsubps_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			addsubps(xmm13, oword[r12 + rax]),
			addsubps(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_addsubps_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrlw_xmm_xmmm128_instruction();

TEST(NASMBytecode, psrlw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psrlw(xmm13, oword[r12 + rax]),
			psrlw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrlw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrld_xmm_xmmm128_instruction();

TEST(NASMBytecode, psrld_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psrld(xmm13, oword[r12 + rax]),
			psrld(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrld_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrlq_xmm_xmmm128_instruction();

TEST(NASMBytecode, psrlq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psrlq(xmm13, oword[r12 + rax]),
			psrlq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrlq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_paddq_xmm_xmmm128_instruction();

TEST(NASMBytecode, paddq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			paddq(xmm13, oword[r12 + rax]),
			paddq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_paddq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pmullw_xmm_xmmm128_instruction();

TEST(NASMBytecode, pmullw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pmullw(xmm13, oword[r12 + rax]),
			pmullw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pmullw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movq_m64_xmm_instruction();

TEST(NASMBytecode, movq_m64_xmm_instruction_test)
{
	const auto casm_bytecode{ movq(qword[r11 + rax], xmm2).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movq_m64_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movdq2q_mm_xmm_instruction();

TEST(NASMBytecode, movdq2q_mm_xmm_instruction_test)
{
	const auto casm_bytecode{ movdq2q(mm2, xmm3).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movdq2q_mm_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pmovmskb_r32_mm_instruction();

TEST(NASMBytecode, pmovmskb_r32_mm_instruction_test)
{
	const auto casm_bytecode{ pmovmskb(edx, mm6).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pmovmskb_r32_mm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pmovmskb_r32_xmm_instruction();

TEST(NASMBytecode, pmovmskb_r32_xmm_instruction_test)
{
	const auto casm_bytecode{ pmovmskb(edx, xmm2).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pmovmskb_r32_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psubusb_xmm_xmmm128_instruction();

TEST(NASMBytecode, psubusb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psubusb(xmm13, oword[r12 + rax]),
			psubusb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psubusb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psubusw_xmm_xmmm128_instruction();

TEST(NASMBytecode, psubusw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psubusw(xmm13, oword[r12 + rax]),
			psubusw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psubusw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pminub_xmm_xmmm128_instruction();

TEST(NASMBytecode, pminub_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pminub(xmm13, oword[r12 + rax]),
			pminub(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pminub_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pand_xmm_xmmm128_instruction();

TEST(NASMBytecode, pand_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pand(xmm13, oword[r12 + rax]),
			pand(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pand_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_paddusb_xmm_xmmm128_instruction();

TEST(NASMBytecode, paddusb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			paddusb(xmm13, oword[r12 + rax]),
			paddusb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_paddusb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_paddusw_xmm_xmmm128_instruction();

TEST(NASMBytecode, paddusw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			paddusw(xmm13, oword[r12 + rax]),
			paddusw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_paddusw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pmaxub_xmm_xmmm128_instruction();

TEST(NASMBytecode, pmaxub_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pmaxub(xmm13, oword[r12 + rax]),
			pmaxub(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pmaxub_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pandn_xmm_xmmm128_instruction();

TEST(NASMBytecode, pandn_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pandn(xmm13, oword[r12 + rax]),
			pandn(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pandn_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pavgb_xmm_xmmm128_instruction();

TEST(NASMBytecode, pavgb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pavgb(xmm13, oword[r12 + rax]),
			pavgb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pavgb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psraw_xmm_xmmm128_instruction();

TEST(NASMBytecode, psraw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psraw(xmm13, oword[r12 + rax]),
			psraw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psraw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psrad_xmm_xmmm128_instruction();

TEST(NASMBytecode, psrad_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psrad(xmm13, oword[r12 + rax]),
			psrad(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psrad_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pavgw_xmm_xmmm128_instruction();

TEST(NASMBytecode, pavgw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pavgw(xmm13, oword[r12 + rax]),
			pavgw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pavgw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pmulhuw_xmm_xmmm128_instruction();

TEST(NASMBytecode, pmulhuw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pmulhuw(xmm13, oword[r12 + rax]),
			pmulhuw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pmulhuw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pmulhw_xmm_xmmm128_instruction();

TEST(NASMBytecode, pmulhw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pmulhw(xmm13, oword[r12 + rax]),
			pmulhw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pmulhw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtpd2dq_xmm_xmmm128_instruction();

TEST(NASMBytecode, cvtpd2dq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtpd2dq(xmm13, oword[r12 + rax]),
			cvtpd2dq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtpd2dq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvttpd2dq_xmm_xmmm128_instruction();

TEST(NASMBytecode, cvttpd2dq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvttpd2dq(xmm13, oword[r12 + rax]),
			cvttpd2dq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvttpd2dq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_cvtdq2pd_xmm_xmmm128_instruction();

TEST(NASMBytecode, cvtdq2pd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			cvtdq2pd(xmm13, oword[r12 + rax]),
			cvtdq2pd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_cvtdq2pd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movntq_m64_mm_instruction();

TEST(NASMBytecode, movntq_m64_mm_instruction_test)
{
	const auto casm_bytecode{ movntq(qword[r11 + rax], mm2).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movntq_m64_mm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_movntdq_m128_xmm_instruction();

TEST(NASMBytecode, movntdq_m128_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			movntdq(oword[gs(0x8888888)], xmm2),
			movntdq(oword[r11 + rdx * 8], xmm8)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_movntdq_m128_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psubsb_xmm_xmmm128_instruction();

TEST(NASMBytecode, psubsb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psubsb(xmm13, oword[r12 + rax]),
			psubsb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psubsb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psubsw_xmm_xmmm128_instruction();

TEST(NASMBytecode, psubsw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psubsw(xmm13, oword[r12 + rax]),
			psubsw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psubsw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pminsw_xmm_xmmm128_instruction();

TEST(NASMBytecode, pminsw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pminsw(xmm13, oword[r12 + rax]),
			pminsw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pminsw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_por_xmm_xmmm128_instruction();

TEST(NASMBytecode, por_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			por(xmm13, oword[r12 + rax]),
			por(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_por_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_paddsb_xmm_xmmm128_instruction();

TEST(NASMBytecode, paddsb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			paddsb(xmm13, oword[r12 + rax]),
			paddsb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_paddsb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_paddsw_xmm_xmmm128_instruction();

TEST(NASMBytecode, paddsw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			paddsw(xmm13, oword[r12 + rax]),
			paddsw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_paddsw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pmaxsw_xmm_xmmm128_instruction();

TEST(NASMBytecode, pmaxsw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pmaxsw(xmm13, oword[r12 + rax]),
			pmaxsw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pmaxsw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pxor_xmm_xmmm128_instruction();

TEST(NASMBytecode, pxor_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pxor(xmm13, oword[r12 + rax]),
			pxor(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pxor_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_lddqu_xmm_m128_instruction();

TEST(NASMBytecode, lddqu_xmm_m128_instruction_test)
{
	const auto casm_bytecode{ lddqu(xmm2, oword [rbp + r13 + 0x17_b]).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_lddqu_xmm_m128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psllw_xmm_xmmm128_instruction();

TEST(NASMBytecode, psllw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psllw(xmm13, oword[r12 + rax]),
			psllw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psllw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pslld_xmm_xmmm128_instruction();

TEST(NASMBytecode, pslld_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pslld(xmm13, oword[r12 + rax]),
			pslld(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pslld_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psllq_xmm_xmmm128_instruction();

TEST(NASMBytecode, psllq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psllq(xmm13, oword[r12 + rax]),
			psllq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psllq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pmuludq_xmm_xmmm128_instruction();

TEST(NASMBytecode, pmuludq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pmuludq(xmm13, oword[r12 + rax]),
			pmuludq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pmuludq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_pmaddwd_xmm_xmmm128_instruction();

TEST(NASMBytecode, pmaddwd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			pmaddwd(xmm13, oword[r12 + rax]),
			pmaddwd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_pmaddwd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psadbw_xmm_xmmm128_instruction();

TEST(NASMBytecode, psadbw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psadbw(xmm13, oword[r12 + rax]),
			psadbw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psadbw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_maskmovq_mm_mm_instruction();

TEST(NASMBytecode, maskmovq_mm_mm_instruction_test)
{
	const auto casm_bytecode{ maskmovq(mm2, mm3).bytecode() };

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_maskmovq_mm_mm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_maskmovdqu_xmm_xmm_instruction();

TEST(NASMBytecode, maskmovdqu_xmm_xmm_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			maskmovdqu(xmm4, xmm12),
			maskmovdqu(xmm12, xmm4)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_maskmovdqu_xmm_xmm_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psubb_xmm_xmmm128_instruction();

TEST(NASMBytecode, psubb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psubb(xmm13, oword[r12 + rax]),
			psubb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psubb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psubw_xmm_xmmm128_instruction();

TEST(NASMBytecode, psubw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psubw(xmm13, oword[r12 + rax]),
			psubw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psubw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psubd_xmm_xmmm128_instruction();

TEST(NASMBytecode, psubd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psubd(xmm13, oword[r12 + rax]),
			psubd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psubd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_psubq_xmm_xmmm128_instruction();

TEST(NASMBytecode, psubq_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			psubq(xmm13, oword[r12 + rax]),
			psubq(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_psubq_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_paddb_xmm_xmmm128_instruction();

TEST(NASMBytecode, paddb_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			paddb(xmm13, oword[r12 + rax]),
			paddb(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_paddb_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_paddw_xmm_xmmm128_instruction();

TEST(NASMBytecode, paddw_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			paddw(xmm13, oword[r12 + rax]),
			paddw(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_paddw_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

extern "C" void nasm_paddd_xmm_xmmm128_instruction();

TEST(NASMBytecode, paddd_xmm_xmmm128_instruction_test)
{
	const auto casm_bytecode
	{
		assembler
		{
			paddd(xmm13, oword[r12 + rax]),
			paddd(xmm8, xmm11)
		}.bytecode()
	};

	ASSERT_TRUE(std::memcmp(casm_bytecode.data(), reinterpret_cast<std::byte const* const>(nasm_paddd_xmm_xmmm128_instruction), casm_bytecode.size()) == 0);
};

TEST(LabelTest, crc32_label)
{
	ASSERT_EQ("label"_l.id(), 0x0ea750e8);
}

TEST(FunctionlTest, x64_f)
{
	int i = 0x14;

	casm::f my_f
	{	
		push(rcx),
		mov(rcx, &i),
	
		push(rax),
		xor_(rax, rax),

		"loop"_l,

		inc(rax),
		sub(byte_ptr [rcx], 7),

		cmp(byte_ptr [rcx], 0),
		jnz("loop"_l),

		pop(rax),
		pop(rcx)
	};

	my_f();

	ASSERT_EQ(i, 0);
}

TEST(SingleInstruction, inc_instruction)
{
	constexpr auto result = inc(byte_ptr [rdx + rax * 8]).bytecode();

	constexpr auto expected{ details::make_static_bytecode(0xfe, 0x04, 0xc2) };

	ASSERT_EQ(result, expected);
}

#include <iostream>

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}