#include "decode.h"
#include "ui.h"
#include <graphics.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <shlobj.h>
#include <tchar.h>
#pragma warning(disable : 4996)
HWND hWnd;
int main() {
	//freopen("out.log", "w", stdout);
	hWnd=initgraph(640, 480);
	SetWindowText(hWnd, TEXT("Binary Decode by HXP"));
	setbkcolor(WHITE);
	cleardevice();
	Button Arr_btn[3];

	Arr_btn[0] = CreateButton(50, 100, 150, 40, YELLOW, BLUE, GREEN, TEXT("ѡ�������ļ�")),
		Arr_btn[1] = CreateButton(50, 200, 150, 40, YELLOW, BLUE, GREEN, TEXT("��������������ļ�")),
		Arr_btn[2] = CreateButton(50, 300, 150, 40, YELLOW, BLUE, GREEN, TEXT("���ɽ����ļ�"));

	//char InPath[MAX_PATH], OutPath[MAX_PATH];
	char* InPath, * OutPath;
	InPath = (char*)malloc(sizeof(char) * MAX_PATH);
	OutPath = (char*)malloc(sizeof(char) * MAX_PATH);
	bool click_in, click_out,click_make;
	BeginBatchDraw();
	while(1){
		
		FlushBatchDraw();
		Arr_btn[1].clicked= Arr_btn[1].clicked= Arr_btn[0].clicked=0;
		UpdateAllButtons(Arr_btn, 3);
		click_out = Arr_btn[1].clicked;
		click_in = Arr_btn[0].clicked;
		click_make = Arr_btn[2].clicked;

		if (click_in) {
			//TCHAR title[256] = L"��ѡ��Ҫ������ļ�";
			/*char* temp = hOpenFile(title);
			InPath = !temp?InPath:temp;*/
			//InPath = GetFileNameFromDialog();
			InPath = OpenFileDialog();
			click_in = 0;
			//MessageBox(NULL, InPath), _T("Selected File"), MB_OK);
		}
		if (click_out) {
			OutPath = GetFileNameFromDialog();
			click_out = 0;
		}
		if (click_make) {
			click_make = 0;
			if (InPath && OutPath) {
				//printf("%s\n%s", InPath, OutPath);
				int ret = decodef(InPath, OutPath);

				if (!ret) {
					MessageBox(NULL, _T("�ļ����ɳɹ���"), _T("�ļ����ɳɹ���"), MB_OK);
					return 0;
				}
				else{
					if(ret==2){
						MessageBox(NULL, _T("�ļ����ɲ��ɹ�2��"), _T("�ļ����ɲ��ɹ�2��"), MB_OK);
					}
					if (ret == 3) {
						MessageBox(NULL, _T("�ļ����ɲ��ɹ�3��"), _T("�ļ����ɲ��ɹ�3��"), MB_OK);
					}
				}
			}
			else {
				MessageBox(NULL, _T("����д�ļ���Ϣ"), _T("����д�ļ���Ϣ"), MB_OK);
			}
		}
		cleardevice();
		for (int i = 0;i < 3;i++) {
			DrawButton(Arr_btn[i]);
		}
	}
	return 0;
}