#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<time.h>
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
#include<mmsystem.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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
extern PLF* deletePLF(PLF* h, int i);
extern void bubbleSortDescending(int array1[], int array2[], int size);
extern void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
IMAGE choose_bg;



int ranking_list()
{
	cleardevice();
	int choose_sign = 0;
	int button1 = 0;
	int button2 = 0;
	int button3 = 0;
	int button4 = 0;
	int button5 = 0;
	int button6 = 0;
	int level[10] = { -1 };
	int score[10] = { -1 };
	char name[10][20];
	IMAGE list_bg;
	loadimage(&list_bg, "./resource/rankinglist/ui.png", 1280, 720);
	loadimage(&choose_bg, "./resource/icon/筛选背景.png", 246 * 3, 138 * 3);
	
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
	//计算排名
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

	//显示排名
	while (1)
	{
		putimage(0, 0, &list_bg);
		settextcolor(WHITE);
		settextstyle(30, 0, "思源宋体 CN Semibold");
		outtextxy(500, 150, "用户名");
		outtextxy(850, 150, "等级");
		outtextxy(1130, 150, "分数");

		settextstyle(40, 0, "思源宋体 CN Semibold");
		settextcolor(BLACK);
		BeginBatchDraw();
		for (i = 0; i < num; i++)
		{
			if (score[i] == 0)
			{
				break;
			}
			setfillcolor(WHITE);
			fillrectangle(420, 200 + i * 80 - 15, 1250, 200 + i * 80 + 15 + textheight("WWW"));
			char level_buffer[10];
			char score_buffer[10];
			outtextxy(470, 200 + i * 80, name[i]);
			sprintf(level_buffer, "%d", level[i] / 1000);
			outtextxy(850, 200 + i * 80, level_buffer);
			sprintf(score_buffer, "%d", score[i]);
			outtextxy(1120, 200 + i * 80, score_buffer);
		}
		EndBatchDraw();
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
		else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x >= 222 && mousePos.x <= 415 && mousePos.y >= 550 && mousePos.y <= 608)//筛选
		{

			choose_sign = 1;
		}
		if (choose_sign == 1)
		{
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x >= 540 && mousePos.x <= 740 && mousePos.y >= 460 && mousePos.y <= 530)
			{
				//按下确定键
				choose_sign = 0;
				
				
				int min = 0;
				int max = 0;
				int first = -1;
				int last = -1;

				// 按顺序处理每个 button
				if (button1 == 1) {
					if (first == -1) first = 1;
					last = 1;
				}
				if (button2 == 1) {
					if (first == -1) first = 2;
					last = 2;
				}
				if (button3 == 1) {
					if (first == -1) first = 3;
					last = 3;
				}
				if (button4 == 1) {
					if (first == -1) first = 4;
					last = 4;
				}
				if (button5 == 1) {
					if (first == -1) first = 5;
					last = 5;
				}
				if (button6 == 1) {
					if (first == -1) first = 6;
					last = 6;
				}

				if (first != -1 && last != -1) {
					min = 1 + (first - 1) * 10;
					max = last * 10;
				}
				else {
					// 没有按钮被选中时的处理
					min = 0;
					max = 50;
				}
				printf("(%d,%d)\n", min, max);
				//再次读取链表
				PLF* head = load_profile();
				//PLF * p;
				//p = head->next; //将p指向头节点中的next
				//int d = 1;
				//int delet_num = 0;
				//while (p != NULL && d < 10) // 遍历
				//{
				//	if (p->level/1000<min || p->level/1000>max)
				//	{
				//		deletePLF(head, d-delet_num);
				//		printf("delete %d\n", d);
				//		delet_num++;
				//	}
				//	d++;
				//	p = p->next;
				//}

				PLF* cur = head->next, * prev = NULL;
				while (cur) {
					if (cur->level/1000 < min || cur->level/1000 > max) {
						// 需要删除cur节点
						PLF* to_delete = cur;
						if (prev) {
							prev->next = cur->next;
							cur = cur->next;
						}
						else {
							// 头结点需要被删
							head = cur->next;
							cur = head;
						}
						free(to_delete);
						printf("delete\n");
					}
					else {
						prev = cur;
						cur = cur->next;
					}
				}
				printf("delete end\n");
				for (int p = 0; p < 10; p++)
				{
					level[p] = 0;
					score[p] = 0;
					name[p][0] = '\0';
				}
				PLF* r;
				//r = head->next; //将p指向头节点中的next//
				r = head; 
				int i = 0;
				while (r != NULL && i < 10) // 遍历
				{
					level[i] = r->level;
					score[i] = r->manpower + r->ammunition + r->pation + r->part;
					strncpy(name[i], r->gamename, 19);
					name[i][19] = '\0'; // 确保字符串以 NULL 结尾
					i++;
					r = r->next;
				}
				//再次计算排名
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
				button1 = 0;
				button2 = 0;
				button3 = 0;
				button4 = 0;
				button5 = 0;
				button6 = 0;

			}
			else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x >= 450 && mousePos.x <= 450 + 23 && mousePos.y >= 274 && mousePos.y <= 274 + 23)
			{
				if (button1 == 0)
				{
					button1 = 1;
				}
				else
				{
					button1 = 0;
				}
			}
			else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x >= 613 && mousePos.x <= 613 + 23 && mousePos.y >= 274 && mousePos.y <= 274 + 23)
			{
				if (button2 == 0)
				{
					button2 = 1;
				}
				else
				{
					button2 = 0;
				}
			}
			else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x >= 797 && mousePos.x <= 797 + 23 && mousePos.y >= 274 && mousePos.y <= 274 + 23)
			{
				if (button3 == 0)
				{
					button3 = 1;
				}
				else
				{
					button3 = 0;
				}
			}
			else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x >= 450 && mousePos.x <= 450 + 23 && mousePos.y >= 358 && mousePos.y <= 358 + 23)
			{
				if (button4 == 0)
				{
					button4 = 1;
				}
				else
				{
					button4 = 0;
				}
			}
			else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x >= 613 && mousePos.x <= 613 + 23 && mousePos.y >= 358 && mousePos.y <= 358 + 23)
			{
				if (button5 == 0)
				{
					button5 = 1;
				}
				else
				{
					button5 = 0;
				}
			}
			else if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x >= 797 && mousePos.x <= 797 + 23 && mousePos.y >= 358 && mousePos.y <= 358 + 23)
			{
				if (button6 == 0)
				{
					button6 = 1;
				}
				else
				{
					button6 = 0;
				}
			}
		}
		BeginBatchDraw();
		if (choose_sign==1)
		{
			transparentimage3(NULL, 640 - (246 * 3 / 2), 360 - (138 * 3 / 2), &choose_bg);
		}
		if (button1 == 1)
		{
			setfillcolor(RGB(253, 191, 26));
			fillrectangle(450, 274, 450 + 23, 274 + 23);
		}
		if (button2 == 1)
		{
			setfillcolor(RGB(253, 191, 26));
			fillrectangle(613, 274, 613 + 23, 274 + 23);
		}
		if (button3 == 1) 
		{
			setfillcolor(RGB(253, 191, 26));
			fillrectangle(797, 274, 797 + 23, 274 + 23);
		}
		if (button4 == 1)
		{
			setfillcolor(RGB(253, 191, 26));
			fillrectangle(450, 358, 450 + 23, 358 + 23);
		}
		if (button5 == 1)
		{
			setfillcolor(RGB(253, 191, 26));
			fillrectangle(613, 358, 613 + 23, 358 + 23);
		}
		if (button6 == 1)
		{
			setfillcolor(RGB(253, 191, 26));
			fillrectangle(797, 358, 797 + 23, 358 + 23);
		}
		EndBatchDraw();
		Sleep(100);
		cleardevice();
	}
}
