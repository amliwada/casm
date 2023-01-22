bits 64

section .text

nasm_add_rm8_r8_instruction:
	add dl, ah
	add r9b, al
	add al, r11b
	add byte [rdx + rdx * 8 + 0x1122], al
	add byte [rdx + rdx * 8 + 0x1122], spl
	add byte [r11 + rdx * 8 + 0x1122], dil
	add byte [edx + r11d * 8 + 0x1122], r8b
	add byte[rdx + rdx * 8], al
	add byte[rdx + rdx * 8], spl
	add byte[r11 + rdx * 8], dil
	add byte[edx + r11d * 8], r8b
	add byte [r11d], bl
	add byte [rdx], bpl
	add byte [r11d * 4], bl
	add byte [rdx * 4], bpl

global nasm_add_rm8_r8_instruction

nasm_add_rm16_32_64_r16_32_64_instruction:
	add dx, ax
	add edx, eax
	add rdx, rax
	add word[ebx * 4], dx
	add dword[ebx * 4], edx
	add qword[ebx * 4], rdx

global nasm_add_rm16_32_64_r16_32_64_instruction

nasm_add_r8_rm8_instruction:
	add al, dl
	add dl, byte [rax + rax * 8 + 0x11111111]

global nasm_add_r8_rm8_instruction

nasm_add_r16_32_64_rm16_32_64_instruction:
	add cx, word [r11 + rbx]
	add ebx, dword [r11 + rbx]
	add rax, qword [r12]

global nasm_add_r16_32_64_rm16_32_64_instruction

nasm_add_al_imm8_instruction:
	add al, 0x40

global nasm_add_al_imm8_instruction

nasm_add_ax_eax_rax_imm16_32_instruction:
	add ax, 0x8888
	add eax, 0x88888888
	add rax, 0x88888888

global nasm_add_ax_eax_rax_imm16_32_instruction

nasm_or_rm8_r8_instruction:
	or dl, ah
	or r9b, al
	or al, r11b
	or byte [rdx + rdx * 8 + 0x1122], al
	or byte [rdx + rdx * 8 + 0x1122], spl
	or byte [r11 + rdx * 8 + 0x1122], dil
	or byte [edx + r11d * 8 + 0x1122], r8b
	or byte[rdx + rdx * 8], al
	or byte[rdx + rdx * 8], spl
	or byte[r11 + rdx * 8], dil
	or byte[edx + r11d * 8], r8b
	or byte [r11d], bl
	or byte [rdx], bpl
	or byte [r11d * 4], bl
	or byte [rdx * 4], bpl

global nasm_or_rm8_r8_instruction

nasm_or_rm16_32_64_r16_32_64_instruction:
	or dx, ax
	or edx, eax
	or rdx, rax
	or word[ebx * 4], dx
	or dword[ebx * 4], edx
	or qword[ebx * 4], rdx

global nasm_or_rm16_32_64_r16_32_64_instruction

nasm_or_r8_rm8_instruction:
	or al, dl
	or dl, byte [rax + rax * 8 + 0x11111111]

global nasm_or_r8_rm8_instruction

nasm_or_r16_32_64_rm16_32_64_instruction:
	or cx, word [r11 + rbx]
	or ebx, dword [r11 + rbx]
	or rax, qword [r12]

global nasm_or_r16_32_64_rm16_32_64_instruction

nasm_or_al_imm8_instruction:
	or al, 0x40

global nasm_or_al_imm8_instruction

nasm_or_ax_eax_rax_imm16_32_instruction:
	or ax, 0x8888
	or eax, 0x88888888
	or rax, 0x88888888

global nasm_or_ax_eax_rax_imm16_32_instruction

nasm_adc_rm8_r8_instruction:
	adc dl, ah
	adc r9b, al
	adc al, r11b
	adc byte [rdx + rdx * 8 + 0x1122], al
	adc byte [rdx + rdx * 8 + 0x1122], spl
	adc byte [r11 + rdx * 8 + 0x1122], dil
	adc byte [edx + r11d * 8 + 0x1122], r8b
	adc byte[rdx + rdx * 8], al
	adc byte[rdx + rdx * 8], spl
	adc byte[r11 + rdx * 8], dil
	adc byte[edx + r11d * 8], r8b
	adc byte [r11d], bl
	adc byte [rdx], bpl
	adc byte [r11d * 4], bl
	adc byte [rdx * 4], bpl

global nasm_adc_rm8_r8_instruction

nasm_adc_rm16_32_64_r16_32_64_instruction:
	adc dx, ax
	adc edx, eax
	adc rdx, rax
	adc word[ebx * 4], dx
	adc dword[ebx * 4], edx
	adc qword[ebx * 4], rdx

global nasm_adc_rm16_32_64_r16_32_64_instruction

nasm_adc_r8_rm8_instruction:
	adc al, dl
	adc dl, byte [rax + rax * 8 + 0x11111111]

global nasm_adc_r8_rm8_instruction

nasm_adc_r16_32_64_rm16_32_64_instruction:
	adc cx, word [r11 + rbx]
	adc ebx, dword [r11 + rbx]
	adc rax, qword [r12]

global nasm_adc_r16_32_64_rm16_32_64_instruction

nasm_adc_al_imm8_instruction:
	adc al, 0x40

global nasm_adc_al_imm8_instruction

nasm_adc_ax_eax_rax_imm16_32_instruction:
	adc ax, 0x8888
	adc eax, 0x88888888
	adc rax, 0x88888888

global nasm_adc_ax_eax_rax_imm16_32_instruction

nasm_sbb_rm8_r8_instruction:
	sbb dl, ah
	sbb r9b, al
	sbb al, r11b
	sbb byte [rdx + rdx * 8 + 0x1122], al
	sbb byte [rdx + rdx * 8 + 0x1122], spl
	sbb byte [r11 + rdx * 8 + 0x1122], dil
	sbb byte [edx + r11d * 8 + 0x1122], r8b
	sbb byte[rdx + rdx * 8], al
	sbb byte[rdx + rdx * 8], spl
	sbb byte[r11 + rdx * 8], dil
	sbb byte[edx + r11d * 8], r8b
	sbb byte [r11d], bl
	sbb byte [rdx], bpl
	sbb byte [r11d * 4], bl
	sbb byte [rdx * 4], bpl

global nasm_sbb_rm8_r8_instruction

nasm_sbb_rm16_32_64_r16_32_64_instruction:
	sbb dx, ax
	sbb edx, eax
	sbb rdx, rax
	sbb word[ebx * 4], dx
	sbb dword[ebx * 4], edx
	sbb qword[ebx * 4], rdx

global nasm_sbb_rm16_32_64_r16_32_64_instruction

nasm_sbb_r8_rm8_instruction:
	sbb al, dl
	sbb dl, byte [rax + rax * 8 + 0x11111111]

global nasm_sbb_r8_rm8_instruction

nasm_sbb_r16_32_64_rm16_32_64_instruction:
	sbb cx, word [r11 + rbx]
	sbb ebx, dword [r11 + rbx]
	sbb rax, qword [r12]

global nasm_sbb_r16_32_64_rm16_32_64_instruction

nasm_sbb_al_imm8_instruction:
	sbb al, 0x40

global nasm_sbb_al_imm8_instruction

nasm_sbb_ax_eax_rax_imm16_32_instruction:
	sbb ax, 0x8888
	sbb eax, 0x88888888
	sbb rax, 0x88888888

global nasm_sbb_ax_eax_rax_imm16_32_instruction

nasm_and_rm8_r8_instruction:
	and dl, ah
	and r9b, al
	and al, r11b
	and byte [rdx + rdx * 8 + 0x1122], al
	and byte [rdx + rdx * 8 + 0x1122], spl
	and byte [r11 + rdx * 8 + 0x1122], dil
	and byte [edx + r11d * 8 + 0x1122], r8b
	and byte[rdx + rdx * 8], al
	and byte[rdx + rdx * 8], spl
	and byte[r11 + rdx * 8], dil
	and byte[edx + r11d * 8], r8b
	and byte [r11d], bl
	and byte [rdx], bpl
	and byte [r11d * 4], bl
	and byte [rdx * 4], bpl

global nasm_and_rm8_r8_instruction

nasm_and_rm16_32_64_r16_32_64_instruction:
	and dx, ax
	and edx, eax
	and rdx, rax
	and word[ebx * 4], dx
	and dword[ebx * 4], edx
	and qword[ebx * 4], rdx

global nasm_and_rm16_32_64_r16_32_64_instruction

nasm_and_r8_rm8_instruction:
	and al, dl
	and dl, byte [rax + rax * 8 + 0x11111111]

global nasm_and_r8_rm8_instruction

nasm_and_r16_32_64_rm16_32_64_instruction:
	and cx, word [r11 + rbx]
	and ebx, dword [r11 + rbx]
	and rax, qword [r12]

global nasm_and_r16_32_64_rm16_32_64_instruction

nasm_and_al_imm8_instruction:
	and al, 0x40

global nasm_and_al_imm8_instruction

nasm_and_ax_eax_rax_imm16_32_instruction:
	and ax, 0x8888
	and eax, 0x88888888
	and rax, 0x88888888

global nasm_and_ax_eax_rax_imm16_32_instruction

nasm_sub_rm8_r8_instruction:
	sub dl, ah
	sub r9b, al
	sub al, r11b
	sub byte [rdx + rdx * 8 + 0x1122], al
	sub byte [rdx + rdx * 8 + 0x1122], spl
	sub byte [r11 + rdx * 8 + 0x1122], dil
	sub byte [edx + r11d * 8 + 0x1122], r8b
	sub byte[rdx + rdx * 8], al
	sub byte[rdx + rdx * 8], spl
	sub byte[r11 + rdx * 8], dil
	sub byte[edx + r11d * 8], r8b
	sub byte [r11d], bl
	sub byte [rdx], bpl
	sub byte [r11d * 4], bl
	sub byte [rdx * 4], bpl

global nasm_sub_rm8_r8_instruction

nasm_sub_rm16_32_64_r16_32_64_instruction:
	sub dx, ax
	sub edx, eax
	sub rdx, rax
	sub word[ebx * 4], dx
	sub dword[ebx * 4], edx
	sub qword[ebx * 4], rdx

global nasm_sub_rm16_32_64_r16_32_64_instruction

nasm_sub_r8_rm8_instruction:
	sub al, dl
	sub dl, byte [rax + rax * 8 + 0x11111111]

global nasm_sub_r8_rm8_instruction

nasm_sub_r16_32_64_rm16_32_64_instruction:
	sub cx, word [r11 + rbx]
	sub ebx, dword [r11 + rbx]
	sub rax, qword [r12]

global nasm_sub_r16_32_64_rm16_32_64_instruction

nasm_sub_al_imm8_instruction:
	sub al, 0x40

global nasm_sub_al_imm8_instruction

nasm_sub_ax_eax_rax_imm16_32_instruction:
	sub ax, 0x8888
	sub eax, 0x88888888
	sub rax, 0x88888888

global nasm_sub_ax_eax_rax_imm16_32_instruction

nasm_xor_rm8_r8_instruction:
	xor dl, ah
	xor r9b, al
	xor al, r11b
	xor byte [rdx + rdx * 8 + 0x1122], al
	xor byte [rdx + rdx * 8 + 0x1122], spl
	xor byte [r11 + rdx * 8 + 0x1122], dil
	xor byte [edx + r11d * 8 + 0x1122], r8b
	xor byte[rdx + rdx * 8], al
	xor byte[rdx + rdx * 8], spl
	xor byte[r11 + rdx * 8], dil
	xor byte[edx + r11d * 8], r8b
	xor byte [r11d], bl
	xor byte [rdx], bpl
	xor byte [r11d * 4], bl
	xor byte [rdx * 4], bpl

global nasm_xor_rm8_r8_instruction

nasm_xor_rm16_32_64_r16_32_64_instruction:
	xor dx, ax
	xor edx, eax
	xor rdx, rax
	xor word[ebx * 4], dx
	xor dword[ebx * 4], edx
	xor qword[ebx * 4], rdx

global nasm_xor_rm16_32_64_r16_32_64_instruction

nasm_xor_r8_rm8_instruction:
	xor al, dl
	xor dl, byte [rax + rax * 8 + 0x11111111]

global nasm_xor_r8_rm8_instruction

nasm_xor_r16_32_64_rm16_32_64_instruction:
	xor cx, word [r11 + rbx]
	xor ebx, dword [r11 + rbx]
	xor rax, qword [r12]

global nasm_xor_r16_32_64_rm16_32_64_instruction

nasm_xor_al_imm8_instruction:
	xor al, 0x40

global nasm_xor_al_imm8_instruction

nasm_xor_ax_eax_rax_imm16_32_instruction:
	xor ax, 0x8888
	xor eax, 0x88888888
	xor rax, 0x88888888

global nasm_xor_ax_eax_rax_imm16_32_instruction

nasm_cmp_rm8_r8_instruction:
	cmp dl, ah
	cmp r9b, al
	cmp al, r11b
	cmp byte [rdx + rdx * 8 + 0x1122], al
	cmp byte [rdx + rdx * 8 + 0x1122], spl
	cmp byte [r11 + rdx * 8 + 0x1122], dil
	cmp byte [edx + r11d * 8 + 0x1122], r8b
	cmp byte[rdx + rdx * 8], al
	cmp byte[rdx + rdx * 8], spl
	cmp byte[r11 + rdx * 8], dil
	cmp byte[edx + r11d * 8], r8b
	cmp byte [r11d], bl
	cmp byte [rdx], bpl
	cmp byte [r11d * 4], bl
	cmp byte [rdx * 4], bpl

global nasm_cmp_rm8_r8_instruction

nasm_cmp_rm16_32_64_r16_32_64_instruction:
	cmp dx, ax
	cmp edx, eax
	cmp rdx, rax
	cmp word[ebx * 4], dx
	cmp dword[ebx * 4], edx
	cmp qword[ebx * 4], rdx

global nasm_cmp_rm16_32_64_r16_32_64_instruction

nasm_cmp_r8_rm8_instruction:
	cmp al, dl
	cmp dl, byte [rax + rax * 8 + 0x11111111]

global nasm_cmp_r8_rm8_instruction

nasm_cmp_r16_32_64_rm16_32_64_instruction:
	cmp cx, word [r11 + rbx]
	cmp ebx, dword [r11 + rbx]
	cmp rax, qword [r12]

global nasm_cmp_r16_32_64_rm16_32_64_instruction

nasm_cmp_al_imm8_instruction:
	cmp al, 0x40

global nasm_cmp_al_imm8_instruction

nasm_cmp_ax_eax_rax_imm16_32_instruction:
	cmp ax, 0x8888
	cmp eax, 0x88888888
	cmp rax, 0x88888888

global nasm_cmp_ax_eax_rax_imm16_32_instruction

nasm_push_r16_64_instruction_by_register:
	push ax
	push cx
	push dx
	push bx
	push sp
	push bp
	push si
	push di
	push rax
	push rcx
	push rdx
	push rbx
	push rsp
	push rbp
	push rsi
	push rdi
	push r8
	push r12

global nasm_push_r16_64_instruction_by_register

nasm_pop_r16_64_instruction_by_register:
	pop ax
	pop cx
	pop dx
	pop bx
	pop sp
	pop bp
	pop si
	pop di
	pop rax
	pop rcx
	pop rdx
	pop rbx
	pop rsp
	pop rbp
	pop rsi
	pop rdi
	pop r8
	pop r12

global nasm_pop_r16_64_instruction_by_register

nasm_movsxd_r32_64_rm32_instruction:
	movsxd rdx, ecx

global nasm_movsxd_r32_64_rm32_instruction

nasm_push_imm32_instruction:
	push 0x11113333

global nasm_push_imm32_instruction

nasm_imul_r16_32_64_rm16_32_64_imm16_32_instruction:
	imul bx, cx, 0x44
	imul ebx, ecx, 0x4444
	imul rbx, rcx, 0x44444444

global nasm_imul_r16_32_64_rm16_32_64_imm16_32_instruction

nasm_push_imm8_instruction:
	push 0x11

global nasm_push_imm8_instruction

nasm_imul_r16_32_64_rm16_32_64_imm8_instruction:
	imul bx, cx, 0x44
	imul ebx, ecx, 0x44
	imul rbx, rcx, 0x44

global nasm_imul_r16_32_64_rm16_32_64_imm8_instruction

nasm_ins_no_operands_instruction:
	ins 

global nasm_ins_no_operands_instruction

nasm_insb_no_operands_instruction:
	insb 

global nasm_insb_no_operands_instruction

nasm_insw_no_operands_instruction:
	insw 

global nasm_insw_no_operands_instruction

nasm_insd_no_operands_instruction:
	insd 

global nasm_insd_no_operands_instruction

nasm_outsb_no_operands_instruction:
	outsb 

global nasm_outsb_no_operands_instruction

nasm_outsw_no_operands_instruction:
	outsw 

global nasm_outsw_no_operands_instruction

nasm_outsd_no_operands_instruction:
	outsd 

global nasm_outsd_no_operands_instruction

nasm_add_rm8_imm8_instruction_by_number:
	add byte [ebx], 11
	add dl, 11
	add al, 11

global nasm_add_rm8_imm8_instruction_by_number

nasm_or_rm8_imm8_instruction_by_number:
	or byte [ebx], 11
	or dl, 11
	or al, 11

global nasm_or_rm8_imm8_instruction_by_number

nasm_adc_rm8_imm8_instruction_by_number:
	adc byte [ebx], 11
	adc dl, 11
	adc al, 11

global nasm_adc_rm8_imm8_instruction_by_number

nasm_sbb_rm8_imm8_instruction_by_number:
	sbb byte [ebx], 11
	sbb dl, 11
	sbb al, 11

