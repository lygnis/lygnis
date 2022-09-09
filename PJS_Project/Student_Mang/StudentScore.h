#pragma once
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>	//rand
#include<time.h>
#include<string.h>
#include<conio.h>
#include<io.h>	// _finddata_t, _findfirst, _findnext
#define MAX_SAVE_FILE 100
// 최대 100명 번호 국영수 점수를 입력받고
// 번호, 총점, 평균을 출력하시오. (비연결리스트 사용)

// 저장, 출력에 필요한 구조체 선언
typedef struct Stuednt {
	char s_name[8];	//이름
	int s_index;		//번호
	int s_Kor;		//국어
	int s_Eng;		//영어
	int s_Math;		//수학
	int s_Total;		//총점
	float s_Total_Average;	//평균	//24 +8 =32 (char [9] 1바이트가 4바이트로 패킹된다)


}Student;

//로드 이후에 작업된 학생 정보
Student* g_PStudentData = 0;

//전체 학생 수
int g_totalStudent;
//파일 검색 및 저장 배열
struct _finddata_t g_saveFileArr[MAX_SAVE_FILE];	//_finddata_t 구조체에 100 배열 넣기
//저장되어 있는 파일 개수
int g_saveFileCount = 0;
//현재 작업 중인 파일이름
char g_CurrentFile[256] = {0};


// 선언한 케이스 (데이타 저장, 데이터 로드, 데이터출력, 데이터 번호로 찾기, 데이터 이름으로 찾기, 예제, 나가기
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

// 처음 데이터 생성함수
void CreateSampleData();

// 로드 데이터 출력함수
void PrintData();

// 로드 데이터 이름으로 검색 및 출력
void FinName();

// 로드 데이터 인덱스로 검색 및 출력
void FindIndex();

// 메모리 데이터 저장
int FileSave();

// 메모리 데이터 로드
int FileLoad();

// 신규데이터를 파일에 출력 및 로드
void NewData();

// 파일 찾기
void FindFile(void);


// 샘플 예제 만들기
void CreateSampleData()
{
	// 샘플 예제는 만들때 초기화 를 시킨다.
	g_totalStudent = 10;
	if (g_PStudentData != NULL)	// 만약 작업된 학생 정보가 있다면
	{
		free(g_PStudentData);		// 데이터를 초기화 시켜준다.
		g_PStudentData = 0;

	}

	if (g_PStudentData == NULL)
	{
		int testSize = sizeof(Student);
		g_PStudentData = (Student*)malloc(sizeof(Student) * g_totalStudent);	// 학생 정보 데이터가 널이라면 
	}
	for (int i = 0; i < g_totalStudent; i++)
	{
		g_PStudentData[i].s_name[0] = 65 + rand() % 26;
		g_PStudentData[i].s_name[1] = 65 + rand() % 26;
		g_PStudentData[i].s_name[2] = 65 + rand() % 26;
		g_PStudentData[i].s_name[3] = '\0';	//이름을 랜덤하게 입력받고 이름 끝을 확인하기 위해 마지막에 0삽입

		g_PStudentData[i].s_index = i;		// 번호 입력

		g_PStudentData[i].s_Kor = rand() % 101;
		g_PStudentData[i].s_Eng = rand() % 101;
		g_PStudentData[i].s_Math = rand() % 101;	// 성적 입력

		g_PStudentData[i].s_Total = g_PStudentData[i].s_Kor + g_PStudentData[i].s_Eng + g_PStudentData[i].s_Math;
		g_PStudentData[i].s_Total_Average = g_PStudentData[i].s_Total / 3.0f;		// 평균


	}
	PrintData();		// 예제 입력이 끝나면 출력한다.
}

void PrintData()
{
	if (g_PStudentData == 0)
	{
		printf("데이터가 없습니다");
		return;
	}
	system("cls");
	printf("\n=====================================");
	printf("\n==========성적관리프로그램===========");
	printf("\n=====================================");
	printf("\n번호 \t이름 \t 국어 \t 수학 \t 영어 \t 총점 \t 평균");
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
	// 출력상태 종료
}

