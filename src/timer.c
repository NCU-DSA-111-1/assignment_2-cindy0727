#include "../inc/function.h"

ev_io stop_watcher; 
ev_timer timeout_watcher;
time_t user1starttime, user2starttime, user1endtime, user2endtime, user1usedtime, user2usedtime;

void user1timer()
{
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init (&stop_watcher, user1stop_cb,0, EV_READ); //Call the call back function when io incident happen
    ev_io_start (loop, &stop_watcher);  //Start stop watcher
    ev_timer_init(&timeout_watcher, user1timeout_cb,0,1); //Call the call back function once for one second  
    ev_timer_start (loop, &timeout_watcher);  //Start timeout watcher
    user1starttime = time(NULL);  //Set start time of player X
    ev_run(loop,0);  //Put the watcher into the libev loop and run
}

void user2timer()
{
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init (&stop_watcher, user2stop_cb,0, EV_READ); //Call the call back function when io incident happen
    ev_io_start (loop, &stop_watcher);  //Start stop watcher
    ev_timer_init(&timeout_watcher, user2timeout_cb,0,1); //Call the call back function once for one second  
    ev_timer_start (loop, &timeout_watcher);  //Start timeout watcher
    user2starttime = time(NULL);  //Set start time of player X
    ev_run(loop,0);  //Put the watcher into the libev loop and run
}

void user1timermove()
{
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init (&stop_watcher, user1stop_cb,0, EV_READ);
    ev_io_start (loop, &stop_watcher);
    ev_timer_init(&timeout_watcher, user1timeout_cbmove,0,1);
    ev_timer_start (loop, &timeout_watcher);
    user1starttime = time(NULL);
    ev_run(loop,0);
}

void user2timermove()
{
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init (&stop_watcher, user2stop_cb,0, EV_READ);
    ev_io_start (loop, &stop_watcher);
    ev_timer_init(&timeout_watcher, user2timeout_cbmove,0,1);
    ev_timer_start (loop, &timeout_watcher);
    user2starttime = time(NULL);
    ev_run(loop,0);
}

//The callback of time
void user1timeout_cb (EV_P_ ev_timer *w, int revents)
{   
    // printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
    // scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
    //Compute the time pass by since timestart and change the seconds into hours, minutes, and second 
    user1endtime = time(NULL);
    user1hour = (user1endtime - user1starttime + user1usedtime) / 3600;
    user1minute = (user1endtime - user1starttime + user1usedtime - user1hour * 3600)/60;
    user1second = user1endtime - user1starttime + user1usedtime - user1hour * 3600 - user1minute * 60;
    //system("clear");
    //Display the interface of the game
    // printf(" 此手用時：%02ld秒\n", (user1endtime - user1starttime));//
    // printf(" user1遊戲時間：%02d:%02d:%02d\n",user1hour,user1minute,user1second);
    // printf(" user2遊戲時間：%02d:%02d:%02d\n\n",user2hour,user2minute,user2second);

    //printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
    //scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
    /*chessprint();
    printf(" 打入棋子請輸入H\n 悔棋請輸入0\n 儲存先前對弈過程請輸入S\n 關閉遊戲請輸入x\n");
    if(player==1)
        printf(" 玩家X輸入移動棋子的 X 座標與 Y 座標: ");
    else
        printf(" 玩家y輸入移動棋子的 X 座標與 Y 座標: ");
    fflush(stdout);*/
}

void user2timeout_cb (EV_P_ ev_timer *w, int revents)
{   
    // printf("依據圖上座標 User1 輸入想移動的棋子的原始座標空格移動後的位置座標:");
    // scanf("%1s%d%d%d", &usermeptr->input, &usermeptr->orignrow, &usermeptr->aftercol, &usermeptr->afterrow);
    //Compute the time pass by since timestart and change the seconds into hours, minutes, and second 
    user2endtime = time(NULL);
    user2hour = (user2endtime - user2starttime + user2usedtime) / 3600;
    user2minute = (user2endtime - user2starttime + user2usedtime - user2hour * 3600)/60;
    user2second = user2endtime - user2starttime + user2usedtime - user2hour * 3600 - user2minute * 60;
}
// void user2timeout_cb (EV_P_ ev_timer *w, int revents)
// {   
//     //Compute the time pass by since timestart and change the seconds into hours, minutes, and second 
//     user2endtime = time(NULL);
//     user2hour = (user2endtime - user2starttime + user2usedtime) / 3600;
//     user2minute = (user2endtime - user2starttime + user2usedtime - user2hour * 3600)/60;
//     user2second = user2endtime - user2starttime + user2usedtime - user2hour * 3600 - user2minute * 60;
//     //system("clear");
//     //Display the interface of the game
//     printf(" 此手用時：%02ld秒\n", (user2endtime - user2starttime));
//     printf(" user1遊戲時間：%02d:%02d:%02d\n",user1hour,user1minute,user1second);
//     printf(" user2遊戲時間：%02d:%02d:%02d\n\n",user2hour,user2minute,user2second);
//     /*chessprint();
//     printf(" 打入棋子請輸入H\n 悔棋請輸入0\n 儲存先前對弈過程請輸入S\n 關閉遊戲請輸入x\n");
//     if(player==1)
//         printf(" 玩家X輸入移動棋子的 X 座標與 Y 座標: ");
//     else
//         printf(" 玩家y輸入移動棋子的 X 座標與 Y 座標: ");
//     fflush(stdout);*/
// }