global nasm_sbb_rm8_imm8_instruction_by_number

nasm_and_rm8_imm8_instruction_by_number:
	and byte [ebx], 11
	and dl, 11
	and al, 11

global nasm_and_rm8_imm8_instruction_by_number

nasm_sub_rm8_imm8_instruction_by_number:
	sub byte [ebx], 11
	sub dl, 11
	sub al, 11

global nasm_sub_rm8_imm8_instruction_by_number

nasm_xor_rm8_imm8_instruction_by_number:
	xor byte [ebx], 11
	xor dl, 11
	xor al, 11

global nasm_xor_rm8_imm8_instruction_by_number

nasm_cmp_rm8_imm8_instruction_by_number:
	cmp byte [ebx], 11
	cmp dl, 11
	cmp al, 11

global nasm_cmp_rm8_imm8_instruction_by_number

nasm_add_rm16_32_imm16_32_instruction_by_number:
	add dx, 0x1111
	add edx, 0x113333
	add word[ebx * 4], 0x1111
	add dword[ebx * 4], 0x113333

global nasm_add_rm16_32_imm16_32_instruction_by_number

nasm_or_rm16_32_imm16_32_instruction_by_number:
	or dx, 0x1111
	or edx, 0x113333
	or word[ebx * 4], 0x1111
	or dword[ebx * 4], 0x113333

global nasm_or_rm16_32_imm16_32_instruction_by_number

nasm_adc_rm16_32_imm16_32_instruction_by_number:
	adc dx, 0x1111
	adc edx, 0x113333
	adc word[ebx * 4], 0x1111
	adc dword[ebx * 4], 0x113333

global nasm_adc_rm16_32_imm16_32_instruction_by_number

nasm_sbb_rm16_32_imm16_32_instruction_by_number:
	sbb dx, 0x1111
	sbb edx, 0x113333
	sbb word[ebx * 4], 0x1111
	sbb dword[ebx * 4], 0x113333

global nasm_sbb_rm16_32_imm16_32_instruction_by_number

nasm_and_rm16_32_imm16_32_instruction_by_number:
	and dx, 0x1111
	and edx, 0x113333
	and word[ebx * 4], 0x1111
	and dword[ebx * 4], 0x113333

global nasm_and_rm16_32_imm16_32_instruction_by_number

nasm_sub_rm16_32_imm16_32_instruction_by_number:
	sub dx, 0x1111
	sub edx, 0x113333
	sub word[ebx * 4], 0x1111
	sub dword[ebx * 4], 0x113333

global nasm_sub_rm16_32_imm16_32_instruction_by_number

nasm_xor_rm16_32_imm16_32_instruction_by_number:
	xor dx, 0x1111
	xor edx, 0x113333
	xor word[ebx * 4], 0x1111
	xor dword[ebx * 4], 0x113333

global nasm_xor_rm16_32_imm16_32_instruction_by_number

nasm_cmp_rm16_32_imm16_32_instruction_by_number:
	cmp dx, 0x1111
	cmp edx, 0x113333
	cmp word[ebx * 4], 0x1111
	cmp dword[ebx * 4], 0x113333

global nasm_cmp_rm16_32_imm16_32_instruction_by_number

nasm_add_rm16_32_imm8_instruction_by_number:
	add dx, 0x11
	add edx, 0x11
	add word[ebx * 4], 0x11
	add dword[ebx * 4], 0x11

global nasm_add_rm16_32_imm8_instruction_by_number

nasm_or_rm16_32_imm8_instruction_by_number:
	or dx, 0x11
	or edx, 0x11
	or word[ebx * 4], 0x11
	or dword[ebx * 4], 0x11

global nasm_or_rm16_32_imm8_instruction_by_number

nasm_adc_rm16_32_imm8_instruction_by_number:
	adc dx, 0x11
	adc edx, 0x11
	adc word[ebx * 4], 0x11
	adc dword[ebx * 4], 0x11

global nasm_adc_rm16_32_imm8_instruction_by_number

nasm_sbb_rm16_32_imm8_instruction_by_number:
	sbb dx, 0x11
	sbb edx, 0x11
	sbb word[ebx * 4], 0x11
	sbb dword[ebx * 4], 0x11

global nasm_sbb_rm16_32_imm8_instruction_by_number

nasm_and_rm16_32_imm8_instruction_by_number:
	and dx, 0x11
	and edx, 0x11
	and word[ebx * 4], 0x11
	and dword[ebx * 4], 0x11

global nasm_and_rm16_32_imm8_instruction_by_number

nasm_sub_rm16_32_imm8_instruction_by_number:
	sub dx, 0x11
	sub edx, 0x11
	sub word[ebx * 4], 0x11
	sub dword[ebx * 4], 0x11

global nasm_sub_rm16_32_imm8_instruction_by_number

nasm_xor_rm16_32_imm8_instruction_by_number:
	xor dx, 0x11
	xor edx, 0x11
	xor word[ebx * 4], 0x11
	xor dword[ebx * 4], 0x11

global nasm_xor_rm16_32_imm8_instruction_by_number

nasm_cmp_rm16_32_imm8_instruction_by_number:
	cmp dx, 0x11
	cmp edx, 0x11
	cmp word[ebx * 4], 0x11
	cmp dword[ebx * 4], 0x11

global nasm_cmp_rm16_32_imm8_instruction_by_number

nasm_test_rm8_r8_instruction:
	test dl, ah
	test r9b, al
	test al, r11b
	test byte [rdx + rdx * 8 + 0x1122], al
	test byte [rdx + rdx * 8 + 0x1122], spl
	test byte [r11 + rdx * 8 + 0x1122], dil
	test byte [edx + r11d * 8 + 0x1122], r8b
	test byte[rdx + rdx * 8], al
	test byte[rdx + rdx * 8], spl
	test byte[r11 + rdx * 8], dil
	test byte[edx + r11d * 8], r8b
	test byte [r11d], bl
	test byte [rdx], bpl
	test byte [r11d * 4], bl
	test byte [rdx * 4], bpl

global nasm_test_rm8_r8_instruction

nasm_test_rm16_32_64_r16_32_64_instruction:
	test dx, ax
	test edx, eax
	test rdx, rax
	test word[ebx * 4], dx
	test dword[ebx * 4], edx
	test qword[ebx * 4], rdx

global nasm_test_rm16_32_64_r16_32_64_instruction

nasm_xchg_r8_rm8_instruction:
	xchg al, dl
	xchg dl, byte [rax + rax * 8 + 0x11111111]

global nasm_xchg_r8_rm8_instruction

nasm_xchg_r16_32_64_rm16_32_64_instruction:
	xchg cx, word [r11 + rbx]
	xchg ebx, dword [r11 + rbx]
	xchg rax, qword [r12]

global nasm_xchg_r16_32_64_rm16_32_64_instruction

nasm_mov_rm8_r8_instruction:
	mov dl, ah
	mov r9b, al
	mov al, r11b
	mov byte [rdx + rdx * 8 + 0x1122], al
	mov byte [rdx + rdx * 8 + 0x1122], spl
	mov byte [r11 + rdx * 8 + 0x1122], dil
	mov byte [edx + r11d * 8 + 0x1122], r8b
	mov byte[rdx + rdx * 8], al
	mov byte[rdx + rdx * 8], spl
	mov byte[r11 + rdx * 8], dil
	mov byte[edx + r11d * 8], r8b
	mov byte [r11d], bl
	mov byte [rdx], bpl
	mov byte [r11d * 4], bl
	mov byte [rdx * 4], bpl

global nasm_mov_rm8_r8_instruction

nasm_mov_rm16_32_64_r16_32_64_instruction:
	mov dx, ax
	mov edx, eax
	mov rdx, rax
	mov word[ebx * 4], dx
	mov dword[ebx * 4], edx
	mov qword[ebx * 4], rdx

global nasm_mov_rm16_32_64_r16_32_64_instruction

nasm_mov_r8_rm8_instruction:
	mov al, dl
	mov dl, byte [rax + rax * 8 + 0x11111111]

global nasm_mov_r8_rm8_instruction

nasm_mov_r16_32_64_rm16_32_64_instruction:
	mov cx, word [r11 + rbx]
	mov ebx, dword [r11 + rbx]
	mov rax, qword [r12]

global nasm_mov_r16_32_64_rm16_32_64_instruction

nasm_mov_m16_sreg_instruction:
	mov word [r11 + rbx * 8], gs
	mov word [r11 + rbx * 8], ds

global nasm_mov_m16_sreg_instruction

nasm_mov_r16_32_64_sreg_instruction:
	mov dx, ds
	mov edx, fs
	mov rdx, ss

global nasm_mov_r16_32_64_sreg_instruction

nasm_lea_r16_32_64_m_instruction:
	lea dx, [r14d]
	lea edx, [r14d]
	lea rdx, [r14d]

global nasm_lea_r16_32_64_m_instruction

nasm_mov_sreg_rm16_instruction:
	mov es, word [0x321]
	mov ds, ax

global nasm_mov_sreg_rm16_instruction

nasm_pop_m16_64_instruction_by_number:
	pop word [r11 + rbx * 8]
	pop qword [r11 + rbx * 8]

global nasm_pop_m16_64_instruction_by_number

nasm_xchg_r16_32_64_ax_eax_rax_instruction_by_register:
	xchg dx, ax
	xchg edx, eax
	xchg rdx, rax

global nasm_xchg_r16_32_64_ax_eax_rax_instruction_by_register

nasm_nop_no_operands_instruction:
	nop 

global nasm_nop_no_operands_instruction

nasm_pause_no_operands_instruction:
	pause 

global nasm_pause_no_operands_instruction

nasm_cbw_no_operands_instruction:
	cbw 

global nasm_cbw_no_operands_instruction

nasm_cwde_no_operands_instruction:
	cwde 

global nasm_cwde_no_operands_instruction

nasm_cdqe_no_operands_instruction:
	cdqe 

global nasm_cdqe_no_operands_instruction

nasm_cwd_no_operands_instruction:
	cwd 

global nasm_cwd_no_operands_instruction

nasm_cdq_no_operands_instruction:
	cdq 

global nasm_cdq_no_operands_instruction

nasm_cqo_no_operands_instruction:
	cqo 

global nasm_cqo_no_operands_instruction

nasm_fwait_no_operands_instruction:
	fwait 

global nasm_fwait_no_operands_instruction

nasm_wait_no_operands_instruction:
	wait 

global nasm_wait_no_operands_instruction

nasm_pushf_no_operands_instruction:
	pushf 

global nasm_pushf_no_operands_instruction

nasm_pushfq_no_operands_instruction:
	pushfq 

global nasm_pushfq_no_operands_instruction

nasm_popf_no_operands_instruction:
	popf 

global nasm_popf_no_operands_instruction

nasm_popfq_no_operands_instruction:
	popfq 

global nasm_popfq_no_operands_instruction

nasm_sahf_no_operands_instruction:
	sahf 

global nasm_sahf_no_operands_instruction

nasm_lahf_no_operands_instruction:
	lahf 

global nasm_lahf_no_operands_instruction

nasm_movsb_no_operands_instruction:
	movsb 

global nasm_movsb_no_operands_instruction

nasm_movsw_no_operands_instruction:
	movsw 

global nasm_movsw_no_operands_instruction

nasm_movsd_no_operands_instruction:
	movsd 

global nasm_movsd_no_operands_instruction

nasm_movsq_no_operands_instruction:
	movsq 

global nasm_movsq_no_operands_instruction

nasm_cmpsb_no_operands_instruction:
	cmpsb 

global nasm_cmpsb_no_operands_instruction

nasm_cmpsw_no_operands_instruction:
	cmpsw 

global nasm_cmpsw_no_operands_instruction

nasm_cmpsd_no_operands_instruction:
	cmpsd 

global nasm_cmpsd_no_operands_instruction

nasm_cmpsq_no_operands_instruction:
	cmpsq 

global nasm_cmpsq_no_operands_instruction

nasm_test_al_imm8_instruction:
	test al, 0x40

global nasm_test_al_imm8_instruction

nasm_test_ax_eax_rax_imm16_32_instruction:
	test ax, 0x8888
	test eax, 0x88888888
	test rax, 0x88888888

global nasm_test_ax_eax_rax_imm16_32_instruction

nasm_stosb_no_operands_instruction:
	stosb 

global nasm_stosb_no_operands_instruction

nasm_stosw_no_operands_instruction:
	stosw 

global nasm_stosw_no_operands_instruction

nasm_stosd_no_operands_instruction:
	stosd 

global nasm_stosd_no_operands_instruction

nasm_stosq_no_operands_instruction:
	stosq 

global nasm_stosq_no_operands_instruction

nasm_lodsb_no_operands_instruction:
	lodsb 

global nasm_lodsb_no_operands_instruction

nasm_lodsw_no_operands_instruction:
	lodsw 

global nasm_lodsw_no_operands_instruction

nasm_lodsd_no_operands_instruction:
	lodsd 

global nasm_lodsd_no_operands_instruction

nasm_lodsq_no_operands_instruction:
	lodsq 

global nasm_lodsq_no_operands_instruction

nasm_scasb_no_operands_instruction:
	scasb 

global nasm_scasb_no_operands_instruction

nasm_scasw_no_operands_instruction:
	scasw 

global nasm_scasw_no_operands_instruction

nasm_scasd_no_operands_instruction:
	scasd 

global nasm_scasd_no_operands_instruction

nasm_scasq_no_operands_instruction:
	scasq 

global nasm_scasq_no_operands_instruction

nasm_mov_r8_imm8_instruction_by_register:
	mov al, 11
	mov cl, 11
	mov dl, 11
	mov bl, 11
	mov ah, 11
	mov ch, 11
	mov dh, 11
	mov bh, 11

global nasm_mov_r8_imm8_instruction_by_register

nasm_mov_r16_32_64_imm16_32_64_instruction_by_register:
	mov dx, 0x1111
	mov edx, 0x11111111
	mov rdx, 0x111111111111

global nasm_mov_r16_32_64_imm16_32_64_instruction_by_register

nasm_rol_rm8_imm8_instruction_by_number:
	rol byte [ebx], 11
	rol dl, 11
	rol al, 11

global nasm_rol_rm8_imm8_instruction_by_number

nasm_ror_rm8_imm8_instruction_by_number:
	ror byte [ebx], 11
	ror dl, 11
	ror al, 11

global nasm_ror_rm8_imm8_instruction_by_number

nasm_rcl_rm8_imm8_instruction_by_number:
	rcl byte [ebx], 11
	rcl dl, 11
	rcl al, 11

global nasm_rcl_rm8_imm8_instruction_by_number

nasm_rcr_rm8_imm8_instruction_by_number:
	rcr byte [ebx], 11
	rcr dl, 11
	rcr al, 11

global nasm_rcr_rm8_imm8_instruction_by_number

nasm_shl_rm8_imm8_instruction_by_number:
	shl byte [ebx], 11
	shl dl, 11
	shl al, 11

global nasm_shl_rm8_imm8_instruction_by_number

nasm_sal_rm8_imm8_instruction_by_number:
	sal byte [ebx], 11
	sal dl, 11
	sal al, 11

global nasm_sal_rm8_imm8_instruction_by_number

nasm_shr_rm8_imm8_instruction_by_number:
	shr byte [ebx], 11
	shr dl, 11
	shr al, 11

global nasm_shr_rm8_imm8_instruction_by_number

nasm_sar_rm8_imm8_instruction_by_number:
	sar byte [ebx], 11
	sar dl, 11
	sar al, 11

global nasm_sar_rm8_imm8_instruction_by_number

nasm_rol_rm16_32_imm8_instruction_by_number:
	rol dx, 0x11
	rol edx, 0x11
	rol word[ebx * 4], 0x11
	rol dword[ebx * 4], 0x11

global nasm_rol_rm16_32_imm8_instruction_by_number

nasm_ror_rm16_32_imm8_instruction_by_number:
	ror dx, 0x11
	ror edx, 0x11
	ror word[ebx * 4], 0x11
	ror dword[ebx * 4], 0x11

global nasm_ror_rm16_32_imm8_instruction_by_number

nasm_rcl_rm16_32_imm8_instruction_by_number:
	rcl dx, 0x11
	rcl edx, 0x11
	rcl word[ebx * 4], 0x11
	rcl dword[ebx * 4], 0x11

global nasm_rcl_rm16_32_imm8_instruction_by_number

nasm_rcr_rm16_32_imm8_instruction_by_number:
	rcr dx, 0x11
	rcr edx, 0x11
	rcr word[ebx * 4], 0x11
	rcr dword[ebx * 4], 0x11

global nasm_rcr_rm16_32_imm8_instruction_by_number

nasm_shl_rm16_32_imm8_instruction_by_number:
	shl dx, 0x11
	shl edx, 0x11
	shl word[ebx * 4], 0x11
	shl dword[ebx * 4], 0x11

global nasm_shl_rm16_32_imm8_instruction_by_number

nasm_sal_rm16_32_imm8_instruction_by_number:
	sal dx, 0x11
	sal edx, 0x11
	sal word[ebx * 4], 0x11
	sal dword[ebx * 4], 0x11

global nasm_sal_rm16_32_imm8_instruction_by_number

nasm_shr_rm16_32_imm8_instruction_by_number:
	shr dx, 0x11
	shr edx, 0x11
	shr word[ebx * 4], 0x11
	shr dword[ebx * 4], 0x11

global nasm_shr_rm16_32_imm8_instruction_by_number

nasm_sar_rm16_32_imm8_instruction_by_number:
	sar dx, 0x11
	sar edx, 0x11
	sar word[ebx * 4], 0x11
	sar dword[ebx * 4], 0x11

global nasm_sar_rm16_32_imm8_instruction_by_number

