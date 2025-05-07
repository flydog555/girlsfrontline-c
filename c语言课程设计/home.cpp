#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<time.h>
#include "profile.h"
#include "shared.h"
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

extern void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
extern int gacha(int sign);
extern void PlayBGM(const char* filePath);
extern void StopBGM();

char dollname[10] = "HK416";

extern int Profile_Number;

int home()
{
	cleardevice();
	//播放bgm
	PlayBGM("./resource/BGM/Day1.mp3");


	//显示背景
	IMAGE img;
	IMAGE button1;
	IMAGE button2;
	IMAGE button3;
	IMAGE top;
	IMAGE lr;
	IMAGE ammo;
	IMAGE manpower;
	IMAGE pation;
	IMAGE part;

	loadimage(&img, "./resource/image/homebg.jpg", 1280, 720);
	loadimage(&button1, "./resource/icon/home1.png", 400, 100);
	loadimage(&button2, "./resource/icon/home2.png", 400, 110);
	loadimage(&button3, "./resource/icon/home3.png", 420, 105);
	loadimage(&top, "./resource/icon/hometop.png", 1280, 150);
	loadimage(&lr, "./resource/icon/levelround.png", 45, 45);
	loadimage(&manpower, "./resource/icon/人力图标.png", 115, 57);
	loadimage(&ammo, "./resource/icon/弹药图标.png", 100, 57);
	loadimage(&pation, "./resource/icon/口粮图标.png", 94, 57);
	loadimage(&part, "./resource/icon/零件图标.png", 96, 57);


	//显示人物
	IMAGE ch;
	if (strcmp(dollname, "HK416") == 0)
	{
		loadimage(&ch, "./resource/character/5星/HK416.png", 585, 1024);
	}
	else if (strcmp(dollname, "RPK16") == 0)
	{
		loadimage(&ch, "./resource/character/5星/RPK16.png", 746/2, 1024);
	}
	else if (strcmp(dollname, "AA12") == 0)
	{
		loadimage(&ch, "./resource/character/5星/AA12.png", 1469 / 2, 1024);
	}
	else if (strcmp(dollname, "RO635") == 0)
	{
		loadimage(&ch, "./resource/character/5星/RO635.png", 1197 / 2, 1024);
	}
	//显示名称
	setbkmode(TRANSPARENT);
	
	int currentLine = 0;
	//int sign = 0;
	int tempcode;
	int tempmanpower;
	int tempammunition;
	int temppation;
	int temppart;

	char filename[20];
	char name[100];
	char tempname[100];
	char levelStr[10]; // 确保数组足够大以容纳转换后的字符串
	char levelStr1[10];
	char levelStr2[10];
	char levelStr3[10];
	char levelStr4[10];

	//读取配置文件
	sprintf(filename, "file%d.txt", Profile_Number);  ////////
	FILE* file = fopen(filename, "r");
	while (fgets(tempname, sizeof(tempname), file) != NULL)
	{
		currentLine++;
		if (currentLine == 3)
		{
			char* colon = strchr(tempname, ':');
			char* value = colon + 1;
			value[strcspn(value, "\n")] = '\0';
			strcpy(name, value);
			fscanf(file, "level:%d", &tempcode); //等级
			sprintf(levelStr, "%d", tempcode/1000);
		}
		else if (currentLine == 4)
		{
			fscanf(file, "manpower:%d", &tempmanpower);//人力
			sprintf(levelStr1, "%d", tempmanpower);
		}
		else if (currentLine == 5)
		{
			fscanf(file, "ammunition:%d", &tempammunition);//弹药
			sprintf(levelStr2, "%d", tempammunition);
		}
		else if (currentLine == 6)
		{
			fscanf(file, "pation:%d", &temppation);//口粮
			sprintf(levelStr3, "%d", temppation);
		}
		else if (currentLine == 7)
		{
			fscanf(file, "part:%d", &temppart);//零件
			sprintf(levelStr4, "%d", temppart);
		}
	}
	fclose(file);
	

	
	//显示
	time_t start_time = time(NULL);
	while (difftime(time(NULL), start_time) < 1)
	{
		BeginBatchDraw();
		putimage(0, 0, &img);
		transparentimage3(NULL, 800, 260, &button1);
		transparentimage3(NULL, 800, 150, &button2);
		transparentimage3(NULL, 780, 375, &button3);
		transparentimage3(NULL, 0, 0, &top);
		transparentimage3(NULL, 10, 5, &lr);
		if (strcmp(dollname, "HK416") == 0)
		{
			transparentimage3(NULL, 100, 100, &ch);
		}
		else if (strcmp(dollname, "RPK16") == 0)
		{
			transparentimage3(NULL, 100, 100, &ch);
		}
		else if (strcmp(dollname, "AA12") == 0)
		{
			transparentimage3(NULL, 30, 50, &ch);
		}
		else if (strcmp(dollname, "RO635") == 0)
		{
			transparentimage3(NULL, 70, 50, &ch);
		}
		transparentimage3(NULL, 700, 0, &manpower);
		transparentimage3(NULL, 850, 0, &ammo);
		transparentimage3(NULL, 1000, 0, &pation);
		transparentimage3(NULL, 1140, 0, &part);

		settextcolor(RGB(255, 255, 255));
		settextstyle(35, 0, "黑体");
		outtextxy(70, 10, name); 
		settextstyle(20, 0, "黑体");
		outtextxy(21, 17, levelStr);
		settextstyle(30, 0, "黑体");
		settextcolor(RGB(250, 164, 19));

		outtextxy(770, 27, levelStr1);
		outtextxy(910, 27, levelStr2);
		outtextxy(1050, 27, levelStr3);
		outtextxy(1190, 27, levelStr4);
		EndBatchDraw();
	}
	//按键
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 800 && msg.x <= 800 + 200 && msg.y >= 150 && msg.y <= 150 + 100)//1键区域
				{
					printf("1\n");
					StopBGM();
					return 1;
				}
				if (msg.x >= 800 && msg.x <= 800 + 200 && msg.y >= 260 && msg.y <= 260 + 100)//2键区域
				{
					printf("2\n");
					//printf("%d\n",gacha(5));
					StopBGM();
					return 2;
				}
				//if (msg.x >= 1000 && msg.x <= 1000 + 200 && msg.y >= 260 && msg.y <= 260 + 100)//3键区域
				//{
				//	printf("3\n");
				//	StopBGM();
				//	return 3;
				//}
				//if (msg.x >= 780 && msg.x <= 780 + 210 && msg.y >= 375 && msg.y <= 375 + 105)//4键区域
				//{
				//	printf("4\n");
				//	StopBGM();
				//	return 4;
				//}
				if (msg.x >= 990 && msg.x <= 990 + 210 && msg.y >= 375 && msg.y <= 375 + 105)//5键区域
				{
					printf("5\n");
					return 5;
				}
				break;
			default:
				break;
			}
		}
		
	}
}