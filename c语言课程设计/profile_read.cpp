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

PLF* createfromtail(int n) // β�巨��������
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

		// ��ȡ username
		fgets(temp, sizeof(temp), file);
		char* colon = strchr(temp, ':');
		if (colon != NULL) {
			strcpy(p->username, colon + 1); // ֱ�ӿ���ð�ź���ַ���
			p->username[strcspn(p->username, "\n")] = '\0'; // ȥ�����з�
		}

		// ��ȡ password
		fscanf(file, "password:%d\n", &p->password);

		// ��ȡ gamename
		fgets(temp, sizeof(temp), file);
		colon = strchr(temp, ':');
		if (colon != NULL) {
			strcpy(p->gamename, colon + 1);
			p->gamename[strcspn(p->gamename, "\n")] = '\0'; // ȥ�����з�
		}

		// ��ȡ level, manpower, ammunition, pation, part
		fscanf(file, "level:%d\n", &p->level);
		fscanf(file, "manpower:%d\n", &p->manpower);
		fscanf(file, "ammunition:%d\n", &p->ammunition);
		fscanf(file, "pation:%d\n", &p->pation);
		fscanf(file, "part:%d\n", &p->part);

		p->profile_id = i;

		// ���ӵ�����
		tail->next = p;
		tail = p;
		fclose(file); // �ǵùر��ļ�
	}

	tail->next = NULL;

	return head;
}

PLF* load_profile()//���������ļ�
{
	//��ȡproile�����ļ�
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
	p = head->next; //��pָ��ͷ�ڵ��е�next
	while (p != NULL) //����
	{
		//printf("id:%d\n�û�����%s\n���룺%d\n", p->profile_id, p->username, p->password);
		if (strcmp(p->username, username) == 0) //�û���ƥ��
		{
			Profile_Number = p->profile_id;
			return p->password; //��������
			break;
		}
		p = p->next;
	}
	return -1; //�û���������
}


PLF* deletePLF(PLF* h, int i)
{
	PLF* p, * s;
	p = h;
	int j = 1;
	if (h == NULL || i <= 0)
	{
		printf("ɾ����Ч\n");
		return h;  //����ԭ����
	}
	if (i == 1)  //Ҫɾ�����ǵ�һ���ڵ�
	{
		h = h->next; //��h�����ͷָ��ָ��ڶ����ڵ�
		free(p);
	}
	else
	{
		while (p->next != NULL && j < i - 1)
		{
			p = p->next;
			j++;
		}
		if (p->next == NULL) //����������
		{
			printf("ɾ����Ч\n");
			return h;
		}
		s = p->next;  //���ҵ���λ�õ���һ��λ�ö����s
		p->next = s->next;
		free(s);
	}
}