nasm_retn_imm16_instruction:
	retn 0x1111

global nasm_retn_imm16_instruction

nasm_ret_no_operands_instruction:
	ret 

global nasm_ret_no_operands_instruction

nasm_mov_m8_imm8_instruction_by_number:
	mov byte [r11 + rax], 0x11

global nasm_mov_m8_imm8_instruction_by_number

nasm_mov_m16_32_64_imm16_32_instruction_by_number:
	mov word [r11 + rbx * 8], 0x8888
	mov word[r11 + rbx * 8], 0x8888
	mov word[r11 + rbx * 8], 0x8888
	mov dword [r11 + rbx * 8], 0x88888888
	mov qword [r11 + rbx * 8], 0x88888888888

global nasm_mov_m16_32_64_imm16_32_instruction_by_number

nasm_leave_no_operands_instruction:
	leave 

global nasm_leave_no_operands_instruction

nasm_retf_imm16_instruction:
	retf 0x1111

global nasm_retf_imm16_instruction

nasm_retf_no_operands_instruction:
	retf 

global nasm_retf_no_operands_instruction

nasm_int3_no_operands_instruction:
	int3 

global nasm_int3_no_operands_instruction

nasm_int_imm8_instruction:
	int 0x11

global nasm_int_imm8_instruction

nasm_iret_no_operands_instruction:
	iret 

global nasm_iret_no_operands_instruction

nasm_iretd_no_operands_instruction:
	iretd 

global nasm_iretd_no_operands_instruction

nasm_iretq_no_operands_instruction:
	iretq 

global nasm_iretq_no_operands_instruction

nasm_rol_rm8_cl_instruction_by_number:
	rol byte [ebx], cl
	rol bl, cl
	rol al, cl

global nasm_rol_rm8_cl_instruction_by_number

nasm_ror_rm8_cl_instruction_by_number:
	ror byte [ebx], cl
	ror bl, cl
	ror al, cl

global nasm_ror_rm8_cl_instruction_by_number

nasm_rcl_rm8_cl_instruction_by_number:
	rcl byte [ebx], cl
	rcl bl, cl
	rcl al, cl

global nasm_rcl_rm8_cl_instruction_by_number

nasm_rcr_rm8_cl_instruction_by_number:
	rcr byte [ebx], cl
	rcr bl, cl
	rcr al, cl

global nasm_rcr_rm8_cl_instruction_by_number

nasm_shl_rm8_cl_instruction_by_number:
	shl byte [ebx], cl
	shl bl, cl
	shl al, cl

global nasm_shl_rm8_cl_instruction_by_number

nasm_sal_rm8_cl_instruction_by_number:
	sal byte [ebx], cl
	sal bl, cl
	sal al, cl

global nasm_sal_rm8_cl_instruction_by_number

nasm_shr_rm8_cl_instruction_by_number:
	shr byte [ebx], cl
	shr bl, cl
	shr al, cl

global nasm_shr_rm8_cl_instruction_by_number

nasm_sar_rm8_cl_instruction_by_number:
	sar byte [ebx], cl
	sar bl, cl
	sar al, cl

global nasm_sar_rm8_cl_instruction_by_number

nasm_rol_rm16_32_64_cl_instruction_by_number:
	rol dx, cl
	rol edx, cl
	rol rdx, cl

global nasm_rol_rm16_32_64_cl_instruction_by_number

nasm_ror_rm16_32_64_cl_instruction_by_number:
	ror dx, cl
	ror edx, cl
	ror rdx, cl

global nasm_ror_rm16_32_64_cl_instruction_by_number

nasm_rcl_rm16_32_64_cl_instruction_by_number:
	rcl dx, cl
	rcl edx, cl
	rcl rdx, cl

global nasm_rcl_rm16_32_64_cl_instruction_by_number

nasm_rcr_rm16_32_64_cl_instruction_by_number:
	rcr dx, cl
	rcr edx, cl
	rcr rdx, cl

global nasm_rcr_rm16_32_64_cl_instruction_by_number

nasm_shl_rm16_32_64_cl_instruction_by_number:
	shl dx, cl
	shl edx, cl
	shl rdx, cl

global nasm_shl_rm16_32_64_cl_instruction_by_number

nasm_sal_rm16_32_64_cl_instruction_by_number:
	sal dx, cl
	sal edx, cl
	sal rdx, cl

global nasm_sal_rm16_32_64_cl_instruction_by_number

nasm_shr_rm16_32_64_cl_instruction_by_number:
	shr dx, cl
	shr edx, cl
	shr rdx, cl

global nasm_shr_rm16_32_64_cl_instruction_by_number

nasm_sar_rm16_32_64_cl_instruction_by_number:
	sar dx, cl
	sar edx, cl
	sar rdx, cl

global nasm_sar_rm16_32_64_cl_instruction_by_number

nasm_xlat_no_operands_instruction:
	xlat 

global nasm_xlat_no_operands_instruction

nasm_xlatb_no_operands_instruction:
	xlatb 

global nasm_xlatb_no_operands_instruction

nasm_fadd_m32_instruction_by_number:
	fadd dword [r11 + rax]

global nasm_fadd_m32_instruction_by_number

nasm_fadd_sti_instruction_by_number:
	fadd st6

global nasm_fadd_sti_instruction_by_number

nasm_fadd_st_sti_instruction_by_number:
	fadd st0, st6

global nasm_fadd_st_sti_instruction_by_number

nasm_fmul_m32_instruction_by_number:
	fmul dword [r11 + rax]

global nasm_fmul_m32_instruction_by_number

nasm_fmul_sti_instruction_by_number:
	fmul st6

global nasm_fmul_sti_instruction_by_number

nasm_fmul_st_sti_instruction_by_number:
	fmul st0, st6

global nasm_fmul_st_sti_instruction_by_number

nasm_fcom_stm32_instruction_by_number:
	fcom st6
	fcom dword [rdx]

global nasm_fcom_stm32_instruction_by_number

nasm_fcom_no_operands_instruction:
	fcom 

global nasm_fcom_no_operands_instruction

nasm_fcomp_stm32_instruction_by_number:
	fcomp st6
	fcomp dword [rdx]

global nasm_fcomp_stm32_instruction_by_number

nasm_fcomp_no_operands_instruction:
	fcomp 

global nasm_fcomp_no_operands_instruction

nasm_fsub_m32_instruction_by_number:
	fsub dword [r11 + rax]

global nasm_fsub_m32_instruction_by_number

nasm_fsub_sti_instruction_by_number:
	fsub st6

global nasm_fsub_sti_instruction_by_number

nasm_fsub_st_sti_instruction_by_number:
	fsub st0, st6

global nasm_fsub_st_sti_instruction_by_number

nasm_fsubr_m32_instruction_by_number:
	fsubr dword [r11 + rax]

global nasm_fsubr_m32_instruction_by_number

nasm_fsubr_sti_instruction_by_number:
	fsubr st6

global nasm_fsubr_sti_instruction_by_number

nasm_fsubr_st_sti_instruction_by_number:
	fsubr st0, st6

global nasm_fsubr_st_sti_instruction_by_number

nasm_fdiv_m32_instruction_by_number:
	fdiv dword [r11 + rax]

global nasm_fdiv_m32_instruction_by_number

nasm_fdiv_sti_instruction_by_number:
	fdiv st6

global nasm_fdiv_sti_instruction_by_number

nasm_fdiv_st_sti_instruction_by_number:
	fdiv st0, st6

global nasm_fdiv_st_sti_instruction_by_number

nasm_fdivr_m32_instruction_by_number:
	fdivr dword [r11 + rax]

global nasm_fdivr_m32_instruction_by_number

nasm_fdivr_sti_instruction_by_number:
	fdivr st6

global nasm_fdivr_sti_instruction_by_number

nasm_fdivr_st_sti_instruction_by_number:
	fdivr st0, st6

global nasm_fdivr_st_sti_instruction_by_number

nasm_fld_stm32_instruction_by_number:
	fld st6
	fld dword [rdx]

global nasm_fld_stm32_instruction_by_number

nasm_fxch_sti_instruction_by_number:
	fxch st6

global nasm_fxch_sti_instruction_by_number

nasm_fxch_no_operands_instruction:
	fxch 

global nasm_fxch_no_operands_instruction

nasm_fst_m32_instruction_by_number:
	fst dword [r11 + rax]

global nasm_fst_m32_instruction_by_number

nasm_fnop_no_operands_instruction:
	fnop 

global nasm_fnop_no_operands_instruction

nasm_fstp_m32_instruction_by_number:
	fstp dword [r11 + rax]

global nasm_fstp_m32_instruction_by_number

nasm_fldenv_m_instruction_by_number:
	fldenv [0x11223344]
	fldenv [rbx + r12 * 4 ]

global nasm_fldenv_m_instruction_by_number

nasm_fchs_no_operands_instruction:
	fchs 

global nasm_fchs_no_operands_instruction

nasm_fabs_no_operands_instruction:
	fabs 

global nasm_fabs_no_operands_instruction

nasm_ftst_no_operands_instruction:
	ftst 

global nasm_ftst_no_operands_instruction

nasm_fxam_no_operands_instruction:
	fxam 

global nasm_fxam_no_operands_instruction

nasm_fldcw_m16_instruction_by_number:
	fldcw word [r11 + rbx * 8]

global nasm_fldcw_m16_instruction_by_number

nasm_fld1_no_operands_instruction:
	fld1 

global nasm_fld1_no_operands_instruction

nasm_fldl2t_no_operands_instruction:
	fldl2t 

global nasm_fldl2t_no_operands_instruction

nasm_fldl2e_no_operands_instruction:
	fldl2e 

global nasm_fldl2e_no_operands_instruction

nasm_fldpi_no_operands_instruction:
	fldpi 

global nasm_fldpi_no_operands_instruction

nasm_fldlg2_no_operands_instruction:
	fldlg2 

global nasm_fldlg2_no_operands_instruction

nasm_fldln2_no_operands_instruction:
	fldln2 

global nasm_fldln2_no_operands_instruction

nasm_fldz_no_operands_instruction:
	fldz 

global nasm_fldz_no_operands_instruction

nasm_fnstenv_m_instruction_by_number:
	fnstenv [0x11223344]
	fnstenv [rbx + r12 * 4 ]

global nasm_fnstenv_m_instruction_by_number

nasm_fstenv_m_instruction_by_number:
	fstenv [0x11223344]
	fstenv [rbx + r12 * 4 ]

global nasm_fstenv_m_instruction_by_number

nasm_f2xm1_no_operands_instruction:
	f2xm1 

global nasm_f2xm1_no_operands_instruction

nasm_fyl2x_no_operands_instruction:
	fyl2x 

global nasm_fyl2x_no_operands_instruction

nasm_fptan_no_operands_instruction:
	fptan 

global nasm_fptan_no_operands_instruction

nasm_fpatan_no_operands_instruction:
	fpatan 

global nasm_fpatan_no_operands_instruction

nasm_fxtract_no_operands_instruction:
	fxtract 

global nasm_fxtract_no_operands_instruction

nasm_fprem1_no_operands_instruction:
	fprem1 

global nasm_fprem1_no_operands_instruction

nasm_fdecstp_no_operands_instruction:
	fdecstp 

global nasm_fdecstp_no_operands_instruction

nasm_fincstp_no_operands_instruction:
	fincstp 

global nasm_fincstp_no_operands_instruction

nasm_fnstcw_m16_instruction_by_number:
	fnstcw word [r11 + rbx * 8]

global nasm_fnstcw_m16_instruction_by_number

nasm_fstcw_m16_instruction_by_number:
	fstcw word [r11 + rbx * 8]

global nasm_fstcw_m16_instruction_by_number

nasm_fprem_no_operands_instruction:
	fprem 

global nasm_fprem_no_operands_instruction

nasm_fyl2xp1_no_operands_instruction:
	fyl2xp1 

global nasm_fyl2xp1_no_operands_instruction

nasm_fsqrt_no_operands_instruction:
	fsqrt 

global nasm_fsqrt_no_operands_instruction

nasm_fsincos_no_operands_instruction:
	fsincos 

global nasm_fsincos_no_operands_instruction

nasm_frndint_no_operands_instruction:
	frndint 

global nasm_frndint_no_operands_instruction

nasm_fscale_no_operands_instruction:
	fscale 

global nasm_fscale_no_operands_instruction

nasm_fsin_no_operands_instruction:
	fsin 

global nasm_fsin_no_operands_instruction

nasm_fcos_no_operands_instruction:
	fcos 

global nasm_fcos_no_operands_instruction

nasm_fiadd_m32_instruction_by_number:
	fiadd dword [r11 + rax]

global nasm_fiadd_m32_instruction_by_number

nasm_fcmovb_sti_instruction_by_number:
	fcmovb st6

global nasm_fcmovb_sti_instruction_by_number

nasm_fimul_m32_instruction_by_number:
	fimul dword [r11 + rax]

global nasm_fimul_m32_instruction_by_number

nasm_fcmove_sti_instruction_by_number:
	fcmove st6

global nasm_fcmove_sti_instruction_by_number

nasm_ficom_m32_instruction_by_number:
	ficom dword [r11 + rax]

global nasm_ficom_m32_instruction_by_number

nasm_fcmovbe_sti_instruction_by_number:
	fcmovbe st6

global nasm_fcmovbe_sti_instruction_by_number

nasm_ficomp_m32_instruction_by_number:
	ficomp dword [r11 + rax]

global nasm_ficomp_m32_instruction_by_number

nasm_fcmovu_sti_instruction_by_number:
	fcmovu st6

global nasm_fcmovu_sti_instruction_by_number

nasm_fisub_m32_instruction_by_number:
	fisub dword [r11 + rax]

global nasm_fisub_m32_instruction_by_number

nasm_fisubr_m32_instruction_by_number:
	fisubr dword [r11 + rax]

global nasm_fisubr_m32_instruction_by_number

nasm_fucompp_no_operands_instruction:
	fucompp 

global nasm_fucompp_no_operands_instruction

nasm_fidiv_m32_instruction_by_number:
	fidiv dword [r11 + rax]

global nasm_fidiv_m32_instruction_by_number

nasm_fidivr_m32_instruction_by_number:
	fidivr dword [r11 + rax]

global nasm_fidivr_m32_instruction_by_number

nasm_fild_m32_instruction_by_number:
	fild dword [r11 + rax]

global nasm_fild_m32_instruction_by_number

nasm_fcmovnb_sti_instruction_by_number:
	fcmovnb st6

global nasm_fcmovnb_sti_instruction_by_number

nasm_fisttp_m32_instruction_by_number:
	fisttp dword [r11 + rax]

global nasm_fisttp_m32_instruction_by_number

nasm_fcmovne_sti_instruction_by_number:
	fcmovne st6

global nasm_fcmovne_sti_instruction_by_number

nasm_fist_m32_instruction_by_number:
	fist dword [r11 + rax]

global nasm_fist_m32_instruction_by_number

nasm_fcmovnbe_sti_instruction_by_number:
	fcmovnbe st6

global nasm_fcmovnbe_sti_instruction_by_number

nasm_fistp_m32_instruction_by_number:
	fistp dword [r11 + rax]

global nasm_fistp_m32_instruction_by_number

nasm_fcmovnu_sti_instruction_by_number:
	fcmovnu st6

global nasm_fcmovnu_sti_instruction_by_number

nasm_fneni_no_operands_instruction:
	fneni 

global nasm_fneni_no_operands_instruction

nasm_fndisi_no_operands_instruction:
	fndisi 

global nasm_fndisi_no_operands_instruction

nasm_fnclex_no_operands_instruction:
	fnclex 

global nasm_fnclex_no_operands_instruction

nasm_fclex_no_operands_instruction:
	fclex 

global nasm_fclex_no_operands_instruction

nasm_fninit_no_operands_instruction:
	fninit 

global nasm_fninit_no_operands_instruction

nasm_finit_no_operands_instruction:
	finit 

global nasm_finit_no_operands_instruction

nasm_fld_m80_instruction_by_number:
	fld tword [r11 + rax]

global nasm_fld_m80_instruction_by_number

nasm_fucomi_sti_instruction_by_number:
	fucomi st6

global nasm_fucomi_sti_instruction_by_number

nasm_fcomi_sti_instruction_by_number:
	fcomi st6

global nasm_fcomi_sti_instruction_by_number

nasm_fstp_m80_instruction_by_number:
	fstp tword [r11 + rax]

global nasm_fstp_m80_instruction_by_number

nasm_fadd_sti_st_instruction_by_number:
	fadd st6, st0

global nasm_fadd_sti_st_instruction_by_number

nasm_fmul_sti_st_instruction_by_number:
	fmul st6, st0

global nasm_fmul_sti_st_instruction_by_number

nasm_fsubr_sti_st_instruction_by_number:
	fsubr st6, st0

global nasm_fsubr_sti_st_instruction_by_number

nasm_fsub_sti_st_instruction_by_number:
	fsub st6, st0

global nasm_fsub_sti_st_instruction_by_number

nasm_fdivr_sti_st_instruction_by_number:
	fdivr st6, st0

global nasm_fdivr_sti_st_instruction_by_number

nasm_fdiv_sti_st_instruction_by_number:
	fdiv st6, st0

global nasm_fdiv_sti_st_instruction_by_number

nasm_ffree_sti_instruction_by_number:
	ffree st6

global nasm_ffree_sti_instruction_by_number

nasm_fst_sti_instruction_by_number:
	fst st6

global nasm_fst_sti_instruction_by_number

nasm_fstp_stm64_instruction_by_number:
	fstp st6
	fstp qword [rdx]

global nasm_fstp_stm64_instruction_by_number

