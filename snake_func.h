#include "init.h"
#include <stdlib.h>
#include <time.h>

/**
 *@author YYZiMig
 * @description 这是一个我自己制作的贪吃蛇游戏,用到了最基本的链表,和一些windows 的api
 * 加入双缓冲
 *
 * 地图
 *  # 为墙
 *  > 为蛇头
 *  + 为蛇身
 *  * 为食物
 *  + weishesheng
 *
 */



extern HANDLE hOut,hBuf;
extern int bs_col,size_x,size_y,nx,ny,length;
extern COORD sk_hd_pos,fd_pos,tip;
void eatFood(char map[size_x][size_y]);




//蛇
struct snake {
    int x;
    int y;
    struct snake *bd_next;
};

void eatFood(char map[size_x][size_y]){
    food:
        nx =random(1,size_x-2 );
        ny=random(1,size_y-2 );
        if(map[nx][ny] != '+' && map[nx][ny] != '>' && map[nx][ny] != '#'){
            map[nx][ny] ='*';
            fd_pos.X = nx;
            fd_pos.Y = ny;
        }else
            goto food;
}


//地图打印函数 控制台会一直闪 地图越大,闪的越频繁
void printMap(char *maps,int x,int y){
    for(int i =0;i<x;i++){
        for(int j =0;j<y;j++){
           //指针偏移量
           int offset = j + y*i;
           //墙的设置
           maps[offset] == '#'? SetConsoleTextAttribute(hOut,0xcc) :NULL;
           //食物的设置
           maps[offset] == '*'? SetConsoleTextAttribute(hOut,0x99) :NULL;
           //蛇身的设置
           maps[offset] == '+'? SetConsoleTextAttribute(hOut,0xaa) :NULL;
           //蛇头的设置
           maps[offset] == '>'? SetConsoleTextAttribute(hOut,0x22) :NULL;
           printf("%2c",maps[offset]);
           //设置为默认样式
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

//双缓冲 控制台一直闪 需要将控制台的滚动条给隐藏掉
void double_cache(char *map,unsigned int x ,unsigned int y){
     //控制双缓冲切换的开关变量静态的不会重新加载
     static  int  flag = 0;
     //开始变换开关
     flag ^=1;
     //偏移变量,用来偏移空格
     int index = 0;
     //字符信息
     CHAR_INFO CharInfo;
     //字符信息数组
     CHAR_INFO charInfoAarray[x*y*2];

     for (int i = 0; i < x; i++){
         for (int j = 0; j < y; j++){
             int offset = j + y * i;
             switch(map[offset]){
                case '#':{
                  //墙的设置
                 CharInfo.Attributes =0xcc;
                 break;
                }
                case '*':{
                 //食物的设置
                 CharInfo.Attributes =0x99;
                 break;
                }
                case '+':{
                 //蛇身的设置
                 CharInfo.Attributes =0xaa;
                 break;
                }
                case '>':{
                 //蛇头的设置
                 CharInfo.Attributes =0x22;
                 break;
                }
                default:{
                 //默认样式设置
                    CharInfo.Attributes =bs_col;
                    break;
                }
             }


             CharInfo.Char.UnicodeChar = ' ';
             charInfoAarray[index] = CharInfo;
             index++;

             CharInfo.Char.UnicodeChar = map[offset];
             charInfoAarray[index] = CharInfo;
             index++;
         }
     }
    //固定值(控制台窗口固定的属性值) x和y的值是相反的
     COORD BufferSize = {y*2,x};
     //缓冲区左上角的起始位置
     COORD BufferPos = { 0, 0 };
     //显示多大的缓冲区: 大小是一个矩形
     SMALL_RECT rect = { 0, 0, y*2,x};

     //将地图的信息写入两个缓冲区中
     WriteConsoleOutput(hBuf, charInfoAarray, BufferSize, BufferPos, &rect);
     WriteConsoleOutput(hOut, charInfoAarray, BufferSize, BufferPos, &rect);
     //利用开关变量控制缓冲区的切换
     if(flag){
         SetConsoleActiveScreenBuffer(hOut);
     }else{
         SetConsoleActiveScreenBuffer(hBuf);
     }
}
