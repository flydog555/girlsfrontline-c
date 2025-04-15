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
			printf("输入账户\n");
			clicksign = 1;
		}
	}
	else if (x > 530 && x < 530 + 290 && y>330 && y < 330 + 40)//
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("输入密码\n");
			clicksign = 2;
		}
	}

	//账户文本框
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

	//账户页面
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
	//检测登录按钮
	if (mousePos.x > 500 && mousePos.x < 500 + 300 && mousePos.y>430 && mousePos.y < 470)
	{
		DrawButten_Pressed(500, 430, 300, 40, "登录");
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("登录\n");
			int filesign;
			//读取先导文件，确定一共有多少个账户
			FILE* signfile = fopen("sign.txt", "r");
			fscanf(signfile, "%d", &filesign);
			fclose(signfile);
			//遍历所有文件，判断输入的账户是否存在
			FILE* file;
			char filename[20];
			char temp[100];//文件中读取的用户名

			int i;
			for (i = 1; i <= filesign; i++)
			{
				sprintf(filename, "file%d.txt", i);
				file = fopen(filename, "r");
				fgets(temp, sizeof(temp), file);
				char* colon = strchr(temp, ':');
				if (colon != NULL)
				{
					char* value = colon + 1; // 指向冒号后一个字符  
					// 去掉换行符  
					value[strcspn(value, "\n")] = '\0'; // 替换换行符为结束符
					string Accout(AccountStr);
					string readname(value);//将读取到的value从char格式转换为string格式
					if (Accout == readname)
					{
						Profile_Number = i;
						int tempcode;//从文件读取的密码
						fscanf(file, "password:%d", &tempcode);
						string Password(PasswordStr);
						string readcode = to_string(tempcode);//将读取到的int类型密码转换为wstring类型
						if (readcode == Password)
						{
							MessageBox(GetHWnd(), _T("密码正确"), _T("成功"), MB_OK);
							fclose(file);
							printf("成功登录");
							LoginExitSign = 0;
						}
						else if (readcode != Password)
						{
							fclose(file);
							MessageBox(GetHWnd(), _T("密码错误"), _T("警告"), MB_ICONWARNING | MB_OK);
							printf("\n失败1");
						}

					}
					else if (Accout != readname)
					{
						fclose(file);
						MessageBox(GetHWnd(), _T("未找到该账户"), _T("警告"), MB_ICONWARNING | MB_OK);
						printf("\n失败2");

					}
				}

			}
		}
	}
	else
	{
		DrawButten(500, 430, 300, 40, "登录");
	}

	//检测注册按钮
	if (mousePos.x > 500 && mousePos.x < 500 + 300 && mousePos.y>500 && mousePos.y < 540)
	{
		DrawButten_Pressed(500, 500, 300, 40, "还没有账户？注册");
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			printf("注册\n");
			LoginExitSign = -1;
		}
	}
	else
	{
		DrawButten(500, 500, 300, 40, "还没有账户？注册");
	}

	//检测登录输入框
	input(mousePos.x, mousePos.y);
}

void draw_init()
{
	//画背景
	DrawBackground();
	//画标题
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("微软雅黑"));
	outtextxy(600, 150, "欢迎！");
	//画按钮
	DrawButten(500, 430, 300, 40, "登录");
	DrawButten(500, 500, 300, 40, "还没有账户？注册");
	//画输入框
	DrawTextbox(530, 250, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("微软雅黑"));
	outtextxy(450, 250, "账户：");
	DrawTextbox(530, 330, 290, 40, "");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T("微软雅黑"));
	outtextxy(450, 330, "密码：");
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
		settextstyle(30 * 1.0, 0, _T("微软雅黑"));
		outtextxy(530, 250, AccountStr);
		outtextxy(530, 330, PasswordStr);
		EndBatchDraw();
		MouseDetect();
		Sleep(100);
	}
	return LoginExitSign;
}