nasm_frstor_m_instruction_by_number:
	frstor [0x11223344]
	frstor [rbx + r12 * 4 ]

global nasm_frstor_m_instruction_by_number

nasm_fucom_sti_instruction_by_number:
	fucom st6

global nasm_fucom_sti_instruction_by_number

nasm_fucom_no_operands_instruction:
	fucom 

global nasm_fucom_no_operands_instruction

nasm_fucomp_sti_instruction_by_number:
	fucomp st6

global nasm_fucomp_sti_instruction_by_number

nasm_fucomp_no_operands_instruction:
	fucomp 

global nasm_fucomp_no_operands_instruction

nasm_fnsave_m_instruction_by_number:
	fnsave [0x11223344]
	fnsave [rbx + r12 * 4 ]

global nasm_fnsave_m_instruction_by_number

nasm_fsave_m_instruction_by_number:
	fsave [0x11223344]
	fsave [rbx + r12 * 4 ]

global nasm_fsave_m_instruction_by_number

nasm_fnstsw_m16_instruction_by_number:
	fnstsw word [r11 + rbx * 8]

global nasm_fnstsw_m16_instruction_by_number

nasm_fstsw_m16_instruction_by_number:
	fstsw word [r11 + rbx * 8]

global nasm_fstsw_m16_instruction_by_number

nasm_fiadd_m16_instruction_by_number:
	fiadd word [r11 + rbx * 8]

global nasm_fiadd_m16_instruction_by_number

nasm_faddp_sti_instruction_by_number:
	faddp st6

global nasm_faddp_sti_instruction_by_number

nasm_faddp_no_operands_instruction:
	faddp 

global nasm_faddp_no_operands_instruction

nasm_fimul_m16_instruction_by_number:
	fimul word [r11 + rbx * 8]

global nasm_fimul_m16_instruction_by_number

nasm_fmulp_sti_instruction_by_number:
	fmulp st6

global nasm_fmulp_sti_instruction_by_number

nasm_fmulp_no_operands_instruction:
	fmulp 

global nasm_fmulp_no_operands_instruction

nasm_ficom_m16_instruction_by_number:
	ficom word [r11 + rbx * 8]

global nasm_ficom_m16_instruction_by_number

nasm_ficomp_m16_instruction_by_number:
	ficomp word [r11 + rbx * 8]

global nasm_ficomp_m16_instruction_by_number

nasm_fcompp_no_operands_instruction:
	fcompp 

global nasm_fcompp_no_operands_instruction

nasm_fisub_m16_instruction_by_number:
	fisub word [r11 + rbx * 8]

global nasm_fisub_m16_instruction_by_number

nasm_fsubrp_sti_instruction_by_number:
	fsubrp st6

global nasm_fsubrp_sti_instruction_by_number

nasm_fsubrp_no_operands_instruction:
	fsubrp 

global nasm_fsubrp_no_operands_instruction

nasm_fisubr_m16_instruction_by_number:
	fisubr word [r11 + rbx * 8]

global nasm_fisubr_m16_instruction_by_number

nasm_fsubp_sti_instruction_by_number:
	fsubp st6

global nasm_fsubp_sti_instruction_by_number

nasm_fsubp_no_operands_instruction:
	fsubp 

global nasm_fsubp_no_operands_instruction

nasm_fidiv_m16_instruction_by_number:
	fidiv word [r11 + rbx * 8]

global nasm_fidiv_m16_instruction_by_number

nasm_fdivrp_sti_instruction_by_number:
	fdivrp st6

global nasm_fdivrp_sti_instruction_by_number

nasm_fdivrp_no_operands_instruction:
	fdivrp 

global nasm_fdivrp_no_operands_instruction

nasm_fidivr_m16_instruction_by_number:
	fidivr word [r11 + rbx * 8]

global nasm_fidivr_m16_instruction_by_number

nasm_fdivp_sti_instruction_by_number:
	fdivp st6

global nasm_fdivp_sti_instruction_by_number

nasm_fdivp_no_operands_instruction:
	fdivp 

global nasm_fdivp_no_operands_instruction

nasm_fild_m16_instruction_by_number:
	fild word [r11 + rbx * 8]

global nasm_fild_m16_instruction_by_number

nasm_ffreep_sti_instruction_by_number:
	ffreep st6

global nasm_ffreep_sti_instruction_by_number

nasm_fisttp_m16_instruction_by_number:
	fisttp word [r11 + rbx * 8]

global nasm_fisttp_m16_instruction_by_number

nasm_fist_m16_instruction_by_number:
	fist word [r11 + rbx * 8]

global nasm_fist_m16_instruction_by_number

nasm_fistp_m16_instruction_by_number:
	fistp word [r11 + rbx * 8]

global nasm_fistp_m16_instruction_by_number

nasm_fbld_m80_instruction_by_number:
	fbld tword [r11 + rax]

global nasm_fbld_m80_instruction_by_number

nasm_fnstsw_ax_instruction:
	fnstsw ax

global nasm_fnstsw_ax_instruction

nasm_fstsw_ax_instruction:
	fstsw ax

global nasm_fstsw_ax_instruction

nasm_fucomip_sti_instruction_by_number:
	fucomip st6

global nasm_fucomip_sti_instruction_by_number

nasm_fbstp_m80_instruction_by_number:
	fbstp tword [r11 + rax]

global nasm_fbstp_m80_instruction_by_number

nasm_fcomip_sti_instruction_by_number:
	fcomip st6

global nasm_fcomip_sti_instruction_by_number

nasm_in_al_imm8_instruction:
	in al, 0x40

global nasm_in_al_imm8_instruction

nasm_in_eax_imm8_instruction:
	in eax, 0x88

global nasm_in_eax_imm8_instruction

nasm_out_imm8_al_instruction:
	out 0x11, al

global nasm_out_imm8_al_instruction

nasm_out_imm8_eax_instruction:
	out 0x11, eax

global nasm_out_imm8_eax_instruction

nasm_in_al_dx_instruction:
	in al, dx

global nasm_in_al_dx_instruction

nasm_in_eax_dx_instruction:
	in eax, dx

global nasm_in_eax_dx_instruction

nasm_out_dx_al_instruction:
	out dx, al

global nasm_out_dx_al_instruction

nasm_out_dx_eax_instruction:
	out dx, eax

global nasm_out_dx_eax_instruction

nasm_lock_no_operands_instruction:
	lock 

global nasm_lock_no_operands_instruction

nasm_int1_no_operands_instruction:
	int1 

global nasm_int1_no_operands_instruction

nasm_icebp_no_operands_instruction:
	icebp 

global nasm_icebp_no_operands_instruction

nasm_repnz_no_operands_instruction:
	repnz 

global nasm_repnz_no_operands_instruction

nasm_repne_no_operands_instruction:
	repne 

global nasm_repne_no_operands_instruction

nasm_repz_no_operands_instruction:
	repz 

global nasm_repz_no_operands_instruction

nasm_repe_no_operands_instruction:
	repe 

global nasm_repe_no_operands_instruction

nasm_rep_no_operands_instruction:
	rep 

global nasm_rep_no_operands_instruction

nasm_hlt_no_operands_instruction:
	hlt 

global nasm_hlt_no_operands_instruction

nasm_cmc_no_operands_instruction:
	cmc 

global nasm_cmc_no_operands_instruction

nasm_test_rm8_imm8_instruction_by_number:
	test byte [ebx], 11
	test dl, 11
	test al, 11

global nasm_test_rm8_imm8_instruction_by_number

nasm_test_rm16_32_64_imm16_32_instruction_by_number:
	test dx, 0x1111
	test edx, 0x111122
	test rdx, 0x111122
	test word [ebx * 4], 0x1111
	test dword [ebx * 4], 0x111122
	test qword [ebx * 4], 0x111122

global nasm_test_rm16_32_64_imm16_32_instruction_by_number

nasm_clc_no_operands_instruction:
	clc 

global nasm_clc_no_operands_instruction

nasm_stc_no_operands_instruction:
	stc 

global nasm_stc_no_operands_instruction

nasm_cli_no_operands_instruction:
	cli 

global nasm_cli_no_operands_instruction

nasm_sti_no_operands_instruction:
	sti 

global nasm_sti_no_operands_instruction

nasm_cld_no_operands_instruction:
	cld 

global nasm_cld_no_operands_instruction

nasm_std_no_operands_instruction:
	std 

global nasm_std_no_operands_instruction

nasm_call_rm64_instruction_by_number:
	call rdx
	call qword[ebx * 4]

global nasm_call_rm64_instruction_by_number

nasm_jmp_rm64_instruction_by_number:
	jmp rdx
	jmp qword[ebx * 4]

global nasm_jmp_rm64_instruction_by_number

nasm_push_m16_64_instruction_by_number:
	push word [r11 + rbx * 8]
	push qword [r11 + rbx * 8]

global nasm_push_m16_64_instruction_by_number

nasm_sldt_m16_instruction_by_number:
	sldt word [r11 + rbx * 8]

global nasm_sldt_m16_instruction_by_number

nasm_sldt_r16_32_instruction_by_number:
	sldt dx
	sldt edx

global nasm_sldt_r16_32_instruction_by_number

nasm_str_m16_instruction_by_number:
	str word [r11 + rbx * 8]

global nasm_str_m16_instruction_by_number

nasm_str_r16_32_64_instruction_by_number:
	str dx
	str edx
	str rdx

global nasm_str_r16_32_64_instruction_by_number

nasm_lldt_rm16_instruction_by_number:
	lldt dx
	lldt word[r11 + rax * 4]

global nasm_lldt_rm16_instruction_by_number

nasm_ltr_rm16_instruction_by_number:
	ltr dx
	ltr word[r11 + rax * 4]

global nasm_ltr_rm16_instruction_by_number

nasm_verr_rm16_instruction_by_number:
	verr dx
	verr word[r11 + rax * 4]

global nasm_verr_rm16_instruction_by_number

nasm_verw_rm16_instruction_by_number:
	verw dx
	verw word[r11 + rax * 4]

global nasm_verw_rm16_instruction_by_number

nasm_sgdt_m_instruction_by_number:
	sgdt [0x11223344]
	sgdt [rbx + r12 * 4 ]

global nasm_sgdt_m_instruction_by_number

nasm_vmcall_no_operands_instruction:
	vmcall 

global nasm_vmcall_no_operands_instruction

nasm_vmlaunch_no_operands_instruction:
	vmlaunch 

global nasm_vmlaunch_no_operands_instruction

nasm_vmresume_no_operands_instruction:
	vmresume 

global nasm_vmresume_no_operands_instruction

nasm_vmxoff_no_operands_instruction:
	vmxoff 

global nasm_vmxoff_no_operands_instruction

nasm_sidt_m_instruction_by_number:
	sidt [0x11223344]
	sidt [rbx + r12 * 4 ]

global nasm_sidt_m_instruction_by_number

nasm_monitor_no_operands_instruction:
	monitor 

global nasm_monitor_no_operands_instruction

nasm_mwait_no_operands_instruction:
	mwait 

global nasm_mwait_no_operands_instruction

nasm_lgdt_m_instruction_by_number:
	lgdt [0x11223344]
	lgdt [rbx + r12 * 4 ]

global nasm_lgdt_m_instruction_by_number

nasm_xgetbv_no_operands_instruction:
	xgetbv 

global nasm_xgetbv_no_operands_instruction

nasm_xsetbv_no_operands_instruction:
	xsetbv 

global nasm_xsetbv_no_operands_instruction

nasm_lidt_m_instruction_by_number:
	lidt [0x11223344]
	lidt [rbx + r12 * 4 ]

global nasm_lidt_m_instruction_by_number

nasm_smsw_m16_instruction_by_number:
	smsw word [r11 + rbx * 8]

global nasm_smsw_m16_instruction_by_number

nasm_smsw_r16_32_64_instruction_by_number:
	smsw dx
	smsw edx
	smsw rdx

global nasm_smsw_r16_32_64_instruction_by_number

nasm_lmsw_rm16_instruction_by_number:
	lmsw dx
	lmsw word[r11 + rax * 4]

global nasm_lmsw_rm16_instruction_by_number

nasm_invlpg_m_instruction_by_number:
	invlpg [0x11223344]
	invlpg [rbx + r12 * 4 ]

global nasm_invlpg_m_instruction_by_number

nasm_swapgs_no_operands_instruction:
	swapgs 

global nasm_swapgs_no_operands_instruction

nasm_rdtscp_no_operands_instruction:
	rdtscp 

global nasm_rdtscp_no_operands_instruction

nasm_lar_r16_32_64_m16_instruction:
	lar dx, word [r11 + rax + 0x11]
	lar edx, word [r11 + rax + 0x112233]
	lar rdx, word [r11 + rax + 0x11]

global nasm_lar_r16_32_64_m16_instruction

nasm_lar_r16_32_64_r16_32_instruction:
	lar dx, ax
	lar edx, eax
	lar rdx, eax

global nasm_lar_r16_32_64_r16_32_instruction

nasm_lsl_r16_32_64_m16_instruction:
	lsl dx, word [r11 + rax + 0x11]
	lsl edx, word [r11 + rax + 0x112233]
	lsl rdx, word [r11 + rax + 0x11]

global nasm_lsl_r16_32_64_m16_instruction

nasm_lsl_r16_32_64_r16_32_instruction:
	lsl dx, ax
	lsl edx, eax
	lsl rdx, eax

global nasm_lsl_r16_32_64_r16_32_instruction

nasm_syscall_no_operands_instruction:
	syscall 

global nasm_syscall_no_operands_instruction

nasm_clts_no_operands_instruction:
	clts 

global nasm_clts_no_operands_instruction

nasm_sysret_no_operands_instruction:
	sysret 

global nasm_sysret_no_operands_instruction

nasm_invd_no_operands_instruction:
	invd 

global nasm_invd_no_operands_instruction

nasm_wbinvd_no_operands_instruction:
	wbinvd 

global nasm_wbinvd_no_operands_instruction

nasm_ud2_no_operands_instruction:
	ud2 

global nasm_ud2_no_operands_instruction

nasm_movups_xmm_xmmm128_instruction:
	movups xmm13, [r12 + rax]
	movups xmm8, xmm11

global nasm_movups_xmm_xmmm128_instruction

nasm_movss_xmm_xmmm32_instruction:
	movss xmm4, dword [r12 + rax]
	movss xmm2, xmm9

global nasm_movss_xmm_xmmm32_instruction

nasm_movupd_xmm_xmmm128_instruction:
	movupd xmm13, [r12 + rax]
	movupd xmm8, xmm11

global nasm_movupd_xmm_xmmm128_instruction

nasm_movsd_xmm_xmmm64_instruction:
	movsd xmm12, [r12 + rax]
	movsd xmm11, xmm3

global nasm_movsd_xmm_xmmm64_instruction

nasm_movups_xmmm128_xmm_instruction:
	movups xmm2, xmm6
	movups oword [rbp + rcx * 2], xmm6
	movups oword [r10 + rbp + 0x80], xmm6
	movups oword [rbp + 0x8012333], xmm6
	movups oword [rbp + 0x80], xmm6
	movups oword [rbp + 0xffffffff], xmm6
	movups oword [rbp + 0xff], xmm6

global nasm_movups_xmmm128_xmm_instruction

nasm_movss_xmmm32_xmm_instruction:
	movss xmm2, xmm6
	movss dword [esp + ecx * 2], xmm6

global nasm_movss_xmmm32_xmm_instruction

nasm_movupd_xmmm128_xmm_instruction:
	movupd xmm2, xmm6
	movupd oword [rbp + rcx * 2], xmm6
	movupd oword [r10 + rbp + 0x80], xmm6
	movupd oword [rbp + 0x8012333], xmm6
	movupd oword [rbp + 0x80], xmm6
	movupd oword [rbp + 0xffffffff], xmm6
	movupd oword [rbp + 0xff], xmm6

global nasm_movupd_xmmm128_xmm_instruction

nasm_movsd_xmmm64_xmm_instruction:
	movsd xmm2, xmm6
	movsd qword [r13 + r11], xmm6

global nasm_movsd_xmmm64_xmm_instruction

nasm_movhlps_xmm_xmm_instruction:
	movhlps xmm4, xmm12
	movhlps xmm12, xmm4

global nasm_movhlps_xmm_xmm_instruction

nasm_movlps_xmm_m64_instruction:
	movlps xmm13, qword [r13d]

global nasm_movlps_xmm_m64_instruction

nasm_movlpd_xmm_m64_instruction:
	movlpd xmm13, qword [r13d]

global nasm_movlpd_xmm_m64_instruction

nasm_movddup_xmm_xmmm64_instruction:
	movddup xmm12, [r12 + rax]
	movddup xmm11, xmm3

global nasm_movddup_xmm_xmmm64_instruction

nasm_movsldup_xmm_xmmm64_instruction:
	movsldup xmm12, [r12 + rax]
	movsldup xmm11, xmm3

global nasm_movsldup_xmm_xmmm64_instruction

nasm_movlps_m64_xmm_instruction:
	movlps qword [r11 + rax], xmm2

global nasm_movlps_m64_xmm_instruction

nasm_movlpd_m64_xmm_instruction:
	movlpd qword [r11 + rax], xmm2

global nasm_movlpd_m64_xmm_instruction

nasm_unpcklps_xmm_xmmm64_instruction:
	unpcklps xmm12, [r12 + rax]
	unpcklps xmm11, xmm3

global nasm_unpcklps_xmm_xmmm64_instruction

nasm_unpcklpd_xmm_xmmm128_instruction:
	unpcklpd xmm13, [r12 + rax]
	unpcklpd xmm8, xmm11

global nasm_unpcklpd_xmm_xmmm128_instruction

nasm_unpckhps_xmm_xmmm64_instruction:
	unpckhps xmm12, [r12 + rax]
	unpckhps xmm11, xmm3

