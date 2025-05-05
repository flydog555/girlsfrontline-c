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

int fail_sign = 0;

typedef struct profile
{
	int profile_id;
	char username[20];
	int password;
	struct profile* next;
}PLF;

extern PLF* load_profile();
extern int check_profile(PLF* head, char* username);

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
			printf("ÊäÈëÕË»§\n");
			clicksign = 1;
		}
	}
	else if (x > 530 && x < 530 + 290 && y>330 && y < 330 + 40)//
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("ÊäÈëÃÜÂë\n");
			clicksign = 2;
		}
	}

	//ÕË»§ÎÄ±¾¿ò
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

	//ÃÜÂëÎÄ±¾¿ò
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
	PLF* head = load_profile();
	//¼ì²âµÇÂ¼°´Å¥
	if (mousePos.x > 500 && mousePos.x < 500 + 300 && mousePos.y>430 && mousePos.y < 470)
	{
		DrawButten_Pressed(500, 430, 300, 40, "µÇÂ¼");
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			fail_sign = 0;
			if (check_profile(head, AccountStr) == -1)
			{
				MessageBox(GetHWnd(), _T("Î´ÕÒµ½¸ÃÕË»§"), _T("¾¯¸æ"), MB_ICONWARNING | MB_OK);
				printf("ÕË»§²»´æÔÚ");
			}
			else if (check_profile(head, AccountStr) == atoi(PasswordStr))
			{
				MessageBox(GetHWnd(), _T("ÃÜÂëÕýÈ·"), _T("³É¹¦"), MB_OK);
				printf("³É¹¦µÇÂ¼");
				LoginExitSign = 0;
				fail_sign = 1;
			}
			else if (check_profile(head, AccountStr) != atoi(PasswordStr) && check_profile(head, AccountStr) != -1)
			{
				MessageBox(GetHWnd(), _T("ÃÜÂë´íÎó"), _T("Ê§°Ü"), MB_OK);
				printf("ÃÜÂë´íÎó");
			}
		}
	}
	else
	{
		DrawButten(500, 430, 300, 40, "µÇÂ¼");
	}

	//¼ì²â×¢²á°´Å¥
	if (mousePos.x > 500 && mousePos.x < 500 + 300 && mousePos.y>500 && mousePos.y < 540)
	{
		DrawButten_Pressed(500, 500, 300, 40, "»¹Ã»ÓÐÕË»§£¿×¢²á");
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("×¢²á\n");
			LoginExitSign = -1;
		}
	}
	else
	{
		DrawButten(500, 500, 300, 40, "»¹Ã»ÓÐÕË»§£¿×¢²á");
	}

	//¼ì²âµÇÂ¼ÊäÈë¿ò
	input(mousePos.x, mousePos.y);
}

void draw_init()
{
	//»­±³¾°
	DrawBackground();
	//»­±êÌâ
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(600, 150, "»¶Ó­£¡");
	//»­°´Å¥
	DrawButten(500, 430, 300, 40, "µÇÂ¼");
	DrawButten(500, 500, 300, 40, "»¹Ã»ÓÐÕË»§£¿×¢²á");
	//»­ÊäÈë¿ò
	DrawTextbox(530, 250, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(450, 250, "ÕË»§£º");
	DrawTextbox(530, 330, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(450, 330, "ÃÜÂë£º");
}

int login()
{
	LoginExitSign = 1;

	while (LoginExitSign == 1)
	{
		cleardevice();
		BeginBatchDraw();
		draw_init();
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(30 * 1.0, 0, _T("Î¢ÈíÑÅºÚ"));
		outtextxy(530, 250, AccountStr);
		outtextxy(530, 330, PasswordStr);
		EndBatchDraw();
		MouseDetect();

		Sleep(100);
	}

	return LoginExitSign;
}