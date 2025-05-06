#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

extern int Profile_Number;

typedef struct profile
{
	int profile_id;
	char username[20];
	char gamename[20];
	int password;
	int level;
	int manpower;
	int ammunition;
	int pation;
	int part;
	struct profile* next;
}PLF;

PLF* head;

PLF* createfromtail(int n) // 尾插法创建链表
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

		p = (PLF*)malloc(sizeof(PLF));
		sprintf(filename, "file%d.txt", i);
		file = fopen(filename, "r");
		if (file == NULL) {
			fprintf(stderr, "Unable to open file: %s\n", filename);
			continue; // Skip if the file can't be opened
		}

		// 读取 username
		fgets(temp, sizeof(temp), file);
		char* colon = strchr(temp, ':');
		if (colon != NULL) {
			strcpy(p->username, colon + 1); // 直接拷贝冒号后的字符串
			p->username[strcspn(p->username, "\n")] = '\0'; // 去除换行符
		}

		// 读取 password
		fscanf(file, "password:%d\n", &p->password);

		// 读取 gamename
		fgets(temp, sizeof(temp), file);
		colon = strchr(temp, ':');
		if (colon != NULL) {
			strcpy(p->gamename, colon + 1);
			p->gamename[strcspn(p->gamename, "\n")] = '\0'; // 去除换行符
		}

		// 读取 level, manpower, ammunition, pation, part
		fscanf(file, "level:%d\n", &p->level);
		fscanf(file, "manpower:%d\n", &p->manpower);
		fscanf(file, "ammunition:%d\n", &p->ammunition);
		fscanf(file, "pation:%d\n", &p->pation);
		fscanf(file, "part:%d\n", &p->part);

		p->profile_id = i;

		// 连接到链表
		tail->next = p;
		tail = p;
		fclose(file); // 记得关闭文件
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
			Profile_Number = p->profile_id;
			return p->password; //返回密码
			break;
		}
		p = p->next;
	}
	return -1; //用户名不存在
}

