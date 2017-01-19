#include <stdio.h>

void draw_chessboard();            //绘制棋盘
void arranged_the_piece(int, int); //放置棋子
void judge();                      //判断胜负
void init();                       //初始化

#define CHESSBOARD_SIZE 19 //19 * 19 size

char chessboard[CHESSBOARD_SIZE][CHESSBOARD_SIZE]; //整个棋盘

int main(int argc, char *argv[])
{
    init();
    draw_chessboard();

    return 0;
}

void draw_chessboard()
{
    int i, j;
    printf("   ");
    for (i = 0; i < CHESSBOARD_SIZE; i++)
    {
        printf(" %2d", i + 1);
    }
    printf("\n");

    for (i = 0; i < CHESSBOARD_SIZE; i++)
    {
        printf(" %2d", i + 1);
        for (j = 0; j < CHESSBOARD_SIZE; j++)
        {
            printf(" %2c", chessboard[i][j]);
        }
        printf("\n");
    }
}

void init()
{
    int i, j;
    for (i = 0; i < CHESSBOARD_SIZE; i++)
    {
        for (j = 0; j < CHESSBOARD_SIZE; j++)
        {
            chessboard[i][j] = '*';
        }
    }
}