global nasm_unpckhps_xmm_xmmm64_instruction

nasm_unpckhpd_xmm_xmmm128_instruction:
	unpckhpd xmm13, [r12 + rax]
	unpckhpd xmm8, xmm11

global nasm_unpckhpd_xmm_xmmm128_instruction

nasm_movlhps_xmm_xmm_instruction:
	movlhps xmm4, xmm12
	movlhps xmm12, xmm4

global nasm_movlhps_xmm_xmm_instruction

nasm_movhps_xmm_m64_instruction:
	movhps xmm13, qword [r13d]

global nasm_movhps_xmm_m64_instruction

nasm_movhpd_xmm_m64_instruction:
	movhpd xmm13, qword [r13d]

global nasm_movhpd_xmm_m64_instruction

nasm_movshdup_xmm_xmmm64_instruction:
	movshdup xmm12, [r12 + rax]
	movshdup xmm11, xmm3

global nasm_movshdup_xmm_xmmm64_instruction

nasm_movhps_m64_xmm_instruction:
	movhps qword [r11 + rax], xmm2

global nasm_movhps_m64_xmm_instruction

nasm_movhpd_m64_xmm_instruction:
	movhpd qword [r11 + rax], xmm2

global nasm_movhpd_m64_xmm_instruction

nasm_prefetchnta_m8_instruction_by_number:
	prefetchnta [r11 + rax]

global nasm_prefetchnta_m8_instruction_by_number

nasm_prefetcht0_m8_instruction_by_number:
	prefetcht0 [r11 + rax]

global nasm_prefetcht0_m8_instruction_by_number

nasm_prefetcht1_m8_instruction_by_number:
	prefetcht1 [r11 + rax]

global nasm_prefetcht1_m8_instruction_by_number

nasm_prefetcht2_m8_instruction_by_number:
	prefetcht2 [r11 + rax]

global nasm_prefetcht2_m8_instruction_by_number

nasm_nop_rm16_32_instruction:
	nop dx
	nop edx
	nop word[ebx * 4]
	nop dword[ebx * 4]

global nasm_nop_rm16_32_instruction

nasm_mov_r64_crn_instruction:
	mov rdx, cr0

global nasm_mov_r64_crn_instruction

nasm_mov_r64_drn_instruction:
	mov rax, dr0

global nasm_mov_r64_drn_instruction

nasm_mov_crn_r64_instruction:
	mov cr0, rcx

global nasm_mov_crn_r64_instruction

nasm_mov_drn_r64_instruction:
	mov dr0, rcx

global nasm_mov_drn_r64_instruction

nasm_movaps_xmm_xmmm128_instruction:
	movaps xmm13, [r12 + rax]
	movaps xmm8, xmm11

global nasm_movaps_xmm_xmmm128_instruction

nasm_movapd_xmm_xmmm128_instruction:
	movapd xmm13, [r12 + rax]
	movapd xmm8, xmm11

global nasm_movapd_xmm_xmmm128_instruction

nasm_movaps_xmmm128_xmm_instruction:
	movaps xmm2, xmm6
	movaps oword [rbp + rcx * 2], xmm6
	movaps oword [r10 + rbp + 0x80], xmm6
	movaps oword [rbp + 0x8012333], xmm6
	movaps oword [rbp + 0x80], xmm6
	movaps oword [rbp + 0xffffffff], xmm6
	movaps oword [rbp + 0xff], xmm6

global nasm_movaps_xmmm128_xmm_instruction

nasm_movapd_xmmm128_xmm_instruction:
	movapd xmm2, xmm6
	movapd oword [rbp + rcx * 2], xmm6
	movapd oword [r10 + rbp + 0x80], xmm6
	movapd oword [rbp + 0x8012333], xmm6
	movapd oword [rbp + 0x80], xmm6
	movapd oword [rbp + 0xffffffff], xmm6
	movapd oword [rbp + 0xff], xmm6

global nasm_movapd_xmmm128_xmm_instruction

nasm_cvtpi2ps_xmm_mmm64_instruction:
	cvtpi2ps xmm15, qword [eax * 4]
	cvtpi2ps xmm15, mm5

global nasm_cvtpi2ps_xmm_mmm64_instruction

nasm_cvtsi2ss_xmm_rm32_64_instruction:
	cvtsi2ss xmm15, dword [r13d]
	cvtsi2ss xmm3, qword [r13 + r13]

global nasm_cvtsi2ss_xmm_rm32_64_instruction

nasm_cvtpi2pd_xmm_mmm64_instruction:
	cvtpi2pd xmm15, qword [eax * 4]
	cvtpi2pd xmm15, mm5

global nasm_cvtpi2pd_xmm_mmm64_instruction

nasm_cvtsi2sd_xmm_rm32_64_instruction:
	cvtsi2sd xmm15, dword [r13d]
	cvtsi2sd xmm3, qword [r13 + r13]

global nasm_cvtsi2sd_xmm_rm32_64_instruction

nasm_movntps_m128_xmm_instruction:
	movntps gs:[0x8888888], xmm2
	movntps oword [r11 + rdx * 8], xmm8

global nasm_movntps_m128_xmm_instruction

nasm_movntpd_m128_xmm_instruction:
	movntpd gs:[0x8888888], xmm2
	movntpd oword [r11 + rdx * 8], xmm8

global nasm_movntpd_m128_xmm_instruction

nasm_cvttps2pi_mm_xmmm64_instruction:
	cvttps2pi mm2, xmm3
	cvttps2pi mm6, [r11 + rax * 4]

global nasm_cvttps2pi_mm_xmmm64_instruction

nasm_cvttss2si_r32_64_xmmm32_instruction:
	cvttss2si edx, xmm2
	cvttss2si edx, dword [ebp + 0x12]
	cvttss2si rdx, xmm2
	cvttss2si rdx, dword [ebp + 0x12]

global nasm_cvttss2si_r32_64_xmmm32_instruction

nasm_cvttpd2pi_mm_xmmm128_instruction:
	cvttpd2pi mm2, xmm3
	cvttpd2pi mm6, [r11 + rax * 4]

global nasm_cvttpd2pi_mm_xmmm128_instruction

nasm_cvttsd2si_r32_64_xmmm64_instruction:
	cvttsd2si edx, xmm2
	cvttsd2si edx, qword [rcx + r15 + 0x1212]
	cvttsd2si rdx, xmm2
	cvttsd2si rdx, qword [rcx + r15 + 0x1212]

global nasm_cvttsd2si_r32_64_xmmm64_instruction

nasm_cvtps2pi_mm_xmmm64_instruction:
	cvtps2pi mm2, xmm3
	cvtps2pi mm6, [r11 + rax * 4]

global nasm_cvtps2pi_mm_xmmm64_instruction

nasm_cvtss2si_r32_64_xmmm32_instruction:
	cvtss2si edx, xmm2
	cvtss2si edx, dword [ebp + 0x12]
	cvtss2si rdx, xmm2
	cvtss2si rdx, dword [ebp + 0x12]

global nasm_cvtss2si_r32_64_xmmm32_instruction

nasm_cvtpd2pi_mm_xmmm128_instruction:
	cvtpd2pi mm2, xmm3
	cvtpd2pi mm6, [r11 + rax * 4]

global nasm_cvtpd2pi_mm_xmmm128_instruction

nasm_cvtsd2si_r32_64_xmmm64_instruction:
	cvtsd2si edx, xmm2
	cvtsd2si edx, qword [rcx + r15 + 0x1212]
	cvtsd2si rdx, xmm2
	cvtsd2si rdx, qword [rcx + r15 + 0x1212]

global nasm_cvtsd2si_r32_64_xmmm64_instruction

nasm_ucomiss_xmm_xmmm32_instruction:
	ucomiss xmm4, dword [r12 + rax]
	ucomiss xmm2, xmm9

global nasm_ucomiss_xmm_xmmm32_instruction

nasm_ucomisd_xmm_xmmm64_instruction:
	ucomisd xmm12, [r12 + rax]
	ucomisd xmm11, xmm3

global nasm_ucomisd_xmm_xmmm64_instruction

nasm_comiss_xmm_xmmm32_instruction:
	comiss xmm4, dword [r12 + rax]
	comiss xmm2, xmm9

global nasm_comiss_xmm_xmmm32_instruction

nasm_comisd_xmm_xmmm64_instruction:
	comisd xmm12, [r12 + rax]
	comisd xmm11, xmm3

global nasm_comisd_xmm_xmmm64_instruction

nasm_wrmsr_no_operands_instruction:
	wrmsr 

global nasm_wrmsr_no_operands_instruction

nasm_rdtsc_no_operands_instruction:
	rdtsc 

global nasm_rdtsc_no_operands_instruction

nasm_rdmsr_no_operands_instruction:
	rdmsr 

global nasm_rdmsr_no_operands_instruction

nasm_rdpmc_no_operands_instruction:
	rdpmc 

global nasm_rdpmc_no_operands_instruction

nasm_sysenter_no_operands_instruction:
	sysenter 

global nasm_sysenter_no_operands_instruction

nasm_sysexit_no_operands_instruction:
	sysexit 

global nasm_sysexit_no_operands_instruction

nasm_getsec_no_operands_instruction:
	getsec 

global nasm_getsec_no_operands_instruction

nasm_invept_r64_m128_instruction:
	invept rax, oword [0x11223344]

global nasm_invept_r64_m128_instruction

nasm_invvpid_r64_m128_instruction:
	invvpid rax, oword [0x11223344]

global nasm_invvpid_r64_m128_instruction

nasm_movbe_r16_32_64_m16_32_64_instruction:
	movbe dx, word [r11 + rax]
	movbe edx, dword [r11 + rax]
	movbe rdx, qword [r11 + rax]

global nasm_movbe_r16_32_64_m16_32_64_instruction

nasm_crc32_r32_64_rm8_instruction:
	crc32 edx, cl
	crc32 edx, byte [rcx]
	crc32 rdx, cl
	crc32 rdx, byte [rcx]

global nasm_crc32_r32_64_rm8_instruction

nasm_movbe_m16_32_64_r16_32_64_instruction:
	movbe word [r11 + rbx * 8], dx
	movbe dword [r11 + rbx * 8], eax
	movbe qword [r11 + rbx * 8], rdx

global nasm_movbe_m16_32_64_r16_32_64_instruction

nasm_crc32_r32_64_rm16_32_64_instruction:
	crc32 edx, cx
	crc32 edx, ecx
	crc32 rdx, rcx

global nasm_crc32_r32_64_rm16_32_64_instruction

nasm_roundps_xmm_xmmm128_imm8_instruction:
	roundps xmm4, [r12 + rax], 4
	roundps xmm9, xmm8, 4

global nasm_roundps_xmm_xmmm128_imm8_instruction

nasm_roundpd_xmm_xmmm128_imm8_instruction:
	roundpd xmm4, [r12 + rax], 4
	roundpd xmm9, xmm8, 4

global nasm_roundpd_xmm_xmmm128_imm8_instruction

nasm_roundss_xmm_xmmm32_imm8_instruction:
	roundss xmm4, dword [r12 + rax], 4
	roundss xmm2, xmm3, 4

global nasm_roundss_xmm_xmmm32_imm8_instruction

nasm_roundsd_xmm_xmmm64_imm8_instruction:
	roundsd xmm14, [r12 + rax], 4
	roundsd xmm2, xmm11, 4

global nasm_roundsd_xmm_xmmm64_imm8_instruction

nasm_blendps_xmm_xmmm128_imm8_instruction:
	blendps xmm4, [r12 + rax], 4
	blendps xmm9, xmm8, 4

global nasm_blendps_xmm_xmmm128_imm8_instruction

nasm_blendpd_xmm_xmmm128_imm8_instruction:
	blendpd xmm4, [r12 + rax], 4
	blendpd xmm9, xmm8, 4

global nasm_blendpd_xmm_xmmm128_imm8_instruction

nasm_pblendw_xmm_xmmm128_imm8_instruction:
	pblendw xmm4, [r12 + rax], 4
	pblendw xmm9, xmm8, 4

global nasm_pblendw_xmm_xmmm128_imm8_instruction

nasm_palignr_xmm_xmmm128_imm8_instruction:
	palignr xmm4, [r12 + rax], 4
	palignr xmm9, xmm8, 4

global nasm_palignr_xmm_xmmm128_imm8_instruction

nasm_pextrb_m8_xmm_imm8_instruction:
	pextrb [r11 + rax], xmm6, 0x11

global nasm_pextrb_m8_xmm_imm8_instruction

nasm_pextrb_r32_64_xmm_imm8_instruction:
	pextrb edx, xmm2, 12
	pextrb rdx, xmm7, 12

global nasm_pextrb_r32_64_xmm_imm8_instruction

nasm_pextrd_rm32_xmm_imm8_instruction:
	pextrd edx, xmm5, 0x55
	pextrd dword[ebx * 4], xmm5, 0x55

global nasm_pextrd_rm32_xmm_imm8_instruction

nasm_pextrq_rm64_xmm_imm8_instruction:
	pextrq rdx, xmm6, 0x11
	pextrq qword[ebx * 4], xmm6, 0x11

global nasm_pextrq_rm64_xmm_imm8_instruction

nasm_extractps_rm32_xmm_imm8_instruction:
	extractps edx, xmm5, 0x55
	extractps dword[ebx * 4], xmm5, 0x55

global nasm_extractps_rm32_xmm_imm8_instruction

nasm_pinsrb_xmm_m8_imm8_instruction:
	pinsrb xmm12, byte [rsp + 0x45], 0x17

global nasm_pinsrb_xmm_m8_imm8_instruction

nasm_pinsrb_xmm_r32_imm8_instruction:
	pinsrb xmm15, ecx, 4
	pinsrb xmm3, r13d, 4

global nasm_pinsrb_xmm_r32_imm8_instruction

nasm_insertps_xmm_m32_imm8_instruction:
	insertps xmm8, dword [r13d * 4], 0x17

global nasm_insertps_xmm_m32_imm8_instruction

nasm_insertps_xmm_xmm_imm8_instruction:
	insertps xmm4, xmm12, 4
	insertps xmm12, xmm4, 4

global nasm_insertps_xmm_xmm_imm8_instruction

nasm_dpps_xmm_xmmm128_imm8_instruction:
	dpps xmm4, [r12 + rax], 4
	dpps xmm9, xmm8, 4

global nasm_dpps_xmm_xmmm128_imm8_instruction

nasm_dppd_xmm_xmmm128_imm8_instruction:
	dppd xmm4, [r12 + rax], 4
	dppd xmm9, xmm8, 4

global nasm_dppd_xmm_xmmm128_imm8_instruction

nasm_mpsadbw_xmm_xmmm128_imm8_instruction:
	mpsadbw xmm4, [r12 + rax], 4
	mpsadbw xmm9, xmm8, 4

global nasm_mpsadbw_xmm_xmmm128_imm8_instruction

nasm_pcmpestrm_xmm_xmmm128_imm8_instruction:
	pcmpestrm xmm4, [r12 + rax], 4
	pcmpestrm xmm9, xmm8, 4

global nasm_pcmpestrm_xmm_xmmm128_imm8_instruction

nasm_pcmpestri_xmm_xmmm128_imm8_instruction:
	pcmpestri xmm4, [r12 + rax], 4
	pcmpestri xmm9, xmm8, 4

global nasm_pcmpestri_xmm_xmmm128_imm8_instruction

nasm_pcmpistrm_xmm_xmmm128_imm8_instruction:
	pcmpistrm xmm4, [r12 + rax], 4
	pcmpistrm xmm9, xmm8, 4

global nasm_pcmpistrm_xmm_xmmm128_imm8_instruction

nasm_pcmpistri_xmm_xmmm128_imm8_instruction:
	pcmpistri xmm4, [r12 + rax], 4
	pcmpistri xmm9, xmm8, 4

global nasm_pcmpistri_xmm_xmmm128_imm8_instruction

nasm_cmovo_r16_32_64_rm16_32_64_instruction:
	cmovo cx, word [r11 + rbx]
	cmovo ebx, dword [r11 + rbx]
	cmovo rax, qword [r12]

global nasm_cmovo_r16_32_64_rm16_32_64_instruction

nasm_cmovno_r16_32_64_rm16_32_64_instruction:
	cmovno cx, word [r11 + rbx]
	cmovno ebx, dword [r11 + rbx]
	cmovno rax, qword [r12]

global nasm_cmovno_r16_32_64_rm16_32_64_instruction

nasm_cmovb_r16_32_64_rm16_32_64_instruction:
	cmovb cx, word [r11 + rbx]
	cmovb ebx, dword [r11 + rbx]
	cmovb rax, qword [r12]

global nasm_cmovb_r16_32_64_rm16_32_64_instruction

nasm_cmovnae_r16_32_64_rm16_32_64_instruction:
	cmovnae cx, word [r11 + rbx]
	cmovnae ebx, dword [r11 + rbx]
	cmovnae rax, qword [r12]

global nasm_cmovnae_r16_32_64_rm16_32_64_instruction

nasm_cmovc_r16_32_64_rm16_32_64_instruction:
	cmovc cx, word [r11 + rbx]
	cmovc ebx, dword [r11 + rbx]
	cmovc rax, qword [r12]

global nasm_cmovc_r16_32_64_rm16_32_64_instruction

nasm_cmovnb_r16_32_64_rm16_32_64_instruction:
	cmovnb cx, word [r11 + rbx]
	cmovnb ebx, dword [r11 + rbx]
	cmovnb rax, qword [r12]

global nasm_cmovnb_r16_32_64_rm16_32_64_instruction

