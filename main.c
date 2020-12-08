#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include<mmsystem.h>
#include "snake_func.h"

int main()
{
    //游戏音乐 bgm
    //PlaySound(TEXT("E:\\code\\c\\snake-game\\Chinese_Tea.wav"), NULL, SND_FILENAME | SND_ASYNC );

    //游戏地图

    int size_x =8,size_y =11;
    COORD sk_hd_pos = {3,3},fd_pos = {4,4};




    char map[8][11];

    for(int row =0;row<size_x;row++){
        for(int col =0;col<size_y;col++){
           if( row==0 || row+1 == size_x||col==0||col+1 == size_y){
                map[row][col] ='#';
           }else{
                map[row][col] =' ';
           }
        }
    }

    map[sk_hd_pos.X][sk_hd_pos.Y] = '>';
    map[fd_pos.X][fd_pos.Y] = '*';











    //蛇的移动方向
    char direct = 'd';
    //获取标标准缓冲
    hOut= GetStdHandle(STD_OUTPUT_HANDLE);
    //创建新的缓冲区
    hBuf = CreateConsoleScreenBuffer(
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                NULL,CONSOLE_TEXTMODE_BUFFER,NULL);


    //结束提示语的位置
    COORD tip={4,2};
    //控制台字体基本样式
    SetConsoleTextAttribute(hOut,bs_col);
    //蛇头和蛇体位置判断
    struct snake sb = {sk_hd_pos.X,sk_hd_pos.Y,NULL},*sb_next = NULL;
    struct snake *sk_hd = &sb;
    while(1){
        sb_next = sk_hd;
        //清理屏幕
        system("cls");
        //获得键盘输入 非阻塞
        if(kbhit()) direct = getch();
        map[sk_hd->x][sk_hd->y] = ' ';
        //记录蛇头爬行之前的点
        int p_x = sk_hd->x,p_y = sk_hd->y;
        switch(direct){
            case 'w':{
                sk_hd->x -=1;
                break;
            }
            case 's':{
                sk_hd->x +=1;
                break;
            }
            case 'a':{
                sk_hd->y -=1;
                break;
            }
            case 'd':{
                sk_hd->y +=1;
                break;
            }
            default:{

            }
        } 
        //身体的爬行
        while(sb_next->bd_next){
           int ax = sb_next->bd_next->x,ay = sb_next->bd_next->y;
           map[p_x][p_y] = '+';
           map[ax][ay] = ' ';
           sb_next->bd_next->x = p_x;
           sb_next->bd_next->y = p_y;
           p_x = ax;
           p_y = ay;
           sb_next = sb_next->bd_next;
        }
        //判断游戏中的事件
        if(!(map[sk_hd->x][sk_hd->y] ^ '#')){
            //游戏结束... 要将蛇的身体释放
            SetConsoleCursorPosition(hOut,tip);
            SetConsoleTextAttribute(hOut,0x0c);
            printf("game over!\n");
            //释放内存
            sb_next = sk_hd;
            if(sb_next->bd_next){
                while(sb_next->bd_next){
                   struct snake *sp = sb_next;
                   sb_next = sb_next->bd_next;
                   free(sp);
                }
            }
            break;
        }else if(!(map[sk_hd->x][sk_hd->y] ^ '*')){
            //吃到食物
            map[p_x][p_y] = '+';
            //循环中不要声明普通的结构体变量，
            //struct snake sk_tail = {p_x,p_y,NULL};
            //声明的结构体也不要释放
            struct snake *sk_tail = (struct snake *) malloc(sizeof(struct snake));
            sk_tail->x = p_x;
            sk_tail->y = p_y;
            sk_tail->bd_next = NULL;
            //改变next重新指向蛇头
            sb_next = sk_hd;
            if(sb_next->bd_next){
                while(sb_next->bd_next){
                   sb_next = sb_next->bd_next;
                }
                sb_next->bd_next = sk_tail;
            }else{
                sk_hd->bd_next = sk_tail;
            }
            //设置食物
            food:{
                int nx = random(0,6),ny =random(0,8);
                if(map[nx][ny] != '+' && map[nx][ny] != '>' ){
                    map[nx][ny] ='*';
                }else{
                    sleep(200);
                    goto food;
                }
            }
        }
        map[sk_hd->x][sk_hd->y] = '>';
        printMap(map,11,8);
        Sleep(300);
        setbuf(stdin,NULL);
    }
    return 0;
}


