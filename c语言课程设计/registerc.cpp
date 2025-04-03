//#define _CRT_SECURE_NO_WARNINGS 1
//#include <graphics.h>
//#include <easyx.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include <tchar.h>
//
//#define _CRT_SECURE_NO_WARNINGS 1
//#undef UNICODE
//#undef _UNICODE
//
//int sign1;
//
//// 按钮结构体
//typedef struct Button {
//    int x;
//    int y;
//    int width;
//    int height;
//    float scale;
//    bool isMouseOver;
//    char text[100];
//    void (*onClick)();
//} Button;
//
//// 文字输入框结构体
//typedef struct TextBox {
//    int x;
//    int y;
//    int width;
//    int height;
//    int maxWord;
//    char text[100];
//    bool isSelected;
//    bool showCursor;
//    int cursorPos;
//} TextBox;
//
//// Widget 结构体
//typedef struct Widget {
//    int width;
//    int height;
//    int currentIndex;
//    IMAGE* pages[10];
//    Button* buttons[10][10];
//    TextBox* textBoxs[10][10];
//    int buttonCount[10];
//    int textBoxCount[10];
//} Widget;
//
//void checkMouseOver(Button* button, int mouseX, int mouseY);
//bool checkClick(Button* button, int mouseX, int mouseY);
//void drawButton(Button* button);
//void clearTextBox(TextBox* textBox);
//void setText(TextBox* textBox, const char* newText);
//void drawTextBox(TextBox* textBox);
//bool checkTextBoxClick(TextBox* textBox, int mouseX, int mouseY);
//void keyInputTextBox(TextBox* textBox, wchar_t ch);
//void updateCursorTextBox(TextBox* textBox);
//void addPage(Widget* widget, IMAGE* page);
//void addButton(Widget* widget, int index, Button* button);
//void addTextBox(Widget* widget, int index, TextBox* textBox);
//void setCurrentIndex(Widget* widget, int index);
//void mouseClick(Widget* widget, int mouseX, int mouseY);
//void mouseMove(Widget* widget, int mouseX, int mouseY);
//void keyInputWidget(Widget* widget, wchar_t ch);
//void drawWidget(Widget* widget);
//void registerButtonClicked();
//void initregister(Widget* widget);
//void runWidget(Widget* widget);
//void closeWidget(Widget* widget);
//
//void regist() {
//    Widget widget;
//    widget.width = 1280;
//    widget.height = 720;
//    initregister(&widget);
//    runWidget(&widget);
//    closeWidget(&widget);
//    printf("%d", 2);
//}
//
//void checkMouseOver(Button* button, int mouseX, int mouseY) {
//    button->isMouseOver = (mouseX >= button->x && mouseX <= button->x + button->width && mouseY >= button->y && mouseY <= button->y + button->height);
//    if (button->isMouseOver) {
//        button->scale = 0.9f;
//    }
//    else {
//        button->scale = 1.0f;
//    }
//}
//
//bool checkClick(Button* button, int mouseX, int mouseY) {
//    if (mouseX >= button->x && mouseX <= button->x + button->width && mouseY >= button->y && mouseY <= button->y + button->height) {
//        button->onClick();
//        button->isMouseOver = false;
//        button->scale = 1.0f;
//        return true;
//    }
//    return false;
//}
//
//void drawButton(Button* button) {
//    int scaledWidth = button->width * button->scale;
//    int scaledHeight = button->height * button->scale;
//    int scaledX = button->x + (button->width - scaledWidth) / 2;
//    int scaledY = button->y + (button->height - scaledHeight) / 2;
//
//    if (button->isMouseOver) {
//        setlinecolor(RGB(0, 120, 215));
//        setfillcolor(RGB(229, 241, 251));
//    }
//    else {
//        setlinecolor(RGB(173, 173, 173));
//        setfillcolor(RGB(225, 225, 225));
//    }
//
//    fillrectangle(scaledX, scaledY, scaledX + scaledWidth, scaledY + scaledHeight);
//    settextcolor(BLACK);
//    setbkmode(TRANSPARENT);
//    settextstyle(20 * button->scale, 0, _T("微软雅黑"));
//    int textX = scaledX + (scaledWidth - textwidth(button->text)) / 2;
//    int textY = scaledY + (scaledHeight - textheight(_T("微软雅黑"))) / 2;
//    outtextxy(textX, textY, button->text);
//}
//
//void clearTextBox(TextBox* textBox) {
//    textBox->text[0] = '\0';
//}
//
//void setText(TextBox* textBox, const char* newText) {
//    strncpy(textBox->text, newText, textBox->maxWord);
//    textBox->text[textBox->maxWord - 1] = '\0';
//    textBox->cursorPos = strlen(textBox->text);
//}
//
//void drawTextBox(TextBox* textBox) {
//    setfillcolor(WHITE);
//    if (textBox->isSelected) {
//        setlinecolor(RGB(0, 120, 215));
//        fillrectangle(textBox->x, textBox->y, textBox->x + textBox->width, textBox->y + textBox->height);
//    }
//    else {
//        setlinecolor(RGB(122, 122, 122));
//        fillrectangle(textBox->x, textBox->y, textBox->x + textBox->width, textBox->y + textBox->height);
//    }
//
//    settextcolor(BLACK);
//    setbkmode(TRANSPARENT);
//    settextstyle(textBox->height * 3 / 4, 0, _T("微软雅黑"));
//
//    outtextxy(textBox->x + 5, textBox->y + (textBox->height - textheight(_T("微软雅黑"))) / 2, textBox->text);
//
//    setlinecolor(BLACK);
//    if (textBox->isSelected && textBox->showCursor) {
//        int cursorX = textBox->x + 5 + textwidth(textBox->text) / 2;
//        line(cursorX, textBox->y + 2 + textBox->height / 8, cursorX, textBox->y + textBox->height * 7 / 8 - 2);
//    }
//}
//
//bool checkTextBoxClick(TextBox* textBox, int mouseX, int mouseY) {
//    if (mouseX >= textBox->x && mouseX <= textBox->x + textBox->width && mouseY >= textBox->y && mouseY <= textBox->y + textBox->height) {
//        textBox->isSelected = true;
//        return true;
//    }
//    else {
//        textBox->isSelected = false;
//        textBox->cursorPos = strlen(textBox->text);
//        return false;
//    }
//}
//
//void keyInputTextBox(TextBox* textBox, wchar_t ch) {
//    if (textBox->isSelected) {
//        switch (ch) {
//        case '\b':  // 用户按退格键，删掉一个字符
//            if (strlen(textBox->text) > 0 && textBox->cursorPos > 0) {
//                textBox->text[textBox->cursorPos - 1] = '\0';
//                textBox->cursorPos--;
//            }
//            break;
//        case '\r':
//        case '\n':
//            textBox->cursorPos = strlen(textBox->text);
//            textBox->isSelected = false;
//            break;
//        default:    // 用户按其它键，接受文本输入
//            if (strlen(textBox->text) < textBox->maxWord - 1) {
//                textBox->text[textBox->cursorPos] = ch;
//                textBox->text[textBox->cursorPos + 1] = '\0';
//                textBox->cursorPos++;
//            }
//        }
//    }
//}
//
//void updateCursorTextBox(TextBox* textBox) {
//    static DWORD lastTick = GetTickCount();
//    DWORD currentTick = GetTickCount();
//    if (currentTick - lastTick >= 500) { // 每500毫秒切换光标状态
//        textBox->showCursor = !textBox->showCursor;
//        lastTick = currentTick;
//    }
//}
//
//void addPage(Widget* widget, IMAGE* page) {
//    widget->pages[widget->currentIndex] = page;
//    widget->buttonCount[widget->currentIndex] = 0;
//    widget->textBoxCount[widget->currentIndex] = 0;
//    widget->currentIndex++;
//}
//
//void addButton(Widget* widget, int index, Button* button) {
//    if (index >= 0 && index < widget->currentIndex) {
//        widget->buttons[index][widget->buttonCount[index]] = button;
//        widget->buttonCount[index]++;
//    }
//}
//
//void addTextBox(Widget* widget, int index, TextBox* textBox) {
//    if (index >= 0 && index < widget->currentIndex) {
//        widget->textBoxs[index][widget->textBoxCount[index]] = textBox;
//        widget->textBoxCount[index]++;
//    }
//}
//
//void setCurrentIndex(Widget* widget, int index) {
//    if (index >= 0 && index < widget->currentIndex) {
//        widget->currentIndex = index;
//    }
//}
//
//void mouseClick(Widget* widget, int mouseX, int mouseY) {
//    for (int i = 0; i < widget->buttonCount[0]; i++) {
//        if (checkClick(widget->buttons[0][i], mouseX, mouseY)) {
//            //registerButtonClicked(widget);
//            break;
//        }
//    }
//    for (int i = 0; i < widget->textBoxCount[0]; i++) {
//        checkTextBoxClick(widget->textBoxs[0][i], mouseX, mouseY);
//    }
//}
//
//void mouseMove(Widget* widget, int mouseX, int mouseY) {
//    for (int i = 0; i < widget->buttonCount[0]; i++) {
//        checkMouseOver(widget->buttons[0][i], mouseX, mouseY);
//    }
//}
//
//void keyInputWidget(Widget* widget, wchar_t ch) {
//    for (int i = 0; i < widget->textBoxCount[0]; i++) {
//        if (widget->textBoxs[0][i]->isSelected) {
//            keyInputTextBox(widget->textBoxs[0][i], ch);
//        }
//    }
//}
//
//void drawWidget(Widget* widget) {
//    putimage(0, 0, widget->pages[0]);
//    for (int i = 0; i < widget->buttonCount[0]; i++) {
//        drawButton(widget->buttons[0][i]);
//    }
//    for (int i = 0; i < widget->textBoxCount[0]; i++) {
//        if (widget->textBoxs[0][i]->isSelected) {
//            updateCursorTextBox(widget->textBoxs[0][i]);
//        }
//        drawTextBox(widget->textBoxs[0][i]);
//    }
//}
//
//void registerButtonClicked(Widget* widget) {
//    FILE* file, * signfile, * signfilea;
//    char filename[20];
//    // 读取命名次数
//    signfile = fopen("sign.txt", "r");
//    fscanf(signfile, "%d", &sign1);
//    fclose(signfile);
//    sprintf(filename, "file%d.txt", sign1);
//    signfilea = fopen("sign.txt", "w");
//    fprintf(signfilea, "%d", sign1 + 1);
//    fclose(signfilea);
//    file = fopen(filename, "w+"); // 创建配置文件
//    fprintf(file, "accountname:%s\n", widget->textBoxs[0][0]->text); // 写入用户名
//    fprintf(file, "password:%s\n", widget->textBoxs[0][1]->text); // 写入密码
//    fprintf(file, "name:%s\n", widget->textBoxs[0][2]->text); // 写入昵称
//    fprintf(file, "level:1\n"); // 写入初始等级
//    fprintf(file, "manpower:10000\n"); // 写入初始人力
//    fprintf(file, "ammunition:10000\n"); // 写入初始弹药
//    fprintf(file, "pation:10000\n"); // 写入初始口狼
//    fprintf(file, "part:10000\n"); // 写入初始零件
//    MessageBox(GetHWnd(), _T("注册成功，请登录"), _T("成功"), MB_OK);
//    fclose(file);
//    clearTextBox(widget->textBoxs[0][0]);
//    clearTextBox(widget->textBoxs[0][1]);
//    clearTextBox(widget->textBoxs[0][2]);
//    closegraph();
//    //login();
//}
//
//void initregister(Widget* widget) {
//    initgraph(widget->width, widget->height);
//    // 创建页面1
//    IMAGE* page2 = new IMAGE(widget->width, widget->height);
//    IMAGE bg1;
//    loadimage(&bg1, _T("./resource/background/login.jpg"), widget->width, widget->height);
//    putimage(0, 0, &bg1);
//
//    // 在界面1显示账户、密码、昵称字样
//    settextcolor(RGB(255, 255, 255));
//    setbkmode(TRANSPARENT);
//    settextstyle(30, 0, _T("微软雅黑"));
//    outtextxy(550, 300, "账户：");
//    outtextxy(550, 350, "密码：");
//    outtextxy(550, 400, "昵称：");
//    settextstyle(50, 0, _T("微软雅黑"));
//    outtextxy(600, 200, "注册");
//    getimage(page2, 0, 0, widget->width, widget->height);
//    addPage(widget, page2);
//
//    // 在界面1创建按钮（登录）
//    Button* button1_1 = (Button*)malloc(sizeof(Button));
//    button1_1->x = 565;
//    button1_1->y = 450;
//    button1_1->width = 150;
//    button1_1->height = 30;
//    strcpy(button1_1->text, "注册");
//    button1_1->scale = 1.0f;
//    button1_1->isMouseOver = false;
//    button1_1->onClick = registerButtonClicked;
//    //button1_1->onClick = (void(*)(void))registerButtonClicked; // 类型转换
//    addButton(widget, 0, button1_1);
//
//    // 在界面1创建文本框（账户）
//    TextBox* textbox2_1 = (TextBox*)malloc(sizeof(TextBox));
//    textbox2_1->x = 615;
//    textbox2_1->y = 300;
//    textbox2_1->width = 150;
//    textbox2_1->height = 30;
//    textbox2_1->maxWord = 10;
//    textbox2_1->isSelected = false;
//    textbox2_1->showCursor = false;
//    textbox2_1->cursorPos = 0;
//    textbox2_1->text[0] = '\0';
//    addTextBox(widget, 0, textbox2_1);
//
//    // 在界面1创建文本框(密码)
//    TextBox* textbox2_2 = (TextBox*)malloc(sizeof(TextBox));
//    textbox2_2->x = 615;
//    textbox2_2->y = 350;
//    textbox2_2->width = 150;
//    textbox2_2->height = 30;
//    textbox2_2->maxWord = 10;
//    textbox2_2->isSelected = false;
//    textbox2_2->showCursor = false;
//    textbox2_2->cursorPos = 0;
//    textbox2_2->text[0] = '\0';
//    addTextBox(widget, 0, textbox2_2);
//
//    // 在界面1创建文本框(昵称)
//    TextBox* textbox2_3 = (TextBox*)malloc(sizeof(TextBox));
//    textbox2_3->x = 615;
//    textbox2_3->y = 400;
//    textbox2_3->width = 150;
//    textbox2_3->height = 30;
//    textbox2_3->maxWord = 10;
//    textbox2_3->isSelected = false;
//    textbox2_3->showCursor = false;
//    textbox2_3->cursorPos = 0;
//    textbox2_3->text[0] = '\0';
//    addTextBox(widget, 0, textbox2_3);
//
//    setCurrentIndex(widget, 0);
//}
//
//void runWidget(Widget* widget) {
//    ExMessage msg;
//    BeginBatchDraw();
//    while (true) {
//        if (peekmessage(&msg)) {
//            int mouseX = msg.x;
//            int mouseY = msg.y;
//            switch (msg.message) {
//            case WM_LBUTTONDOWN:
//                mouseClick(widget, mouseX, mouseY);
//                break;
//            case WM_MOUSEMOVE:
//                mouseMove(widget, mouseX, mouseY);
//                break;
//            case WM_CHAR:
//                keyInputWidget(widget, msg.ch);
//                break;
//            }
//        }
//        drawWidget(widget);
//        FlushBatchDraw();
//        Sleep(10);
//    }
//    EndBatchDraw();
//}
//
//void closeWidget(Widget* widget) {
//    closegraph();
//}
//
