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
    int x, y;           // 位置
    int width, height;  // 尺寸
    COLORREF normal;    // 正常颜色
    COLORREF hover;     // 悬停颜色
    COLORREF pressed;   // 按下颜色
    const TCHAR* text;   // 显示文字
    bool isHovered;     // 是否悬停
    bool isPressed;     // 是否被按下
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