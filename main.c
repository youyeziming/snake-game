#include <stdio.h>
#include <conio.h>
#include "snake_func.h"

int main()
{



    //游戏中的配置初始化
    initial_load();

    //游戏地图初始化
    char map[size_x][size_y];

    for(int row =0;row<size_x;row++){
        for(int col =0;col<size_y;col++){
           if( row==0 || row+1 == size_x||col==0||col+1 == size_y){
               //将地图四周设置为墙
                map[row][col] ='#';
           }else{
                map[row][col] =' ';
           }
        }
    }
    //在地图上设置好蛇头和食物的位置
    map[sk_hd_pos.X][sk_hd_pos.Y] = '>';
    map[fd_pos.X][fd_pos.Y] = '*';
    //蛇的移动方向
    char direct = 'd';

    //控制台字体基本样式
    SetConsoleTextAttribute(hOut,bs_col);
    //蛇头和蛇体位置判断
    struct snake sb = {sk_hd_pos.X,sk_hd_pos.Y,NULL},*sb_next = NULL;
    struct snake *sk_hd = &sb;
    while(1){
        sb_next = sk_hd;
        //清理屏幕 双缓冲模式下可以不用
        //system("cls");
        //获得键盘输入
        if(kbhit()){
            char key = direct;
            direct = getch();
            //排除其它键
            direct = direct == 'q' || direct == 'a' || direct == 'w' || direct == 's'|| direct == 'd' ? direct : key;
            switch(key){
                case 'w':{
                    if(direct  == 's' && length !=0) direct = key;
                    break;
                }
                case 's':{
                    if(direct   == 'w'  && length !=0)
                        direct = key;
                    break;
                }
                case 'a':{
                    if(direct   == 'd'  && length !=0)
                        direct = key;
                    break;
                }
                case 'd':{
                    if(direct  == 'a'  && length !=0)
                        direct = key;
                    break;
                }
                case 'q':{
                    switch(direct){
                        case 'w':{
                            map[sk_hd->x -1][sk_hd->y] == '+'?direct = key:NULL;
                            break;
                        }
                        case 's':{
                            map[sk_hd->x +1][sk_hd->y] == '+'?direct = key:NULL;
                            break;
                        }
                        case 'a':{
                            map[sk_hd->x][sk_hd->y -1] == '+'?direct = key:NULL;
                            break;
                        }
                        case 'd':{
                            map[sk_hd->x][sk_hd->y +1] == '+'?direct = key:NULL;
                            break;
                        }
                    }
                }
            }
        }

        //清空之前爬行点
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
        if(!(map[sk_hd->x][sk_hd->y] ^ '#') || !(map[sk_hd->x][sk_hd->y] ^ '+')&&direct !='q'){
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
            length++;
            //循环中不要声明普通的结构体变量,否则内存地址相同
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
            //食物的随机出现
            HANDLE TEatFood = CreateThread((LPSECURITY_ATTRIBUTES) 0,0,
                                  (LPTHREAD_START_ROUTINE) eatFood,
                                  (LPVOID)map, 0,0);
        }
        map[sk_hd->x][sk_hd->y] = '>';

        //打印的方法
        //printMap(&map,size_x,size_y);
        //双缓冲的方法
        double_cache(&map,size_x,size_y);
        Sleep(300);
        setbuf(stdin,NULL);
    }

    return 0;
}


