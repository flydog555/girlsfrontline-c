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
			printf("ÊäÈëÕË»§\n");
			clicksign_Register = 1;
		}
	}
	else if (x > 530 && x < 530 + 290 && y>420 && y < 420 + 40)//
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("ÊäÈëÃÜÂë\n");
			clicksign_Register = 2;
		}
	}
	else if (x > 590 && x < 590 + 230 && y>250 && y < 250 + 40)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("ÊäÈëÃÜÂë\n");
			clicksign_Register = 3;
		}
	}

	//ÕË»§ÎÄ±¾¿ò
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

	//ÕË»§Ò³Ãæ
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

	//êÇ³ÆÒ³Ãæ
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

	//¼ì²â×¢²á°´Å¥
	if (mousePos.x > 500 && mousePos.x < 500 + 300 && mousePos.y>500 && mousePos.y < 540)
	{
		DrawButten_Pressed(500, 500, 300, 40, "×¢²á");
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("×¢²á\n");
			RegisterExitSign = 0;
			FILE* file, * signfile, * signfilea;
			char filename[20];
			//¶ÁÈ¡ÃüÃû´ÎÊý
			signfile = fopen("sign.txt", "r");
			fscanf(signfile, "%d", &sign_count_Register);
			fclose(signfile);
			sprintf(filename, "file%d.txt", sign_count_Register+1);
			signfilea = fopen("sign.txt", "w");
			fprintf(signfilea, "%d", sign_count_Register + 1);
			fclose(signfilea);
			file = fopen(filename, "w+");//´´½¨ÅäÖÃÎÄ¼þ
			fprintf(file, "accountname:%s\n", AccountStr_Register);//Ð´ÈëÓÃ»§Ãû
			fprintf(file, "password:%s\n", PasswordStr_Register);//Ð´ÈëÃÜÂë
			fprintf(file, "name:%s\n", NameStr_Register);//Ð´ÈëêÇ³Æ
			fprintf(file, "level:1\n");//Ð´Èë³õÊ¼µÈ¼¶
			fprintf(file, "manpower:10000\n");//Ð´Èë³õÊ¼ÈËÁ¦
			fprintf(file, "ammunition:10000\n");//Ð´Èë³õÊ¼µ¯Ò©
			fprintf(file, "pation:10000\n");//Ð´Èë³õÊ¼¿ÚÀÇ
			fprintf(file, "part:10000\n");//Ð´Èë³õÊ¼Áã¼þ
			MessageBox(GetHWnd(), _T("×¢²á³É¹¦£¬ÇëµÇÂ¼"), _T("³É¹¦"), MB_OK);
			fclose(file);
			RegisterExitSign = 0;
		}
	}
	else
	{
		DrawButten(500, 500, 300, 40, "×¢²á");
	}

	//¼ì²âµÇÂ¼ÊäÈë¿ò
	input_Register(mousePos.x, mousePos.y);
}

void draw_init_Register()
{
	//»­±³¾°
	DrawBackground_Register();
	//»­±êÌâ
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(580, 150, "ÕË»§×¢²á");
	//»­°´Å¥
	DrawButten(500, 500, 300, 40, "×¢²á");
	//»­ÊäÈë¿ò
	DrawTextbox(590, 250, 230, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(450, 250, "ÓÎÏ·êÇ³Æ£º");
	DrawTextbox(530, 330, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(450, 330, "ÕË»§£º");
	DrawTextbox(530, 410, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("Î¢ÈíÑÅºÚ"));
	outtextxy(450, 410, "ÃÜÂë£º");
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
		settextstyle(30 * 1.0, 0, _T("Î¢ÈíÑÅºÚ"));
		outtextxy(590, 250, NameStr_Register);
		outtextxy(530, 330, AccountStr_Register);
		outtextxy(530, 420, PasswordStr_Register);
		EndBatchDraw();
		MouseDetect_Register();
		Sleep(100);
	}
	return 0;
}