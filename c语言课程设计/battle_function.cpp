#define _CRT_SECURE_NO_WARNINGS 1
#include <graphics.h> 
#include <easyx.h>
#include <conio.h>  
#include <stdio.h>  
#include <string.h>
#include <math.h>
#include <time.h>
#include <io.h>         
#include <windows.h>
#include <fcntl.h>  
#include "battle_main.h"
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")

#define ENEMY_SPEED 2 // 敌人速度
#define MAX_BULLETS 7

extern int BULLET_DAMGE;// 子弹伤害
extern int BULLET_SPEED; // 子弹速度
extern int BULLET_INTERVAL; // 子弹间隔
extern int RATIO;
char bullet_damge_display[2];

extern int pause_sign;
extern int level_up;
extern char dollname[10];

extern void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

//人物位置
int x = 640 - 170;
int y = 360 - 170;
int* px = &x;
int* py = &y;
//检测键鼠状态变化标志
int sign = 0;
int* psign = &sign;  //将sign指针化
//鼠标追踪
int mx = 100;
int my = 100;
int* pmx = &mx;//鼠标的实时x坐标
int* pmy = &my;//鼠标的实时y坐标
//帧率控制
int anime_fps = 30; // 动画播放帧率
int start_time_anime = 0;
int frame_time_anime = 0;
//ui显示
int killed_number = 0;  //击杀计数
char killed_number_display[20];
int lv = 0; //等级
char lv_display[20];
int live = 3;
//子弹
int bx = 500;
int by = 500;
int* bpy = &bx;//子弹的实时位置y
int* bpx = &by;//子弹的实时位置x
int* bullet_active = &bx;//子弹是否激活
int hit_frame = 10;//伤害显示的总帧数
int hit = 0;//子弹是否击中,是否显示伤害
//敌人
int ex = 0;
int ey = 0;
int* dpx = &ex;//敌人的实时位置x
int* dpy = &ey;//敌人的实时位置y
int* enemy_active = &ex;//敌人是否存活
int tsign = 0;//记录线程循环次数
int enemyflame = 0;//敌人移动动画帧
int enemyflame_die = 0;//敌人死亡动画帧
int enemyflame_attack = 0;//敌人血量
int Isleft = 0;//敌人移动方向
int die_x = 0;
int die_y = 0;


//暂停ui
extern int level_attack;
extern int level_speed;
extern int level_health;
extern int level_gain;
int level_max = 3;
char level_buffer[5];


//子弹
typedef struct {
    int x, y;//子弹位置  
    int targetX, targetY;//目标位置  
    int active;//子弹是否活跃  
} Bullet;

Bullet bullets[MAX_BULLETS];  //子弹数组

//敌人
typedef struct {
    int x, y; // 敌人位置  
    int targetX, targetY; // 目标位置  
    int active; // 敌人是否活跃  
    int health;
} enemy;

enemy enemyInstance = { 0 };

//动画帧加载
extern const char* golyat_move_left[];
extern const char* golyat_move_right[];
extern int Frames_Count_Golyat_Move;

extern const char* golyat_die_left[];
extern const char* golyat_die_right[];
extern int Frames_Count_Golyat_Die;

extern const char* golyat_attack_left[];
extern const char* golyat_attack_right[];
extern int Frames_Count_Golyat_Attack;


//自定义函数的声明
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
void playAnimationd(bool isleft, const char status[], char name[], int frameCount, int a);
void drawProgressBar(int x, int y, int progress, int total);
void ui_process();
void fire();
void enemy_data();
void enemy_show();


IMAGE background;
IMAGE bulletimg;
IMAGE enemyimg;
IMAGE heart;
IMAGE pause;
IMAGE pause_bg;
IMAGE icon1;
IMAGE icon2;
IMAGE icon3;
IMAGE icon4;
IMAGE icon_null;
IMAGE back;

