#include <stdint.h>

#include "AddressingModes.h"
#include "Decoder.h"
#include "Instructions.h"
#include "Processor6502.h"

// uint16_t ((*modes[])(Processor6502*)) = 
decode modes[] =
{
	resolve_imp, resolve_ix, NULL, NULL, NULL, resolve_z, resolve_z, NULL, resolve_imp, resolve_ime, resolve_acc, NULL, NULL, resolve_a, resolve_a, NULL,
	resolve_r, resolve_iy, NULL, NULL, NULL, resolve_zx, resolve_zx, NULL, resolve_imp, resolve_ay, NULL, NULL, NULL, resolve_ax, resolve_ax, NULL,
	resolve_a, resolve_ix, NULL, NULL, resolve_z, resolve_z, resolve_z, NULL, resolve_imp, resolve_ime, resolve_acc, NULL, resolve_a, resolve_a, resolve_a, NULL,
	resolve_r, resolve_iy, NULL, NULL, NULL, resolve_zx, resolve_zx, NULL, resolve_imp, resolve_ay, NULL, NULL, NULL, resolve_ax, resolve_ax, NULL,
	resolve_imp, resolve_ix, NULL, NULL, NULL, resolve_z, resolve_z, NULL, resolve_imp, resolve_ime, resolve_acc, NULL, resolve_a, resolve_a, resolve_a, NULL,
	resolve_r, resolve_iy, NULL, NULL, NULL, resolve_zx, resolve_zx, NULL, resolve_imp, resolve_ay, NULL, NULL, NULL, resolve_ax, resolve_ax, NULL,
	resolve_imp, resolve_ix, NULL, NULL, NULL, resolve_z, resolve_z, NULL, resolve_imp, resolve_ime, resolve_acc, NULL, resolve_i, resolve_a, resolve_a, NULL,
	resolve_r, resolve_iy, NULL, NULL, NULL, resolve_zx, resolve_zx, NULL, resolve_imp, resolve_ay, NULL, NULL, NULL, resolve_ax, resolve_ax, NULL,
	NULL, resolve_ix, NULL, NULL, resolve_z, resolve_z, resolve_z, NULL, resolve_imp, NULL, resolve_imp, NULL, resolve_a, resolve_a, resolve_a, NULL,
	resolve_r, resolve_iy, NULL, NULL, resolve_zx, resolve_zx, resolve_zy, NULL, resolve_imp, resolve_ay, resolve_imp, NULL, NULL, resolve_ax, NULL, NULL,
	resolve_ime, resolve_ix, resolve_ime, NULL, resolve_z, resolve_z, resolve_z, NULL, resolve_imp, resolve_ime, resolve_imp, NULL, resolve_a, resolve_a, resolve_a, NULL,
	resolve_r, resolve_iy, NULL, NULL, resolve_zx, resolve_zx, resolve_zy, NULL, resolve_imp, resolve_ay, resolve_imp, NULL, resolve_ax, resolve_ax, resolve_ay, NULL,
	resolve_ime, resolve_ix, NULL, NULL, resolve_z, resolve_z, resolve_z, NULL, resolve_imp, resolve_ime, resolve_imp, NULL, resolve_a, resolve_a, resolve_a, NULL,
	resolve_r, resolve_iy, NULL, NULL, NULL, resolve_zx, resolve_zx, NULL, resolve_imp, resolve_ay, NULL, NULL, NULL, resolve_ax, resolve_ax, NULL,
	resolve_ime, resolve_ix, NULL, NULL, resolve_z, resolve_z, resolve_z, NULL, resolve_imp, resolve_ime, resolve_imp, NULL, resolve_a, resolve_a, resolve_a, NULL,
	resolve_r, resolve_iy, NULL, NULL, NULL, resolve_zx, resolve_zx, NULL, resolve_imp, resolve_ay, NULL, NULL, NULL, resolve_ax, resolve_ax, NULL
};

// void (*instructions[])(Processor6502*, uint16_t) =
operate instructions[] =
{
	brk, ora, NULL, NULL, NULL, ora, asl, NULL, php, ora, aslA, NULL, NULL, ora, asl, NULL,
	bpl, ora, NULL, NULL, NULL, ora, asl, NULL, clc, ora, NULL, NULL, NULL, ora, asl, NULL,
	jsr, bAnd, NULL, NULL, bit, bAnd, rol, NULL, plp, bAnd, rolA, NULL, bit, bAnd, rol, NULL,
	bmi, bAnd, NULL, NULL, NULL, bAnd, rol, NULL, sec, bAnd, NULL, NULL, NULL, bAnd, rol, NULL,
	rti, eor, NULL, NULL, NULL, eor, lsr, NULL, pha, eor, lsrA, NULL, jmp, eor, lsr, NULL,
	bvc, eor, NULL, NULL, NULL, eor, lsr, NULL, cli, eor, NULL, NULL, NULL, eor, lsr, NULL,
	rts, adc, NULL, NULL, NULL, adc, ror, NULL, pla, adc, rorA, NULL, jmp, adc, ror, NULL,
	bvs, adc, NULL, NULL, NULL, adc, ror, NULL, sei, adc, NULL, NULL, NULL, adc, ror, NULL,
	NULL, sta, NULL, NULL, sty, sta, stx, NULL, dey, NULL, txa, NULL, sty, sta, stx, NULL,
	bcc, sta, NULL, NULL, sty, sta, stx, NULL, tya, sta, txs, NULL, NULL, sta, NULL, NULL,
	ldy, lda, ldx, NULL, ldy, lda, ldx, NULL, tay, lda, tax, NULL, ldy, lda, ldx, NULL,
	bcs, lda, NULL, NULL, ldy, lda, ldx, NULL, clv, lda, tsx, NULL, ldy, lda, ldx, NULL,
	cpy, cmp, NULL, NULL, cpy, cmp, dec, NULL, iny, cmp, dex, NULL, cpy, cmp, dec, NULL,
	bne, cmp, NULL, NULL, NULL, cmp, dec, NULL, cld, cmp, NULL, NULL, NULL, cmp, dec, NULL,
	cpx, sbc, NULL, NULL, cpx, sbc, inc, NULL, inx, sbc, nop, NULL, cpx, sbc, inc, NULL,
	beq, sbc, NULL, NULL, NULL, sbc, inc, NULL, sed, sbc, NULL, NULL, NULL, sbc, inc, NULL
};

// uint16_t (*getDecoder(uint8_t opcode))(Processor6502*)
decode getDecoder(uint8_t opcode)
{
	return modes[opcode];
}

// void (*getInstruction(uint8_t opcode))(Processor6502*, uint16_t)
operate getInstruction(uint8_t opcode)
{
	return instructions[opcode];
}