nasm_cmovae_r16_32_64_rm16_32_64_instruction:
	cmovae cx, word [r11 + rbx]
	cmovae ebx, dword [r11 + rbx]
	cmovae rax, qword [r12]

global nasm_cmovae_r16_32_64_rm16_32_64_instruction

nasm_cmovnc_r16_32_64_rm16_32_64_instruction:
	cmovnc cx, word [r11 + rbx]
	cmovnc ebx, dword [r11 + rbx]
	cmovnc rax, qword [r12]

global nasm_cmovnc_r16_32_64_rm16_32_64_instruction

nasm_cmovz_r16_32_64_rm16_32_64_instruction:
	cmovz cx, word [r11 + rbx]
	cmovz ebx, dword [r11 + rbx]
	cmovz rax, qword [r12]

global nasm_cmovz_r16_32_64_rm16_32_64_instruction

nasm_cmove_r16_32_64_rm16_32_64_instruction:
	cmove cx, word [r11 + rbx]
	cmove ebx, dword [r11 + rbx]
	cmove rax, qword [r12]

global nasm_cmove_r16_32_64_rm16_32_64_instruction

nasm_cmovnz_r16_32_64_rm16_32_64_instruction:
	cmovnz cx, word [r11 + rbx]
	cmovnz ebx, dword [r11 + rbx]
	cmovnz rax, qword [r12]

global nasm_cmovnz_r16_32_64_rm16_32_64_instruction

nasm_cmovne_r16_32_64_rm16_32_64_instruction:
	cmovne cx, word [r11 + rbx]
	cmovne ebx, dword [r11 + rbx]
	cmovne rax, qword [r12]

global nasm_cmovne_r16_32_64_rm16_32_64_instruction

nasm_cmovbe_r16_32_64_rm16_32_64_instruction:
	cmovbe cx, word [r11 + rbx]
	cmovbe ebx, dword [r11 + rbx]
	cmovbe rax, qword [r12]

global nasm_cmovbe_r16_32_64_rm16_32_64_instruction

nasm_cmovna_r16_32_64_rm16_32_64_instruction:
	cmovna cx, word [r11 + rbx]
	cmovna ebx, dword [r11 + rbx]
	cmovna rax, qword [r12]

global nasm_cmovna_r16_32_64_rm16_32_64_instruction

nasm_cmovnbe_r16_32_64_rm16_32_64_instruction:
	cmovnbe cx, word [r11 + rbx]
	cmovnbe ebx, dword [r11 + rbx]
	cmovnbe rax, qword [r12]

global nasm_cmovnbe_r16_32_64_rm16_32_64_instruction

nasm_cmova_r16_32_64_rm16_32_64_instruction:
	cmova cx, word [r11 + rbx]
	cmova ebx, dword [r11 + rbx]
	cmova rax, qword [r12]

global nasm_cmova_r16_32_64_rm16_32_64_instruction

nasm_cmovs_r16_32_64_rm16_32_64_instruction:
	cmovs cx, word [r11 + rbx]
	cmovs ebx, dword [r11 + rbx]
	cmovs rax, qword [r12]

global nasm_cmovs_r16_32_64_rm16_32_64_instruction

nasm_cmovns_r16_32_64_rm16_32_64_instruction:
	cmovns cx, word [r11 + rbx]
	cmovns ebx, dword [r11 + rbx]
	cmovns rax, qword [r12]

global nasm_cmovns_r16_32_64_rm16_32_64_instruction

nasm_cmovp_r16_32_64_rm16_32_64_instruction:
	cmovp cx, word [r11 + rbx]
	cmovp ebx, dword [r11 + rbx]
	cmovp rax, qword [r12]

global nasm_cmovp_r16_32_64_rm16_32_64_instruction

nasm_cmovpe_r16_32_64_rm16_32_64_instruction:
	cmovpe cx, word [r11 + rbx]
	cmovpe ebx, dword [r11 + rbx]
	cmovpe rax, qword [r12]

global nasm_cmovpe_r16_32_64_rm16_32_64_instruction

nasm_cmovnp_r16_32_64_rm16_32_64_instruction:
	cmovnp cx, word [r11 + rbx]
	cmovnp ebx, dword [r11 + rbx]
	cmovnp rax, qword [r12]

global nasm_cmovnp_r16_32_64_rm16_32_64_instruction

nasm_cmovpo_r16_32_64_rm16_32_64_instruction:
	cmovpo cx, word [r11 + rbx]
	cmovpo ebx, dword [r11 + rbx]
	cmovpo rax, qword [r12]

global nasm_cmovpo_r16_32_64_rm16_32_64_instruction

nasm_cmovl_r16_32_64_rm16_32_64_instruction:
	cmovl cx, word [r11 + rbx]
	cmovl ebx, dword [r11 + rbx]
	cmovl rax, qword [r12]

global nasm_cmovl_r16_32_64_rm16_32_64_instruction

nasm_cmovnge_r16_32_64_rm16_32_64_instruction:
	cmovnge cx, word [r11 + rbx]
	cmovnge ebx, dword [r11 + rbx]
	cmovnge rax, qword [r12]

global nasm_cmovnge_r16_32_64_rm16_32_64_instruction

nasm_cmovnl_r16_32_64_rm16_32_64_instruction:
	cmovnl cx, word [r11 + rbx]
	cmovnl ebx, dword [r11 + rbx]
	cmovnl rax, qword [r12]

global nasm_cmovnl_r16_32_64_rm16_32_64_instruction

nasm_cmovge_r16_32_64_rm16_32_64_instruction:
	cmovge cx, word [r11 + rbx]
	cmovge ebx, dword [r11 + rbx]
	cmovge rax, qword [r12]

global nasm_cmovge_r16_32_64_rm16_32_64_instruction

nasm_cmovle_r16_32_64_rm16_32_64_instruction:
	cmovle cx, word [r11 + rbx]
	cmovle ebx, dword [r11 + rbx]
	cmovle rax, qword [r12]

global nasm_cmovle_r16_32_64_rm16_32_64_instruction

nasm_cmovng_r16_32_64_rm16_32_64_instruction:
	cmovng cx, word [r11 + rbx]
	cmovng ebx, dword [r11 + rbx]
	cmovng rax, qword [r12]

global nasm_cmovng_r16_32_64_rm16_32_64_instruction

nasm_cmovnle_r16_32_64_rm16_32_64_instruction:
	cmovnle cx, word [r11 + rbx]
	cmovnle ebx, dword [r11 + rbx]
	cmovnle rax, qword [r12]

global nasm_cmovnle_r16_32_64_rm16_32_64_instruction

nasm_cmovg_r16_32_64_rm16_32_64_instruction:
	cmovg cx, word [r11 + rbx]
	cmovg ebx, dword [r11 + rbx]
	cmovg rax, qword [r12]

global nasm_cmovg_r16_32_64_rm16_32_64_instruction

nasm_movmskps_r32_64_xmm_instruction:
	movmskps edx, xmm2
	movmskps rdx, xmm7

global nasm_movmskps_r32_64_xmm_instruction

nasm_movmskpd_r32_64_xmm_instruction:
	movmskpd edx, xmm2
	movmskpd rdx, xmm7

global nasm_movmskpd_r32_64_xmm_instruction

nasm_sqrtps_xmm_xmmm128_instruction:
	sqrtps xmm13, [r12 + rax]
	sqrtps xmm8, xmm11

global nasm_sqrtps_xmm_xmmm128_instruction

nasm_sqrtss_xmm_xmmm32_instruction:
	sqrtss xmm4, dword [r12 + rax]
	sqrtss xmm2, xmm9

global nasm_sqrtss_xmm_xmmm32_instruction

nasm_sqrtpd_xmm_xmmm128_instruction:
	sqrtpd xmm13, [r12 + rax]
	sqrtpd xmm8, xmm11

global nasm_sqrtpd_xmm_xmmm128_instruction

nasm_sqrtsd_xmm_xmmm64_instruction:
	sqrtsd xmm12, [r12 + rax]
	sqrtsd xmm11, xmm3

global nasm_sqrtsd_xmm_xmmm64_instruction

nasm_rsqrtps_xmm_xmmm128_instruction:
	rsqrtps xmm13, [r12 + rax]
	rsqrtps xmm8, xmm11

global nasm_rsqrtps_xmm_xmmm128_instruction

nasm_rsqrtss_xmm_xmmm32_instruction:
	rsqrtss xmm4, dword [r12 + rax]
	rsqrtss xmm2, xmm9

global nasm_rsqrtss_xmm_xmmm32_instruction

nasm_rcpps_xmm_xmmm128_instruction:
	rcpps xmm13, [r12 + rax]
	rcpps xmm8, xmm11

global nasm_rcpps_xmm_xmmm128_instruction

nasm_rcpss_xmm_xmmm32_instruction:
	rcpss xmm4, dword [r12 + rax]
	rcpss xmm2, xmm9

global nasm_rcpss_xmm_xmmm32_instruction

nasm_andps_xmm_xmmm128_instruction:
	andps xmm13, [r12 + rax]
	andps xmm8, xmm11

global nasm_andps_xmm_xmmm128_instruction

nasm_andpd_xmm_xmmm128_instruction:
	andpd xmm13, [r12 + rax]
	andpd xmm8, xmm11

global nasm_andpd_xmm_xmmm128_instruction

nasm_andnps_xmm_xmmm128_instruction:
	andnps xmm13, [r12 + rax]
	andnps xmm8, xmm11

global nasm_andnps_xmm_xmmm128_instruction

nasm_andnpd_xmm_xmmm128_instruction:
	andnpd xmm13, [r12 + rax]
	andnpd xmm8, xmm11

global nasm_andnpd_xmm_xmmm128_instruction

nasm_orps_xmm_xmmm128_instruction:
	orps xmm13, [r12 + rax]
	orps xmm8, xmm11

global nasm_orps_xmm_xmmm128_instruction

nasm_orpd_xmm_xmmm128_instruction:
	orpd xmm13, [r12 + rax]
	orpd xmm8, xmm11

global nasm_orpd_xmm_xmmm128_instruction

nasm_xorps_xmm_xmmm128_instruction:
	xorps xmm13, [r12 + rax]
	xorps xmm8, xmm11

global nasm_xorps_xmm_xmmm128_instruction

nasm_xorpd_xmm_xmmm128_instruction:
	xorpd xmm13, [r12 + rax]
	xorpd xmm8, xmm11

global nasm_xorpd_xmm_xmmm128_instruction

nasm_addps_xmm_xmmm128_instruction:
	addps xmm13, [r12 + rax]
	addps xmm8, xmm11

global nasm_addps_xmm_xmmm128_instruction

nasm_addss_xmm_xmmm32_instruction:
	addss xmm4, dword [r12 + rax]
	addss xmm2, xmm9

global nasm_addss_xmm_xmmm32_instruction

nasm_addpd_xmm_xmmm128_instruction:
	addpd xmm13, [r12 + rax]
	addpd xmm8, xmm11

global nasm_addpd_xmm_xmmm128_instruction

nasm_addsd_xmm_xmmm64_instruction:
	addsd xmm12, [r12 + rax]
	addsd xmm11, xmm3

global nasm_addsd_xmm_xmmm64_instruction

nasm_mulps_xmm_xmmm128_instruction:
	mulps xmm13, [r12 + rax]
	mulps xmm8, xmm11

global nasm_mulps_xmm_xmmm128_instruction

nasm_mulss_xmm_xmmm32_instruction:
	mulss xmm4, dword [r12 + rax]
	mulss xmm2, xmm9

global nasm_mulss_xmm_xmmm32_instruction

nasm_mulpd_xmm_xmmm128_instruction:
	mulpd xmm13, [r12 + rax]
	mulpd xmm8, xmm11

global nasm_mulpd_xmm_xmmm128_instruction

nasm_mulsd_xmm_xmmm64_instruction:
	mulsd xmm12, [r12 + rax]
	mulsd xmm11, xmm3

global nasm_mulsd_xmm_xmmm64_instruction

nasm_cvtps2pd_xmm_xmmm128_instruction:
	cvtps2pd xmm13, [r12 + rax]
	cvtps2pd xmm8, xmm11

global nasm_cvtps2pd_xmm_xmmm128_instruction

nasm_cvtpd2ps_xmm_xmmm128_instruction:
	cvtpd2ps xmm13, [r12 + rax]
	cvtpd2ps xmm8, xmm11

global nasm_cvtpd2ps_xmm_xmmm128_instruction

nasm_cvtss2sd_xmm_xmmm32_instruction:
	cvtss2sd xmm4, dword [r12 + rax]
	cvtss2sd xmm2, xmm9

global nasm_cvtss2sd_xmm_xmmm32_instruction

nasm_cvtsd2ss_xmm_xmmm64_instruction:
	cvtsd2ss xmm12, [r12 + rax]
	cvtsd2ss xmm11, xmm3

global nasm_cvtsd2ss_xmm_xmmm64_instruction

nasm_cvtdq2ps_xmm_xmmm128_instruction:
	cvtdq2ps xmm13, [r12 + rax]
	cvtdq2ps xmm8, xmm11

global nasm_cvtdq2ps_xmm_xmmm128_instruction

nasm_cvtps2dq_xmm_xmmm128_instruction:
	cvtps2dq xmm13, [r12 + rax]
	cvtps2dq xmm8, xmm11

global nasm_cvtps2dq_xmm_xmmm128_instruction

nasm_cvttps2dq_xmm_xmmm128_instruction:
	cvttps2dq xmm13, [r12 + rax]
	cvttps2dq xmm8, xmm11

global nasm_cvttps2dq_xmm_xmmm128_instruction

nasm_subps_xmm_xmmm128_instruction:
	subps xmm13, [r12 + rax]
	subps xmm8, xmm11

global nasm_subps_xmm_xmmm128_instruction

nasm_subss_xmm_xmmm32_instruction:
	subss xmm4, dword [r12 + rax]
	subss xmm2, xmm9

global nasm_subss_xmm_xmmm32_instruction

nasm_subpd_xmm_xmmm128_instruction:
	subpd xmm13, [r12 + rax]
	subpd xmm8, xmm11

global nasm_subpd_xmm_xmmm128_instruction

nasm_subsd_xmm_xmmm64_instruction:
	subsd xmm12, [r12 + rax]
	subsd xmm11, xmm3

global nasm_subsd_xmm_xmmm64_instruction

nasm_minps_xmm_xmmm128_instruction:
	minps xmm13, [r12 + rax]
	minps xmm8, xmm11

global nasm_minps_xmm_xmmm128_instruction

nasm_minss_xmm_xmmm32_instruction:
	minss xmm4, dword [r12 + rax]
	minss xmm2, xmm9

global nasm_minss_xmm_xmmm32_instruction

nasm_minpd_xmm_xmmm128_instruction:
	minpd xmm13, [r12 + rax]
	minpd xmm8, xmm11

global nasm_minpd_xmm_xmmm128_instruction

nasm_minsd_xmm_xmmm64_instruction:
	minsd xmm12, [r12 + rax]
	minsd xmm11, xmm3

global nasm_minsd_xmm_xmmm64_instruction

nasm_divps_xmm_xmmm128_instruction:
	divps xmm13, [r12 + rax]
	divps xmm8, xmm11

global nasm_divps_xmm_xmmm128_instruction

nasm_divss_xmm_xmmm32_instruction:
	divss xmm4, dword [r12 + rax]
	divss xmm2, xmm9

global nasm_divss_xmm_xmmm32_instruction

nasm_divpd_xmm_xmmm128_instruction:
	divpd xmm13, [r12 + rax]
	divpd xmm8, xmm11

global nasm_divpd_xmm_xmmm128_instruction

nasm_divsd_xmm_xmmm64_instruction:
	divsd xmm12, [r12 + rax]
	divsd xmm11, xmm3

global nasm_divsd_xmm_xmmm64_instruction

nasm_maxps_xmm_xmmm128_instruction:
	maxps xmm13, [r12 + rax]
	maxps xmm8, xmm11

global nasm_maxps_xmm_xmmm128_instruction

nasm_maxss_xmm_xmmm32_instruction:
	maxss xmm4, dword [r12 + rax]
	maxss xmm2, xmm9

global nasm_maxss_xmm_xmmm32_instruction

nasm_maxpd_xmm_xmmm128_instruction:
	maxpd xmm13, [r12 + rax]
	maxpd xmm8, xmm11

global nasm_maxpd_xmm_xmmm128_instruction

nasm_maxsd_xmm_xmmm64_instruction:
	maxsd xmm12, [r12 + rax]
	maxsd xmm11, xmm3

global nasm_maxsd_xmm_xmmm64_instruction

nasm_punpcklbw_xmm_xmmm128_instruction:
	punpcklbw xmm13, [r12 + rax]
	punpcklbw xmm8, xmm11

global nasm_punpcklbw_xmm_xmmm128_instruction

nasm_punpcklwd_xmm_xmmm128_instruction:
	punpcklwd xmm13, [r12 + rax]
	punpcklwd xmm8, xmm11

global nasm_punpcklwd_xmm_xmmm128_instruction

nasm_punpckldq_xmm_xmmm128_instruction:
	punpckldq xmm13, [r12 + rax]
	punpckldq xmm8, xmm11

global nasm_punpckldq_xmm_xmmm128_instruction

nasm_packsswb_xmm_xmmm128_instruction:
	packsswb xmm13, [r12 + rax]
	packsswb xmm8, xmm11

global nasm_packsswb_xmm_xmmm128_instruction

nasm_pcmpgtb_xmm_xmmm128_instruction:
	pcmpgtb xmm13, [r12 + rax]
	pcmpgtb xmm8, xmm11

global nasm_pcmpgtb_xmm_xmmm128_instruction

nasm_pcmpgtw_xmm_xmmm128_instruction:
	pcmpgtw xmm13, [r12 + rax]
	pcmpgtw xmm8, xmm11

