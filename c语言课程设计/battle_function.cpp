#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h> 
#include <easyx.h>
#include <conio.h>  
#include <stdio.h>  
#include <math.h>
#include <time.h>
#include "battle_main.h"
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

#define BULLET_SPEED 10 // �ӵ��ٶ�
#define ENEMY_SPEED 2 // �����ٶ�
#define MAX_BULLETS 7

extern void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

//����λ��
int x = 640 - 170;
int y = 360 - 170;
int* px = &x;
int* py = &y;
//������״̬�仯��־
int sign = 0;
int* psign = &sign;  //��signָ�뻯
//���׷��
int mx = 100;
int my = 100;
int* pmx = &mx;//����ʵʱx����
int* pmy = &my;//����ʵʱy����
//֡�ʿ���
int anime_fps = 30; // ��������֡��
int start_time_anime = 0;
int frame_time_anime = 0;
//ui��ʾ
int killed_number = 0;  //��ɱ����
char killed_number_display[20];
int lv = 0; //�ȼ�
char lv_display[20];
int live = 3;
//�ӵ�
int bx = 500;
int by = 500;
int* bpy = &bx;//�ӵ���ʵʱλ��y
int* bpx = &by;//�ӵ���ʵʱλ��x
int* bullet_active = &bx;//�ӵ��Ƿ񼤻�
int hit_frame = 10;//�˺���ʾ����֡��
int hit = 0;//�ӵ��Ƿ����,�Ƿ���ʾ�˺�
//����
int ex = 0;
int ey = 0;
int* dpx = &ex;//���˵�ʵʱλ��x
int* dpy = &ey;//���˵�ʵʱλ��y
int* enemy_active = &ex;//�����Ƿ���
int tsign = 0;//��¼�߳�ѭ������
int enemyflame = 0;//�����ƶ�����֡
int enemyflame_die = 0;//������������֡
int enemyflame_attack = 0;//����Ѫ��
int Isleft = 0;//�����ƶ�����

//�ӵ�
typedef struct {
    int x, y;//�ӵ�λ��  
    int targetX, targetY;//Ŀ��λ��  
    int active;//�ӵ��Ƿ��Ծ  
} Bullet;

Bullet bullets[MAX_BULLETS];  //�ӵ�����

//����
typedef struct {
    int x, y; // ����λ��  
    int targetX, targetY; // Ŀ��λ��  
    int active; // �����Ƿ��Ծ  
    int health;
} enemy;

//����֡����
extern const char* frames_run_left[];
extern const char* frames_run_right[];
extern int Frames_Count_Run;

extern const char* frames_wait_left[];
extern const char* frames_wait_right[];
extern int Frames_Count_Wait;

extern const char* frames_fire_left[];
extern const char* frames_fire_right[];
extern int Frames_Count_Fire;

extern const char* golyat_move_left[];
extern const char* golyat_move_right[];
extern int Frames_Count_Golyat_Move;

extern const char* golyat_die_left[];
extern const char* golyat_die_right[];
extern int Frames_Count_Golyat_Die;

extern const char* golyat_attack_left[];
extern const char* golyat_attack_right[];
extern int Frames_Count_Golyat_Attack;


//�Զ��庯��������
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
void playAnimation(const char* frames[], int frameCount, int a);
void drawProgressBar(int x, int y, int progress, int total);
void ui_process();
void fire();
void enemy_data();
void enemy_show();


IMAGE background;
IMAGE bulletimg;
IMAGE enemyimg;
IMAGE heart;

