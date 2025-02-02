#pragma once
#ifndef _UI_H
#define _UI_H
#include <windows.h>
#include <graphics.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <shlobj.h>
#include <tchar.h>
char* hOpenFile(TCHAR* WindowName);
struct Button {
    int x, y;           // λ��
    int width, height;  // �ߴ�
    COLORREF normal;    // ������ɫ
    COLORREF hover;     // ��ͣ��ɫ
    COLORREF pressed;   // ������ɫ
    const TCHAR* text;   // ��ʾ����
    bool isHovered;     // �Ƿ���ͣ
    bool isPressed;     // �Ƿ񱻰���
    bool clicked;
    ~Button()
    {
        clicked = false;
    }
};
Button CreateButton(int x, int y, int w, int h, COLORREF normal, COLORREF hover, COLORREF pressed, const TCHAR* text);
void DrawButton(Button& btn);
bool UpdateButton(Button& btn);
void UpdateAllButtons(Button buttons[], int count);
char* GetFileNameFromDialog();
char* OpenFileDialog();
#endif // !_UI_H