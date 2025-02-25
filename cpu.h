#pragma once
#include <stdint.h>
#define MEMORY_SIZE 65536 // 64 KB памяти для 6502

// Структура процессора 6502
typedef struct {
    uint8_t A;      // Аккумулятор
    uint8_t X;      // Регистры X
    uint8_t Y;      // Регистры Y
    uint8_t SP;     // Стековый указатель
    uint8_t status; // Регистры статуса
    uint16_t PC;    // Счетчик команд
    uint8_t memory[MEMORY_SIZE]; // Память
} CPU6502;

CPU6502 cpu;

// Прототипы функций
void cpu_init(CPU6502* cpu);
void cpu_load_program(CPU6502* cpu, const uint8_t* program, size_t program_size);
void cpu_run(CPU6502* cpu);
void cpu_print_registers(CPU6502* cpu);