//自定义函数的定义
int calculate_frame_count(char name[], const char status[])
{
    printf("%s\n", name);
    printf("%d\n", strcmp(name, "RPK16"));
    printf("\n");
    if (strcmp(name, "HK416")==0)
    {
        if (strcmp(status, "wait")==0)
        {
            return 54;
        }
        else if (strcmp(status, "run")==0)
        {
            return 24;
        }
        else if (strcmp(status, "fire")==0)
        {
            return 34;
        }
    }
    else if (strcmp(name, "RPK16")==0)
    {
        if (strcmp(status, "wait")==0)
        {
            return 54;
        }
        else if (strcmp(status, "run")==0)
        {
            return 24;
        }
        else if (strcmp(status, "fire")==0)
        {
            printf("FIRE\n");
            return 14;
        }
    }
    else if (strcmp(name, "RO635")==0)
    {
        if (strcmp(status, "wait")==0)
        {
            return 54;
        }
        else if (strcmp(status, "run")==0)
        {
            return 24;
        }
        else if (strcmp(status, "fire")==0)
        {
            return 14;
        }
    }
    else if (strcmp(name, "AA12")==0)
    {
        if (strcmp(status, "wait")==0)
        {
            return 54;
        }
        else if (strcmp(status, "run")==0)
        {
            return 24;
        }
        else if (strcmp(status, "fire")==0)
        {
            return 40;
        }
    }
}

void playAnimationd(bool isleft, const char status[], char name[], int frameCount, int a)
{
    IMAGE img;
    settextstyle(25, 0, "黑体");
    char IsLeft[6];
    if (isleft)
    {
        strcpy(IsLeft, "left");
    }
    else
    {
        strcpy(IsLeft, "right");
    }

    for (int i = 0; i < frameCount; i++)
    {
        cleardevice(); // 清除屏幕
        start_time_anime = clock();
        if (*psign != a)
        {
            break;
        }
        BeginBatchDraw();
        //加载背景
        putimage(0, 0, &background);
        //加载ui
        drawProgressBar(240, 10, killed_number * RATIO - lv * 1000, 1000);
        setbkmode(TRANSPARENT);
        outtextxy(1020, 50, killed_number_display);
        outtextxy(250, 11, "Lv.");
        outtextxy(285, 11, lv_display);
        for (int i = 0; i < live; i++)
        {
            transparentimage3(NULL, 240 + i * 30, 40, &heart);
        }
        transparentimage3(NULL, 110, 15, &pause);
        transparentimage3(NULL, 50, 15, &back);
        //加载射击线 
        setcolor(WHITE);
        setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
        circle(*pmx, *pmy, 20);
        setlinecolor(WHITE);
        setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
        line(*pmx, *pmy, *px + 170, *py + 170);
        //加载子弹
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (bullets[i].active)
            {
                transparentimage3(NULL, bullets[i].x, bullets[i].y, &bulletimg);
            }

        }
        //加载敌人
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
                transparentimage3(NULL, die_x, die_y, &enemyimg);
            }
            else
            {
                loadimage(&enemyimg, golyat_die_right[enemyflame_die]);
                transparentimage3(NULL, die_x, die_y, &enemyimg);
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
        //加载伤害
        if (hit == 1 && hit_frame != 0)
        {
            settextstyle(40, 0, "黑体");
            settextcolor(YELLOW);
            sprintf(bullet_damge_display, "%d", BULLET_DAMGE);
            if (*enemy_active == 1)
            {
                outtextxy(*dpx + 100, *dpy + 100, bullet_damge_display);
            }
            else if (*enemy_active == 0)
            {
                outtextxy(die_x + 100, die_y + 100, bullet_damge_display);
            }
            
            settextstyle(25, 0, "黑体");
            settextcolor(WHITE);
            hit_frame--;
        }
        if (hit_frame == 0)
        {
            hit = 0;
            hit_frame = 10;
        }
        //加载当前人物帧图像
        char filename[50]; // 足够容纳最大字符串的大小  
        snprintf(filename, sizeof(filename), "./resource/character/%s/%s_%s/(%d).png", name, status, IsLeft, i + 1);
        loadimage(&img, _strdup(filename));
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
        playAnimationd(1,"wait",dollname, calculate_frame_count(dollname,"wait"), *psign);
        //playAnimationd(1,"wait",name, Frames_Count_Wait, *psign);
    }
    if (*psign == 10)
    {
        playAnimationd(0, "wait", dollname, calculate_frame_count(dollname, "wait"), *psign);
        //playAnimationd(0, "wait", name, Frames_Count_Wait, *psign);
    }
    if (*psign == 1)
    {
        playAnimationd(0, "run", dollname, calculate_frame_count(dollname, "run"), *psign);
        //playAnimationd(0, "run", name, Frames_Count_Run, *psign);
    }
    if (*psign == 2)
    {
        playAnimationd(1, "run", dollname, calculate_frame_count(dollname, "run"), *psign);
        //playAnimationd(1, "run", name, Frames_Count_Run, *psign);
    }
    if (*psign == 3)
    {
        playAnimationd(1, "fire", dollname, calculate_frame_count(dollname, "fire"), *psign);
        //playAnimationd(1, "fire", name, Frames_Count_Fire, *psign);
    }
    if (*psign == 4)
    {
        playAnimationd(0, "fire", dollname, calculate_frame_count(dollname, "fire"), *psign);
        //playAnimationd(0, "fire", name, Frames_Count_Fire, *psign);
    }
}

