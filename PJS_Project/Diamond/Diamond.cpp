// Diamond.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>





int main()
{
    // 다이아몬드 만들기
    // 열의 최대치를 입력 받는다.
    // 입력받은 열이 짝수면 첫줄에선 별이 두칸
    // 다음 행에선 양옆으로 한칸씩 늘어나게 출력한다.
    // 열의 최소 입력값은 3
    // 2/3  2/4   5/5   5/6    7/7  7/8     9/9  9/10   11/11   11/12   13/13 13/14

    
    int row = 0;
    scanf_s("%d", &row);
    int col = row;
    int iRow = (row / 2) + 1;
    int iNumRow = row;
    char reNum = 0;
    if (row % 2 == 0)
    {
        col--;
    }
    for (int i = 0; i < col; i++)
    {
        for (int j = 1; j<=row; j++)
        {
            if (j >= iNumRow&&iNumRow>=iRow)
            {
                printf("*");
                

            }
            else
            {
                printf(" ");
            }
        }
        if (iNumRow <= iRow)
            reNum = 1;
        if (reNum == 0)
        {
            iNumRow--;
            row++;
        }
        if (reNum == 1)
        {
            iNumRow++;
            row--;
        }

        printf("\n");
    }
    

    
    




    return 0;
}


