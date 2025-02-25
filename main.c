#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "cpu.h"
#include <SDL.h>

// ����� �����
int main() {
    setlocale(LC_ALL, "");
    CPU6502 cpu;
    cpu_init(&cpu);
    if (initSDL() != 0) {
        return -1;
    }

    int quit = 0;
    SDL_Event e;

    // ������� ������ ���������:
    // LDA #$05 ; ��������� 5 � �����������
    // STA $20  ; ��������� ����������� �� ������ $20
    // BRK       ; ���������� ����������
    uint8_t program[] = {
        0xA9, 0x05, // LDA #$05
        0x85, 0x20, // STA $20
        0x00        // BRK
    };

    cpu_load_program(&cpu, program, sizeof(program));
    cpu_run(&cpu);
   

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        //renderSamplePPUData();  // � �������� ���������� ��� ����� ������������ ����������� �� PPU
        updateScreen();
        SDL_Delay(16);  // ������������ FPS �� 60 ������ � �������
    }

    closeSDL();
    // ����� ����������
    cpu_print_registers(&cpu);
    printf("�������� �� ������ $20: 0x%02X\n", cpu.memory[0x20]);

    return 0;
}