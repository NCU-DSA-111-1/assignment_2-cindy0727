//#include "../inc/user.h"
#include "../inc/function.h"

int i, j;
extern user chess_board;
extern user *usermeptr;
extern user *useryouptr;

void user1move(user * user11, user * user22)
{
    //移動棋子
    while(1)
    {
        if((user11->userchess_board[(user11->orignrow -1)][(user11->origncol -1)] != ' ') && (user11->userchess_board[(user11->afterrow -1)][(user11->aftercol -1)]) == ' ')
        {
            if(user1chessandmove(user11, user22) == 1)
            {
                user11->userchess_board[(user11->afterrow -1)][(user11->aftercol -1)] = user11->userchess_board[(user11->orignrow -1)][(user11->origncol -1)];
                user11->userchess_board[(user11->orignrow -1)][(user11->origncol -1)] = ' ';
                break;
            }
            else
            {
                printf("\n輸入不正確 請重新輸入\n");
                printchess(usermeptr, useryouptr, &chess_board);
                printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                user1timer();
                scanf("%1s%d%d%d", &user11->input, &user11->orignrow, &user11->aftercol, &user11->afterrow);
                user11->origncol = user11->input - 48;
                user11->origncol = 10 - user11->origncol;
                user11->aftercol = 10 - user11->aftercol;
            }
        }
        else
        {
            printf("\n輸入不正確 請重新輸入\n");
            printchess(usermeptr, useryouptr, &chess_board);
            printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
            user1timer();
            scanf("%1s%d%d%d", &user11->input, &user11->orignrow, &user11->aftercol, &user11->afterrow);
            user11->origncol = user11->input - 48;
            user11->origncol = 10 - user11->origncol;
            user11->aftercol = 10 - user11->aftercol;
        }
    }
}

void user2move(user * user22, user * user11)
{
    //移動棋子
    while(1)
    {
        if((user22->userchess_board[(user22->orignrow -1)][(user22->origncol -1)] != ' ') && (user22->userchess_board[(user22->afterrow -1)][(user22->aftercol -1)]) == ' ')
        {
            if(user2chessandmove(user22, user11) == 1)
            {
                user22->userchess_board[(user22->afterrow -1)][(user22->aftercol -1)] = user22->userchess_board[(user22->orignrow -1)][(user22->origncol -1)];
                user22->userchess_board[(user22->orignrow -1)][(user22->origncol -1)] = ' ';
                break;
            }
            else
            {
                printf("\n輸入不正確 請重新輸入\n");
                printchess(usermeptr, useryouptr, &chess_board);
                printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
                user2timer();
                scanf("%1s%d%d%d", &user22->input, &user22->orignrow, &user22->aftercol, &user22->afterrow);
                user22->origncol = user22->input - 48;
                user22->origncol = 10 - user22->origncol;
                user22->aftercol = 10 - user22->aftercol;
            }
        }
        else
        {
            printf("\n輸入不正確 請重新輸入\n");
            printchess(usermeptr, useryouptr, &chess_board);
            printf("依據圖上座標 User2 輸入想移動的棋子的原始座標空格移動後的位置座標:\n輸入s 0 0 0表示儲存 輸入0 0 0 0 表示悔棋\n");
            user2timer();
            scanf("%1s%d%d%d", &user22->input, &user22->orignrow, &user22->aftercol, &user22->afterrow);
            user22->origncol = user22->input - 48;
            user22->origncol = 10 - user22->origncol;
            user22->aftercol = 10 - user22->aftercol;
        }
    }
}

//user1吃掉user2的子
void user1eatuser2(user * user1, user * user2)
{
    if(user2->userchess_board[user1->afterrow -1][user1->aftercol -1] != ' ')
    {
        //暫存user2被吃掉的棋
        user2->tmp = user2->userchess_board[user1->afterrow -1][user1->aftercol -1];
        user2->tmprow = user1->afterrow -1;
        user2->tmpcol = user1->aftercol -1;
        user2->userchess_board[user1->afterrow -1][user1->aftercol -1] = ' ';
    }
}

//user2吃掉user1的子
void user2eatuser1(user * user2, user * user1)
{
    if(user1->userchess_board[user2->afterrow -1][user2->aftercol -1] != ' ')
    {
        //暫存user1被吃掉的棋
        user1->tmp = user1->userchess_board[user2->afterrow -1][user2->aftercol -1];
        user1->tmprow = user2->afterrow - 1;
        user1->tmpcol = user2->aftercol - 1;
        user1->userchess_board[user2->afterrow -1][user2->aftercol -1] = ' ';
    }
}

