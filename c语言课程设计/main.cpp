#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include "profile.h"
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>
#include "shared.h"
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

extern int repair();
extern int home();
extern int battle();
extern Profile* insert(Profile* h, const char* accontname, const char* code, const char* name);
extern Profile* createfromtail();
extern int login();

int main()
{
	
	//��������
	initgraph(1280, 720);
	cleardevice();

	//��ȡ���ھ��
	HWND hnd = GetHWnd();

	//���ô��ڱ���
	SetWindowText(hnd, "��Ůǰ��");

	//��¼��ע��

	while (login() != 0)
	{
		;
	}
	
	while (1)
	{
		if (home() == 1)
		{
			if (repair() == -1)
			{
				continue;
			}
		}
		else if (home() == 2)
		{
			if (battle() == -1)
			{
				continue;
			}
		}
	}

		getchar();
		closegraph;
		return 0;
}