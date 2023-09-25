#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define UP 72 // -32 + H 998
#define DOWN 80 // -32 + P 999
#define LEFT 75 // -32 + K 996
#define RIGHT 77 // -32 + M 997

void clear(int array[], int n)
{
    for (int i = 0; i < n; i++) {
        array[i] = 0;
    }
}

int main()
{
    char ch = ' '; // 사용자에게 입력 받음
    int result[100] = {}; // 입력받은 문자를 저장할 배열
    int index = 0; // 배열의 입력된 문자 수
    int i = 0;

    while (ch != 27) {
        if (index > 93) {
            break;
        }
        else if (index >= 5) {
            for (i = 0; i < index; i++) {

                if ((result[i] == -32 && result[i + 1] == 999) && (result[i + 2] == -32 && result[i + 3] == 997) && (char)result[i + 4] == 'a') {
                    printf("\n아도겐!\n");
                    // 문자 배열을 비움
                    clear(result, index);
                    index = 0;
                }

                if ((result[i] == -32 && result[i + 1] == 997) && (result[i + 2] == -32 && result[i + 3] == 999) && (result[i + 4] == -32 && result[i + 5] == 997) && (char)result[i + 6] == 'f') {
                    printf("\n뻐큐!\n");
                    // 문자 배열을 비움
                    clear(result, index);
                    index = 0;
                }

                if ((result[i] == -32 && result[i + 1] == 996) && (result[i + 2] == -32 && result[i + 3] == 996) && (char)result[i + 4] == 's') {
                    printf("\n안녕!\n");
                    // 문자 배열을 비움
                    clear(result, index);
                    index = 0;
                }

            }
        }

        ch = _getch();

        // 숫자를 준 이유는 알파벳과 구분하기 위함
        switch (ch)
        {
        case LEFT:
            if (result[index - 1] == -32) {
                printf("<- ");
                result[index] = 996;
            }
            else {
                printf("%c ", ch);
                result[index] = ch;
            }
            index++;
            break;
        case RIGHT:
            if (result[index - 1] == -32) {
                printf("-> ");
                result[index] = 997;
            }
            else {
                printf("%c ", ch);
                result[index] = ch;
            }
            index++;
            break;
        case UP:
            if (result[index - 1] == -32) {
                printf("↑ ");
                result[index] = 998;
            }
            else {
                printf("%c ", ch);
                result[index] = ch;
            }
            index++;
            break;
        case DOWN:
            if (result[index - 1] == -32) {
                printf("↓ ");
                result[index] = 999;
            }
            else {
                printf("%c ", ch);
                result[index] = ch;
            }
            index++;
            break;
        default:
            if (ch != -32) {
                printf("%c ", ch);
                result[index] = ch;
            }
            else {
                result[index] = ch;
            }
            index++;
            break;
        }
        Sleep(300);
    }
}