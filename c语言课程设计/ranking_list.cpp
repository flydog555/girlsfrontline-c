#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<time.h>
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>


typedef struct profile
{
	int profile_id;
	char username[20];
	char gamename[20];
	int password;
	int level;
	int manpower;
	int ammunition;
	int pation;
	int part;
	struct profile* next;
}PLF;

extern PLF* load_profile();


extern void bubbleSortDescending(int array1[], int array2[], int size);


int ranking_list()
{
	cleardevice();
	int level[10] = { -1 };
	int score[10] = { -1 };
	char name[10][20];
	IMAGE list_bg;
	loadimage(&list_bg, "./resource/rankinglist/ui.png", 1280, 720);
	putimage(0, 0, &list_bg);
	//读取链表
	PLF* head = load_profile();
	PLF* p;
	p = head->next; //将p指向头节点中的next
	int i = 0;
	while (p != NULL && i < 10) // 遍历
	{
		level[i] = p->level;
		score[i] = p->manpower + p->ammunition + p->pation + p->part;
		strncpy(name[i], p->gamename, 19);
		name[i][19] = '\0'; // 确保字符串以 NULL 结尾
		i++;
		p = p->next;
	}
	//显示排名
	int num = i; // 记录有效排名数量
	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < num - 1 - i; j++) {
			if (level[j] < level[j + 1]) {
				// 交换元素
				int temp1 = level[j];
				level[j] = level[j + 1];
				level[j + 1] = temp1;

				int temp2 = score[j];
				score[j] = score[j + 1];
				score[j + 1] = temp2;

				char temp3[20]; // 临时数组用于存储一行数据
				strcpy(temp3, name[j]); // 先保存 name[j]
				strcpy(name[j], name[j + 1]); // 交换 name[j] 和 name[j + 1]
				strcpy(name[j + 1], temp3); // 将临时值赋回
			}
		}
	}
	settextcolor(WHITE);
	settextstyle(25, 0, "黑体");
	outtextxy(480, 150, "用户名");
	outtextxy(830, 150, "等级");
	outtextxy(1130, 150, "分数");

	settextstyle(35, 0, "黑体");
	settextcolor(BLACK);
	for (i = 0; i < num; i++)
	{
		setfillcolor(WHITE);
		fillrectangle(400, 200 + i * 80 - 15, 1250, 200 + i * 80 + 15 + textheight("WWW"));
		char level_buffer[10];
		char score_buffer[10];
		outtextxy(450, 200+i*80, name[i]);
		sprintf(level_buffer, "%d", level[i]);
		outtextxy(800, 200+i*80, level_buffer);
		sprintf(score_buffer, "%d", score[i]);
		outtextxy(1100, 200+i*80, score_buffer);
	}
	while (1)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GetHWnd(), &mousePos);
		if (mousePos.x >= 10 && mousePos.x <= 164 && mousePos.y >= 17 && mousePos.y <= 84)//返回
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				return -1;
			}
		}
	}
}