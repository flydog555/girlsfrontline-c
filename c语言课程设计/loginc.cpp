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

extern int Profile_Number;

int LoginExitSign = 1;
int clicksign = 0;
int clicksign1 = 0;

char AccountChar;
char AccountStr[100];
int AccountCounter = 0;

char PasswordChar;
char PasswordStr[100];
int PasswordCounter = 0;

void DrawBackground()
{
	IMAGE bg;
	loadimage(&bg, _T("./resource/image/loginbg.jpg"), 1280, 720);
	putimage(0, 0, &bg);
}

void input(int x, int y)
{

	if (x > 530 && x < 530 + 290 && y>250 && y < 290)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("�����˻�\n");
			clicksign = 1;
		}
	}
	else if (x > 530 && x < 530 + 290 && y>330 && y < 330 + 40)//
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("��������\n");
			clicksign = 2;
		}
	}

	//�˻��ı���
	if (clicksign == 1)
	{

		if (_kbhit)
		{
			AccountChar = _getch();
			if (AccountChar == '\b' || AccountChar == 8)
			{
				if (AccountCounter > 0)
				{
					AccountCounter--;
					AccountStr[AccountCounter] = '\0';
				}
			}
			else if (AccountChar == 27)
			{
				clicksign = 0;
			}
			else
			{
				AccountStr[AccountCounter] = AccountChar;
				AccountCounter++;
				AccountStr[AccountCounter] = '\0';
			}
		}
	}

	//�˻�ҳ��
	if (clicksign == 2)
	{

		if (_kbhit)
		{
			PasswordChar = _getch();
			if (PasswordChar == '\b' || PasswordChar == 8)
			{
				if (PasswordCounter > 0)
				{
					PasswordCounter--;
					PasswordStr[PasswordCounter] = '\0';
				}
			}
			else if (PasswordChar == 27)
			{
				clicksign = 0;
			}
			else
			{
				PasswordStr[PasswordCounter] = PasswordChar;
				PasswordCounter++;
				PasswordStr[PasswordCounter] = '\0';
			}
		}
	}
}

void MouseDetect()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(GetHWnd(), &mousePos);
	//����¼��ť
	if (mousePos.x > 500 && mousePos.x < 500 + 300 && mousePos.y>430 && mousePos.y < 470)
	{
		DrawButten_Pressed(500, 430, 300, 40, "��¼");
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("��¼\n");
			int filesign;
			//��ȡ�ȵ��ļ���ȷ��һ���ж��ٸ��˻�
			FILE* signfile = fopen("sign.txt", "r");
			fscanf(signfile, "%d", &filesign);
			fclose(signfile);
			//���������ļ����ж�������˻��Ƿ����
			FILE* file;
			char filename[20];
			char temp[100];//�ļ��ж�ȡ���û���

			int i;
			for (i = 1; i <= filesign; i++)
			{
				sprintf(filename, "file%d.txt", i);
				file = fopen(filename, "r");
				fgets(temp, sizeof(temp), file);
				char* colon = strchr(temp, ':');
				if (colon != NULL)
				{
					char* value = colon + 1; // ָ��ð�ź�һ���ַ�  
					// ȥ�����з�  
					value[strcspn(value, "\n")] = '\0'; // �滻���з�Ϊ������
					string Accout(AccountStr);
					string readname(value);//����ȡ����value��char��ʽת��Ϊstring��ʽ
					if (Accout == readname)
					{
						Profile_Number = i;
						int tempcode;//���ļ���ȡ������
						fscanf(file, "password:%d", &tempcode);
						string Password(PasswordStr);
						string readcode = to_string(tempcode);//����ȡ����int��������ת��Ϊwstring����
						if (readcode == Password)
						{
							MessageBox(GetHWnd(), _T("������ȷ"), _T("�ɹ�"), MB_OK);
							fclose(file);
							printf("�ɹ���¼");
							LoginExitSign = 0;
						}
						else if (readcode != Password)
						{
							fclose(file);
							MessageBox(GetHWnd(), _T("�������"), _T("����"), MB_ICONWARNING | MB_OK);
							printf("\nʧ��1");
						}

					}
					else if (Accout != readname)
					{
						fclose(file);
						MessageBox(GetHWnd(), _T("δ�ҵ����˻�"), _T("����"), MB_ICONWARNING | MB_OK);
						printf("\nʧ��2");

					}
				}

			}
		}
	}
	else
	{
		DrawButten(500, 430, 300, 40, "��¼");
	}

	//���ע�ᰴť
	if (mousePos.x > 500 && mousePos.x < 500 + 300 && mousePos.y>500 && mousePos.y < 540)
	{
		DrawButten_Pressed(500, 500, 300, 40, "��û���˻���ע��");
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("ע��\n");
			LoginExitSign = -1;
		}
	}
	else
	{
		DrawButten(500, 500, 300, 40, "��û���˻���ע��");
	}

	//����¼�����
	input(mousePos.x, mousePos.y);
}

void draw_init()
{
	//������
	DrawBackground();
	//������
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("΢���ź�"));
	outtextxy(600, 150, "��ӭ��");
	//����ť
	DrawButten(500, 430, 300, 40, "��¼");
	DrawButten(500, 500, 300, 40, "��û���˻���ע��");
	//�������
	DrawTextbox(530, 250, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("΢���ź�"));
	outtextxy(450, 250, "�˻���");
	DrawTextbox(530, 330, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("΢���ź�"));
	outtextxy(450, 330, "���룺");
}

int login()
{
	LoginExitSign = 1;
	while (LoginExitSign==1)
	{
		cleardevice();
		BeginBatchDraw();
		draw_init();
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30 * 1.0, 0, _T("΢���ź�"));
		outtextxy(530, 250, AccountStr);
		outtextxy(530, 330, PasswordStr);
		EndBatchDraw();
		MouseDetect();
		Sleep(100);
	}
	return LoginExitSign;
}