void keymove()
{
    //检测键盘状态 
    if (GetAsyncKeyState('W')>=0||GetAsyncKeyState('S')>=0||GetAsyncKeyState('A')>=0||GetAsyncKeyState('D')>=0)
    {
        if (*pmx < *px) // 检查是否鼠标在小人左侧
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
        if (*pmx > *px) // 检查是否鼠标在小人右侧
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

    if (GetAsyncKeyState('W') < 0) // 使用字符常量代替VK_W 
    {
        *py -= 10;
        *psign = 1;
    }
    if (GetAsyncKeyState('S') < 0) // 使用字符常量代替VK_S  
    {
        *py += 10;
        *psign = 2;
    }
    if (GetAsyncKeyState('A') < 0) // 使用字符常量代替VK_A  
    {
        *px -= 10;
        *psign = 2;
    }
    if (GetAsyncKeyState('D') < 0) // 使用字符常量代替VK_D  
    {
        *px += 10;
        *psign = 1;
    }

    // 边界检查
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
        *py = 720 - 270; // 假设帧高度为100
    }

    Sleep(50); // 控制检查的刷新频率
}

void drawProgressBar(int x, int y, int progress, int total)
{
    // 计算进度条的宽度  
    int barWidth = 800; // 进度条的总宽度  
    int barHeight = 25; // 进度条的高度  
    int filledWidth = (progress * barWidth) / total; // 已填充的宽度  

    // 绘制已填充的进度部分
    setfillcolor(RGB(13, 140, 251));
    solidrectangle(x, y, x + filledWidth, y + barHeight); // 绘制进度条 
    // 设置进度条的背景颜色  
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
    rectangle(x, y, x + barWidth, y + barHeight); // 绘制背景框  
}

void ui_process()
{
    if (tsign == 0)//仅第一次循环执行
    {
        //加载基本图片资源
        loadimage(&background, "./resource/image/bg.jpg", 1280, 720);
        loadimage(&bulletimg, "./resource/icon/bullet.png", 21, 21);//加载子弹图片
        loadimage(&heart, "./resource/icon/heart.png", 32, 32);//加载心图片
        loadimage(&pause, "./resource/icon/pause.png", 34, 34);//加载暂停图片
        loadimage(&back, "./resource/icon/back.png", 34, 34);
        loadimage(&pause_bg, "./resource/icon/暂停背景.png", 246 * 3, 138 * 3);
        loadimage(&icon1, "./resource/icon/伤害提升.png", 75, 75);
        loadimage(&icon2, "./resource/icon/射速提升.png", 75, 75);
        loadimage(&icon3, "./resource/icon/生命提升.png", 75, 75);
        loadimage(&icon4, "./resource/icon/收获提升.png", 75, 75);
        loadimage(&icon_null, "./resource/icon/null.png", 75, 75);
        //读取人形基本数据
        
        
    }
    //level_up = 0;
    if (killed_number * RATIO - lv * 1000 >= 1000)
    {
        lv++;
        pause_sign = 1;
        level_up = 1;
    }
    
    //字符转换
    sprintf(killed_number_display, "%d", killed_number * RATIO);
    sprintf(lv_display, "%d", lv);
    //鼠标追踪
    POINT mousePos;
    GetCursorPos(&mousePos);
    ScreenToClient(GetHWnd(), &mousePos);
    
    *pmx = mousePos.x;
    *pmy = mousePos.y;
    tsign++;
}

