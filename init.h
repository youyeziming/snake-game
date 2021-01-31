#include <windows.h>
#include<mmsystem.h>

HANDLE hOut,hBuf;
int size_x =8,size_y =15,nx,ny,length;
COORD sk_hd_pos,fd_pos,tip;

int bs_col = FOREGROUND_GREEN | FOREGROUND_INTENSITY;




void initial_load(){
    system("cls");
    //游戏音乐 bgm
    //PlaySound(TEXT("E:\\code\\c\\snake-game\\Chinese_Tea.wav"), NULL, SND_FILENAME | SND_ASYNC );
    sk_hd_pos.X = 3;
    sk_hd_pos.Y = 3;
    fd_pos.X = 4;
    fd_pos.Y = 4;
    tip.X = size_x;
    tip.Y = size_y /4;


    //获取标标准缓冲
    hOut= GetStdHandle(STD_OUTPUT_HANDLE);


    //创建新的缓冲区
    hBuf = CreateConsoleScreenBuffer(
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                NULL,CONSOLE_TEXTMODE_BUFFER,NULL);





    CONSOLE_CURSOR_INFO ci = {1,0};

    SetConsoleCursorInfo(hOut,&ci);
    SetConsoleCursorInfo(hBuf,&ci);

    COORD size = {60,30};
    SetConsoleScreenBufferSize(hOut,size);
    SetConsoleScreenBufferSize(hBuf,size);


    //SetConsoleTitle('1');
}
