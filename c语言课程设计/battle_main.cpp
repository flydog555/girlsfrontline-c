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
extern void PlayBGM(const char* filePath);
extern void StopBGM();
extern void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

volatile int exitFlag = 0;
volatile int threadsPaused = 0; // 标志变量，控制线程暂停状态
int pause_sign = 0;


int mousex = 0;
int mousey = 0;
int level_up = 0;
int pause = 0;

/* 线程函数声明 */
void Thread1(void*);
void Thread2(void*);
void Thread3(void*);
void Thread4(void*);
void Thread5(void*);
void Thread6(void*);
void Thread7(void*);
void Thread8(void*);

/* 线程句柄 */
HANDLE h1, h2, h3, h4, h5, h6, h7, h8;

/* 线程共享内存 */
volatile int i = 0;

/* 主线程 */
int battle()
{
	PlayBGM("./resource/BGM/Beacon.mp3");
	/* 创建线程 */
	h1 = (HANDLE)_beginthread(Thread1, 0, NULL);//线程1
	h2 = (HANDLE)_beginthread(Thread2, 0, NULL);//线程2
	h3 = (HANDLE)_beginthread(Thread3, 0, NULL);//线程3
	h4 = (HANDLE)_beginthread(Thread4, 0, NULL);//线程4
	h5 = (HANDLE)_beginthread(Thread5, 0, NULL);//线程5
	h6 = (HANDLE)_beginthread(Thread6, 0, NULL);//线程6
	h7 = (HANDLE)_beginthread(Thread7, 0, NULL);//线程7
	h8 = (HANDLE)_beginthread(Thread8, 0, NULL);//线程7

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
			//pause_sign = 0;
			//threadsPaused = 1;
		}


		//if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x > 70 && mousePos.x < 70 + 34 && mousePos.y>15 && mousePos.y < 15 + 34 ) { // 按 'P' 键暂停/恢复
		//	if (threadsPaused || pause_sign == 0) {////////////////////////
		//		printf("Resuming threads...\n");
		//		ResumeThread(h1);
		//		ResumeThread(h2);
		//		ResumeThread(h3);
		//		ResumeThread(h4);
		//		ResumeThread(h5);
		//		ResumeThread(h6);
		//		ResumeThread(h7);
		//		threadsPaused = 0;
		//	}
		//	else if(!threadsPaused || pause_sign == 1){//////////////////////
		//		printf("Suspending threads...\n");
		//		SuspendThread(h1);
		//		SuspendThread(h2);
		//		SuspendThread(h3);
		//		SuspendThread(h4);
		//		SuspendThread(h5);
		//		SuspendThread(h6);
		//		SuspendThread(h7);
		//		threadsPaused = 1;
		//	}
			//if (pause_sign == 1)
			//{
			//	pause_sign = 0;
			//	threadsPaused = 1;
			//}
			//else if (pause_sign == 0)
			//{
			//	pause_sign = 1;
			//	threadsPaused = 0;
			//}
		//Sleep(1000); // 防止按键过快  
	}
		// 检查全局变量a的值，持续暂停线程  
		/*if (pause_sign == 1 && !threadsPaused) {
			printf("Global variable a is set to 1. Suspending threads...\n");
			SuspendThread(h1);
			SuspendThread(h2);
			SuspendThread(h3);
			SuspendThread(h4);
			SuspendThread(h5);
			SuspendThread(h6);
			SuspendThread(h7);
			threadsPaused = 1;
		}
		else if (pause_sign == 0 && threadsPaused) {
			printf("Global variable a is set to 0. Resuming threads...\n");
			ResumeThread(h1);
			ResumeThread(h2);
			ResumeThread(h3);
			ResumeThread(h4);
			ResumeThread(h5);
			ResumeThread(h6);
			ResumeThread(h7);
			threadsPaused = 0;
		}*/

		//Sleep(100); // 降低主循环频率  
		

	WaitForSingleObject(h1, INFINITE);//等待线程1结束
	WaitForSingleObject(h2, INFINITE);//等待线程2结束
	WaitForSingleObject(h3, INFINITE);//等待线程3结束
	WaitForSingleObject(h4, INFINITE);//等待线程4结束
	WaitForSingleObject(h5, INFINITE);//等待线程5结束
	WaitForSingleObject(h6, INFINITE);//等待线程6结束
	WaitForSingleObject(h7, INFINITE);//等待线程7结束
	WaitForSingleObject(h8, INFINITE);//等待线程7结束

	StopBGM();
	cleardevice();
	
	printf("You are killed");
	printf("主线程结束\n");
	return -1;
}


void Thread1(void* arg)  //线程1：渲染线程
{
	while (!exitFlag)
	{
		character_move();
	}

}

void Thread2(void* arg)  //线程2：键鼠控制
{
	while (!exitFlag)
	{
		keymove();
	}
}

void Thread3(void* arg)  //线程3：数据处理线程
{
	while (!exitFlag)
	{
		ui_process();
		Sleep(10);
	}
}

void Thread4(void* arg)  //线程4：子弹数据处理线程
{
	while (!exitFlag)
	{
		fire();
	}
}

void Thread5(void* arg)  //线程5：子弹渲染线程
{
	while (!exitFlag)
	{
		fire_rander();
	}
}

void Thread6(void* arg)  //线程6：敌人数据处理线程
{
	while (!exitFlag)
	{
		enemy_data();
	}
}

void Thread7(void* arg)  //线程7：敌人动画处理线程
{
	while (!exitFlag)
	{
		enemy_show();
	}
}

void Thread8(void* arg)  //线程8：暂停后控制
{
	IMAGE pause_bg;
	loadimage(&pause_bg, "./resource/icon/暂停背景.png", 246*3, 138*3);
	while (!exitFlag)
	{
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GetHWnd(), &mousePos);
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x > 70 && mousePos.x < 70 + 34 && mousePos.y>15 && mousePos.y < 15 + 34)
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
		if (pause_sign == 1 && level_up == 1)
		{
			POINT mousePos;
			GetCursorPos(&mousePos);
			ScreenToClient(GetHWnd(), &mousePos);
			setfillcolor(RED);
			setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
			transparentimage3(NULL, 640-(246*3/2), 360-(138*3/2), &pause_bg);
			fillrectangle(640 - 150, 360 + 100, 640 + 150, 360 + 150);
			outtextxy((490 + 790) / 2 - textwidth("确定") / 2, (460 + 510) / 2 - textheight("确定") / 2, "确定");
			/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x > 70 && mousePos.x < 70 + 34 && mousePos.y>15 && mousePos.y < 15 + 34)
			{
				pause_sign = 0;
			}*/
		}
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) && mousePos.x > 640 - 150 && mousePos.x < 640 + 150 && mousePos.y>360 + 100 && mousePos.y < 360 + 150)
		{
			pause_sign = 0;
			level_up = 0;
		}
		Sleep(100);
	}
}

// 停止所有线程时设置 exitFlag  
void stop_all_threads() {
	exitFlag = 1;
}