//子弹开火

void fire_move(Bullet* bullet, int heroX, int heroY, int targetX, int targetY) {
    bullet->x = heroX;
    bullet->y = heroY;
    bullet->targetX = targetX;
    bullet->targetY = targetY;
    bullet->active = 1; // 激活子弹  
}

void updateBullet(Bullet* bullet) {
    if (bullet->active) {
        // 计算子弹的方向  
        int dx = bullet->targetX - bullet->x;
        int dy = bullet->targetY - bullet->y;
        double distance = sqrt(dx * dx + dy * dy);

        // 如果子弹到达目标位置，停用子弹  
        if (distance < BULLET_SPEED) {
            bullet->active = 0;
            bullet->x = -500;
            bullet->y = -500;
            return;
        }
        // 更新子弹位置  
        bullet->x += (int)(BULLET_SPEED * (dx / distance));
        bullet->y += (int)(BULLET_SPEED * (dy / distance));
    }
}

void fire() {
    // 检测鼠标左键发射子弹  
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (!bullets[i].active) // 只有在子弹未激活时才能发射
            {
                fire_move(&bullets[i], *px + 170, *py + 170, *pmx, *pmy);

                break;  //是否单发发射
            }

        }

    }
    Sleep(BULLET_INTERVAL);
}

void fire_rander()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        updateBullet(&bullets[i]);
    }
    Sleep(1);
}

//敌人刷新及寻路
void enemy_move(enemy* enemy, int heroX, int heroY, int targetX, int targetY)
{
    enemy->x = heroX;
    enemy->y = heroY;
    enemy->targetX = targetX;
    enemy->targetY = targetY;
    enemy->active = 1; // 敌人是否存活  
}

