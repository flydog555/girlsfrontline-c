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
volatile int threadsPaused = 0; // ��־�����������߳���ͣ״̬

/* �̺߳������� */
void Thread1(void*);
void Thread2(void*);
void Thread3(void*);
void Thread4(void*);
void Thread5(void*);
void Thread6(void*);
void Thread7(void*);

/* �߳̾�� */
HANDLE h1, h2, h3, h4, h5, h6, h7;

/* �̹߳����ڴ� */
volatile int i = 0;

/* ���߳� */
int battle()
{
	PlayBGM("./resource/BGM/Beacon.mp3");
	/* �����߳� */
	h1 = (HANDLE)_beginthread(Thread1, 0, NULL);//�߳�1
	h2 = (HANDLE)_beginthread(Thread2, 0, NULL);//�߳�2
	h3 = (HANDLE)_beginthread(Thread3, 0, NULL);//�߳�3
	h4 = (HANDLE)_beginthread(Thread4, 0, NULL);//�߳�4
	h5 = (HANDLE)_beginthread(Thread5, 0, NULL);//�߳�5
	h6 = (HANDLE)_beginthread(Thread6, 0, NULL);//�߳�6
	h7 = (HANDLE)_beginthread(Thread7, 0, NULL);//�߳�7

	// ������ѭ��  
	while (!exitFlag) {
		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(GetHWnd(), &mousePos);
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && mousePos.x > 70 && mousePos.x < 70 + 34 && mousePos.y>15 && mousePos.y < 15 + 34) { // �� 'P' ����ͣ/�ָ�
			if (threadsPaused) {
				printf("Resuming threads...\n");
				ResumeThread(h1);
				ResumeThread(h2);
				ResumeThread(h3);
				ResumeThread(h4);
				ResumeThread(h5);
				ResumeThread(h6);
				ResumeThread(h7);
				threadsPaused = 0;
			}
			else {
				printf("Suspending threads...\n");
				SuspendThread(h1);
				SuspendThread(h2);
				SuspendThread(h3);
				SuspendThread(h4);
				SuspendThread(h5);
				SuspendThread(h6);
				SuspendThread(h7);
				threadsPaused = 1;
			}
			Sleep(500); // ��ֹ��������  
		}
		Sleep(100); // ������ѭ��Ƶ��  
	}

	WaitForSingleObject(h1, INFINITE);//�ȴ��߳�1����
	WaitForSingleObject(h2, INFINITE);//�ȴ��߳�2����
	WaitForSingleObject(h3, INFINITE);//�ȴ��߳�3����
	WaitForSingleObject(h4, INFINITE);//�ȴ��߳�4����
	WaitForSingleObject(h5, INFINITE);//�ȴ��߳�5����
	WaitForSingleObject(h6, INFINITE);//�ȴ��߳�6����
	WaitForSingleObject(h7, INFINITE);//�ȴ��߳�7����

	StopBGM();
	cleardevice();
	
	printf("You are killed");
	printf("���߳̽���\n");
	return -1;
}


void Thread1(void* arg)  //�߳�1����Ⱦ�߳�
{
	while (!exitFlag)
	{
		character_move();
	}

}

void Thread2(void* arg)  //�߳�2���������
{
	while (!exitFlag)
	{
		keymove();
	}
}

void Thread3(void* arg)  //�߳�3�����ݴ����߳�
{
	while (!exitFlag)
	{
		ui_process();
		Sleep(10);
	}
}

void Thread4(void* arg)  //�߳�4���ӵ����ݴ����߳�
{
	while (!exitFlag)
	{
		fire();
	}
}

void Thread5(void* arg)  //�߳�5���ӵ���Ⱦ�߳�
{
	while (!exitFlag)
	{
		fire_rander();
	}
}

void Thread6(void* arg)  //�߳�6���������ݴ����߳�
{
	while (!exitFlag)
	{
		enemy_data();
	}
}

void Thread7(void* arg)  //�߳�7�����˶��������߳�
{
	while (!exitFlag)
	{
		enemy_show();
	}
}

// ֹͣ�����߳�ʱ���� exitFlag  
void stop_all_threads() {
	exitFlag = 1;
}