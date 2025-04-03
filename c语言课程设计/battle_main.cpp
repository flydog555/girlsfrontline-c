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

volatile int exitFlag = 0;

/* 线程函数声明 */
void Thread1(void*);
void Thread2(void*);
void Thread3(void*);
void Thread4(void*);
void Thread5(void*);
void Thread6(void*);
void Thread7(void*);

/* 线程句柄 */
HANDLE h1, h2, h3, h4, h5, h6, h7;

/* 线程共享内存 */
volatile int i = 0;

/* 主线程 */
void battle()
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

	WaitForSingleObject(h1, INFINITE);//等待线程1结束
	WaitForSingleObject(h2, INFINITE);//等待线程2结束
	WaitForSingleObject(h3, INFINITE);//等待线程3结束
	WaitForSingleObject(h4, INFINITE);//等待线程4结束
	WaitForSingleObject(h5, INFINITE);//等待线程5结束
	WaitForSingleObject(h6, INFINITE);//等待线程6结束
	WaitForSingleObject(h7, INFINITE);//等待线程7结束

	cleardevice();
	StopBGM();
	printf("You are killed");
	closegraph();
	printf("主线程结束\n");
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