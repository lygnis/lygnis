#pragma once
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>	//rand
#include<time.h>
#include<string.h>
#include<conio.h>
#include<io.h>	// _finddata_t, _findfirst, _findnext
#define MAX_SAVE_FILE 100
// �ִ� 100�� ��ȣ ������ ������ �Է¹ް�
// ��ȣ, ����, ����� ����Ͻÿ�. (�񿬰Ḯ��Ʈ ���)

// ����, ��¿� �ʿ��� ����ü ����
typedef struct Stuednt {
	char s_name[8];	//�̸�
	int s_index;		//��ȣ
	int s_Kor;		//����
	int s_Eng;		//����
	int s_Math;		//����
	int s_Total;		//����
	float s_Total_Average;	//���	//24 +8 =32 (char [9] 1����Ʈ�� 4����Ʈ�� ��ŷ�ȴ�)


}Student;

//�ε� ���Ŀ� �۾��� �л� ����
Student* g_PStudentData = 0;

//��ü �л� ��
int g_totalStudent;
//���� �˻� �� ���� �迭
struct _finddata_t g_saveFileArr[MAX_SAVE_FILE];	//_finddata_t ����ü�� 100 �迭 �ֱ�
//����Ǿ� �ִ� ���� ����
int g_saveFileCount = 0;
//���� �۾� ���� �����̸�
char g_CurrentFile[256] = {0};


// ������ ���̽� (����Ÿ ����, ������ �ε�, ���������, ������ ��ȣ�� ã��, ������ �̸����� ã��, ����, ������
enum Data
{
	DataSave,
	DataLoad,
	DataPrint,
	DataFindIndex,
	DataFindName,
	DataSample,
	Exit = 99,
};

// ó�� ������ �����Լ�
void CreateSampleData();

// �ε� ������ ����Լ�
void PrintData();

// �ε� ������ �̸����� �˻� �� ���
void FinName();

// �ε� ������ �ε����� �˻� �� ���
void FindIndex();

// �޸� ������ ����
int FileSave();

// �޸� ������ �ε�
int FileLoad();

// �űԵ����͸� ���Ͽ� ��� �� �ε�
void NewData();

// ���� ã��
void FindFile(void);


// ���� ���� �����
void CreateSampleData()
{
	// ���� ������ ���鶧 �ʱ�ȭ �� ��Ų��.
	g_totalStudent = 10;
	if (g_PStudentData != NULL)	// ���� �۾��� �л� ������ �ִٸ�
	{
		free(g_PStudentData);		// �����͸� �ʱ�ȭ �����ش�.
		g_PStudentData = 0;

	}

	if (g_PStudentData == NULL)
	{
		int testSize = sizeof(Student);
		g_PStudentData = (Student*)malloc(sizeof(Student) * g_totalStudent);	// �л� ���� �����Ͱ� ���̶�� 
	}
	for (int i = 0; i < g_totalStudent; i++)
	{
		g_PStudentData[i].s_name[0] = 65 + rand() % 26;
		g_PStudentData[i].s_name[1] = 65 + rand() % 26;
		g_PStudentData[i].s_name[2] = 65 + rand() % 26;
		g_PStudentData[i].s_name[3] = '\0';	//�̸��� �����ϰ� �Է¹ް� �̸� ���� Ȯ���ϱ� ���� �������� 0����

		g_PStudentData[i].s_index = i;		// ��ȣ �Է�

		g_PStudentData[i].s_Kor = rand() % 101;
		g_PStudentData[i].s_Eng = rand() % 101;
		g_PStudentData[i].s_Math = rand() % 101;	// ���� �Է�

		g_PStudentData[i].s_Total = g_PStudentData[i].s_Kor + g_PStudentData[i].s_Eng + g_PStudentData[i].s_Math;
		g_PStudentData[i].s_Total_Average = g_PStudentData[i].s_Total / 3.0f;		// ���


	}
	PrintData();		// ���� �Է��� ������ ����Ѵ�.
}

void PrintData()
{
	if (g_PStudentData == 0)
	{
		printf("�����Ͱ� �����ϴ�");
		return;
	}
	system("cls");
	printf("\n=====================================");
	printf("\n==========�����������α׷�===========");
	printf("\n=====================================");
	printf("\n��ȣ \t�̸� \t ���� \t ���� \t ���� \t ���� \t ���");
	printf("\n===================================================");

	for (int i = 0; i < g_totalStudent; i++)
	{
		printf("\n%3d %8s %7d %7d %7d %7d %10.4f",
			g_PStudentData[i].s_index,
			g_PStudentData[i].s_name,
			g_PStudentData[i].s_Kor,
			g_PStudentData[i].s_Eng,
			g_PStudentData[i].s_Math,
			g_PStudentData[i].s_Total,
			g_PStudentData[i].s_Total_Average
		);
	}
	// ��»��� ����
}

void FindIndex()
{
	int findIndex = 0;
	printf("\n ��ȣ�� �Է��ϼ���");
	scanf_s("%d", &findIndex);

	if (findIndex >= 0)		// ��ȣ�� �Է��� ã��
	{
		printf("\n%3d %8s %7d %7d %7d %7d %10.4f",
			g_PStudentData[findIndex].s_index,
			g_PStudentData[findIndex].s_name,
			g_PStudentData[findIndex].s_Kor,
			g_PStudentData[findIndex].s_Eng,
			g_PStudentData[findIndex].s_Math,
			g_PStudentData[findIndex].s_Total,
			g_PStudentData[findIndex].s_Total_Average);
	}
	else
	{
		printf("\n��ȣ�� �����ϴ�");
		return;
	}
}

