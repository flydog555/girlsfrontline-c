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
extern void creataccount();
extern void login();

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

	//login();

	//�˺ų�ʼ��
	/*int yesno=MessageBox(hnd, "�Ƿ������ʺ�", "�˺ŵ�½", MB_YESNO);
	Profile* p = createfromtail();
	char tempaccontname[100];
	char tempcode[20];
	char tempname[100];*/
	//if (yesno == IDYES)
	/*if (1)
	{
		while (1)
		{
			if (login() == 1)
			{
				break;
			}
		}
	}*/
	/*else if (yesno == IDNO)
	{
		creataccount();
	}*/
	
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