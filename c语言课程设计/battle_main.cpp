#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <graphics.h>  
#include <conio.h>  

extern void keymove();
extern void character_move();
extern void ui_process();
extern void fire();
extern void fire_rander();
extern void enemy_data();
extern void enemy_show();
extern void draw_pause_ui();
extern void PlayBGM(const char* filePath);
extern void StopBGM();
extern void enemy_generate();
extern void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
extern void draw_end_ui();


volatile int exitFlag = 0;
volatile int threadsPaused = 0; // 标志变量，控制线程暂停状态
int pause_sign = 0;

extern int level_attack;
extern int level_speed;
extern int level_health;
extern int level_gain;
extern char dollname[10];

int mousex = 0;
int mousey = 0;
int level_up = 0;
int pause = 0;
int RATIO = 100;
char filename[100];
extern int Profile_Number;

extern int BULLET_DAMGE;// 子弹伤害
extern int BULLET_SPEED; // 子弹速度
extern int BULLET_INTERVAL; // 子弹间隔
extern int live;

extern int score;
extern int killed_number;

/* 线程函数声明 */
void Thread1(void*);
void Thread2(void*);
void Thread3(void*);
void Thread4(void*);
void Thread5(void*);
void Thread6(void*);
void Thread7(void*);
void Thread8(void*);
void Thread9(void*);

/* 线程句柄 */
HANDLE h1, h2, h3, h4, h5, h6, h7, h8, h9;

/* 线程共享内存 */
volatile int i = 0;

/* 主线程 */
int battle()
{
	exitFlag = 0;
	threadsPaused = 0;
	pause_sign = 0;
	mousex = 0;
	mousey = 0;
	level_up = 0;
	pause = 0;
	RATIO = 100;
	PlayBGM("./resource/BGM/Beacon.mp3");

	/* 创建线程 */
	h1 = (HANDLE)_beginthread(Thread1, 0, NULL);//线程1
	h2 = (HANDLE)_beginthread(Thread2, 0, NULL);//线程2
	h3 = (HANDLE)_beginthread(Thread3, 0, NULL);//线程3
	h4 = (HANDLE)_beginthread(Thread4, 0, NULL);//线程4
	h5 = (HANDLE)_beginthread(Thread5, 0, NULL);//线程5
	h6 = (HANDLE)_beginthread(Thread6, 0, NULL);//线程6
	h7 = (HANDLE)_beginthread(Thread7, 0, NULL);//线程7
	h8 = (HANDLE)_beginthread(Thread8, 0, NULL);//线程8
	h9 = (HANDLE)_beginthread(Thread9, 0, NULL);//线程9

	// 主控制循环  
	while (!exitFlag) 
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GetHWnd(), &mousePos);
		mousex = mousePos.x;
		mousey = mousePos.y;
		if (pause_sign == 0) {////////////////////////
			printf("Resuming threads...\n");//恢复
			ResumeThread(h1);
			ResumeThread(h2);
			ResumeThread(h3);
			ResumeThread(h4);
			ResumeThread(h5);
			ResumeThread(h6);
			ResumeThread(h7);
			ResumeThread(h8);
			//pause_sign = 1;
			//threadsPaused = 0;
		}
		else if (pause_sign == 1) {//////////////////////
			printf("Suspending threads...\n");//暂停
			SuspendThread(h1);
			SuspendThread(h2);
			SuspendThread(h3);
			SuspendThread(h4);
			SuspendThread(h5);
			SuspendThread(h6);
			SuspendThread(h7);
			SuspendThread(h8);
			//pause_sign = 0;
			//threadsPaused = 1;
		} 
	}


	WaitForSingleObject(h1, INFINITE);//等待线程1结束
	WaitForSingleObject(h2, INFINITE);//等待线程2结束
	WaitForSingleObject(h3, INFINITE);//等待线程3结束
	WaitForSingleObject(h4, INFINITE);//等待线程4结束
	WaitForSingleObject(h5, INFINITE);//等待线程5结束
	WaitForSingleObject(h6, INFINITE);//等待线程6结束
	WaitForSingleObject(h7, INFINITE);//等待线程7结束
	WaitForSingleObject(h8, INFINITE);//等待线程8结束
	WaitForSingleObject(h9, INFINITE);//等待线程9结束

	CloseHandle(h1);
	CloseHandle(h2);
	CloseHandle(h3);
	CloseHandle(h4);
	CloseHandle(h5);
	CloseHandle(h6);
	CloseHandle(h7);
	CloseHandle(h8);
	CloseHandle(h9);

	while (1)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GetHWnd(), &mousePos);
		draw_end_ui();
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && mousePos.x > 640 - 150 && mousePos.x < 640 + 150 && mousePos.y>360 + 100 && mousePos.y < 360 + 150)
		{
			sprintf(filename, "file%d.txt", Profile_Number);
			FILE* file = fopen(filename, "r");
			if (file == NULL) {
				printf("无法打开文件\n");
			}

			// 创建临时文件以写入修改后的内容
			FILE* temp_file = fopen("temp.txt", "w");
			if (temp_file == NULL) {
				printf("无法创建临时文件\n");
				fclose(file);
			}

			char line[100];
			int manpower = 0;

			// 逐行读取文件
			while (fgets(line, sizeof(line), file)) {
				printf("读取到的行: [%s]\n", line); // 调试用
				char* found1 = strstr(line, "manpower:");
				char* found2 = strstr(line, "ammunition:");
				char* found3 = strstr(line, "pation:");
				char* found4 = strstr(line, "part:");
				if (found1) {
					int manpower = 0;
					sscanf(found1 + 9, "%d", &manpower);
					manpower += score;
					fprintf(temp_file, "manpower:%d\n", manpower);
				}
				else if (found2)
				{
					int ammunition = 0;
					sscanf(found2 + 11, "%d", &ammunition);
					ammunition += score;
					fprintf(temp_file, "ammunition:%d\n", ammunition);
				}
				else if (found3)
				{
					int pation = 0;
					sscanf(found3 + 7, "%d", &pation);
					pation += score;
					fprintf(temp_file, "pation:%d\n", pation);
				}
				else if (found4)
				{
					int part = 0;
					sscanf(found4 + 5, "%d", &part);
					part += score;
					fprintf(temp_file, "part:%d\n", part);
				}
				else {
					fputs(line, temp_file);
				}
			}

			fclose(file); // 关闭原始文件
			fclose(temp_file); // 关闭临时文件

			// 删除原文件
			remove(filename);
			// 重命名临时文件为原文件名
			rename("temp.txt", filename);

			break;
		}
		Sleep(1000 / 60);
	}

	StopBGM();
	cleardevice();
	
	printf("You are killed");
	printf("主线程结束\n");
	return -1;
}