global nasm_pcmpgtw_xmm_xmmm128_instruction

nasm_pcmpgtd_xmm_xmmm128_instruction:
	pcmpgtd xmm13, [r12 + rax]
	pcmpgtd xmm8, xmm11

global nasm_pcmpgtd_xmm_xmmm128_instruction

nasm_packuswb_xmm_xmmm128_instruction:
	packuswb xmm13, [r12 + rax]
	packuswb xmm8, xmm11

global nasm_packuswb_xmm_xmmm128_instruction

nasm_punpckhbw_xmm_xmmm128_instruction:
	punpckhbw xmm13, [r12 + rax]
	punpckhbw xmm8, xmm11

global nasm_punpckhbw_xmm_xmmm128_instruction

nasm_punpckhwd_xmm_xmmm128_instruction:
	punpckhwd xmm13, [r12 + rax]
	punpckhwd xmm8, xmm11

global nasm_punpckhwd_xmm_xmmm128_instruction

nasm_punpckhdq_xmm_xmmm128_instruction:
	punpckhdq xmm13, [r12 + rax]
	punpckhdq xmm8, xmm11

global nasm_punpckhdq_xmm_xmmm128_instruction

nasm_packssdw_xmm_xmmm128_instruction:
	packssdw xmm13, [r12 + rax]
	packssdw xmm8, xmm11

global nasm_packssdw_xmm_xmmm128_instruction

nasm_punpcklqdq_xmm_xmmm128_instruction:
	punpcklqdq xmm13, [r12 + rax]
	punpcklqdq xmm8, xmm11

global nasm_punpcklqdq_xmm_xmmm128_instruction

nasm_punpckhqdq_xmm_xmmm128_instruction:
	punpckhqdq xmm13, [r12 + rax]
	punpckhqdq xmm8, xmm11

global nasm_punpckhqdq_xmm_xmmm128_instruction

nasm_movd_mm_rm32_instruction:
	movd mm2, edx
	movd mm6, dword [r11 + rax * 4]

global nasm_movd_mm_rm32_instruction

nasm_movq_mm_r64_instruction:
	movq mm2, rdx

global nasm_movq_mm_r64_instruction

nasm_movq_xmm_r64_instruction:
	movq xmm15, qword [eax + r11d]
	movq xmm3, r14

global nasm_movq_xmm_r64_instruction

nasm_movq_mm_mm_instruction:
	movq mm2, mm3

global nasm_movq_mm_mm_instruction

nasm_movq_mm_m64_instruction:
	movq mm2, qword [r11 + rax]

global nasm_movq_mm_m64_instruction

nasm_movdqa_xmm_xmmm128_instruction:
	movdqa xmm13, [r12 + rax]
	movdqa xmm8, xmm11

global nasm_movdqa_xmm_xmmm128_instruction

nasm_movdqu_xmm_xmmm128_instruction:
	movdqu xmm13, [r12 + rax]
	movdqu xmm8, xmm11

global nasm_movdqu_xmm_xmmm128_instruction

nasm_pshuflw_xmm_xmmm128_imm8_instruction:
	pshuflw xmm4, [r12 + rax], 4
	pshuflw xmm9, xmm8, 4

global nasm_pshuflw_xmm_xmmm128_imm8_instruction

nasm_pshufhw_xmm_xmmm128_imm8_instruction:
	pshufhw xmm4, [r12 + rax], 4
	pshufhw xmm9, xmm8, 4

global nasm_pshufhw_xmm_xmmm128_imm8_instruction

nasm_pshufd_xmm_xmmm128_imm8_instruction:
	pshufd xmm4, [r12 + rax], 4
	pshufd xmm9, xmm8, 4

global nasm_pshufd_xmm_xmmm128_imm8_instruction

nasm_psrlw_mm_imm8_instruction_by_number:
	psrlw mm2, 0x11

global nasm_psrlw_mm_imm8_instruction_by_number

nasm_psrlw_xmm_imm8_instruction_by_number:
	psrlw xmm2, 17

global nasm_psrlw_xmm_imm8_instruction_by_number

nasm_psraw_mm_imm8_instruction_by_number:
	psraw mm2, 0x11

global nasm_psraw_mm_imm8_instruction_by_number

nasm_psraw_xmm_imm8_instruction_by_number:
	psraw xmm2, 17

global nasm_psraw_xmm_imm8_instruction_by_number

nasm_psllw_mm_imm8_instruction_by_number:
	psllw mm2, 0x11

global nasm_psllw_mm_imm8_instruction_by_number

nasm_psllw_xmm_imm8_instruction_by_number:
	psllw xmm2, 17

global nasm_psllw_xmm_imm8_instruction_by_number

nasm_psrld_mm_imm8_instruction_by_number:
	psrld mm2, 0x11

global nasm_psrld_mm_imm8_instruction_by_number

nasm_psrld_xmm_imm8_instruction_by_number:
	psrld xmm2, 17

global nasm_psrld_xmm_imm8_instruction_by_number

nasm_psrad_mm_imm8_instruction_by_number:
	psrad mm2, 0x11

global nasm_psrad_mm_imm8_instruction_by_number

nasm_psrad_xmm_imm8_instruction_by_number:
	psrad xmm2, 17

global nasm_psrad_xmm_imm8_instruction_by_number

nasm_pslld_mm_imm8_instruction_by_number:
	pslld mm2, 0x11

global nasm_pslld_mm_imm8_instruction_by_number

nasm_pslld_xmm_imm8_instruction_by_number:
	pslld xmm2, 17

global nasm_pslld_xmm_imm8_instruction_by_number

nasm_psrlq_mm_imm8_instruction_by_number:
	psrlq mm2, 0x11

global nasm_psrlq_mm_imm8_instruction_by_number

nasm_psrlq_xmm_imm8_instruction_by_number:
	psrlq xmm2, 17

global nasm_psrlq_xmm_imm8_instruction_by_number

nasm_psrldq_xmm_imm8_instruction_by_number:
	psrldq xmm2, 17

global nasm_psrldq_xmm_imm8_instruction_by_number

nasm_psllq_mm_imm8_instruction_by_number:
	psllq mm2, 0x11

global nasm_psllq_mm_imm8_instruction_by_number

nasm_psllq_xmm_imm8_instruction_by_number:
	psllq xmm2, 17

global nasm_psllq_xmm_imm8_instruction_by_number

nasm_pslldq_xmm_imm8_instruction_by_number:
	pslldq xmm2, 17

global nasm_pslldq_xmm_imm8_instruction_by_number

nasm_pcmpeqb_xmm_xmmm128_instruction:
	pcmpeqb xmm13, [r12 + rax]
	pcmpeqb xmm8, xmm11

global nasm_pcmpeqb_xmm_xmmm128_instruction

nasm_pcmpeqw_xmm_xmmm128_instruction:
	pcmpeqw xmm13, [r12 + rax]
	pcmpeqw xmm8, xmm11

global nasm_pcmpeqw_xmm_xmmm128_instruction

nasm_pcmpeqd_xmm_xmmm128_instruction:
	pcmpeqd xmm13, [r12 + rax]
	pcmpeqd xmm8, xmm11

global nasm_pcmpeqd_xmm_xmmm128_instruction

nasm_emms_no_operands_instruction:
	emms 

global nasm_emms_no_operands_instruction

nasm_vmread_rm64_r64_instruction:
	vmread rdx, rax
	vmread qword[ebx * 4], rdx

global nasm_vmread_rm64_r64_instruction

nasm_vmwrite_r64_rm64_instruction:
	vmwrite rax, rdx
	vmwrite rax, qword [rdx + rdx * 8]

global nasm_vmwrite_r64_rm64_instruction

nasm_haddpd_xmm_xmmm128_instruction:
	haddpd xmm13, [r12 + rax]
	haddpd xmm8, xmm11

global nasm_haddpd_xmm_xmmm128_instruction

nasm_haddps_xmm_xmmm128_instruction:
	haddps xmm13, [r12 + rax]
	haddps xmm8, xmm11

global nasm_haddps_xmm_xmmm128_instruction

nasm_hsubpd_xmm_xmmm128_instruction:
	hsubpd xmm13, [r12 + rax]
	hsubpd xmm8, xmm11

global nasm_hsubpd_xmm_xmmm128_instruction

nasm_hsubps_xmm_xmmm128_instruction:
	hsubps xmm13, [r12 + rax]
	hsubps xmm8, xmm11

global nasm_hsubps_xmm_xmmm128_instruction

nasm_movd_rm32_mm_instruction:
	movd edx, mm5
	movd dword[r11 + rax * 4], mm5

global nasm_movd_rm32_mm_instruction

nasm_movq_rm64_mm_instruction:
	movq rdx, mm5
	movq qword[ebx * 4], mm5

global nasm_movq_rm64_mm_instruction

nasm_movd_rm32_xmm_instruction:
	movd edx, xmm5
	movd dword[ebx * 4], xmm5

global nasm_movd_rm32_xmm_instruction

nasm_movq_xmm_xmmm64_instruction:
	movq xmm12, [r12 + rax]
	movq xmm11, xmm3

global nasm_movq_xmm_xmmm64_instruction

nasm_movq_mmm64_mm_instruction:
	movq qword [r11 + rax], mm6
	movq mm2, mm6

global nasm_movq_mmm64_mm_instruction

nasm_movdqa_xmmm128_xmm_instruction:
	movdqa xmm2, xmm6
	movdqa oword [rbp + rcx * 2], xmm6
	movdqa oword [r10 + rbp + 0x80], xmm6
	movdqa oword [rbp + 0x8012333], xmm6
	movdqa oword [rbp + 0x80], xmm6
	movdqa oword [rbp + 0xffffffff], xmm6
	movdqa oword [rbp + 0xff], xmm6

global nasm_movdqa_xmmm128_xmm_instruction

nasm_movdqu_xmmm128_xmm_instruction:
	movdqu xmm2, xmm6
	movdqu oword [rbp + rcx * 2], xmm6
	movdqu oword [r10 + rbp + 0x80], xmm6
	movdqu oword [rbp + 0x8012333], xmm6
	movdqu oword [rbp + 0x80], xmm6
	movdqu oword [rbp + 0xffffffff], xmm6
	movdqu oword [rbp + 0xff], xmm6

global nasm_movdqu_xmmm128_xmm_instruction

nasm_push_fs_instruction:
	push fs

global nasm_push_fs_instruction

nasm_pop_fs_instruction:
	pop fs

global nasm_pop_fs_instruction

nasm_cpuid_no_operands_instruction:
	cpuid 

global nasm_cpuid_no_operands_instruction

nasm_bt_rm16_32_64_r16_32_64_instruction:
	bt dx, ax
	bt edx, eax
	bt rdx, rax
	bt word[ebx * 4], dx
	bt dword[ebx * 4], edx
	bt qword[ebx * 4], rdx

global nasm_bt_rm16_32_64_r16_32_64_instruction

nasm_shld_rm16_32_64_r16_32_64_imm8_instruction:
	shld dx, ax, 0x11
	shld edx, eax, 0x11
	shld rdx, rax, 0x11
	shld word[ebx * 4], dx, 0x11
	shld dword[ebx * 4], edx, 0x11
	shld qword[ebx * 4], rdx, 0x11

global nasm_shld_rm16_32_64_r16_32_64_imm8_instruction

nasm_shld_rm16_32_64_r16_32_64_cl_instruction:
	shld dx, ax, cl
	shld edx, eax, cl
	shld rdx, rax, cl
	shld word[ebx * 4], dx, cl
	shld dword[ebx * 4], edx, cl
	shld qword[ebx * 4], rdx, cl

global nasm_shld_rm16_32_64_r16_32_64_cl_instruction

nasm_push_gs_instruction:
	push gs

global nasm_push_gs_instruction

nasm_pop_gs_instruction:
	pop gs

global nasm_pop_gs_instruction

nasm_rsm_no_operands_instruction:
	rsm 

global nasm_rsm_no_operands_instruction

nasm_bts_rm16_32_64_r16_32_64_instruction:
	bts dx, ax
	bts edx, eax
	bts rdx, rax
	bts word[ebx * 4], dx
	bts dword[ebx * 4], edx
	bts qword[ebx * 4], rdx

global nasm_bts_rm16_32_64_r16_32_64_instruction

nasm_shrd_rm16_32_64_r16_32_64_imm8_instruction:
	shrd dx, ax, 0x11
	shrd edx, eax, 0x11
	shrd rdx, rax, 0x11
	shrd word[ebx * 4], dx, 0x11
	shrd dword[ebx * 4], edx, 0x11
	shrd qword[ebx * 4], rdx, 0x11

global nasm_shrd_rm16_32_64_r16_32_64_imm8_instruction

nasm_shrd_rm16_32_64_r16_32_64_cl_instruction:
	shrd dx, ax, cl
	shrd edx, eax, cl
	shrd rdx, rax, cl
	shrd word[ebx * 4], dx, cl
	shrd dword[ebx * 4], edx, cl
	shrd qword[ebx * 4], rdx, cl

global nasm_shrd_rm16_32_64_r16_32_64_cl_instruction

nasm_fxsave_m_instruction_by_number:
	fxsave [0x11223344]
	fxsave [rbx + r12 * 4 ]

global nasm_fxsave_m_instruction_by_number

nasm_fxrstor_m_instruction_by_number:
	fxrstor [0x11223344]
	fxrstor [rbx + r12 * 4 ]

global nasm_fxrstor_m_instruction_by_number

nasm_ldmxcsr_m32_instruction_by_number:
	ldmxcsr dword [r11 + rax]

global nasm_ldmxcsr_m32_instruction_by_number

nasm_stmxcsr_m32_instruction_by_number:
	stmxcsr dword [r11 + rax]

global nasm_stmxcsr_m32_instruction_by_number

nasm_xsave_m_instruction_by_number:
	xsave [0x11223344]
	xsave [rbx + r12 * 4 ]

global nasm_xsave_m_instruction_by_number

nasm_lfence_no_operands_instruction:
	lfence 

global nasm_lfence_no_operands_instruction

nasm_xrstor_m_instruction_by_number:
	xrstor [0x11223344]
	xrstor [rbx + r12 * 4 ]

global nasm_xrstor_m_instruction_by_number

nasm_mfence_no_operands_instruction:
	mfence 

global nasm_mfence_no_operands_instruction

nasm_sfence_no_operands_instruction:
	sfence 

global nasm_sfence_no_operands_instruction

nasm_clflush_m8_instruction_by_number:
	clflush [r11 + rax]

global nasm_clflush_m8_instruction_by_number

nasm_imul_r16_32_64_rm16_32_64_instruction:
	imul cx, word [r11 + rbx]
	imul ebx, dword [r11 + rbx]
	imul rax, qword [r12]

global nasm_imul_r16_32_64_rm16_32_64_instruction

nasm_cmpxchg_rm8_r8_instruction:
	cmpxchg dl, ah
	cmpxchg r9b, al
	cmpxchg al, r11b
	cmpxchg byte [rdx + rdx * 8 + 0x1122], al
	cmpxchg byte [rdx + rdx * 8 + 0x1122], spl
	cmpxchg byte [r11 + rdx * 8 + 0x1122], dil
	cmpxchg byte [edx + r11d * 8 + 0x1122], r8b
	cmpxchg byte[rdx + rdx * 8], al
	cmpxchg byte[rdx + rdx * 8], spl
	cmpxchg byte[r11 + rdx * 8], dil
	cmpxchg byte[edx + r11d * 8], r8b
	cmpxchg byte [r11d], bl
	cmpxchg byte [rdx], bpl
	cmpxchg byte [r11d * 4], bl
	cmpxchg byte [rdx * 4], bpl

global nasm_cmpxchg_rm8_r8_instruction

nasm_cmpxchg_rm16_32_64_r16_32_64_instruction:
	cmpxchg dx, ax
	cmpxchg edx, eax
	cmpxchg rdx, rax
	cmpxchg word[ebx * 4], dx
	cmpxchg dword[ebx * 4], edx
	cmpxchg qword[ebx * 4], rdx

global nasm_cmpxchg_rm16_32_64_r16_32_64_instruction

nasm_lss_r16_32_64_m_instruction:
	lss dx, [r14d]
	lss edx, [r14d]
	lss rdx, [r14d]

global nasm_lss_r16_32_64_m_instruction

nasm_btr_rm16_32_64_r16_32_64_instruction:
	btr dx, ax
	btr edx, eax
	btr rdx, rax
	btr word[ebx * 4], dx
	btr dword[ebx * 4], edx
	btr qword[ebx * 4], rdx

global nasm_btr_rm16_32_64_r16_32_64_instruction

nasm_lfs_r16_32_64_m_instruction:
	lfs dx, [r14d]
	lfs edx, [r14d]
	lfs rdx, [r14d]

global nasm_lfs_r16_32_64_m_instruction

nasm_lgs_r16_32_64_m_instruction:
	lgs dx, [r14d]
	lgs edx, [r14d]
	lgs rdx, [r14d]

global nasm_lgs_r16_32_64_m_instruction

nasm_movzx_r16_32_64_rm8_instruction:
	movzx dx, byte [eax]
	movzx edx, byte [r11 + rbx]
	movzx rdx, byte [r8d]
	movzx dx, al
	movzx edx, al
	movzx rdx, al

global nasm_movzx_r16_32_64_rm8_instruction

nasm_movzx_r16_32_rm16_instruction:
	movzx ebx, dx
	movzx edx, cl

global nasm_movzx_r16_32_rm16_instruction

nasm_popcnt_r16_32_64_rm16_32_64_instruction:
	popcnt cx, word [r11 + rbx]
	popcnt ebx, dword [r11 + rbx]
	popcnt rax, qword [r12]

