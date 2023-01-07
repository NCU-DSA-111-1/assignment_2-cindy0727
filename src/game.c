//#include "../inc/user.h"
#include "../inc/function.h"

int breaking = 0;
int savedone = 0;

int ireg = 0;
int cg = 0;
int tmpcg =0;


int game(int * rear1, int * rear2, int *front1, int *front2, int *count, user **tmpusermefrontptr, user **tmpuseryoufrontptr)
{
    //初始化雙方
    creat_user1(usermeptr);
    creat_user2(useryouptr);
    printf(" user1遊戲時間：00:00:00\n");
    printf(" user2遊戲時間：00:00:00\n\n");
    printchess(usermeptr, useryouptr, &chess_board);

    *tmpusermefrontptr = usermefrontptr;//存檔時的暫存
    *tmpuseryoufrontptr = useryoufrontptr;

    //開始下棋
    //user1輸入
    *rear1 += 1;
    usermeptr = addme(usermeptr);
    printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
    user1timer();
    scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
    if(usermeptr->input == 115)
    {
        printchess(usermeptr, useryouptr, &chess_board);
        printf("第一筆才不給你儲存資料 想不到吧哈哈 沒啦只是還要改linkedlist很麻煩所以第二手再儲存 感恩\n");
        printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
        user1timer();
        scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
    }
    usermeptr->origncol = usermeptr->input - 48;
    usermeptr->origncol = 10 - usermeptr->origncol;
    usermeptr->aftercol = 10 - usermeptr->aftercol;
    cg +=1;
    user1move(usermeptr, useryouptr);
    //system("clear");
    //printf("跳出來\n");
    printchess(usermeptr, useryouptr, &chess_board);
    //第二手開始進入迴圈
    while(1)
    {
        *rear2 += 1;
        if(cg > tmpcg)
        {
            useryouptr = addyou(useryouptr);
            ireg = 0;
        }
        else
        {
            useryouptr = youequal(useryouptr);
        }
        printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
        user2timer();
        scanf("%1s%d%d%d", &useryouptr->input, &useryouptr->orignrow, &useryouptr->aftercol, &useryouptr->afterrow);
        while(1)
        {
            if(useryouptr->input == 48)
            {
                //user2輸入為0代表user1悔棋
                if(ireg == 0)
                {
                    tmpcg = cg;
                }
                *rear1 = *rear1 - 1;
                if(*rear1 == (-1))
                {
                    printf("\n輸入不正確，請重新輸入\n");
                    *rear1 +=1;
                    break;
                }
                usermeptr = usermeptr->prev;
                *rear2 = *rear2 - 1;
                if(*rear2 == (-1))
                {
                    *rear2 +=1;
                    printf("\n輸入不正確，請重新輸入\n");
                    break;
                }
                useryouptr = useryouptr->prev;
                if((useryouptr->tmprow != (-1)) || (useryouptr->tmpcol != (-1)))//user1有吃掉user2的棋子
                {
                    useryouptr->userchess_board[useryouptr->tmprow][useryouptr->tmpcol] = useryouptr->tmp;
                    useryouptr->tmprow = -1;
                    useryouptr->tmpcol = -1;
                }
                cg -=1;
                ireg +=1;
                //system("clear");
                printchess(usermeptr, useryouptr, &chess_board);
                *rear1 += 1;
                
                if(cg > tmpcg)
                {
                    usermeptr = addme(usermeptr);
                    ireg = 0;
                }
                else
                {
                    usermeptr = meequal(usermeptr);
                }
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                user1timer();
                scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
                
                //user1輸入0代表user2悔棋
                if((usermeptr->input == 48))
                {
                    *rear2 -= 1;
                    if(*rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear2 +=1;
                        break;
                    }
                    useryouptr = useryouptr->prev;
                    *rear1 -= 1;
                    if(*rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear1 += 1;
                        break;
                    }
                    usermeptr = usermeptr->prev;
                    if((usermeptr->tmprow != (-1)) && (usermeptr->tmpcol != (-1)))//user2走的時候有吃掉user1的棋子
                    {
                        usermeptr->userchess_board[usermeptr->tmprow][usermeptr->tmpcol] = usermeptr->tmp;
                        usermeptr->tmprow = (-1);
                        usermeptr->tmpcol = (-1);
                    }
                    cg -=1;
                    ireg +=1;
                    //system("clear");
                    printchess(usermeptr, useryouptr, &chess_board);
                }
                //user1輸入s表示儲存 不儲存s
                else if(usermeptr->input == 115)
                {
                    //先寫到站存記憶體
                    savedone = 0;
                    if((*front1 > (*rear1-1)) && (*front2 > *rear2))
                    {
                        printf("真滴抱歉 目前不支援悔棋部分超過先前儲存部分 將直接結束遊戲\n");
                        return 0;
                    }
                    while((*front1 < (*rear1-1)) || (*front2 < *rear2))
                    {
                        if(*front1 > *front2)
                        {
                            *front2 +=1;
                            *tmpuseryoufrontptr = (*tmpuseryoufrontptr)->next;
                            user *tmp;
                            tmp = (user *)malloc(sizeof(user));
                            tmp->prev = tmp;
                            tmp->next = NULL;
                            tmp->orignrow =  (*tmpuseryoufrontptr)->orignrow;
                            tmp->origncol =  (*tmpuseryoufrontptr)->origncol;
                            tmp->afterrow =  (*tmpuseryoufrontptr)->afterrow;
                            tmp->aftercol =  (*tmpuseryoufrontptr)->aftercol;
                            userloadptr->next = tmp;
                            userloadptr = userloadptr->next;
                            *count +=1;
                        }
                        else if(*front1 <= *front2)
                        {
                            *front1 +=1;//因為第一筆資料在rear = 1的時候 所以事先動再移
                            *tmpusermefrontptr = (*tmpusermefrontptr)->next;
                            if(*front1 == 1)
                            {
                                userloadptr->orignrow = (*tmpusermefrontptr)->orignrow;
                                userloadptr->origncol = (*tmpusermefrontptr)->origncol;
                                userloadptr->afterrow = (*tmpusermefrontptr)->afterrow;
                                userloadptr->aftercol = (*tmpusermefrontptr)->aftercol;
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
                                tmp->orignrow = (*tmpusermefrontptr)->orignrow;
                                tmp->origncol = (*tmpusermefrontptr)->origncol;
                                tmp->afterrow = (*tmpusermefrontptr)->afterrow;
                                tmp->aftercol = (*tmpusermefrontptr)->aftercol;
                                tmp->next = tmp;
                                userloadptr = userloadptr->next;
                            }
                            *count +=1;
                        }   
                        savedone = 1;
                    }
                    //usermeptr = usermeptr->prev;
                    printf("\n儲存完畢 請重新輸入座標\n\n");
                    sleep(1);
                    printchess(usermeptr, useryouptr, &chess_board);
                    printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                    user1timer();
                    scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
                }    
                else//輸入非0可移動
                {
                    cg +=1;
                    usermeptr->origncol = usermeptr->input - 48;
                    usermeptr->origncol = 10 - usermeptr->origncol;
                    usermeptr->aftercol = 10 - usermeptr->aftercol;
                    user1move(usermeptr, useryouptr);
                    user1eatuser2(usermeptr,useryouptr);
                    //system("clear");
                    printchess(usermeptr, useryouptr, &chess_board);
                    //判斷勝利
                    if(whowins(&chess_board) == 1)
                    {
                        breaking = 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        return 1;
                        break;
                    }
                    else if(whowins(&chess_board) == 2)
                    {
                        breaking =1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        return 1;
                        break;
                    }
                }
                *rear2 += 1;
                if(cg > tmpcg)
                {
                    useryouptr = addyou(useryouptr);
                    ireg = 0;
                }
                else
                {
                    useryouptr = youequal(useryouptr);
                }
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                user2timer();
                scanf("%1s%d%d%d", &useryouptr->input, &useryouptr->orignrow, &useryouptr->aftercol, &useryouptr->afterrow);
            }
            //user2輸入s表示儲存
            else if(useryouptr->input == 115)
            {
                savedone = 0;
                if((*front1 > (*rear1-1)) && (*front2 > *rear2))
                {
                    printf("真滴抱歉 目前不支援悔棋部分超過先前儲存部分 將直接結束遊戲\n");
                    return 0;
                }
                while((*front1 < *rear1) || (*front2 < (*rear2-1)))
                {
                    if(*front1 > *front2)
                    {
                        *front2 +=1;
                        *tmpuseryoufrontptr = (*tmpuseryoufrontptr)->next;
                        user *tmp;
                        tmp = (user *)malloc(sizeof(user));
                        tmp->prev = userloadptr;
                        tmp->next = NULL;
                        tmp->orignrow = (*tmpuseryoufrontptr)->orignrow;
                        tmp->origncol = (*tmpuseryoufrontptr)->origncol;
                        tmp->afterrow = (*tmpuseryoufrontptr)->afterrow;
                        tmp->aftercol = (*tmpuseryoufrontptr)->aftercol;
                        userloadptr->next = tmp;
                        userloadptr = userloadptr->next;
                        *count +=1;
                    }
                    else if(*front1 <= *front2)
                    {
                        *front1 +=1;//因為第一筆資料在rear = 1的時候 所以事先動再移 
                        *tmpusermefrontptr = (*tmpusermefrontptr)->next;
                        if(*front1 == 1)
                            {
                                userloadptr->orignrow = (*tmpusermefrontptr)->orignrow;
                                userloadptr->origncol = (*tmpusermefrontptr)->origncol;
                                userloadptr->afterrow = (*tmpusermefrontptr)->afterrow;
                                userloadptr->aftercol = (*tmpusermefrontptr)->aftercol;
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
                                tmp->orignrow = (*tmpusermefrontptr)->orignrow;
                                tmp->origncol = (*tmpusermefrontptr)->origncol;
                                tmp->afterrow = (*tmpusermefrontptr)->afterrow;
                                tmp->aftercol = (*tmpusermefrontptr)->aftercol;
                                userloadptr->next = tmp;
                                userloadptr = userloadptr->next;
                            }
                            *count +=1;
                    }
                    savedone = 1;
                }
                //useryouptr = useryouptr->prev;
                printf("\n儲存完畢 請重新輸入座標\n\n");
                sleep(1);
                printchess(usermeptr, useryouptr, &chess_board);
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                user2timer();
                scanf("%1s%d%d%d", &useryouptr->input, &useryouptr->orignrow, &useryouptr->aftercol, &useryouptr->afterrow);
            }    
            else
            {
                break;
            }
        }
        if(breaking == 1)
        {
            break;
        }
        //rear2大於0才有辦法移動
        if(*rear2>0)
        {
            cg +=1;
            useryouptr->origncol = useryouptr->input - 48;
            useryouptr->origncol = 10 - useryouptr->origncol;
            useryouptr->aftercol = 10 - useryouptr->aftercol;
            user2move(useryouptr, usermeptr);
            user2eatuser1(useryouptr,usermeptr);
        }
        printchess(usermeptr, useryouptr, &chess_board);
        //判斷勝利
        if(whowins(&chess_board) == 1)
        {
            printf("\nuser1勝利！！！！\n\n\n");
            return 1;
            break;
        }
        else if(whowins(&chess_board) == 2)
        {
            printf("\nuser2勝利！！！！\n\n\n");
            return 1;
            break;
        }

        *rear1 += 1;
        if(cg > tmpcg)
        {
            usermeptr = addme(usermeptr);
            ireg = 0;
        }
        else
        {
            usermeptr = meequal(usermeptr);
        }
        printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
        user1timer();
        scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
        while(1)
        {
            if((usermeptr->input == 48))
            {
                if(ireg == 0)
                {
                    tmpcg = cg;
                }
                //user1輸入為0代表user2悔棋
                *rear2 -= 1;
                if(*rear2 == (-1))
                {
                    printf("\n輸入不正確，請重新輸入\n");
                    *rear2 +=1;
                    break;
                }
                useryouptr = useryouptr->prev;
                *rear1 -= 1;
                if(*rear1 == (-1))
                {
                    *rear1 +=1;
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
                cg -=1;
                ireg +=1;
                //system("clear");
                printchess(usermeptr, useryouptr, &chess_board);
                *rear2 += 1;
                if(cg > tmpcg)
                {
                    useryouptr = addyou(useryouptr);
                    ireg = 0;
                }
                else
                {
                    useryouptr = youequal(useryouptr);
                }
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                user2timer();
                scanf("%1s%d%d%d", &useryouptr->input, &useryouptr->orignrow, &useryouptr->aftercol, &useryouptr->afterrow);
                
                
                //user2輸入0代表user1悔棋
                if((useryouptr->input == 48))
                {
                    *rear1 = *rear1 - 1;
                    if(*rear1 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear1 +=1;
                        break;
                    }
                    usermeptr = usermeptr->prev;
                    *rear2 = *rear2 - 1;
                    if(*rear2 == (-1))
                    {
                        printf("\n輸入不正確，請重新輸入\n");
                        *rear2 +=1;
                        break;
                    }
                    useryouptr = useryouptr->prev;
                    if((useryouptr->tmprow != (-1)) && (useryouptr->tmpcol != (-1)))
                    {
                        useryouptr->userchess_board[useryouptr->tmprow][useryouptr->tmpcol] = useryouptr->tmp;
                        useryouptr->tmprow = (-1);
                        useryouptr->tmpcol = (-1);
                    }
                    cg -=1;
                    ireg +=1;
                    //system("clear");
                    printchess(usermeptr, useryouptr, &chess_board);
                }
                //user2輸入s儲存
                else if(useryouptr->input == 115)
                {
                    savedone = 0;
                    if((*front1 > (*rear1-1)) && (*front2 > *rear2))
                    {
                        printf("真滴抱歉 目前不支援悔棋部分超過先前儲存部分 將直接結束遊戲\n");
                        return 0;
                    }
                    while((*front1 < *rear1)|| (*front2 < (*rear2-1)))
                    {
                        if(*front1 > *front2)
                        {
                            *front2 +=1;
                            *tmpuseryoufrontptr = (*tmpuseryoufrontptr)->next;
                            user *tmp;
                            tmp = (user *)malloc(sizeof(user));
                            tmp->prev = userloadptr;
                            tmp->next = NULL;
                            tmp->orignrow = (*tmpuseryoufrontptr)->orignrow;
                            tmp->origncol = (*tmpuseryoufrontptr)->origncol;
                            tmp->afterrow = (*tmpuseryoufrontptr)->afterrow;
                            tmp->aftercol = (*tmpuseryoufrontptr)->aftercol;
                            userloadptr->next = tmp;
                            userloadptr = userloadptr->next;
                            *count +=1;
                        }
                        else if(*front1 <= *front2)
                        {
                            *front1 +=1;//因為第一筆資料在rear = 1的時候 所以事先動再移 
                            *tmpusermefrontptr = (*tmpusermefrontptr)->next;
                            if(*front1 == 1)
                            {
                                userloadptr->orignrow = (*tmpusermefrontptr)->orignrow;
                                userloadptr->origncol = (*tmpusermefrontptr)->origncol;
                                userloadptr->afterrow = (*tmpusermefrontptr)->afterrow;
                                userloadptr->aftercol = (*tmpusermefrontptr)->aftercol;
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
                                tmp->orignrow = (*tmpusermefrontptr)->orignrow;
                                tmp->origncol = (*tmpusermefrontptr)->origncol;
                                tmp->afterrow = (*tmpusermefrontptr)->afterrow;
                                tmp->aftercol = (*tmpusermefrontptr)->aftercol;
                                userloadptr->next = tmp;
                                userloadptr = userloadptr->next;
                            }
                            *count +=1;
                        }
                        savedone =1;
                    }
                    //useryouptr = useryouptr->prev;
                    printf("\n儲存完畢 請重新輸入座標\n\n");
                    sleep(1);
                    printchess(usermeptr, useryouptr, &chess_board);
                    printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                    user2timer();
                    scanf("%1s%d%d%d", &useryouptr->input, &useryouptr->orignrow, &useryouptr->aftercol, &useryouptr->afterrow);
                }    
                else
                {
                    cg +=1;
                    useryouptr->origncol = useryouptr->input - 48;
                    useryouptr->origncol = 10 - useryouptr->origncol;
                    useryouptr->aftercol = 10 - useryouptr->aftercol;
                    user2move(useryouptr, usermeptr);
                    user2eatuser1(useryouptr,usermeptr);
                    //system("clear");
                    printchess(usermeptr, useryouptr, &chess_board);
                    if(whowins(&chess_board) == 1)
                    {
                        breaking += 1;
                        printf("\nuser1勝利！！！！\n\n\n");
                        return 1;
                        break;
                    }
                    else if(whowins(&chess_board) == 2)
                    {
                        breaking += 1;
                        printf("\nuser2勝利！！！！\n\n\n");
                        return 1;
                        break;
                    }
                }
                *rear1 += 1;
                if(cg > tmpcg)
                {
                    usermeptr = addme(usermeptr);
                    ireg = 0;
                }
                else
                {
                    usermeptr = meequal(usermeptr);
                }
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                user1timer();
                scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
            }
            //user1輸入s表示儲存
            else if(usermeptr->input == 115)
            {
                savedone = 0;
                if((*front1 > (*rear1-1)) && (*front2 > *rear2))
                {
                    printf("真滴抱歉 目前不支援悔棋部分超過先前儲存部分 將直接結束遊戲\n");
                    return 0;
                }
                while((*front1 < (*rear1-1)) || (*front2 < *rear2))
                {
                    if(*front1 > *front2)
                    {
                        *front2 +=1;
                        *tmpuseryoufrontptr = (*tmpuseryoufrontptr)->next;
                        user *tmp;
                        tmp = (user *)malloc(sizeof(user));
                        tmp->prev = userloadptr;
                        tmp->next = NULL;
                        tmp->orignrow = (*tmpuseryoufrontptr)->orignrow;
                        tmp->origncol = (*tmpuseryoufrontptr)->origncol;
                        tmp->afterrow = (*tmpuseryoufrontptr)->afterrow;
                        tmp->aftercol = (*tmpuseryoufrontptr)->aftercol;
                        userloadptr->next = tmp;
                        userloadptr = userloadptr->next;
                        *count +=1;
                    }
                    else if(*front1 <= *front2)
                    {
                        *front1 +=1;//因為第一筆資料在rear = 1的時候 所以事先動再移 
                        *tmpusermefrontptr = (*tmpusermefrontptr)->next;
                        if(*front1 == 1)
                        {
                            userloadptr->orignrow = (*tmpusermefrontptr)->orignrow;
                            userloadptr->origncol = (*tmpusermefrontptr)->origncol;
                            userloadptr->afterrow = (*tmpusermefrontptr)->afterrow;
                            userloadptr->aftercol = (*tmpusermefrontptr)->aftercol;
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
                            tmp->orignrow = (*tmpusermefrontptr)->orignrow;
                            tmp->origncol = (*tmpusermefrontptr)->origncol;
                            tmp->afterrow = (*tmpusermefrontptr)->afterrow;
                            tmp->aftercol = (*tmpusermefrontptr)->aftercol;
                            userloadptr->next = tmp;
                            userloadptr = userloadptr->next;
                        }
                        *count +=1;
                    }
                    savedone =1;
                }
                //*rear1 -=1;
                //usermeptr = usermeptr->prev;
                printf("\n儲存完畢 請重新輸入座標\n\n");
                sleep(1);
                printchess(usermeptr, useryouptr, &chess_board);
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                user1timer();
                scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
            }    
            else
            {
                break;
            }
        }
        if(breaking == 1)
        {
            break;
        }
        if(*rear1 >0)
        {
            cg +=1;
            usermeptr->origncol = usermeptr->input - 48;
            usermeptr->origncol = 10 - usermeptr->origncol;
            usermeptr->aftercol = 10 - usermeptr->aftercol;
            user1move(usermeptr, useryouptr);
            user1eatuser2(usermeptr,useryouptr);
        }
        //system("clear");//本來就沒有
        printchess(usermeptr, useryouptr, &chess_board);
        if(whowins(&chess_board) == 1)//判斷誰贏
        {
            printf("\nuser1勝利！！！！\n\n\n");
            return 1;
            break;
        }
        else if(whowins(&chess_board) == 2)
        {
            printf("\nuser2勝利！！！！\n\n\n");
            return 1;
            break;
        }
    }
}