void FindIndex()
{
	int findIndex = 0;
	printf("\n 번호를 입력하세요");
	scanf_s("%d", &findIndex);

	if (findIndex >= 0)		// 번호를 입력해 찾기
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
		printf("\n번호가 없습니다");
		return;
	}
}

void FindName()
{
	char findName[8] = {0};
	printf("\n 이름을 입력하세요:");

	scanf_s("%s", &findName);
	for (int i = 0; i < g_totalStudent; i++)
	{
		if (strcmp(g_PStudentData[i].s_name, findName) != 0)		//strcmp 같으면 0 다르면 -1 또는 1
		{
			continue;
		}
		
		else													// 0이면
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
	time_t now = time(NULL);		// 현재 시간 체크
	tm* lt = localtime(&now);
	char buffer[256] = { 0 };		// 데이터를 담을 그릇 생성

	strftime(buffer, 256, "%Y년%m월%d일%H시%M분%S초.txt", lt);		//buffer 공간에 시간 데이터를 크기에 맞게 할당
	loadFile = fopen(buffer, "w");							// load 파일에 시간날짜 파일을 만든다.

	fprintf(loadFile, "%d", g_totalStudent);				// 만든 시간 날짜 파일에 총 학생수데이터를 넣는다.

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
	memset(g_CurrentFile, 0, sizeof(char) * 256);		// 메모리 세팅 하기 g_Curr 배열(그릇)을 256바이트 만큼 0으로 초기화 한다. (이 prj에선 전부)
	strcpy(g_CurrentFile, buffer);				//buffer 에있는 문자열을 복사한다.
	fclose(loadFile);
	return 1;		// 케이스 문에서 저장할수 있는 최소 조건이 0보다 커야한다. 그러기 때문에 return 1;

}

int FileLoad()					// 파일을 로드 해올때 마다 파일안에 데이터가 있으면 삭제하고 기존에 있는 문서 데이터를 가져와서
{								// 새로운 동적 메모리에 재할당한다. ***(연결리스트가 아니기 때문에 비효율적인 방식이다.)
	FILE* loadFile;
	FindFile();
	// 저장파일이 없을 때
	if (g_saveFileCount < 1)
	{
		return -1;
	}
	// 파일 포인터 생성
	loadFile = fopen(g_saveFileArr[0].name, "r");
	if (loadFile == NULL)
	{
		return -1;
	}
	if (g_PStudentData != NULL)
	{
		free(g_PStudentData);
		g_PStudentData = NULL;		// 기존 학생데이터들을 싹 다 삭제한다.
	}
	fscanf(loadFile, "%d", &g_totalStudent);		// 기존에 있던 문서에서 총 학생수를 가져온다.

	if (g_PStudentData == NULL)
	{
		g_PStudentData = (Student*)malloc(sizeof(Student) * g_totalStudent);		// 기존에 할당해준 동적 메모리 초과를 방지한다.
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
	printf("\n신규 학생의 데이터를 입력하시오 : ");
	Student newData;
	printf("\n이름 : ");	scanf("%s", newData.s_name);
	printf("\n국어 : ");  scanf("%s", newData.s_Kor);
	printf("\n수학 : ");  scanf("%s", newData.s_Math);
	printf("\n영어 : ");  scanf("%s", newData.s_Eng);

	newData.s_Total = newData.s_Kor + newData.s_Eng + newData.s_Math;
	newData.s_Total_Average = newData.s_Total / 3.f;
	newData.s_index = g_totalStudent;
	// 현재 메모리 데이터를 먼저 저장한다.
	FileSave();

	// 이후 신규 데이터를 파이르이 끝에 추가 저장한다.

	FILE* fp = fopen(g_CurrentFile, "r+");
	if (fp == NULL)		// 세이브를 한적이 한번도 없거나 작성한적이 없으면 Null발생
	{
		return;
	}
	
}