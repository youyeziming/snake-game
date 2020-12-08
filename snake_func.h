#include <windows.h>
#include <stdlib.h>
#include <time.h>






//输出初始化
HANDLE hOut,hBuf;
int bs_col = FOREGROUND_GREEN | FOREGROUND_INTENSITY;

//蛇
struct snake {
    int x;
    int y;
    struct snake *bd_next;
};

//地图打印函数
void printMap(char maps[8][11],int x,int y){

    for(int i =0;i<y;i++){
        for(int j =0;j<11;j++){
           //墙的设置
           maps[i][j] == '#'? SetConsoleTextAttribute(hOut,0xcc) :NULL;
           //食物的设置
           maps[i][j] == '*'? SetConsoleTextAttribute(hOut,0x99) :NULL;
           //蛇身的设置
           maps[i][j] == '+'? SetConsoleTextAttribute(hOut,0xaa) :NULL;
           //蛇头的设置
           maps[i][j] == '>'? SetConsoleTextAttribute(hOut,0x22) :NULL;
           printf("%2c",maps[i][j]);
           SetConsoleTextAttribute(hOut,bs_col);
        }
        printf("\n");
    }
}

//生成指定范围的随机数
int random(int begin,int end){
    srand(time(NULL));
    return  (end - (rand() % (end - begin)));
}
