#ifndef FUNCTION_H
#define FUNCTION_H
#include "user.h"



//main裡的
void initgame(user * chessboard);//初始化棋盤
void printchess(user const * user1, user const * user2, user * chessboard);//印出棋盤
int game(int * rear1, int * rear2, int *front1, int *front2, int *count, user **tmpusermefrontptr, user **tmpuseryoufrontptr);//開新局
void user1move(user * user11, user * user22);//移動user1
void user2move(user * user22, user * user11);//移動user2
void user1eatuser2(user * user1, user * user2);//user1吃掉user2的子
void user2eatuser1(user * user2, user * user1);//user2吃掉user1的子
int whowins(user * chessboard);//user1贏回傳1 user2贏回傳2 沒人贏回傳0
void load();//載入棋譜

user *addme(user *meptr);//要新增一個me的
user *addyou(user *youptr);

user *meequal(user *meptr);//使棋盤和上一個相同 用在遊戲進行的 只是指位器不變 
user *youequal(user *youptr);

user *meequalload(user *meptr);
user *youequalload(user *youptr);

//moving裡的
int user1chessandmove(user * user1, user * user2);//哪個棋子和如何移動
int user2chessandmove(user * user2, user * user1);//哪個棋子和如何移動

//timer裡的
void user1timer();
void user2timer();
void user1timermove();
void user2timermove();
void user1timeout_cb (EV_P_ ev_timer *w, int revents);
void user2timeout_cb (EV_P_ ev_timer *w, int revents);
void user1timeout_cbmove (EV_P_ ev_timer *w, int revents);
void user2timeout_cbmove (EV_P_ ev_timer *w, int revents);
void user1stop_cb (EV_P_ ev_io *w, int revents);
void user2stop_cb (EV_P_ ev_io *w, int revents);



#endif