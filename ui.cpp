#include "ui.h"
#include <windows.h>
#include <graphics.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <shlobj.h>
#include <tchar.h>
#include <stdio.h>
#pragma warning(disable : 4996)
char* hOpenFile(TCHAR* WindowName) {
    OPENFILENAME ofn = { 0 };
    TCHAR szFile[MAX_PATH] = { 0 };

    // 初始化 OPENFILENAME 结构
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = _T("All Files\0*.*\0Text Files\0*.txt\0");
    ofn.nFilterIndex = 1;  // 默认选择第一个过滤器（All Files）
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    char Filepath[MAX_PATH];
    // 显示文件选择对话框
    if (GetOpenFileName(&ofn)) {
        // 用户选择的文件路径保存在 szFile 中
        //size_t temp_i;
        wcstombs(Filepath,szFile,MAX_PATH);
       /// MessageBox(NULL, szFile, _T("文aaaaa成功！"), MB_OK);
        
        return Filepath;
        
    }
    return NULL;
}

char* OpenFileDialog() {
    OPENFILENAMEW ofn = { 0 };
    WCHAR szFile[MAX_PATH] = { 0 };

    // 初始化对话框结构
    ofn.lStructSize = sizeof(OPENFILENAMEW);
    ofn.hwndOwner = GetForegroundWindow();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"All Files\0*.*\0Text Files\0*.txt\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    // 显示对话框
    if (!GetOpenFileNameW(&ofn)) {
        return nullptr;
    }

    // 转换宽字符到UTF-8
    int utf8_len = WideCharToMultiByte(CP_UTF8, 0, szFile, -1, nullptr, 0, nullptr, nullptr);
    if (utf8_len == 0) {
        return nullptr;
    }

    // 分配内存
    char* utf8_path = (char*)malloc(utf8_len);
    if (!utf8_path) {
        return nullptr;
    }

    // 执行实际转换
    if (WideCharToMultiByte(CP_UTF8, 0, szFile, -1, utf8_path, utf8_len, nullptr, nullptr) == 0) {
        free(utf8_path);
        return nullptr;
    }

    return utf8_path;
}


// 创建按钮
Button CreateButton(int x, int y, int w, int h, COLORREF normal, COLORREF hover, COLORREF pressed, const TCHAR* text) {
    Button btn;
    btn.x = x;
    btn.y = y;
    btn.width = w;
    btn.height = h;
    btn.normal = normal;
    btn.hover = hover;
    btn.pressed = pressed;
    btn.text = text;
    btn.isHovered = false;
    btn.isPressed = false;
    return btn;
}

// 绘制按钮
void DrawButton(Button& btn) {
    // 根据状态选择颜色
    COLORREF currentColor = btn.normal;
    if (btn.isPressed) currentColor = btn.pressed;
    else if (btn.isHovered) currentColor = btn.hover;

    setfillcolor(currentColor);
    fillroundrect(btn.x, btn.y,
        btn.x + btn.width,
        btn.y + btn.height,
        5, 5);

    // 文字居中
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    int tx = btn.x + (btn.width - textwidth(btn.text)) / 2;
    int ty = btn.y + (btn.height - textheight(btn.text)) / 2;
    outtextxy(tx, ty, btn.text);
}

// 更新按钮状态，返回是否被点击
bool UpdateButton(Button& btn) {
    ExMessage msg;
    bool clicked = false;

    btn.isHovered = false;  // 重置悬停状态
    if (peekmessage(&msg, EM_MOUSE)) {
        bool inArea = msg.x >= btn.x && msg.x <= btn.x + btn.width && msg.y >= btn.y && msg.y <= btn.y + btn.height;    // 判断光标是否button上

        switch (msg.message) {
        case WM_MOUSEMOVE:
            btn.isHovered = inArea;
            return false;

        case WM_LBUTTONDOWN:
            if (inArea) btn.isPressed = true;
            return false;

        case WM_LBUTTONUP:
            if (btn.isPressed && inArea) {
                return true;
            }
            btn.isPressed = false;
            return false;
        }
    }
    return clicked;
}

char* GetFileNameFromDialog() {
    // 使用宽字符版本输入框
    wchar_t wszFileName[MAX_PATH] = { 0 };

    // 弹出输入对话框
    if (InputBox(wszFileName, MAX_PATH,
        L"请输入文件名",
        L"文件保存",
        L"newfile.txt",
        300, 100, false) == 0) {
        return nullptr; // 用户取消输入
    }

    // 将宽字符转换为多字节
    int nLen = WideCharToMultiByte(CP_ACP, 0, wszFileName, -1, nullptr, 0, nullptr, nullptr);
    if (nLen == 0) return nullptr;

    char* szFileName = (char*)malloc(nLen);
    if (!szFileName) return nullptr;

    WideCharToMultiByte(CP_ACP, 0, wszFileName, -1, szFileName, nLen, nullptr, nullptr);
    return szFileName;
}

// 全局消息处理器
void UpdateAllButtons(Button buttons[], int count) {
    ExMessage msg;
    while (peekmessage(&msg, EM_MOUSE)) {
        for (int i = 0; i < count; ++i) {
            buttons[i].clicked = false;
            bool inArea = msg.x >= buttons[i].x && msg.x <= buttons[i].x + buttons[i].width &&
                msg.y >= buttons[i].y && msg.y <= buttons[i].y + buttons[i].height;

            switch (msg.message) {
            case WM_MOUSEMOVE:
                buttons[i].isHovered = inArea;
                break;

            case WM_LBUTTONDOWN:
                if (inArea) buttons[i].isPressed = true;
                break;

            case WM_LBUTTONUP:
                if (inArea && buttons[i].isPressed) {
                    buttons[i].clicked = true; // ✔ 正确触发点击
                }
                buttons[i].isPressed = false;  // ✔ 必须重置
                //buttons[i].clicked = false;
                break;
            }
        }
    }
}
