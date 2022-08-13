# include "chip8.h"

void CLS(CHIP8 chip8)
{
    memset(chip8.monitor, 0, sizeof(chip8.monitor));
}

void RET(CHIP8 chip8)
{
    --chip8.sp;
    chip8.pc = chip8.stack[chip8.sp];
}

void JP_addr(CHIP8 chip8)
{
    unsigned short addr = chip8.opcode & 0x0FFFu;
    chip8.pc = addr;
}

void CALL_addr(CHIP8 chip8)
{
    unsigned short addr = chip8.opcode & 0x0FFFu;
    chip8.stack[chip8.sp] = chip8.pc;
    ++chip8.sp;
    chip8.pc = addr;
}