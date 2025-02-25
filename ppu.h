#pragma once
#include <SDL.h>

//#define SCREEN_WIDTH 256   // Ширина экрана
//#define SCREEN_HEIGHT 240  // Высота экрана
//#define PIXEL_SIZE 3       // Увеличение для видимости пикселей

#define SCREEN_WIDTH 256   // Ширина экрана
#define SCREEN_HEIGHT 240  // Высота экрана
#define PIXEL_SIZE 3       // Увеличение для видимости пикселей

#define SCREEN_BASE_ADDR 0x2000  // Базовый адрес экрана



// Функция для инициализации SDL
int initSDL();

// Функция для обновления экрана
void updateScreen();
// Функция для отрисовки пикселей
//void drawPixel(int x, int y, Uint32 color);

// Пример работы с PPU (в реальном эмуляторе данные обрабатываются и генерируются процессором)
void renderSamplePPUData();

void closeSDL();
