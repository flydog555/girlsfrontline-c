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

//extern int repair();
extern int home();
extern int battle();
extern int login();
extern int registerf();
extern int choose();
extern int ranking_list();

int Profile_Number = 1;


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
	//while (1)
	//{
	//	if (login() == 0)//�ɹ���¼
	//	{
	//		break;
	//	}
	//	else if (login() == -1)//���ע�ᰴť
	//	{
	//		registerf();
	//	}
	//}
	
	//������
	while (1)
	{
		switch (home()) {
		case 1:
			if (ranking_list() == -1) {
				continue;
			}
			break; 

		case 4:
			cleardevice();
			if (battle() == -1) {
				continue;
			}
			break;

		case 5:
			cleardevice();
			if (choose() == -1) {
				continue;
			}
			break;
		}
	}

		getchar();
		closegraph;
		return 0;
}