void user1timeout_cbmove (EV_P_ ev_timer *w, int revents)
{   
    user1endtime = time(NULL);
    user1hour = (user1endtime - user1starttime + user1usedtime) / 3600;
    user1minute = (user1endtime - user1starttime + user1usedtime - user1hour * 3600)/60;
    user1second = user1endtime - user1starttime + user1usedtime - user1hour * 3600 - user1minute * 60;
    //system("clear");
    //printf(" 此手用時：%02ld秒\n", (user1endtime - user1starttime));
    printf(" user1遊戲時間：%02d:%02d:%02d\n",user1hour,user1minute,user1second);
    printf(" user2遊戲時間：%02d:%02d:%02d\n\n",user2hour,user2minute,user2second);
    /*chessprint();
    if(player==1)
        printf(" 玩家X輸入目標 X 座標與 Y 座標: ");
    else
        printf(" 玩家Y輸入目標 X 座標與 Y 座標: ");
    fflush(stdout);*/  
}

void user2timeout_cbmove (EV_P_ ev_timer *w, int revents)
{   
    user2endtime = time(NULL);
    user2hour = (user2endtime - user2starttime + user2usedtime) / 3600;
    user2minute = (user2endtime - user2starttime + user2usedtime - user2hour * 3600)/60;
    user2second = user2endtime - user2starttime + user2usedtime - user2hour * 3600 - user2minute * 60;
    //system("clear");
    printf(" 此手用時：%02ld秒\n", (user2endtime - user2starttime));
    printf(" user1遊戲時間：%02d:%02d:%02d\n",user1hour,user1minute,user1second);
    printf(" user2遊戲時間：%02d:%02d:%02d\n\n",user2hour,user2minute,user2second);
    /*chessprint();
    if(player==1)
        printf(" 玩家X輸入目標 X 座標與 Y 座標: ");
    else
        printf(" 玩家Y輸入目標 X 座標與 Y 座標: ");
    fflush(stdout);*/  
}

//The callback of io incident happen that is able to stop counting time
void user1stop_cb (EV_P_ ev_io *w, int revents)
{
    //Save the used time
    user1usedtime = user1endtime - user1starttime + user1usedtime;
    // user1hour = (user1endtime - user1starttime + user1usedtime) / 3600;
    // user1minute = (user1endtime - user1starttime + user1usedtime - user1hour * 3600)/60;
    // user1second = user1endtime - user1starttime + user1usedtime - user1hour * 3600 - user1minute * 60;
    system("clear");
    //printf(" \n此手用時：%02ld秒\n", (user1endtime - user1starttime));//
    printf(" user1遊戲時間：%02d:%02d:%02d\n",user1hour,user1minute,user1second);
    printf(" user2遊戲時間：%02d:%02d:%02d\n\n",user2hour,user2minute,user2second);
    // Stop the watchers
    ev_io_stop (EV_A_ w);
    ev_timer_stop (loop, &timeout_watcher);
    // This causes all nested ev_run's to stop iterating
    ev_break (EV_A_ EVBREAK_ALL);
}

void user2stop_cb (EV_P_ ev_io *w, int revents)
{
    //Save the used time
    user2usedtime = user2endtime - user2starttime + user2usedtime;
    // user1hour = (user1endtime - user1starttime + user1usedtime) / 3600;
    // user1minute = (user1endtime - user1starttime + user1usedtime - user1hour * 3600)/60;
    // user1second = user1endtime - user1starttime + user1usedtime - user1hour * 3600 - user1minute * 60;
    // printf(" \n此手用時：%02ld秒\n", (user2endtime - user2starttime));//
    system("clear");
    printf(" user1遊戲時間：%02d:%02d:%02d\n",user1hour,user1minute,user1second);
    printf(" user2遊戲時間：%02d:%02d:%02d\n\n",user2hour,user2minute,user2second);
    // Stop the watchers
    ev_io_stop (EV_A_ w);
    ev_timer_stop (loop, &timeout_watcher);
    // This causes all nested ev_run's to stop iterating
    ev_break (EV_A_ EVBREAK_ALL);
}
// void user2stop_cb (EV_P_ ev_io *w, int revents)
// {
//     //Save the used time
//     user2usedtime = user2endtime - user2starttimestart + user2usedtime;
//     // Stop the watchers
//     ev_io_stop (EV_A_ w);
//     ev_timer_stop (loop, &timeout_watcher);
//     // This causes all nested ev_run's to stop iterating
//     ev_break (EV_A_ EVBREAK_ALL);
// }