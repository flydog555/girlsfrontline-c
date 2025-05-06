#define _CRT_SECURE_NO_WARNINGS 1

#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<stdio.h>
#include<mmsystem.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")
#include "profile.h"

//pngÍ¸Ã÷Ð§¹û
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

//BGM²¥·Å
void PlayBGM(const char* filePath)
{
	char command[256];
	sprintf(command, "open \"%s\" alias BGM", filePath);
	mciSendString(command, 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
}

void StopBGM()
{
	//mciSendString("stop BGM", 0, 0, 0);
	mciSendString("close BGM", 0, 0, 0);
}


void DrawButten(int x, int y, int w, int h, const char* text)
{
	setlinecolor(RGB(89, 89, 89));
	setfillcolor(RGB(232, 232, 232));
	solidrectangle(x, y, x + w, y + h);

	int scaledWidth = w * 1.0;
	int scaledHeight = h * 1.0;
	int scaledX = x + (w - scaledWidth) / 2;
	int scaledY = y + (h - scaledHeight) / 2;
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30 * 1.0, 0, _T("Î¢ÈíÑÅºÚ"));
	int textX = scaledX + (scaledWidth - textwidth(text)) / 2;
	int textY = scaledY + (scaledHeight - textheight(_T("Î¢ÈíÑÅºÚ"))) / 2;
	outtextxy(textX, textY, text);
}

void DrawButten_Pressed(int x, int y, int w, int h, const char* text)
{
	setlinecolor(RGB(89, 89, 89));
	setfillcolor(RGB(135, 226, 255));
	solidrectangle(x, y, x + w, y + h);

	int scaledWidth = w * 1.0;
	int scaledHeight = h * 1.0;
	int scaledX = x + (w - scaledWidth) / 2;
	int scaledY = y + (h - scaledHeight) / 2;
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30 * 1.0, 0, _T("Î¢ÈíÑÅºÚ"));
	int textX = scaledX + (scaledWidth - textwidth(text)) / 2;
	int textY = scaledY + (scaledHeight - textheight(_T("Î¢ÈíÑÅºÚ"))) / 2;
	outtextxy(textX, textY, text);
}

void DrawTextbox(int x, int y, int w, int h, const char* text)
{
	setlinecolor(RGB(89, 89, 89));
	setfillcolor(RGB(232, 232, 232));
	solidrectangle(x, y, x + w, y + h);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30 * 1.0, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(x, y, text);
}

void bubbleSortDescending(int array1[], int array2[], int size) //Êý×éÅÅÐò
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (array1[j] < array1[j + 1]) {
				// ½»»»ÔªËØ
				int temp1 = array1[j];
				array1[j] = array1[j + 1];
				array1[j + 1] = temp1;
				int temp2 = array2[j];
				array2[j] = array2[j + 1];
				array2[j + 1] = temp2;
			}
		}
	}
}