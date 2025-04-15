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
extern Profile* insert(Profile* h, const char* accontname, const char* code, const char* name);
extern Profile* createfromtail();
extern int login();
extern int registerf();
extern int choose();

int Profile_Number = 1;

int main()
{
	
	//创建画面
	initgraph(1280, 720);
	cleardevice();

	//获取窗口句柄
	HWND hnd = GetHWnd();

	//设置窗口标题
	SetWindowText(hnd, "少女前线");

	//登录与注册
	while (1)
	{
		if (login() == 0)//成功登录
		{
			break;
		}
		else if (login() == -1)//点击注册按钮
		{
			registerf();
		}
	}
	
	//主界面
	while (1)
	{
		if (home() == 1)
		{
			/*if (repair() == -1)
			{
				continue;
			}*/
		}
		else if (home() == 2)
		{
			if (battle() == -1)
			{
				continue;
			}
		}
		else if (home() == 3)
		{
			if (choose() == -1)
			{
				continue;
			}
		}
	}

		getchar();
		closegraph;
		return 0;
}