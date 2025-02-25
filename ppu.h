#pragma once
#include <SDL.h>

//#define SCREEN_WIDTH 256   // ������ ������
//#define SCREEN_HEIGHT 240  // ������ ������
//#define PIXEL_SIZE 3       // ���������� ��� ��������� ��������

#define SCREEN_WIDTH 256   // ������ ������
#define SCREEN_HEIGHT 240  // ������ ������
#define PIXEL_SIZE 3       // ���������� ��� ��������� ��������

#define SCREEN_BASE_ADDR 0x2000  // ������� ����� ������



// ������� ��� ������������� SDL
int initSDL();

// ������� ��� ���������� ������
void updateScreen();
// ������� ��� ��������� ��������
//void drawPixel(int x, int y, Uint32 color);

// ������ ������ � PPU (� �������� ��������� ������ �������������� � ������������ �����������)
void renderSamplePPUData();

void closeSDL();
