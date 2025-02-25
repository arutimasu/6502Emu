#include <SDL.h>
#include "ppu.h"

Uint32* screenBuffer= NULL;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
// ������� ��� ������������� SDL
int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("6502 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * PIXEL_SIZE, SCREEN_HEIGHT * PIXEL_SIZE, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!texture) {
        printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    screenBuffer = (Uint32*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));  // �������� ������ ��� ��������
    if (!screenBuffer) {
        printf("Memory allocation failed\n");
        return -1;
    }

    return 0;
}

// ������� ��� ���������� ������
void updateScreen() {
    SDL_UpdateTexture(texture, NULL, screenBuffer, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

 //������� ��� ��������� ��������
void drawPixel(int x, int y, Uint32 color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        screenBuffer[y * SCREEN_WIDTH + x] = color;
    }
}



// ������ ������ � PPU (� �������� ��������� ������ �������������� � ������������ �����������)
void renderSamplePPUData() {
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            // ������� ������: ������������ ����� ��������
            if ((x + y) % 2 == 0) {
                drawPixel(x, y, 0xFFFFFF);  // �����
            }
            else {
                drawPixel(x, y, 0x000000);  // ������
            }
        }
    }
}

void closeSDL() {
    free(screenBuffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}