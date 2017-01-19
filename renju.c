#include <stdio.h>
#include <stdlib.h>

void draw_chessboard();       //绘制棋盘
void arranged_the_piece();    //放置棋子
int judge();                  //判断胜负, 1,继续 -  0,结束
void init();                  //初始化
int check_arranged(int, int); //检测下子是否合法, 1非法，0合法
int is_win(int, int);         //检测此位置是否有五颗连 1有  0没有

#define CHESSBOARD_SIZE 19 //19 * 19 size
#define BETWEEN_IN_SIZE(x) \
    ((x) > 0 && (x) <= CHESSBOARD_SIZE)
#define LOG(FormatString, ...) printf("(%s:%d)" FormatString "\n", __FUNCTION__, __LINE__, __VA_ARGS__)
#define DEBUG 0

char chessboard[CHESSBOARD_SIZE][CHESSBOARD_SIZE]; //整个棋盘
char player = 'A';

int main(int argc, char *argv[])
{
    init();
    draw_chessboard();

    while (judge())
    {
        arranged_the_piece();
        draw_chessboard();
    }

    return 0;
}

int check_arranged(int x, int y)
{
    int i;
    if (!BETWEEN_IN_SIZE(x) || !BETWEEN_IN_SIZE(y))
    {
        printf(" 请输入在 1 ~ %d", CHESSBOARD_SIZE);
        return 1;
    }

    if (chessboard[x - 1][y - 1] != '*')
    {
        printf(" 此位置已有棋子,请重新输入");
        return 1;
    }
}

void arranged_the_piece()
{
    int x, y;
    do
    {
        printf("\n\n 玩家%c 请输入 棋子位置:", player);
        scanf("%d %d", &x, &y);

    } while (check_arranged(x, y));

    chessboard[x - 1][y - 1] = player;

    player = player == 'A' ? 'B' : 'A'; //切换用户
}

char get_piece(int x, int y)
{
    if (BETWEEN_IN_SIZE(x + 1) && BETWEEN_IN_SIZE(y + 1))
    {
        return chessboard[x][y];
    }

    return '*';
}

int is_win(int x, int y)
{
    int a = x, b = y;
    int max_same_piece_size = 1;
    char point_piece = get_piece(x, y);

    if (point_piece == '*')
    {
        return 0;
    }

    //从x,y用贪婪的方式去找最长的同棋子，看看是不是大于5
    //case 竖子方向
    while (get_piece(x, y - 1) == point_piece)
    {
        max_same_piece_size++;
        y--;
    }
    x = a;
    y = b;

    while (get_piece(x, y + 1) == point_piece)
    {
        max_same_piece_size++;
        y++;
    }
    x = a;
    y = b;

    if (max_same_piece_size >= 5)
    {
        return 1;
    }
    max_same_piece_size = 1;

    //case 横方向
    while (get_piece(x - 1, y) == point_piece)
    {
        max_same_piece_size++;
        x--;
    }
    x = a;
    y = b;
    while (get_piece(x + 1, y) == point_piece)
    {
        max_same_piece_size++;
        x++;
    }
    x = a;
    y = b;
    if (max_same_piece_size >= 5)
    {
        return 1;
    }
    max_same_piece_size = 1;

    //case 左斜
    while (get_piece(x - 1, y - 1) == point_piece)
    {
        max_same_piece_size++;
        x--;
        y--;
    }
    x = a;
    y = b;
    while (get_piece(x + 1, y + 1) == point_piece)
    {
        max_same_piece_size++;
        x++;
        y++;
    }
    x = a;
    y = b;
    if (max_same_piece_size >= 5)
    {
        return 1;
    }
    max_same_piece_size = 1;

    //case 右斜
    while (get_piece(x - 1, y + 1) == point_piece)
    {
        max_same_piece_size++;
        x--;
        y++;
    }
    x = a;
    y = b;
    while (get_piece(x + 1, y - 1) == point_piece)
    {
        max_same_piece_size++;
        x++;
        y--;
    }
    x = a;
    y = b;
    if (max_same_piece_size >= 5)
    {
        return 1;
    }

    return 0;
}

int judge()
{
    int i, j;
    for (i = 0; i < CHESSBOARD_SIZE; i++)
    {
        for (j = 0; j < CHESSBOARD_SIZE; j++)
        {
            if (is_win(i, j))
            {
                printf(" 恭喜玩家%c 获得胜利!", player == 'A' ? 'B' : 'A');
                return 0;
            }
        }
    }
    return 1;
}

char *to_piece(int x, int y)
{
    if (chessboard[x][y] == '*')
    {
        return "*";
    }
    return chessboard[x][y] == 'A' ? " ◉" : " ◎";
}

void clearscr(void)
{
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
//add some other OSes here if needed
#else
#error "OS not supported."
//you can also throw an exception indicating the function can't be used
#endif
}

void draw_chessboard()
{
    // system("clear"); //clear sreen
    clearscr();

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
            printf(" %2s", to_piece(i, j));
        }
        printf("\n");
    }
}

void test()
{
    chessboard[0][0] = 'A';
    chessboard[1][1] = 'A';
    chessboard[2][2] = 'A';
    chessboard[3][3] = 'A';
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

    if (DEBUG)
    {
        test();
    }
}