//�Զ��庯���Ķ���
void playAnimation(const char* frames[], int frameCount, int a)  //����Ⱦ����
{
    IMAGE img;
    settextstyle(25, 0, "����");
    for (int i = 0; i < frameCount; i++)
    {
        cleardevice(); // �����Ļ
        start_time_anime = clock();
        if (*psign != a)
        {
            break;
        }
        BeginBatchDraw();
        //���ر���
        putimage(0, 0, &background);
        //����ui
        drawProgressBar(240, 10, killed_number * 100 - lv * 1000, 1000);
        setbkmode(TRANSPARENT);
        outtextxy(1020, 50, killed_number_display);
        outtextxy(250, 11, "Lv.");
        outtextxy(285, 11, lv_display);
        for (int i = 0; i < live; i++)
        {
            transparentimage3(NULL, 240 + i * 30, 40, &heart);
        }
        //��������� 
        setcolor(WHITE);
        setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
        circle(*pmx, *pmy, 20);
        setlinecolor(WHITE);
        setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
        line(*pmx, *pmy, *px + 170, *py + 170);
        //�����ӵ�
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (bullets[i].active)
            {
                transparentimage3(NULL, bullets[i].x, bullets[i].y, &bulletimg);
            }

        }
        //���ص���
        if (*enemy_active == 1)
        {
            if (Isleft == 1)
            {
                loadimage(&enemyimg, golyat_move_left[enemyflame]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
            else
            {
                loadimage(&enemyimg, golyat_move_right[enemyflame]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
        }
        else if (*enemy_active == 0)
        {
            if (Isleft == 1)
            {
                loadimage(&enemyimg, golyat_die_left[enemyflame_die]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
            else
            {
                loadimage(&enemyimg, golyat_die_right[enemyflame_die]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
        }
        else if (*enemy_active == 2)
        {
            if (Isleft == 1)
            {
                loadimage(&enemyimg, golyat_attack_left[enemyflame_attack]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
            else
            {
                loadimage(&enemyimg, golyat_attack_right[enemyflame_attack]);
                transparentimage3(NULL, *dpx, *dpy, &enemyimg);
            }
        }
        //�����˺�
        if (hit == 1 && hit_frame != 0)
        {
            settextstyle(40, 0, "����");
            settextcolor(YELLOW);
            outtextxy(*dpx + 100, *dpy + 100, "10");

            settextstyle(25, 0, "����");
            settextcolor(WHITE);
            hit_frame--;
        }
        if (hit_frame == 0)
        {
            hit = 0;
            hit_frame = 10;
        }
        //���ص�ǰ����֡ͼ��
        loadimage(&img, frames[i]);
        transparentimage3(NULL, *px, *py, &img);
        EndBatchDraw();
        frame_time_anime = clock() - start_time_anime;
        if (i != frameCount - 1)
        {
            if (anime_fps - frame_time_anime > 0)
            {
                Sleep(anime_fps - frame_time_anime);

            }
        }
    }
}

void character_move()
{
    if (*psign == 0)
    {
        playAnimation(frames_wait_left, Frames_Count_Wait, *psign);
    }
    if (*psign == 10)
    {
        playAnimation(frames_wait_right, Frames_Count_Wait, *psign);
    }
    if (*psign == 1)
    {
        playAnimation(frames_run_right, Frames_Count_Run, *psign);
    }
    if (*psign == 2)
    {
        playAnimation(frames_run_left, Frames_Count_Run, *psign);
    }
    if (*psign == 3)
    {
        playAnimation(frames_fire_left, Frames_Count_Fire, *psign);
    }
    if (*psign == 4)
    {
        playAnimation(frames_fire_right, Frames_Count_Fire, *psign);
    }
}

void keymove()
{

    //������״̬ 
    if (!_kbhit())
    {
        if (*pmx < *px) // ����Ƿ������С�����
        {
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
            {
                *psign = 3;
            }
            else
            {
                *psign = 0;
            }
        }
        if (*pmx > *px) // ����Ƿ������С���Ҳ�
        {
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
            {
                *psign = 4;
            }
            else
            {
                *psign = 10;
            }
        }
    }

    if (GetAsyncKeyState('W') < 0) // ʹ���ַ���������VK_W 
    {
        *py -= 10;
        *psign = 1;
    }
    if (GetAsyncKeyState('S') < 0) // ʹ���ַ���������VK_S  
    {
        *py += 10;
        *psign = 2;
    }
    if (GetAsyncKeyState('A') < 0) // ʹ���ַ���������VK_A  
    {
        *px -= 10;
        *psign = 2;
    }
    if (GetAsyncKeyState('D') < 0) // ʹ���ַ���������VK_D  
    {
        *px += 10;
        *psign = 1;
    }

    // �߽���
    if (*px < -100)
    {
        *px = -100;
    }

    if (*px > 1280 - 260)
    {
        *px = 1280 - 260;
    }

    if (*py < -100)
    {
        *py = -100;
    }

    if (*py > 720 - 270)
    {
        *py = 720 - 270; // ����֡�߶�Ϊ100
    }

    Sleep(50); // ���Ƽ���ˢ��Ƶ��
}

void drawProgressBar(int x, int y, int progress, int total)
{
    // ����������Ŀ��  
    int barWidth = 800; // ���������ܿ��  
    int barHeight = 25; // �������ĸ߶�  
    int filledWidth = (progress * barWidth) / total; // �����Ŀ��  

    // ���������Ľ��Ȳ���
    setfillcolor(RGB(13, 140, 251));
    solidrectangle(x, y, x + filledWidth, y + barHeight); // ���ƽ����� 
    // ���ý������ı�����ɫ  
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
    rectangle(x, y, x + barWidth, y + barHeight); // ���Ʊ�����  
}

void ui_process()
{
    if (tsign == 0)//����һ��ѭ��ִ��
    {
        //���ػ���ͼƬ��Դ
        loadimage(&background, "./resource/image/bg.jpg", 1280, 720);
        loadimage(&bulletimg, "./resource/icon/bullet.png", 21, 21);//�����ӵ�ͼƬ
        loadimage(&heart, "./resource/icon/heart.png", 32, 32);//������ͼƬ
    }
    if (killed_number * 100 - lv * 1000 >= 1000)
    {
        lv++;
    }
    //�ַ�ת��
    sprintf(killed_number_display, "%d", killed_number * 100);
    sprintf(lv_display, "%d", lv);
    //���׷��
    POINT mousePos;
    GetCursorPos(&mousePos);
    ScreenToClient(GetHWnd(), &mousePos);
    *pmx = mousePos.x;
    *pmy = mousePos.y;
    tsign++;
}

//�ӵ�����

void fire_move(Bullet* bullet, int heroX, int heroY, int targetX, int targetY) {
    bullet->x = heroX;
    bullet->y = heroY;
    bullet->targetX = targetX;
    bullet->targetY = targetY;
    bullet->active = 1; // �����ӵ�  
}

void updateBullet(Bullet* bullet) {
    if (bullet->active) {
        // �����ӵ��ķ���  
        int dx = bullet->targetX - bullet->x;
        int dy = bullet->targetY - bullet->y;
        double distance = sqrt(dx * dx + dy * dy);

        // ����ӵ�����Ŀ��λ�ã�ͣ���ӵ�  
        if (distance < BULLET_SPEED) {
            bullet->active = 0;
            bullet->x = -500;
            bullet->y = -500;
            return;
        }
        // �����ӵ�λ��  
        bullet->x += (int)(BULLET_SPEED * (dx / distance));
        bullet->y += (int)(BULLET_SPEED * (dy / distance));
    }
}

void fire() {
    while (!exitFlag)
    {
        // ��������������ӵ�  
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            for (int i = 0; i < MAX_BULLETS; i++)
            {
                if (!bullets[i].active) // ֻ�����ӵ�δ����ʱ���ܷ���
                {
                    fire_move(&bullets[i], *px + 170, *py + 170, *pmx, *pmy);

                    break;  //�Ƿ񵥷�����
                }

            }

        }
        Sleep(200);
    }
}

void fire_rander()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        updateBullet(&bullets[i]);
    }
    Sleep(1);
}

//����ˢ�¼�Ѱ·
void enemy_move(enemy* enemy, int heroX, int heroY, int targetX, int targetY)
{
    enemy->x = heroX;
    enemy->y = heroY;
    enemy->targetX = targetX;
    enemy->targetY = targetY;
    enemy->active = 1; // �����Ƿ���  
}

void updateEnemy(enemy* enemy) {
    if (enemy->active) {
        // �������Ѱ·�ķ���  
        int dx = enemy->targetX - enemy->x;
        int dy = enemy->targetY - enemy->y;
        double distance = sqrt(dx * dx + dy * dy);
        // ������˽Ӵ�������  
        if (distance - 100 < ENEMY_SPEED) {
            enemy->active = 2;    /////////////////////

            for (int i = 0; i < Frames_Count_Golyat_Attack; i++)
            {
                start_time_anime = clock();
                enemyflame_attack = i;
                frame_time_anime = clock() - start_time_anime;
                if (i != Frames_Count_Golyat_Attack - 1)
                {
                    if (anime_fps - frame_time_anime > 0)
                    {
                        Sleep(anime_fps - frame_time_anime);
                    }
                }
            }
            live--;
            if (live == 0)
            {
                exitFlag = 1;
            }
            return;
        }

        //�ӵ����е���
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (bullets[i].x >= *dpx + 50 && bullets[i].x <= *dpx + 300 && bullets[i].y >= *dpy + 50 && bullets[i].y <= *dpy + 300)
            {
                enemy->health -= 10;
                bullets[i].active = 0;
                bullets[i].x = -500;
                bullets[i].y = -500;
                hit = 1;
                //���������������
                if (enemy->health == 0)
                {
                    enemy->active = 0;
                    killed_number++;
                    for (int i = 0; i < Frames_Count_Golyat_Die; i++)
                    {
                        start_time_anime = clock();
                        enemyflame_die = i;
                        frame_time_anime = clock() - start_time_anime;
                        if (i != Frames_Count_Golyat_Die - 1)
                        {
                            if (anime_fps - frame_time_anime > 0)
                            {
                                Sleep(anime_fps - frame_time_anime);
                            }
                        }
                    }
                }
            }
        }

        // ���µ���λ��  
        enemy->x += (int)(ENEMY_SPEED * (dx / distance));
        enemy->y += (int)(ENEMY_SPEED * (dy / distance));
        //�жϵ��������ƶ����������ƶ�
        if ((int)(ENEMY_SPEED * (dx / distance)) > 0)
        {
            Isleft = 0;
        }
        else
        {
            Isleft = 1;
        }
        dpx = &enemy->x;
        dpy = &enemy->y;
        enemy_active = &enemy->active;
    }
}


void enemy_data()
{
    enemy enemyInstance = { 0 };
    enemyInstance.health = 50;
    //��������λ�����
    *dpx = 0;
    *dpy = 0;
    int randomx1 = rand() % 101;
    int randomx2 = rand() % 101 + 840;
    int randomchoosex = rand() % 2;
    if (randomchoosex == 0)
    {
        *dpx = randomx1;
    }
    else
    {
        *dpx = randomx2;
    }
    int randomy1 = rand() % 101;
    int randomy2 = rand() % 101 + 280;
    int randomchoosey = rand() % 2;
    if (randomchoosey == 0)
    {
        *dpy = randomy1;
    }
    else
    {
        *dpy = randomy2;
    }
    while (!exitFlag)
    {
        enemy_move(&enemyInstance, *dpx, *dpy, *px, *py);
        updateEnemy(&enemyInstance);
        if (!enemyInstance.active)
        {
            break;
        }
        Sleep(20);
    }
}

void enemy_show()
{
    if (enemy_active)
    {
        for (int i = 0; i < Frames_Count_Golyat_Move; i++)
        {
            start_time_anime = clock();
            enemyflame = i;
            frame_time_anime = clock() - start_time_anime;
            if (i != Frames_Count_Golyat_Move - 1)
            {
                if (anime_fps - frame_time_anime > 0)
                {
                    Sleep(anime_fps - frame_time_anime);
                }
            }
        }
    }
}