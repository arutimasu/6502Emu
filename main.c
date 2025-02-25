#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "cpu.h"
#include <SDL.h>

// Точка входа
int main() {
    setlocale(LC_ALL, "");
    CPU6502 cpu;
    cpu_init(&cpu);
    if (initSDL() != 0) {
        return -1;
    }

    int quit = 0;
    SDL_Event e;

    // Простой пример программы:
    // LDA #$05 ; Загрузить 5 в аккумулятор
    // STA $20  ; Сохранить аккумулятор по адресу $20
    // BRK       ; Остановить выполнение
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

        //renderSamplePPUData();  // В реальной реализации это будет генерировать изображение от PPU
        updateScreen();
        SDL_Delay(16);  // Ограничиваем FPS до 60 кадров в секунду
    }

    closeSDL();
    // Вывод результата
    cpu_print_registers(&cpu);
    printf("Значение по адресу $20: 0x%02X\n", cpu.memory[0x20]);

    return 0;
}