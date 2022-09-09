// MagicSquare.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>


// 마방진
// 1. 3x3 col =3 row =3
// 2. 첫번째 행중 열 중간에 1을 넣는다.
// 3. 1을 기준으로 오른쪽 대각선 1(2,3)-> (3, 4) 로 이동
// 4. 이동시 3by 3  행렬을 넘어가면 (3,4)->(3,1) 로 이동
// 5. (3,1) -> (4,2)->(1,2)
// 6. 대각선 이동시 이미 숫자가 있으면 또는 대각선 이동시 xy 좌표 둘다 초과하면 현재 좌표 아래 행에다 배치
// 7. 행의 좌표를 초과하면 수직(아래) 열의 좌표를 초과하면 수평(왼쪽) 에 배치
typedef struct Coord {
    int x;
    int y;
}coord;

int main()
{
    int maxCount = 0;
    coord pivot = {};
    
    scanf_s("%d", &maxCount);

    int** squareSize = (int**)malloc(sizeof(intptr_t)* maxCount);   //최대값은 20으로 설정
    for (int i = 0; i < maxCount; i++)
    {
        *(squareSize+i) = (int*)malloc(sizeof(int)*maxCount);           //열 동적할당
    }
    for (int i = 0; i < maxCount; i++)
    {
        for (int j = 0; j < maxCount; j++)
        {
            *(*(squareSize+i)+j) = 0;
        }
    }


    for (int iNum =1; iNum <= (maxCount * maxCount); iNum++)
    {
        if (iNum == 9)
            printf(" *");
        
        if (pivot.y>=0&&pivot.x<maxCount)      // 이동한 좌표안에 데이터가 있으면 바로 아래에다 데이터 저장
        {
            if (squareSize[pivot.y][pivot.x] != 0&&iNum>1)
            {
                 pivot.y += 2;
                 pivot.x--;
                 squareSize[pivot.y][pivot.x] = iNum;
            }
            else if (squareSize[pivot.y][pivot.x] == 0&&iNum>1)
            {
                squareSize[pivot.y][pivot.x] = iNum;
            }
        }
        if (iNum == 1)      // 처음 1은
        {

            squareSize[0][(maxCount / 2)] = iNum;
            pivot.x = (maxCount / 2);   // (1,0)
            pivot.y = 0;
        }

        if (pivot.y < 0 &&pivot.x<maxCount)     // 만약 y좌표 값이 0보다 작거나 또는 x의 값이 최대치 안일때
        {
            pivot.y = maxCount-1;                // y값을 최대치로 높인다
            while (squareSize[pivot.y][pivot.x]!=0)     // y값이 최대치로 바꿧을때 안의 값이 0이 아니면 한칸씩 올린다.
            {
                pivot.y++;
                
            }
            squareSize[pivot.y][pivot.x] = iNum;       // 0이면 그 칸에 iNum값을 넣는다.
            
        }
        if (pivot.x >= maxCount&&pivot.y>=0)      //만약 x좌표값이 최대치보다 크다면  또는 y의 값이 0보다 클때
        {
            pivot.x = 0;                        //x의 값을 최소치로 맞춘다.
            

            while (squareSize[pivot.y][pivot.x]!=0) //최소치로 맞춘 x의 값이 0이 아니면 x좌표를 한칸씩 늘려준다.
            {
                pivot.x += 1;
            }
            squareSize[pivot.y][pivot.x] = iNum;
        }
        if (pivot.x >= maxCount && pivot.y < 0)     //x의 값의 최대치보다 크고 y의 값이 0보다 작으면
        {
            pivot.y += 2;
            pivot.x--;
            squareSize[pivot.y][pivot.x] = iNum;
        }
        

        pivot.x++;      //피봇을 이동한다.
        pivot.y--;
        
        //for (int i = 0; i < maxCount; i++)      // 마방진 출력
        //{
        //    for (int j = 0; j < maxCount; j++)
        //    {
        //        printf("%d ", squareSize[i][j]);
        //    }
        //    printf("\n");
        //}
        //printf("\n");
        //printf("================\n");
    }

    
    
    

    
    
    for (int i = 0; i < maxCount; i++)      // 마방진 출력
    {
        for (int j = 0; j < maxCount; j++)
        {
            printf("%d ", squareSize[i][j]);
        }
        printf("\n  ");
        
    }
    int sum = 0;
    int sum_a = 0;
    for (int i = 0; i < maxCount; i++)
    {
        int result = squareSize[0][i];
        sum = sum + result;

        int result_a = squareSize[i][0];
        sum_a = sum_a+ result_a;

        printf("%d == %d\n", sum, sum_a);
    }

    for (int i = 0; i < maxCount; i++)      // 동적할당 메모리 해제
    {
        free(squareSize[i]);
    }
    free(squareSize);
    


    return 0;
}


