#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h>
#include <easyx.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <conio.h>

using namespace std;

extern void DrawButten(int x, int y, int w, int h, const char* text);
extern void DrawButten_Pressed(int x, int y, int w, int h, const char* text);
extern void DrawTextbox(int x, int y, int w, int h, const char* text);

int clicksign_Register = 0;
int clicksign1_Register = 0;

char AccountChar_Register;
char AccountStr_Register[100];
int AccountCounter_Register = 0;

char PasswordChar_Register;
char PasswordStr_Register[100];
int PasswordCounter_Register = 0;

char NameChar_Register;
char NameStr_Register[100];
int NameCounter_Register;

int sign_count_Register = 0;
int RegisterExitSign = 1;

void DrawBackground_Register()
{
	IMAGE bg;
	loadimage(&bg, _T("./resource/image/loginbg.jpg"), 1280, 720);
	putimage(0, 0, &bg);
}

void input_Register(int x, int y)
{

	if (x > 530 && x < 530 + 290 && y>330 && y < 330 + 40)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("�����˻�\n");
			clicksign_Register = 1;
		}
	}
	else if (x > 530 && x < 530 + 290 && y>420 && y < 420 + 40)//
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("��������\n");
			clicksign_Register = 2;
		}
	}
	else if (x > 590 && x < 590 + 230 && y>250 && y < 250 + 40)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("��������\n");
			clicksign_Register = 3;
		}
	}

	//�˻��ı���
	if (clicksign_Register == 1)
	{

		if (_kbhit)
		{
			AccountChar_Register = _getch();
			if (AccountChar_Register == '\b' || AccountChar_Register == 8)
			{
				if (AccountCounter_Register > 0)
				{
					AccountCounter_Register--;
					AccountStr_Register[AccountCounter_Register] = '\0';
				}
			}
			else if (AccountChar_Register == 27)
			{
				clicksign_Register = 0;
			}
			else
			{
				AccountStr_Register[AccountCounter_Register] = AccountChar_Register;
				AccountCounter_Register++;
				AccountStr_Register[AccountCounter_Register] = '\0';
			}
		}
	}

	//�˻�ҳ��
	if (clicksign_Register == 2)
	{

		if (_kbhit)
		{
			PasswordChar_Register = _getch();
			if (PasswordChar_Register == '\b' || PasswordChar_Register == 8)
			{
				if (PasswordCounter_Register > 0)
				{
					PasswordCounter_Register--;
					PasswordStr_Register[PasswordCounter_Register] = '\0';
				}
			}
			else if (PasswordChar_Register == 27)
			{
				clicksign_Register = 0;
			}
			else
			{
				PasswordStr_Register[PasswordCounter_Register] = PasswordChar_Register;
				PasswordCounter_Register++;
				PasswordStr_Register[PasswordCounter_Register] = '\0';
			}
		}
	}

	//�ǳ�ҳ��
	if (clicksign_Register == 3)
	{

		if (_kbhit)
		{
			NameChar_Register = _getch();
			if (NameChar_Register == '\b' || NameChar_Register == 8)
			{
				if (NameCounter_Register > 0)
				{
					NameCounter_Register--;
					NameStr_Register[NameCounter_Register] = '\0';
				}
			}
			else if (NameChar_Register == 27)
			{
				clicksign_Register = 0;
			}
			else
			{
				NameStr_Register[NameCounter_Register] = NameChar_Register;
				NameCounter_Register++;
				NameStr_Register[NameCounter_Register] = '\0';
			}
		}
	}
}

void MouseDetect_Register()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(GetHWnd(), &mousePos);

	//���ע�ᰴť
	if (mousePos.x > 500 && mousePos.x < 500 + 300 && mousePos.y>500 && mousePos.y < 540)
	{
		DrawButten_Pressed(500, 500, 300, 40, "ע��");
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("ע��\n");
			RegisterExitSign = 0;
			FILE* file, * signfile, * signfilea;
			char filename[20];
			//��ȡ��������
			signfile = fopen("sign.txt", "r");
			fscanf(signfile, "%d", &sign_count_Register);
			fclose(signfile);
			sprintf(filename, "file%d.txt", sign_count_Register+1);
			signfilea = fopen("sign.txt", "w");
			fprintf(signfilea, "%d", sign_count_Register + 1);
			fclose(signfilea);
			file = fopen(filename, "w+");//���������ļ�
			fprintf(file, "accountname:%s\n", AccountStr_Register);//д���û���
			fprintf(file, "password:%s\n", PasswordStr_Register);//д������
			fprintf(file, "name:%s\n", NameStr_Register);//д���ǳ�
			fprintf(file, "level:1\n");//д���ʼ�ȼ�
			fprintf(file, "manpower:10000\n");//д���ʼ����
			fprintf(file, "ammunition:10000\n");//д���ʼ��ҩ
			fprintf(file, "pation:10000\n");//д���ʼ����
			fprintf(file, "part:10000\n");//д���ʼ���
			MessageBox(GetHWnd(), _T("ע��ɹ������¼"), _T("�ɹ�"), MB_OK);
			fclose(file);
			RegisterExitSign = 0;
		}
	}
	else
	{
		DrawButten(500, 500, 300, 40, "ע��");
	}

	//����¼�����
	input_Register(mousePos.x, mousePos.y);
}

void draw_init_Register()
{
	//������
	DrawBackground_Register();
	//������
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("΢���ź�"));
	outtextxy(580, 150, "�˻�ע��");
	//����ť
	DrawButten(500, 500, 300, 40, "ע��");
	//�������
	DrawTextbox(590, 250, 230, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("΢���ź�"));
	outtextxy(450, 250, "��Ϸ�ǳƣ�");
	DrawTextbox(530, 330, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("΢���ź�"));
	outtextxy(450, 330, "�˻���");
	DrawTextbox(530, 410, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("΢���ź�"));
	outtextxy(450, 410, "���룺");
}

int registerf()
{
	while (RegisterExitSign==1)
	{
		cleardevice();
		BeginBatchDraw();
		draw_init_Register();
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30 * 1.0, 0, _T("΢���ź�"));
		outtextxy(590, 250, NameStr_Register);
		outtextxy(530, 330, AccountStr_Register);
		outtextxy(530, 420, PasswordStr_Register);
		EndBatchDraw();
		MouseDetect_Register();
		Sleep(100);
	}
	return 0;
}