global nasm_popcnt_r16_32_64_rm16_32_64_instruction

nasm_bt_rm16_32_64_imm8_instruction_by_number:
	bt dx, 0x11
	bt edx, 0x11
	bt rdx, 0x11
	bt word [ebx * 4], 0x11
	bt dword [ebx * 4], 0x11
	bt qword [ebx * 4], 0x11

global nasm_bt_rm16_32_64_imm8_instruction_by_number

nasm_bts_rm16_32_64_imm8_instruction_by_number:
	bts dx, 0x11
	bts edx, 0x11
	bts rdx, 0x11
	bts word [ebx * 4], 0x11
	bts dword [ebx * 4], 0x11
	bts qword [ebx * 4], 0x11

global nasm_bts_rm16_32_64_imm8_instruction_by_number

nasm_btr_rm16_32_64_imm8_instruction_by_number:
	btr dx, 0x11
	btr edx, 0x11
	btr rdx, 0x11
	btr word [ebx * 4], 0x11
	btr dword [ebx * 4], 0x11
	btr qword [ebx * 4], 0x11

global nasm_btr_rm16_32_64_imm8_instruction_by_number

nasm_btc_rm16_32_64_imm8_instruction_by_number:
	btc dx, 0x11
	btc edx, 0x11
	btc rdx, 0x11
	btc word [ebx * 4], 0x11
	btc dword [ebx * 4], 0x11
	btc qword [ebx * 4], 0x11

global nasm_btc_rm16_32_64_imm8_instruction_by_number

nasm_btc_rm16_32_64_r16_32_64_instruction:
	btc dx, ax
	btc edx, eax
	btc rdx, rax
	btc word[ebx * 4], dx
	btc dword[ebx * 4], edx
	btc qword[ebx * 4], rdx

global nasm_btc_rm16_32_64_r16_32_64_instruction

nasm_bsf_r16_32_64_rm16_32_64_instruction:
	bsf cx, word [r11 + rbx]
	bsf ebx, dword [r11 + rbx]
	bsf rax, qword [r12]

global nasm_bsf_r16_32_64_rm16_32_64_instruction

nasm_bsr_r16_32_64_rm16_32_64_instruction:
	bsr cx, word [r11 + rbx]
	bsr ebx, dword [r11 + rbx]
	bsr rax, qword [r12]

global nasm_bsr_r16_32_64_rm16_32_64_instruction

nasm_movsx_r16_32_64_rm8_instruction:
	movsx dx, byte [eax]
	movsx edx, byte [r11 + rbx]
	movsx rdx, byte [r8d]
	movsx dx, al
	movsx edx, al
	movsx rdx, al

global nasm_movsx_r16_32_64_rm8_instruction

nasm_movsx_r16_32_rm16_instruction:
	movsx ebx, dx
	movsx edx, cl

global nasm_movsx_r16_32_rm16_instruction

nasm_xadd_rm8_r8_instruction:
	xadd dl, ah
	xadd r9b, al
	xadd al, r11b
	xadd byte [rdx + rdx * 8 + 0x1122], al
	xadd byte [rdx + rdx * 8 + 0x1122], spl
	xadd byte [r11 + rdx * 8 + 0x1122], dil
	xadd byte [edx + r11d * 8 + 0x1122], r8b
	xadd byte[rdx + rdx * 8], al
	xadd byte[rdx + rdx * 8], spl
	xadd byte[r11 + rdx * 8], dil
	xadd byte[edx + r11d * 8], r8b
	xadd byte [r11d], bl
	xadd byte [rdx], bpl
	xadd byte [r11d * 4], bl
	xadd byte [rdx * 4], bpl

global nasm_xadd_rm8_r8_instruction

nasm_xadd_rm16_32_64_r16_32_64_instruction:
	xadd dx, ax
	xadd edx, eax
	xadd rdx, rax
	xadd word[ebx * 4], dx
	xadd dword[ebx * 4], edx
	xadd qword[ebx * 4], rdx

global nasm_xadd_rm16_32_64_r16_32_64_instruction

nasm_cmpps_xmm_xmmm128_imm8_instruction:
	cmpps xmm4, [r12 + rax], 4
	cmpps xmm9, xmm8, 4

global nasm_cmpps_xmm_xmmm128_imm8_instruction

nasm_cmpss_xmm_xmmm32_imm8_instruction:
	cmpss xmm4, dword [r12 + rax], 4
	cmpss xmm2, xmm3, 4

global nasm_cmpss_xmm_xmmm32_imm8_instruction

nasm_cmppd_xmm_xmmm128_imm8_instruction:
	cmppd xmm4, [r12 + rax], 4
	cmppd xmm9, xmm8, 4

global nasm_cmppd_xmm_xmmm128_imm8_instruction

nasm_cmpsd_xmm_xmmm64_imm8_instruction:
	cmpsd xmm14, [r12 + rax], 4
	cmpsd xmm2, xmm11, 4

global nasm_cmpsd_xmm_xmmm64_imm8_instruction

nasm_movnti_m32_64_r32_64_instruction:
	movnti dword [r11 + rbx * 8 + 0x818181 ], r13d
	movnti qword [r11 + rbx * 4 + 0x11 ], rcx

global nasm_movnti_m32_64_r32_64_instruction

nasm_pinsrw_mm_r32_imm8_instruction:
	pinsrw mm2, edx, 0x11

global nasm_pinsrw_mm_r32_imm8_instruction

nasm_pinsrw_mm_m16_imm8_instruction:
	pinsrw mm2, word [r11 + rax], 0x11

global nasm_pinsrw_mm_m16_imm8_instruction

nasm_pinsrw_xmm_r32_imm8_instruction:
	pinsrw xmm15, ecx, 4
	pinsrw xmm3, r13d, 4

global nasm_pinsrw_xmm_r32_imm8_instruction

nasm_pinsrw_xmm_m16_imm8_instruction:
	pinsrw xmm2, word [0x11223344], 0x17

global nasm_pinsrw_xmm_m16_imm8_instruction

nasm_pextrw_r32_mm_imm8_instruction:
	pextrw edx, mm6, 0x11

global nasm_pextrw_r32_mm_imm8_instruction

nasm_pextrw_r32_64_xmm_imm8_instruction:
	pextrw edx, xmm2, 12
	pextrw rdx, xmm7, 12

global nasm_pextrw_r32_64_xmm_imm8_instruction

nasm_shufps_xmm_xmmm128_imm8_instruction:
	shufps xmm4, [r12 + rax], 4
	shufps xmm9, xmm8, 4

global nasm_shufps_xmm_xmmm128_imm8_instruction

nasm_shufpd_xmm_xmmm128_imm8_instruction:
	shufpd xmm4, [r12 + rax], 4
	shufpd xmm9, xmm8, 4

global nasm_shufpd_xmm_xmmm128_imm8_instruction

nasm_cmpxchg16b_m128_instruction_by_number:
	cmpxchg16b [0x88888888]
	cmpxchg16b [r11 + rdx * 8]
	cmpxchg16b [ecx + r13d * 8]

global nasm_cmpxchg16b_m128_instruction_by_number

nasm_bswap_r32_instruction_by_register:
	bswap eax
	bswap ecx
	bswap edx
	bswap ebx
	bswap esp
	bswap ebp
	bswap esi
	bswap edi

global nasm_bswap_r32_instruction_by_register

nasm_addsubpd_xmm_xmmm128_instruction:
	addsubpd xmm13, [r12 + rax]
	addsubpd xmm8, xmm11

global nasm_addsubpd_xmm_xmmm128_instruction

nasm_addsubps_xmm_xmmm128_instruction:
	addsubps xmm13, [r12 + rax]
	addsubps xmm8, xmm11

global nasm_addsubps_xmm_xmmm128_instruction

nasm_psrlw_xmm_xmmm128_instruction:
	psrlw xmm13, [r12 + rax]
	psrlw xmm8, xmm11

global nasm_psrlw_xmm_xmmm128_instruction

nasm_psrld_xmm_xmmm128_instruction:
	psrld xmm13, [r12 + rax]
	psrld xmm8, xmm11

global nasm_psrld_xmm_xmmm128_instruction

nasm_psrlq_xmm_xmmm128_instruction:
	psrlq xmm13, [r12 + rax]
	psrlq xmm8, xmm11

global nasm_psrlq_xmm_xmmm128_instruction

nasm_paddq_xmm_xmmm128_instruction:
	paddq xmm13, [r12 + rax]
	paddq xmm8, xmm11

global nasm_paddq_xmm_xmmm128_instruction

nasm_pmullw_xmm_xmmm128_instruction:
	pmullw xmm13, [r12 + rax]
	pmullw xmm8, xmm11

global nasm_pmullw_xmm_xmmm128_instruction

nasm_movq_m64_xmm_instruction:
	movq qword [r11 + rax], xmm2

global nasm_movq_m64_xmm_instruction

nasm_movdq2q_mm_xmm_instruction:
	movdq2q mm2, xmm3

global nasm_movdq2q_mm_xmm_instruction

nasm_pmovmskb_r32_mm_instruction:
	pmovmskb edx, mm6

global nasm_pmovmskb_r32_mm_instruction

nasm_pmovmskb_r32_xmm_instruction:
	pmovmskb edx, xmm2

global nasm_pmovmskb_r32_xmm_instruction

nasm_psubusb_xmm_xmmm128_instruction:
	psubusb xmm13, [r12 + rax]
	psubusb xmm8, xmm11

global nasm_psubusb_xmm_xmmm128_instruction

nasm_psubusw_xmm_xmmm128_instruction:
	psubusw xmm13, [r12 + rax]
	psubusw xmm8, xmm11

global nasm_psubusw_xmm_xmmm128_instruction

nasm_pminub_xmm_xmmm128_instruction:
	pminub xmm13, [r12 + rax]
	pminub xmm8, xmm11

global nasm_pminub_xmm_xmmm128_instruction

nasm_pand_xmm_xmmm128_instruction:
	pand xmm13, [r12 + rax]
	pand xmm8, xmm11

global nasm_pand_xmm_xmmm128_instruction

nasm_paddusb_xmm_xmmm128_instruction:
	paddusb xmm13, [r12 + rax]
	paddusb xmm8, xmm11

global nasm_paddusb_xmm_xmmm128_instruction

nasm_paddusw_xmm_xmmm128_instruction:
	paddusw xmm13, [r12 + rax]
	paddusw xmm8, xmm11

global nasm_paddusw_xmm_xmmm128_instruction

nasm_pmaxub_xmm_xmmm128_instruction:
	pmaxub xmm13, [r12 + rax]
	pmaxub xmm8, xmm11

global nasm_pmaxub_xmm_xmmm128_instruction

nasm_pandn_xmm_xmmm128_instruction:
	pandn xmm13, [r12 + rax]
	pandn xmm8, xmm11

global nasm_pandn_xmm_xmmm128_instruction

nasm_pavgb_xmm_xmmm128_instruction:
	pavgb xmm13, [r12 + rax]
	pavgb xmm8, xmm11

global nasm_pavgb_xmm_xmmm128_instruction

nasm_psraw_xmm_xmmm128_instruction:
	psraw xmm13, [r12 + rax]
	psraw xmm8, xmm11

global nasm_psraw_xmm_xmmm128_instruction

nasm_psrad_xmm_xmmm128_instruction:
	psrad xmm13, [r12 + rax]
	psrad xmm8, xmm11

global nasm_psrad_xmm_xmmm128_instruction

nasm_pavgw_xmm_xmmm128_instruction:
	pavgw xmm13, [r12 + rax]
	pavgw xmm8, xmm11

global nasm_pavgw_xmm_xmmm128_instruction

nasm_pmulhuw_xmm_xmmm128_instruction:
	pmulhuw xmm13, [r12 + rax]
	pmulhuw xmm8, xmm11

global nasm_pmulhuw_xmm_xmmm128_instruction

nasm_pmulhw_xmm_xmmm128_instruction:
	pmulhw xmm13, [r12 + rax]
	pmulhw xmm8, xmm11

global nasm_pmulhw_xmm_xmmm128_instruction

nasm_cvtpd2dq_xmm_xmmm128_instruction:
	cvtpd2dq xmm13, [r12 + rax]
	cvtpd2dq xmm8, xmm11

global nasm_cvtpd2dq_xmm_xmmm128_instruction

nasm_cvttpd2dq_xmm_xmmm128_instruction:
	cvttpd2dq xmm13, [r12 + rax]
	cvttpd2dq xmm8, xmm11

global nasm_cvttpd2dq_xmm_xmmm128_instruction

nasm_cvtdq2pd_xmm_xmmm128_instruction:
	cvtdq2pd xmm13, [r12 + rax]
	cvtdq2pd xmm8, xmm11

global nasm_cvtdq2pd_xmm_xmmm128_instruction

nasm_movntq_m64_mm_instruction:
	movntq qword [r11 + rax], mm2

global nasm_movntq_m64_mm_instruction

nasm_movntdq_m128_xmm_instruction:
	movntdq gs:[0x8888888], xmm2
	movntdq oword [r11 + rdx * 8], xmm8

global nasm_movntdq_m128_xmm_instruction

nasm_psubsb_xmm_xmmm128_instruction:
	psubsb xmm13, [r12 + rax]
	psubsb xmm8, xmm11

global nasm_psubsb_xmm_xmmm128_instruction

nasm_psubsw_xmm_xmmm128_instruction:
	psubsw xmm13, [r12 + rax]
	psubsw xmm8, xmm11

global nasm_psubsw_xmm_xmmm128_instruction

nasm_pminsw_xmm_xmmm128_instruction:
	pminsw xmm13, [r12 + rax]
	pminsw xmm8, xmm11

global nasm_pminsw_xmm_xmmm128_instruction

nasm_por_xmm_xmmm128_instruction:
	por xmm13, [r12 + rax]
	por xmm8, xmm11

global nasm_por_xmm_xmmm128_instruction

nasm_paddsb_xmm_xmmm128_instruction:
	paddsb xmm13, [r12 + rax]
	paddsb xmm8, xmm11

global nasm_paddsb_xmm_xmmm128_instruction

nasm_paddsw_xmm_xmmm128_instruction:
	paddsw xmm13, [r12 + rax]
	paddsw xmm8, xmm11

global nasm_paddsw_xmm_xmmm128_instruction

nasm_pmaxsw_xmm_xmmm128_instruction:
	pmaxsw xmm13, [r12 + rax]
	pmaxsw xmm8, xmm11

global nasm_pmaxsw_xmm_xmmm128_instruction

nasm_pxor_xmm_xmmm128_instruction:
	pxor xmm13, [r12 + rax]
	pxor xmm8, xmm11

global nasm_pxor_xmm_xmmm128_instruction

nasm_lddqu_xmm_m128_instruction:
	lddqu xmm2, oword [rbp + r13 + 0x17]

global nasm_lddqu_xmm_m128_instruction

nasm_psllw_xmm_xmmm128_instruction:
	psllw xmm13, [r12 + rax]
	psllw xmm8, xmm11

global nasm_psllw_xmm_xmmm128_instruction

nasm_pslld_xmm_xmmm128_instruction:
	pslld xmm13, [r12 + rax]
	pslld xmm8, xmm11

global nasm_pslld_xmm_xmmm128_instruction

nasm_psllq_xmm_xmmm128_instruction:
	psllq xmm13, [r12 + rax]
	psllq xmm8, xmm11

global nasm_psllq_xmm_xmmm128_instruction

nasm_pmuludq_xmm_xmmm128_instruction:
	pmuludq xmm13, [r12 + rax]
	pmuludq xmm8, xmm11

global nasm_pmuludq_xmm_xmmm128_instruction

nasm_pmaddwd_xmm_xmmm128_instruction:
	pmaddwd xmm13, [r12 + rax]
	pmaddwd xmm8, xmm11

global nasm_pmaddwd_xmm_xmmm128_instruction

nasm_psadbw_xmm_xmmm128_instruction:
	psadbw xmm13, [r12 + rax]
	psadbw xmm8, xmm11

global nasm_psadbw_xmm_xmmm128_instruction

nasm_maskmovq_mm_mm_instruction:
	maskmovq mm2, mm3

global nasm_maskmovq_mm_mm_instruction

nasm_maskmovdqu_xmm_xmm_instruction:
	maskmovdqu xmm4, xmm12
	maskmovdqu xmm12, xmm4

global nasm_maskmovdqu_xmm_xmm_instruction

nasm_psubb_xmm_xmmm128_instruction:
	psubb xmm13, [r12 + rax]
	psubb xmm8, xmm11

global nasm_psubb_xmm_xmmm128_instruction

nasm_psubw_xmm_xmmm128_instruction:
	psubw xmm13, [r12 + rax]
	psubw xmm8, xmm11

global nasm_psubw_xmm_xmmm128_instruction

nasm_psubd_xmm_xmmm128_instruction:
	psubd xmm13, [r12 + rax]
	psubd xmm8, xmm11

global nasm_psubd_xmm_xmmm128_instruction

nasm_psubq_xmm_xmmm128_instruction:
	psubq xmm13, [r12 + rax]
	psubq xmm8, xmm11

global nasm_psubq_xmm_xmmm128_instruction

nasm_paddb_xmm_xmmm128_instruction:
	paddb xmm13, [r12 + rax]
	paddb xmm8, xmm11

global nasm_paddb_xmm_xmmm128_instruction

nasm_paddw_xmm_xmmm128_instruction:
	paddw xmm13, [r12 + rax]
	paddw xmm8, xmm11

global nasm_paddw_xmm_xmmm128_instruction

nasm_paddd_xmm_xmmm128_instruction:
	paddd xmm13, [r12 + rax]
	paddd xmm8, xmm11

global nasm_paddd_xmm_xmmm128_instruction