void FindName()
{
	char findName[8] = {0};
	printf("\n �̸��� �Է��ϼ���:");

	scanf_s("%s", &findName);
	for (int i = 0; i < g_totalStudent; i++)
	{
		if (strcmp(g_PStudentData[i].s_name, findName) != 0)		//strcmp ������ 0 �ٸ��� -1 �Ǵ� 1
		{
			continue;
		}
		
		else													// 0�̸�
		{
				printf("\n%3d %8s %7d %7d %7d %7d %10.4f",
				g_PStudentData[i].s_index,
				g_PStudentData[i].s_name,
				g_PStudentData[i].s_Kor,
				g_PStudentData[i].s_Eng,
				g_PStudentData[i].s_Math,
				g_PStudentData[i].s_Total,
				g_PStudentData[i].s_Total_Average);

				break;

		}
	}
}

int FileSave()
{
	FILE* loadFile;
	time_t now = time(NULL);		// ���� �ð� üũ
	tm* lt = localtime(&now);
	char buffer[256] = { 0 };		// �����͸� ���� �׸� ����

	strftime(buffer, 256, "%Y��%m��%d��%H��%M��%S��.txt", lt);		//buffer ������ �ð� �����͸� ũ�⿡ �°� �Ҵ�
	loadFile = fopen(buffer, "w");							// load ���Ͽ� �ð���¥ ������ �����.

	fprintf(loadFile, "%d", g_totalStudent);				// ���� �ð� ��¥ ���Ͽ� �� �л��������͸� �ִ´�.

	for (int i = 0; i < g_totalStudent; i++)
	{
			printf("\n%3d %8s %7d %7d %7d %7d %10.4f",
			g_PStudentData[i].s_index,
			g_PStudentData[i].s_name,
			g_PStudentData[i].s_Kor,
			g_PStudentData[i].s_Eng,
			g_PStudentData[i].s_Math,
			g_PStudentData[i].s_Total,
			g_PStudentData[i].s_Total_Average);
	}
	memset(g_CurrentFile, 0, sizeof(char) * 256);		// �޸� ���� �ϱ� g_Curr �迭(�׸�)�� 256����Ʈ ��ŭ 0���� �ʱ�ȭ �Ѵ�. (�� prj���� ����)
	strcpy(g_CurrentFile, buffer);				//buffer ���ִ� ���ڿ��� �����Ѵ�.
	fclose(loadFile);
	return 1;		// ���̽� ������ �����Ҽ� �ִ� �ּ� ������ 0���� Ŀ���Ѵ�. �׷��� ������ return 1;

}

int FileLoad()					// ������ �ε� �ؿö� ���� ���Ͼȿ� �����Ͱ� ������ �����ϰ� ������ �ִ� ���� �����͸� �����ͼ�
{								// ���ο� ���� �޸𸮿� ���Ҵ��Ѵ�. ***(���Ḯ��Ʈ�� �ƴϱ� ������ ��ȿ������ ����̴�.)
	FILE* loadFile;
	FindFile();
	// ���������� ���� ��
	if (g_saveFileCount < 1)
	{
		return -1;
	}
	// ���� ������ ����
	loadFile = fopen(g_saveFileArr[0].name, "r");
	if (loadFile == NULL)
	{
		return -1;
	}
	if (g_PStudentData != NULL)
	{
		free(g_PStudentData);
		g_PStudentData = NULL;		// ���� �л������͵��� �� �� �����Ѵ�.
	}
	fscanf(loadFile, "%d", &g_totalStudent);		// ������ �ִ� �������� �� �л����� �����´�.

	if (g_PStudentData == NULL)
	{
		g_PStudentData = (Student*)malloc(sizeof(Student) * g_totalStudent);		// ������ �Ҵ����� ���� �޸� �ʰ��� �����Ѵ�.
	}
	for (int i = 0; i < g_totalStudent; i++)
	{
		fscanf(loadFile, "%d %s %d %d %d %d %f",
			&g_PStudentData[i].s_index,
			&g_PStudentData[i].s_name,
			&g_PStudentData[i].s_Kor,
			&g_PStudentData[i].s_Eng,
			&g_PStudentData[i].s_Math,
			&g_PStudentData[i].s_Total,
			&g_PStudentData[i].s_Total_Average);
			
			
	}
	fclose(loadFile);		
	PrintData();
}

void NewData()
{
	printf("\n�ű� �л��� �����͸� �Է��Ͻÿ� : ");
	Student newData;
	printf("\n�̸� : ");	scanf("%s", newData.s_name);
	printf("\n���� : ");  scanf("%s", newData.s_Kor);
	printf("\n���� : ");  scanf("%s", newData.s_Math);
	printf("\n���� : ");  scanf("%s", newData.s_Eng);

	newData.s_Total = newData.s_Kor + newData.s_Eng + newData.s_Math;
	newData.s_Total_Average = newData.s_Total / 3.f;
	newData.s_index = g_totalStudent;
	// ���� �޸� �����͸� ���� �����Ѵ�.
	FileSave();

	// ���� �ű� �����͸� ���̸��� ���� �߰� �����Ѵ�.

	FILE* fp = fopen(g_CurrentFile, "r+");
	if (fp == NULL)		// ���̺긦 ������ �ѹ��� ���ų� �ۼ������� ������ Null�߻�
	{
		return;
	}
	
}