#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

typedef struct profile
{
    int profile_id;
    char username[20];
    int password;
    struct profile* next;
}PLF;

PLF* head;

PLF* createfromtail(int n)//尾插法创建链表
{
	PLF* p, * head, * tail = NULL;
	head = (PLF*)malloc(sizeof(PLF));
	tail = head;

	int i;
	for (i = 1; i <= n; i++)
	{
		FILE* file;
		char filename[20];
		char temp[100];
		int tempcode;
		p = (PLF*)malloc(sizeof(PLF));
		sprintf(filename, "file%d.txt", i);
		file = fopen(filename, "r");
		fgets(temp, sizeof(temp), file);
		char* colon = strchr(temp, ':');
		if (colon != NULL)
		{
			char* value = colon + 1; // 指向冒号后一个字符  
			// 去掉换行符  
			value[strcspn(value, "\n")] = '\0'; // 替换换行符为结束符
			strcpy(p->username, value);
			fscanf(file, "password:%d", &tempcode);
			p->password = tempcode;
		}
		p->profile_id = i;

		tail->next = p;
		tail = p;
	}
	tail->next = NULL;
	return head;
}

PLF* load_profile()//加载所有文件
{
	//读取proile数量文件
	int n;
	char filename[20];
	FILE* signfile;
	signfile = fopen("sign.txt", "r");
	fscanf(signfile, "%d", &n);
	fclose(signfile);
	return createfromtail(n);
}

int check_profile(PLF* head, char*username)
{
	PLF* p;
	p = head->next; //将p指向头节点中的next
	while (p != NULL) //遍历
	{
		//printf("id:%d\n用户名：%s\n密码：%d\n", p->profile_id, p->username, p->password);
		if (strcmp(p->username, username) == 0) //用户名匹配
		{
			return p->password; //返回密码
			break;
		}
		p = p->next;
	}
	return -1; //用户名不存在
}

