//#include "../inc/user.h"
#include "../inc/function.h"

//getopt要用到的
#include <ctype.h>
//#include <stdlib.h>
//#include <unistd.h>
extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;
int getopt(int argc, char * const *argv, const char *optstring);

int c;//getopt要用的
int mode = 0;//模式選項 1等於開新局 2等於讀檔 

int main(int argc, char ** argv)
{
    //宣告第一個userme userme其他東西在create宣告
    usermeptr = (user *)malloc(sizeof(user)); 
    usermeptr->prev = NULL;
    usermeptr->tmp = ' ';
    usermeptr->tmprow = -1;
    usermeptr->tmpcol = -1;
    usermeptr->orignrow = -1;
    usermeptr->origncol = -1;
    usermeptr->afterrow = -1;
    usermeptr->aftercol = -1;
    usermeptr->input = ' ';
    usermeptr->next = NULL;

    usermefrontptr = usermeptr;

    //宣告第一個userme userme其他東西在create宣告  
    useryouptr = (user *)malloc(sizeof(user));
    useryouptr->prev = NULL;
    useryouptr->tmp = ' ';
    useryouptr->tmprow = -1;
    useryouptr->tmpcol = -1;
    useryouptr->orignrow = -1;
    useryouptr->origncol = -1;
    useryouptr->afterrow = -1;
    useryouptr->aftercol = -1;
    useryouptr->input = ' ';
    useryouptr->next = NULL;

    useryoufrontptr = useryouptr;

    //初始userloadptr
    userloadptr = (user *)malloc(sizeof(user));
    userloadptr->prev = NULL;
    userloadptr->tmp = ' ';
    userloadptr->tmprow = -1;
    userloadptr->tmpcol = -1;
    userloadptr->orignrow = -1;
    userloadptr->origncol = -1;
    userloadptr->afterrow = -1;
    userloadptr->aftercol = -1;
    userloadptr->next = NULL;
    
    //初始化數值
    rearone = 0;
    reartwo = 0;
    frontone = 0;
    fronttwo = 0;
    loadfront = 0;
    
    int counter = 0;
    
    //開始getopt
    opterr = 0;
    while((c = getopt(argc, argv, "ns:l:")) != -1)
    {
        switch(c)
        {
            case 'n':

                mode = 1;
                break;

            case 's':
                if((fptr = fopen(optarg, "w")) == NULL)
                {
                    printf("File could not be open.\n");
                    return 0;
                }
                mode = 1;
                break;

            case 'l':
                if((fptr = fopen(optarg, "r")) == NULL)
                {
                    printf("File could not be open.\n");
                    return 0;
                }
                mode = 2;
                break;

                

        }

    }

    
    //開始遊戲
    if(mode == 1)
    {
        system("clear");
        initgame(&chess_board);
        if(game(&rearone, &reartwo, &frontone, &fronttwo, &counter, &tmpmefrontptr, &tmpyoufrontptr) == 0)
        {
            return 0;
        }
        else
        {
            while((fronttwo < reartwo) || (frontone < rearone))
            {
                if(frontone > fronttwo)
                {
                    fronttwo +=1;
                    tmpyoufrontptr = tmpyoufrontptr->next;
                    user *tmp;
                    tmp = (user *)malloc(sizeof(user));
                    tmp->prev = userloadptr;
                    tmp->next = NULL;
                    tmp->orignrow = tmpyoufrontptr->orignrow;//先寫到站存記憶體
                    tmp->origncol = tmpyoufrontptr->origncol;
                    tmp->afterrow = tmpyoufrontptr->afterrow;
                    tmp->aftercol = tmpyoufrontptr->aftercol;
                    userloadptr->next = tmp;
                    userloadptr = userloadptr->next;
                    counter +=1;
                }
                else if(frontone <= fronttwo)
                {
                    frontone +=1;//因為第一筆資料在rear = 1的時候 所以事先動再移 
                    tmpmefrontptr = tmpmefrontptr->next;
                    if(frontone == 1)
                    {
                        userloadptr->orignrow = tmpmefrontptr->orignrow;
                        userloadptr->origncol = tmpmefrontptr->origncol;
                        userloadptr->afterrow = tmpmefrontptr->afterrow;
                        userloadptr->aftercol = tmpmefrontptr->aftercol;
                        userloadptr->prev = NULL;
                        userloadptr->next = NULL;
                        //記著頭
                        loadfrontptr = userloadptr;
                    }
                    else
                    {
                        user *tmp;
                        tmp = (user *)malloc(sizeof(user));
                        tmp->prev = userloadptr;
                        tmp->next = NULL;
                        tmp->orignrow = tmpmefrontptr->orignrow;
                        tmp->origncol = tmpmefrontptr->origncol;
                        tmp->afterrow = tmpmefrontptr->afterrow;
                        tmp->aftercol = tmpmefrontptr->aftercol;
                        userloadptr->next = tmp;
                        userloadptr = userloadptr->next;
                    
                    }
                    counter +=1;
                    //printf("front1:%d\n", frontone);
                }   
            }
        }
        

        user *tmpfprint;//fprint時用到的暫存器
        tmpfprint = loadfrontptr;
        //printf("\n%d\n", counter);
        for(int c = 0; c < counter; c++)
        {
            //printf("%d \n",c);
            fprintf(fptr, "%d %d %d %d\n", tmpfprint->origncol, tmpfprint->orignrow, tmpfprint->aftercol, tmpfprint->afterrow);
            tmpfprint = tmpfprint->next;
        }
        fprintf(fptr, "%c",'^');
    }
    if(mode == 2)
    {
        system("clear");
        initgame(&chess_board);
        load();
    }
    

    fclose(fptr);

    return 0;
}

void initgame (user * chessboard)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        chessboard->userchess_board[i][j] = ' ';
    }
    
}