// 停止所有线程时设置 exitFlag  
void stop_all_threads() {
	exitFlag = 1;
}

void Thread1(void* arg)  //线程1：渲染线程
{
	while (!exitFlag)
	{
		character_move();
	}
	ExitThread(0);
}

void Thread2(void* arg)  //线程2：键鼠控制
{
	while (!exitFlag)
	{
		keymove();
	}
	ExitThread(0);
}

void Thread3(void* arg)  //线程3：数据处理线程
{
	while (!exitFlag)
	{
		ui_process();
		Sleep(10);
	}
	ExitThread(0);
}

void Thread4(void* arg)  //线程4：子弹数据处理线程
{
	while (!exitFlag)
	{
		fire();
	}
	ExitThread(0);
}

void Thread5(void* arg)  //线程5：子弹渲染线程
{
	while (!exitFlag)
	{
		fire_rander();
	}
	ExitThread(0);
}

void Thread6(void* arg)  //线程6：敌人数据处理线程
{
	while (!exitFlag)
	{
		enemy_data();
	}
	ExitThread(0);
}

void Thread7(void* arg)  //线程7：敌人动画处理线程
{
	while (!exitFlag)
	{
		enemy_show();
	}
	ExitThread(0);
}

void Thread8(void* arg)  //线程8：敌人生成线程
{
	while (!exitFlag)
	{
		enemy_generate();
	}
	ExitThread(0);
}

