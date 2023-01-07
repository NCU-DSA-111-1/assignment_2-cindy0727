//#include "../inc/user.h"
#include "../inc/function.h"

int rear1 = 0;
int rear2 = 0;
int front1 = 0;
int front2 = 0;
int breakload = 0;
char bof;
int c;//計算第幾手
int tmpc;//從哪一手開始往回 因為要判定哪一手開始要讀資料
int ire ;//發現從往回的第一筆c不用剪1 做紀錄用

void load()
{
    c = 0;
    tmpc = 0;
    ire =0;
    //初始化雙方
    creat_user1(usermeptr);//原始棋盤
    creat_user2(useryouptr);//原始棋盤
    printchess(usermeptr, useryouptr, &chess_board);

    //開始下棋
    //user1輸入
    rear1 += 1;
    usermeptr = addme(usermeptr);
    printf("\n輸入b往回一步，輸入f下一步:");
    scanf("%1s", &bof);
    if(bof == 'b')
    {
        printf("輸入不正確，請重新輸入:");
        scanf("%1s", &bof);
    }
    if(bof == 'f')
    {
        fscanf(fptr,"%d%d%d%d", &usermeptr->origncol, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
        c +=1;
        user1move(usermeptr, useryouptr);
        system("clear");
        printchess(usermeptr, useryouptr, &chess_board);
    }
    //第二手開始進入迴圈
    while(1)
    {
        rear2 += 1;
        c +=1;
        if(c > tmpc)
        {
            useryouptr = addyou(useryouptr);
            ire = 0;
            c -=1;
        }
        else
        {
            useryouptr = youequalload(useryouptr);
            c -=1;
        }

        printf("輸入b往回一步，輸入f下一步:");
        scanf("%1s", &bof);
        while(1)
        {
            if(bof == 'b')
            {
                if(ire == 0)
                {
                    tmpc = c;
                }
                //user2輸入為b代表user1悔棋
                rear1 = rear1 - 1;
                if(rear1 == (-1))
                {
                    printf("\n輸入不正確，請重新輸入\n");
                    rear1 +=1;
                    break;
                }
                usermeptr = usermeptr->prev;
                rear2 = rear2 - 1;
                if(rear2 == (-1))
                {
                    rear2 +=1;
                    printf("\n輸入不正確，請重新輸入\n");
                    break;
                }
                useryouptr = useryouptr->prev;
                if((useryouptr->tmprow != (-1)) && (useryouptr->tmpcol != (-1)))//user1有吃掉user2的棋子
                {
                    useryouptr->userchess_board[useryouptr->tmprow][useryouptr->tmpcol] = useryouptr->tmp;
                    useryouptr->tmprow = (-1);
                    useryouptr->tmpcol = (-1);
                }
                c -=1;
                ire +=1;
                system("clear");
                printchess(usermeptr, useryouptr, &chess_board);
                rear1 += 1;
                c +=1;
                if(c > tmpc)
                {
                    usermeptr = addme(usermeptr);
                    ire = 0;
                    c -=1;
                }
                else
                {
                    usermeptr = meequalload(usermeptr);
                    c -=1;
                }

                printf("輸入b往回一步，輸入f下一步:");
                scanf("%1s", &bof);
                
                //user1輸入b代表user2悔棋
                if(bof == 'b')
                {
                    rear2 -= 1;
                    if(rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        rear2 +=1;
                        break;
                    }
                    useryouptr = useryouptr->prev;
                    rear1 -= 1;
                    if(rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        rear1 += 1;
                        break;
                    }
                    usermeptr = usermeptr->prev;
                    if((usermeptr->tmprow != (-1)) && (usermeptr->tmpcol != (-1)))//user2走的時候有吃掉user1的棋子
                    {
                        usermeptr->userchess_board[usermeptr->tmprow][usermeptr->tmpcol] = usermeptr->tmp;
                        usermeptr->tmprow = (-1);
                        usermeptr->tmpcol = (-1);
                    }
                    c -=1;
                    ire +=1;
                    system("clear");
                    printchess(usermeptr, useryouptr, &chess_board);
                }
                else
                {
                    c +=1;
                    user1move(usermeptr, useryouptr);
                    user1eatuser2(usermeptr,useryouptr);
                    system("clear");
                    printchess(usermeptr, useryouptr, &chess_board);
                    //判斷勝利
                    if(whowins(&chess_board) == 1)
                    {
                        breakload = 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        break;
                    }
                    else if(whowins(&chess_board) == 2)
                    {
                        breakload =1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        break;
                    }
                }
                rear2 += 1;
                c +=1;
                if(c > tmpc)
                {
                    useryouptr = addyou(useryouptr);
                    ire = 0;
                    c -=1;
                }
                else
                {
                    useryouptr = youequalload(useryouptr);
                    c -=1;
                }
                printf("輸入b往回一步，輸入f下一步:");
                scanf("%1s", &bof);
            }
            else
            {
                break;
            }
        }
        if(breakload == 1)
        {
            break;
        }
        //rear2大於0才有辦法移動
        if(rear2>0)
        {
            c +=1;
            if(c > tmpc)
            {
                fscanf(fptr,"%d%d%d%d", &useryouptr->origncol, &useryouptr->orignrow, &useryouptr->aftercol, &useryouptr->afterrow);
                ire = 0;
            }
            user2move(useryouptr, usermeptr);
            user2eatuser1(useryouptr,usermeptr);
        }
        system("clear");
        printchess(usermeptr, useryouptr, &chess_board);
        //判斷勝利
        if(whowins(&chess_board) == 1)
        {
            printf("\nuser1勝利！！！！\n\n\n");
            break;
        }
        else if(whowins(&chess_board) == 2)
        {
            printf("\nuser2勝利！！！！\n\n\n");
            break;
        }

        rear1 += 1;
        c +=1;
        if(c > tmpc)
        {
            usermeptr = addme(usermeptr);
            ire = 0;
            c -=1;
        }
        else
        {
            usermeptr = meequalload(usermeptr);
            c -=1;
        }

        printf("輸入b往回一步，輸入f下一步:");
        scanf("%1s", &bof);
        while(1)
        {
            if(bof == 'b')
            {
                if(ire == 0)
                {
                    tmpc = c;
                }
                rear2 -= 1;
                if(rear2 == (-1))
                {
                    printf("\n輸入不正確，請重新輸入\n");
                    rear2 +=1;
                    break;
                }
                useryouptr = useryouptr->prev;
                rear1 -= 1;
                if(rear1 == (-1))
                {
                    rear1 +=1;
                    printf("\n輸入不正確，請重新輸入\n");
                    break;
                }
                usermeptr = usermeptr->prev;
                if((usermeptr->tmprow != (-1)) && (usermeptr->tmpcol != (-1)))
                {
                    usermeptr->userchess_board[usermeptr->tmprow][usermeptr->tmpcol] = usermeptr->tmp;
                    usermeptr->tmprow = (-1);
                    usermeptr->tmpcol = (-1);
                }
                c -=1;
                ire +=1;
                system("clear");
                printchess(usermeptr, useryouptr, &chess_board);
                rear2 += 1;
                c +=1;
                if(c > tmpc)
                {
                    useryouptr = addyou(useryouptr);
                    ire = 0;
                    c -=1;
                }
                else
                {
                    useryouptr = youequalload(useryouptr);
                    c -=1;
                }
                printf("輸入b往回一步，輸入f下一步:");
                scanf("%1s", &bof);
                
                
                //user2輸入b代表user1悔棋
                if(bof == 'b')
                {
                    rear1 = rear1 - 1;
                    if(rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        rear1 +=1;
                        break;
                    }
                    usermeptr = usermeptr->prev;
                    rear2 = rear2 - 1;
                    if(rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        rear2 +=1;
                        break;
                    }
                    useryouptr = useryouptr->prev;
                    if((useryouptr->tmprow != (-1)) && (useryouptr->tmpcol != (-1)))
                    {
                        useryouptr->userchess_board[useryouptr->tmprow][useryouptr->tmpcol] = useryouptr->tmp;
                        useryouptr->tmprow = (-1);
                        useryouptr->tmpcol = (-1);
                    }
                    c -=1;
                    ire +=1;
                    system("clear");
                    printchess(usermeptr, useryouptr, &chess_board);
                }    
                else
                {
                    c +=1;
                    user2move(useryouptr, usermeptr);
                    user2eatuser1(useryouptr,usermeptr);
                    system("clear");
                    printchess(usermeptr, useryouptr, &chess_board);
                    if(whowins(&chess_board) == 1)
                    {
                        breakload += 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        break;
                    }
                    else if(whowins(&chess_board) == 2)
                    {
                        breakload += 1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        break;
                    }
                }
                rear1 += 1;
                c +=1;
                if(c > tmpc)
                {
                    usermeptr = addme(usermeptr);
                    ire = 0;
                    c -=1;
                }
                else
                {
                    usermeptr = meequalload(usermeptr);
                    c -=1;
                }
                printf("輸入b往回一步，輸入f下一步:");
                scanf("%1s", &bof);
            }    
            else
            {
                break;
            }
        }
        if(breakload == 1)
        {
            break;
        }
        if(rear1 >0)
        {
            c +=1;
            if(c > tmpc)
            {
                fscanf(fptr,"%d%d%d%d", &usermeptr->origncol, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
                ire = 0;
            }
            user1move(usermeptr, useryouptr);
            user1eatuser2(usermeptr,useryouptr);
        }
        system("clear");
        printchess(usermeptr, useryouptr, &chess_board);
        if(whowins(&chess_board) == 1)//判斷誰贏
        {
            printf("\nuser1勝利！！！！\n\n\n");
            break;
        }
        else if(whowins(&chess_board) == 2)
        {
            printf("\nuser2勝利！！！！\n\n\n");
            break;
        }
    }
}

