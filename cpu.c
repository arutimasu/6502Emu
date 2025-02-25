#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <SDL.h>

#define MEMORY_SIZE 65536 // 64 KB памяти для 6502
extern Uint32* screenBuffer;
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

// Прототипы функций
void cpu_init(CPU6502* cpu);
void cpu_load_program(CPU6502* cpu, const uint8_t* program, size_t program_size);
void cpu_run(CPU6502* cpu);
void cpu_print_registers(CPU6502* cpu);

// Инициализация процессора
void cpu_init(CPU6502* cpu) {
    cpu->A = cpu->X = cpu->Y = 0;
    cpu->SP = 0xFD; // Инициализируем стековый указатель
    cpu->status = 0;
    cpu->PC = 0x0000;
    memset(cpu->memory, 0, MEMORY_SIZE); // Очищаем память
}

// Загрузка программы в память
void cpu_load_program(CPU6502* cpu, const uint8_t* program, size_t program_size) {
    memcpy(cpu->memory, program, program_size);
}

// Выполнение инструкций процессора
void cpu_run(CPU6502* cpu) {
    while (1) {
        uint8_t instruction = cpu->memory[cpu->PC++];
        switch (instruction) {
        case 0x00: // BRK - Break
            printf("BRK instruction encountered.\n");
            return;
        case 0xA9: { // LDA - Load Accumulator
            uint8_t value = cpu->memory[cpu->PC++];
            cpu->A = value;
            break;
        }
        case 0xEA: // NOP - No Operation
            break;
        case 0x85: { // STA - Store Accumulator
            uint16_t addr = cpu->memory[cpu->PC++];
            //cpu->memory[addr] = cpu->A;
            screenBuffer[addr] = cpu->A;
            break;
        }
        default:
            printf("Неизвестная инструкция: 0x%02X\n", instruction);
            return;
        }
    }
}

// Вывод состояния регистров процессора
void cpu_print_registers(CPU6502* cpu) {
    printf("Регистр A: 0x%02X, X: 0x%02X, Y: 0x%02X, SP: 0x%02X, PC: 0x%04X\n",
        cpu->A, cpu->X, cpu->Y, cpu->SP, cpu->PC);
}

