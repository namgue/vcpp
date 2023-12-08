#pragma once

#include <windows.h>

extern RECT drawingRect;

void DrawBonobono(HWND hWnd, HDC hdc, int blink);

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawBox(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawCircle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawCube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);