//user1贏回傳1 user2贏回傳2 沒人贏回傳0
int whowins(user * chessboard)
{
    int tmp1=0;
    int tmp2=0;
    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            if(chessboard->userchess_board[i][j] =='U')
            {
                tmp1 = 1;
            }
            else if(chessboard->userchess_board[i][j] =='w')
            {
                tmp2 =1;
            }
        }
    }

    if((tmp1 == 1)&&(tmp2 == 0))
    {
        return 1;
    }
    else if((tmp1 == 0)&&(tmp2 == 1))
    {
        return 2;
    }
    else
    {
        return 0;
    }

}

//哪個棋子和如何移動 符合規則回傳1 不符合回傳0
int user1chessandmove(user  * user1, user * user2)
{
    switch(user1->userchess_board[(user1->orignrow)-1][(user1->origncol)-1])
    {
        //步兵只能向前1格
        case 'B':
            if((((user1->aftercol)-(user1->origncol)) != 0) || (((user1->afterrow)-(user1->orignrow))!=(-1)))
            {
                return 0;
            }
            else if(user1->afterrow == 1)//判斷是否不能走
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;

        //香車只能向前衝刺且不能跨越其他人
        case 'H':
    
            if((((user1->aftercol)-(user1->origncol)) != 0) || (((user1->afterrow)-(user1->orignrow))>=0))
            {
                return 0;
            }
            else if(user1->afterrow == 1)//判斷是否不能走
            {
                return 0;
            }
            else
            {
                for(i=((user1->afterrow)); i < ((user1->orignrow)-1); i++)   
                {
                    if((user1->userchess_board[i][(user1->origncol)-1] != ' ') || (user2->userchess_board[i][(user1->origncol)-1]) != ' ')
                    {
                        return 0;
                    }
                }
                if(user1->userchess_board[(user1->afterrow)-1][(user1->aftercol)-1] != ' ')
                {
                    return 0;
                }
                return 1;
            }
            break;

        //桂馬只能往前2格且往右或往左1格
        case 'G':
            if((((user1->afterrow)-(user1->orignrow)) == (-2)) && ((((user1->aftercol)-(user1->origncol)) == 1) || (((user1->aftercol)-(user1->origncol)) == (-1))))
            {
                return 1;
            }
            else if(user1->afterrow == 2)//判斷是否不能走
            {
                return 0;
            }
            else 
            {
                return 0;
            }
            break;

        //銀將只能斜角方向一格或是前方一格
        case 'I':
            if((((((user1->afterrow)-(user1->orignrow)) == 1) || (((user1->afterrow)-(user1->orignrow)) == (-1))) && ((((user1->aftercol)-(user1->origncol)) == 1) || (((user1->aftercol)-(user1->origncol)) == (-1)))) || ((((user1->afterrow)-(user1->orignrow)) == (-1)) && (((user1->aftercol)-(user1->origncol))== 0))) 
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;

        //金將只能向前後左右左前右前一格
        case 'K':
            if((((user1->afterrow)-(user1->orignrow)) >= 2) || (((user1->afterrow)-(user1->orignrow)) <= (-2)) || (((user1->aftercol)-(user1->origncol)) >= 2) || (((user1->aftercol)-(user1->origncol)) <= (-2)))
            {
                return 0;
            }
            else 
            {
                if((((user1->afterrow)-(user1->orignrow)) == 1))
                {
                    if((((user1->aftercol)-(user1->origncol)) ==0))
                    {
                        return 1;
                    }
                    return 0;
                }
                return 1;
            }
            break;

        //角行只能斜向衝刺且不可繞過棋子
        case 'J':
            if(((double)(((user1->afterrow)-(user1->orignrow))/((user1->aftercol)-(user1->origncol))) ==1.0) || ((double)(((user1->afterrow)-(user1->orignrow))/((user1->aftercol)-(user1->origncol))) ==(-1.0)))
            {
                if((user1->afterrow < (user1->orignrow)) && (user1->aftercol > user1->origncol))
                {
                    for(i = (user1->orignrow-2), j = (user1->origncol);i >= (user1->afterrow), j <= (user1->aftercol-2); i--,j++)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][user1->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                    
                }
                    
                
                if((user1->afterrow > (user1->orignrow)) && (user1->aftercol > user1->origncol))
                {
                    for(i = (user1->orignrow), j = (user1->origncol);i <= (user1->afterrow-2), j <= (user1->aftercol-2); i++,j++)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][user1->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                
                if((user1->afterrow < (user1->orignrow)) && (user1->aftercol < user1->origncol))
                {
                    for(i = (user1->orignrow-2), j = (user1->origncol-2);i >= (user1->afterrow), j >= (user1->aftercol); i--,j--)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][user1->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                    
                }

                if((user1->afterrow > (user1->orignrow)) && (user1->aftercol < user1->origncol))
                {
                    for(i = (user1->orignrow), j = (user1->origncol-2);i <= (user1->afterrow-2), j >= (user1->aftercol); i++,j--)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][user1->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                    
                }
            }
            else
            {
                return 0;
            }
            break;

        //飛車只能橫向或縱向移動 不可跨過棋子
        case 'F':
            if((((user1->afterrow)-(user1->orignrow)) == 0) || (((user1->aftercol)-(user1->origncol)) == 0))
            {
                
                if(user1->afterrow < (user1->orignrow))
                {
                    for(i=(user1->orignrow-2); i >= (user1->afterrow); i--)   
                    {
                        if((user1->userchess_board[i][(user1->origncol)-1] != ' ') || (user2->userchess_board[i][(user1->origncol)-1]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][(user1->aftercol)-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user1->afterrow > (user1->orignrow))
                {
                    for(i=(user1->orignrow); i <= (user1->afterrow-2); i++)   
                    {
                        if((user1->userchess_board[i][(user1->origncol)-1] != ' ') || (user2->userchess_board[i][(user1->origncol)-1]) != ' ')
                        {
                            return 0;
                            
                        }
                    }
                    if(user1->userchess_board[user1->afterrow-1][(user1->aftercol)-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user1->aftercol > user1->origncol)
                {
                    for(i=(user1->origncol); i <= (user1->aftercol-2); i++)   
                    {
                        if((user1->userchess_board[((user1->orignrow)-1)][i] != ' ') || (user2->userchess_board[((user1->orignrow)-1)][i]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user1->userchess_board[((user1->afterrow)-1)][user1->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user1->aftercol < user1->origncol)
                {
                    for(i=(user1->origncol-2); i >= (user1->aftercol); i--)   
                    {
                        if((user1->userchess_board[((user1->orignrow)-1)][i] != ' ') || (user2->userchess_board[((user1->orignrow)-1)][i]) != ' ')
                        {
                            printf("1");
                            return 0;
                        }
                    }
                    if(user1->userchess_board[((user1->afterrow)-1)][user1->aftercol-1] != ' ')
                    {
                        printf("2");
                        return 0;
                    }
                    return 1;
                }
            }
            else
            {
                return 0;
            }
            break;

        //玉將八方一格
        default:
            if((((user1->afterrow)-(user1->orignrow)) >= 2) || (((user1->afterrow)-(user1->orignrow)) <= (-2)) || (((user1->aftercol)-(user1->origncol)) >= 2) || (((user1->aftercol)-(user1->origncol)) <= (-2)))
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;
    }
}

//哪個棋子和如何移動
int user2chessandmove(user * user2, user * user1)
{
    switch(user2->userchess_board[(user2->orignrow)-1][(user2->origncol)-1])
    {
        //步兵只能向前1格
        case 'b':
            if((((user2->aftercol)-(user2->origncol)) != 0) || (((user2->afterrow)-(user2->orignrow))!= 1 ))
            {
                return 0;
            }
            else if(user2->afterrow == 9)//判斷是否不能走
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;

        //香車只能向前衝刺且不能跨越其他人
        case 'h':
            if((((user2->aftercol)-(user2->origncol)) != 0) || (((user2->afterrow)-(user2->orignrow))<=0))
            {
                return 0;
            }
            else if(user2->afterrow == 9)//判斷是否不能走
            {
                return 0;
            }
            else
            {

                for(i=(user2->orignrow); i<=(user2->afterrow-2); i++)   
                {
                    if((user1->userchess_board[i][(user2->origncol)-1] != ' ') || (user2->userchess_board[i][(user2->origncol)-1]) != ' ')
                    {
                        return 0;
                    }
                }
                if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                {
                return 0;
                }
                return 1;
            }
            break;

        //桂馬只能往前2格且往右或往左1格
        case 'g':
            if((((user2->afterrow)-(user2->orignrow)) == 2) && ((((user2->aftercol)-(user2->origncol)) == 1) || (((user2->aftercol)-(user2->origncol)) == (-1))))
            {
                return 1;
            }
            else if(user2->afterrow == 8)//判斷是否不能走
            {
                return 0;
            }
            else 
            {
                return 0;
            }
            break;

        //銀將只能斜角方向一格或是前方一格
        case 'i':
            if((((((user2->afterrow)-(user2->orignrow)) == 1) || (((user2->afterrow)-(user2->orignrow)) == (-1))) && ((((user2->aftercol)-(user2->origncol)) == 1) || (((user2->aftercol)-(user2->origncol)) == (-1)))) || ((((user2->afterrow)-(user2->orignrow)) == 1) && (((user2->aftercol)-(user2->origncol))== 0))) 
            {
                return 1;
            }
            else
            {
                return 0;
            }
            break;

        //金將只能向前後左右左前右前一格
        case 'k':
            if((((user2->afterrow)-(user2->orignrow)) >= 2) || (((user2->afterrow)-(user2->orignrow)) <= (-2)) || (((user2->aftercol)-(user2->origncol)) >= 2) || (((user2->aftercol)-(user2->origncol)) <= (-2)))
            {
                return 0;
            }
            else 
            {
                if((((user2->afterrow)-(user2->orignrow)) == (-1)))
                {
                    if((((user2->aftercol)-(user2->origncol)) ==0))
                    {
                        return 1;
                    }
                    return 0;
                }
                return 1;
            }
            break;

        //角行只能斜向衝刺且不可繞過棋子
        case 'j':
            if(((double)(((user2->afterrow)-(user2->orignrow))/((user2->aftercol)-(user2->origncol))) ==1.0) || ((double)(((user2->afterrow)-(user2->orignrow))/((user2->aftercol)-(user2->origncol))) ==(-1.0)))
            {
                if((user2->afterrow < (user2->orignrow)) && (user2->aftercol > user2->origncol))
                {
                    for(i = (user2->orignrow-2), j = (user2->origncol);i >= (user2->afterrow), j <= (user2->aftercol-2); i--,j++)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if((user2->afterrow > (user2->orignrow)) && (user2->aftercol > user2->origncol))
                {
                    for(i = (user2->orignrow), j = (user2->origncol);i <= (user2->afterrow-2), j <= (user2->aftercol-2); i++,j++)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if((user2->afterrow < (user2->orignrow)) && (user2->aftercol < user2->origncol))
                {
                    for(i = (user2->orignrow-2), j = (user2->origncol-2);i >= (user2->afterrow), j >= (user2->aftercol); i--,j--)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if((user2->afterrow > (user2->orignrow)) && (user2->aftercol < user2->origncol))
                {
                    for(i = (user2->orignrow), j = (user2->origncol-2);i <= (user2->afterrow-2), j >= (user2->aftercol); i++,j--)
                    {
                        if((user1->userchess_board[i][j] != ' ') || (user2->userchess_board[i][j]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
            }
            else
            {
                return 0;
            }
            break;

        //飛車只能橫向或縱向移動 不可跨過棋子
        case 'f':
            if(((user2->afterrow)-(user2->orignrow) == 0) || (((user2->aftercol)-(user2->origncol)) == 0))
            {
                if(user2->afterrow < (user2->orignrow))
                {
                    for(i=(user2->orignrow-2); i >= (user2->afterrow); i--)   
                    {
                        if((user1->userchess_board[i][(user2->origncol)-1] != ' ') || (user2->userchess_board[i][(user2->origncol)-1]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user2->afterrow > (user2->orignrow))
                {
                    for(i=(user2->orignrow); i <= (user2->afterrow-2); i++)   
                    {
                        if((user1->userchess_board[i][(user2->origncol)-1] != ' ') || (user2->userchess_board[i][(user2->origncol)-1]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user2->aftercol > user2->origncol)
                {
                    for(i=(user2->origncol); i <= (user2->aftercol-2); i++)   
                    {
                        if((user1->userchess_board[(user2->afterrow-1)][i] != ' ') || (user2->userchess_board[(user2->afterrow-1)][i]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
                if(user2->aftercol < user2->origncol)
                {
                    for(i=(user2->origncol-2); i >= (user2->aftercol); i--)   
                    {
                        if((user1->userchess_board[(user2->afterrow-1)][i] != ' ') || (user2->userchess_board[(user2->afterrow-1)][i]) != ' ')
                        {
                            return 0;
                        }
                    }
                    if(user2->userchess_board[user2->afterrow-1][user2->aftercol-1] != ' ')
                    {
                        return 0;
                    }
                    return 1;
                }
            }
            else
            {
                return 0;
            }
            break;
        
        //玉將八方一格
        default:
            if((((user2->afterrow)-(user2->orignrow)) >= 2) || (((user2->afterrow)-(user2->orignrow)) <= (-2)) || (((user2->aftercol)-(user2->origncol)) >= 2) || (((user2->aftercol)-(user2->origncol)) <= (-2)))
            {
                return 0;
            }
            else
            {
                return 1;
            }
            break;
    }
}

//userme增加一個
user *addme(user *meptr)
{
    user *tmp;
    tmp = (user *)malloc(sizeof(user));
    tmp->prev = meptr;
    tmp->next = NULL;
    tmp->tmp = ' ';
    tmp->tmprow = -1;
    tmp->tmpcol = -1;

    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            tmp->userchess_board[i][j] = meptr->userchess_board[i][j];
        }
    }

    tmp->orignrow = meptr->orignrow;
    tmp->origncol = meptr->origncol;
    tmp->afterrow = meptr->afterrow;
    tmp->aftercol = meptr->aftercol;

    meptr->next = tmp;
    meptr = meptr->next;

    return meptr;
}

//useryou增加一個
user *addyou(user *youptr)
{
    user *tmp;
    tmp = (user *)malloc(sizeof(user));
    tmp->prev = youptr;
    tmp->next = NULL;
    tmp->tmp = ' ';
    tmp->tmprow = -1;
    tmp->tmpcol = -1;

    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            tmp->userchess_board[i][j] = youptr->userchess_board[i][j];
        }
    }

    tmp->orignrow = youptr->orignrow;
    tmp->origncol = youptr->origncol;
    tmp->afterrow = youptr->afterrow;
    tmp->aftercol = youptr->aftercol;

    youptr->next = tmp;
    youptr = youptr->next;

    return youptr;
}

user *meequal(user *meptr)
{
    user *tmp;
    tmp = meptr->next;
    tmp->tmp = meptr->tmp;
    tmp->tmprow = meptr->tmprow;
    tmp->tmpcol = meptr->tmpcol;

    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            tmp->userchess_board[i][j] = meptr->userchess_board[i][j];
        }
    }

    tmp->orignrow = meptr->orignrow;
    tmp->origncol = meptr->origncol;
    tmp->afterrow = meptr->afterrow;
    tmp->aftercol = meptr->aftercol;

    return tmp;
}

user *youequal(user *youptr)
{
    user *tmp;
    tmp = youptr->next;
    tmp->tmp = youptr->tmp;
    tmp->tmprow = youptr->tmprow;
    tmp->tmpcol = youptr->tmpcol;

    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            tmp->userchess_board[i][j] = youptr->userchess_board[i][j];
        }
    }

    tmp->orignrow = youptr->orignrow;
    tmp->origncol = youptr->origncol;
    tmp->afterrow = youptr->afterrow;
    tmp->aftercol = youptr->aftercol;

    return tmp;
}

user *meequalload(user *meptr)
{
    user *tmp;
    tmp = meptr->next;
    //tmp->tmp = meptr->tmp;
    //tmp->tmprow = meptr->tmprow;
    //tmp->tmpcol = meptr->tmpcol;

    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            tmp->userchess_board[i][j] = meptr->userchess_board[i][j];
        }
    }

    //tmp->orignrow = meptr->orignrow;
    //tmp->origncol = meptr->origncol;
    //tmp->afterrow = meptr->afterrow;
    //tmp->aftercol = meptr->aftercol;

    return tmp;
}

user *youequalload(user *youptr)
{
    user *tmp;
    tmp = youptr->next;
    //tmp->tmp = youptr->tmp;
    //tmp->tmprow = youptr->tmprow;
    //tmp->tmpcol = youptr->tmpcol;

    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            tmp->userchess_board[i][j] = youptr->userchess_board[i][j];
        }
    }

    //tmp->orignrow = youptr->orignrow;
    //tmp->origncol = youptr->origncol;
    //tmp->afterrow = youptr->afterrow;
    //tmp->aftercol = youptr->aftercol;

    return tmp;
}


