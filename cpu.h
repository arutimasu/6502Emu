#pragma once
#include <stdint.h>
#define MEMORY_SIZE 65536 // 64 KB ������ ��� 6502

// ��������� ���������� 6502
typedef struct {
    uint8_t A;      // �����������
    uint8_t X;      // �������� X
    uint8_t Y;      // �������� Y
    uint8_t SP;     // �������� ���������
    uint8_t status; // �������� �������
    uint16_t PC;    // ������� ������
    uint8_t memory[MEMORY_SIZE]; // ������
} CPU6502;

CPU6502 cpu;

// ��������� �������
void cpu_init(CPU6502* cpu);
void cpu_load_program(CPU6502* cpu, const uint8_t* program, size_t program_size);
void cpu_run(CPU6502* cpu);
void cpu_print_registers(CPU6502* cpu);