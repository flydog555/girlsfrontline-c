#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

int BULLET_DAMGE;// 子弹伤害
int BULLET_SPEED; // 子弹速度
int BULLET_INTERVAL; // 子弹间隔


extern char dollname[10];

int choose()
{
	cleardevice();
	IMAGE choose_bg;
	loadimage(&choose_bg, "./resource/choose/ui.png", 1280, 720);
	putimage(0, 0, &choose_bg);

	
	while (1)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GetHWnd(), &mousePos);
		if (mousePos.x >= 476 && mousePos.x <= 607 && mousePos.y >= 155 && mousePos.y <= 392)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				putimage(0, 0, &choose_bg);
				setcolor(RGB(61, 153, 227));
				setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
				rectangle(476, 155, 607, 392);
				strcpy(dollname, "HK416");
				BULLET_DAMGE = 15;
				BULLET_SPEED = 10 / 2;
				BULLET_INTERVAL = 200;
			}
		}
		else if (mousePos.x >= 696 && mousePos.x <= 829 && mousePos.y >= 152 && mousePos.y <= 394)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				putimage(0, 0, &choose_bg);
				setcolor(RGB(61, 153, 227));
				setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
				rectangle(696, 152, 829, 394);
				strcpy(dollname, "RO635");
				BULLET_DAMGE = 10;
				BULLET_SPEED = 20 / 2;
				BULLET_INTERVAL = 100;
			}
		}
		else if (mousePos.x >= 934 && mousePos.x <= 1070 && mousePos.y >= 152 && mousePos.y <= 394)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				putimage(0, 0, &choose_bg);
				setcolor(RGB(61, 153, 227));
				setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
				rectangle(934, 152, 1070, 394);
				strcpy(dollname, "RPK16");
				BULLET_DAMGE = 15;
				BULLET_SPEED = 15 / 2;
				BULLET_INTERVAL = 150;
			}
		}
		else if (mousePos.x >= 472 && mousePos.x <= 610 && mousePos.y >= 453 && mousePos.y <= 692)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				putimage(0, 0, &choose_bg);
				setcolor(RGB(61, 153, 227));
				setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
				rectangle(472, 453, 610, 692);
				strcpy(dollname, "AA12");
				BULLET_DAMGE = 25;
				BULLET_SPEED = 5;
				BULLET_INTERVAL = 800;
			}
		}
		else if (mousePos.x >= 10 && mousePos.x <= 164 && mousePos.y >= 17 && mousePos.y <= 84)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				return -1;
			}
		}
		Sleep(10);
	}
	
	
}