void updateEnemy(enemy* enemy) {
    if (enemy->active) {
        // 计算敌人寻路的方向  
        int dx = enemy->targetX - enemy->x;
        int dy = enemy->targetY - enemy->y;
        double distance = sqrt(dx * dx + dy * dy);
        // 如果敌人接触到人物  
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

        //子弹击中敌人
        for (int i = 0; i < MAX_BULLETS; i++)
        {
            if (bullets[i].x >= *dpx + 50 && bullets[i].x <= *dpx + 300 && bullets[i].y >= *dpy + 50 && bullets[i].y <= *dpy + 300)
            {
                enemy->health -= BULLET_DAMGE;
                bullets[i].active = 0;
                bullets[i].x = -500;
                bullets[i].y = -500;
                hit = 1;
                //计算敌人死亡动画
                if (enemy->health <= 0)
                {
                    enemy->active = 0;
                    die_x = *dpx;
                    die_y = *dpy;
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

        // 更新敌人位置  
        enemy->x += (int)(ENEMY_SPEED * (dx / distance));
        enemy->y += (int)(ENEMY_SPEED * (dy / distance));
        //判断敌人向左移动还是向右移动
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

void enemy_generate()
{
    if (!enemyInstance.active)
    {
        enemyInstance.health = 50;
        //敌人生成位置随机
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

    }
}

void enemy_data()
{
    enemy_move(&enemyInstance, *dpx, *dpy, *px, *py);
    updateEnemy(&enemyInstance);
    Sleep(20);
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

void draw_pause_ui()
{
    setfillcolor(RED);
    setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 3);
    transparentimage3(NULL, 640 - (246 * 3 / 2), 360 - (138 * 3 / 2), &pause_bg);
    settextstyle(40, 0, "黑体");
    outtextxy((490 + 790) / 2 - textwidth("请选择一个技能") / 2, (460 + 510) / 2 - textheight("请选择一个技能") / 2 - 280, "请选择一个技能");
    settextstyle(20, 0, "黑体");
    transparentimage3(NULL, 640 - 270 - 75 / 2, 360 - 100, &icon1);
    outtextxy(640 - 270 - textwidth("伤害提升") / 2, 360 - 10, "伤害提升");
    outtextxy(640 - 270 + textwidth("伤害提升") / 2 + 5, 360 - 40, "Lv.");
    
    sprintf(level_buffer, "%d/3", level_attack);
    outtextxy(640 - 270 + textwidth("伤害提升") / 2 + textwidth("Lv.") + 5, 360 - 40, level_buffer);
    transparentimage3(NULL, 640 - 90 - 75 / 2, 360 - 100, &icon2);
    outtextxy(640 - 90 - textwidth("射速提升") / 2, 360 - 10, "射速提升");
    outtextxy(640 - 90 + textwidth("射速提升") / 2 + 5, 360 - 40, "Lv.");
    sprintf(level_buffer, "%d/3", level_speed);
    outtextxy(640 - 90 + textwidth("射速提升") / 2 + textwidth("Lv.") + 5, 360 - 40, level_buffer);
    transparentimage3(NULL, 640 + 90 - 75 / 2, 360 - 100, &icon3);
    outtextxy(640 + 90 - textwidth("生命提升") / 2, 360 - 10, "生命提升");
    outtextxy(640 + 90 + textwidth("射速提升") / 2 + 5, 360 - 40, "Lv.");
    sprintf(level_buffer, "%d/3", level_health);
    outtextxy(640 + 90 + textwidth("生命提升") / 2 + textwidth("Lv.") + 5, 360 - 40, level_buffer);
    transparentimage3(NULL, 640 + 270 - 75 / 2, 360 - 100, &icon4);
    outtextxy(640 + 270 - textwidth("收获提升") / 2, 360 - 10, "收获提升");
    outtextxy(640 + 270 + textwidth("射速提升") / 2 + 5, 360 - 40, "Lv.");
    sprintf(level_buffer, "%d/3", level_gain);
    outtextxy(640 + 270 + textwidth("收获提升") / 2 + textwidth("Lv.") + 5, 360 - 40, level_buffer);
    settextstyle(15, 0, "黑体");
    outtextxy(640 - 270 - textwidth("将伤害提升10%/25%/50%")/2, 360+10, "将伤害提升10%/25%/50%");

    outtextxy(640 - 90 - textwidth("将射速提升10%/25%/50%")/2, 360+10, "将射速提升10%/25%/50%");

    outtextxy(640 + 90 - textwidth("每5/3/2回合") / 2, 360 + 10, "每5/3/2回合");
    outtextxy(640 + 90 - textwidth("回复一格生命值") / 2, 360 + 10 + textheight("回复一格生命值"), "回复一格生命值");

    outtextxy(640 + 270 - textwidth("经验值获取提高")/2, 360+10, "经验值获取提高");
    outtextxy(640 + 270 - textwidth("10%/25%/50%")/2, 360+10+textheight("10%/25%/50%"), "10%/25%/50%");
    outtextxy(640 + 270 - textwidth("结算时资源提升")/2, 360+10+2*textheight("结算时资源提升"), "结算时资源提升");
    outtextxy(640 + 270 - textwidth("10%/25%/50%")/2, 360+10+3*textheight("10%/25%/50%"), "10%/25%/50%");
    fillrectangle(640 - 150, 360 + 100, 640 + 150, 360 + 150);
    settextstyle(30, 0, "黑体");
    outtextxy((490 + 790) / 2 - textwidth("确定") / 2, (460 + 510) / 2 - textheight("确定") / 2, "确定");
    if (level_attack == 3)
    {
        transparentimage3(NULL, 640 - 270 - 75 / 2, 360 - 100, &icon1);
    }
    if (level_speed == 3)
    {
        transparentimage3(NULL, 640 - 90 - 75 / 2, 360 - 100, &icon2);
    }
    if (level_health == 3)
    {
        transparentimage3(NULL, 640 + 90 - 75 / 2, 360 - 100, &icon3);
    }
    if (level_gain == 3)
    {
        transparentimage3(NULL, 640 + 270 - 75 / 2, 360 - 100, &icon4);
    }
}