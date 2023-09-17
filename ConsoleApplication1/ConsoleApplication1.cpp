// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <conio.h>

int main()
{
    printf("김남규의 행복한 VC++\n\n");

    while (1)
    {
        char s;
        printf("command>");
        s = _getche();

        if (s == 27) {
            break;
        }

        while (1) {
            char enter = _getch();
            if (enter == '\r') break;
        }

        printf("\n");

        switch (s)
        {
        case 'q': {
            printf("qwer 화이팅\n");
            break;
        }
        case 'w': {
            printf("과제 너무 좋다\n");
            break;
        }
        case 'e': {
            printf("담주부턴 과제량 3배다\n");
            break;
        }
        case 'r': {
            printf("행복합니다.\n");
            break;
        }

        default: {
            printf("오류입니다. qwer 중에 하나만 입력하세요\n");
            break;
        }
        }

    }
    return 0;
}