void Thread9(void* arg)  //线程9：暂停后控制 
{
	int skill_choose = 0;
	while (!exitFlag)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GetHWnd(), &mousePos);
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x > 110 && mousePos.x < 110 + 34 && mousePos.y>15 && mousePos.y < 15 + 34)
		{
			if (pause_sign == 1)
			{
				pause_sign = 0;
			}
			else if (pause_sign == 0)
			{
				pause_sign = 1;
			}
		}
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x > 50 && mousePos.x < 50 + 34 && mousePos.y>15 && mousePos.y < 15 + 34)
		{
			score=killed_number*RATIO*0.1;
			stop_all_threads();
		}

		if (pause_sign == 1 && level_up == 1)
		{
			draw_pause_ui();
			if (skill_choose == 1)
			{
				rectangle(640 - 270 - 75 / 2, 360 - 100, 640 - 270 + 75 / 2, 360 - 100 + 75);
			}
			else if (skill_choose == 2)
			{
				rectangle(640 - 90 - 75 / 2, 360 - 100, 640 - 90 + 75 / 2, 360 - 100 + 75);
			}
			else if (skill_choose == 3)
			{
				rectangle(640 + 90 - 75 / 2, 360 - 100, 640 + 90 + 75 / 2, 360 - 100 + 75);
			}
			else if (skill_choose == 4)
			{
				rectangle(640 + 270 - 75 / 2, 360 - 100, 640 + 270 + 75 / 2, 360 - 100 + 75);
			}
			POINT mousePos;
			GetCursorPos(&mousePos);
			ScreenToClient(GetHWnd(), &mousePos);
			setcolor(RGB(61, 153, 227));
			setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
			if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && mousePos.x > 640 - 270 - 75 / 2 && mousePos.x < 640 - 270 + 75 / 2 && mousePos.y>360 - 100 && mousePos.y < 360 - 100 + 75)
			{
				if (level_attack < 3)
				{
					skill_choose = 1;
				}
				
			}
			else if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && mousePos.x > 640 - 90 - 75 / 2 && mousePos.x < 640 - 90 + 75 / 2 && mousePos.y>360 - 100 && mousePos.y < 360 - 100 + 75)
			{
				if (level_speed < 3)
				{
					skill_choose = 2;
				}
				
			}
			else if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && mousePos.x > 640 + 90 - 75 / 2 && mousePos.x < 640 + 90 + 75 / 2 && mousePos.y>360 - 100 && mousePos.y < 360 - 100 + 75)
			{
				if (level_health < 3)
				{
					skill_choose = 3;
				}
				
			}
			else if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && mousePos.x > 640 + 270 - 75 / 2 && mousePos.x < 640 + 270 + 75 / 2 && mousePos.y>360 - 100 && mousePos.y < 360 - 100 + 75)
			{
				if (level_gain < 3)
				{
					skill_choose = 4;
				}
				
			}
			setcolor(RGB(255, 255, 255));

			/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x > 70 && mousePos.x < 70 + 34 && mousePos.y>15 && mousePos.y < 15 + 34)
			{
				pause_sign = 0;
			}*/
		}
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && skill_choose!=0 && mousePos.x > 640 - 150 && mousePos.x < 640 + 150 && mousePos.y>360 + 100 && mousePos.y < 360 + 150)
		{
			if (skill_choose == 1)
			{
				if (level_attack < 3)
				{
					level_attack++;
					if (level_attack == 1)
					{
						BULLET_DAMGE = BULLET_DAMGE * 1.1;
					}
					else if (level_attack == 2)
					{
						BULLET_DAMGE = BULLET_DAMGE * 1.25;
					}
					else if (level_attack == 3)
					{
						BULLET_DAMGE = BULLET_DAMGE * 1.5;
					}
				}
			}
			else if (skill_choose == 2)
			{
				if (level_speed < 3)
				{
					level_speed++;
					if (level_speed == 1)
					{
						BULLET_INTERVAL = BULLET_INTERVAL * 0.9;
					}
					else if (level_speed == 2)
					{
						BULLET_INTERVAL = BULLET_INTERVAL * 0.75;
					}
					else if (level_speed == 3)
					{
						BULLET_INTERVAL = BULLET_INTERVAL * 0.5;
					}
				}
			}
			else if (skill_choose == 3)
			{
				if (level_health < 3)
				{
					level_health++;
					if (live < 3)
					{
						live++;
					}
				}
			}
			else if (skill_choose == 4)
			{
				if (level_gain < 3)
				{
					level_gain++;
					if (level_gain == 1)
					{
						RATIO = RATIO * 1.1;
					}
					else if (level_gain == 2)
					{
						RATIO = RATIO * 1.25;
					}
					else if (level_gain == 3)
					{
						RATIO = RATIO * 1.5;
					}
				}
			}
			pause_sign = 0;
			level_up = 0;
		}
		Sleep(100);
	}
	ExitThread(0);
}

