#include "../inc/function.h"

ev_io stop_watcher; 
ev_timer timeout_watcher;
time_t user1starttime, user2starttime, user1endtime, user2endtime, user1usedtime, user2usedtime;

void user1timer()
{
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init (&stop_watcher, user1stop_cb,0, EV_READ); //當io事件發生 呼叫call back
    ev_io_start (loop, &stop_watcher);  //開始 stop watcher
    ev_timer_init(&timeout_watcher, user1timeout_cb,0,1); //每一秒呼叫一次 
    ev_timer_start (loop, &timeout_watcher);  //開始 timeout watcher
    user1starttime = time(NULL);  //設置user1開始時間
    ev_run(loop,0);  //將watcher放在loop並讓他跑
}

void user2timer()
{
    struct ev_loop *loop = EV_DEFAULT;
    ev_io_init (&stop_watcher, user2stop_cb,0, EV_READ); 
    ev_io_start (loop, &stop_watcher);  
    ev_timer_init(&timeout_watcher, user2timeout_cb,0,1);
    ev_timer_start (loop, &timeout_watcher);  
    user2starttime = time(NULL);  //設置user2開始時間
    ev_run(loop,0);  
}


//The callback of time
void user1timeout_cb (EV_P_ ev_timer *w, int revents)
{   
    user1endtime = time(NULL);
    user1hour = (user1endtime - user1starttime + user1usedtime) / 3600;
    user1minute = (user1endtime - user1starttime + user1usedtime - user1hour * 3600)/60;
    user1second = user1endtime - user1starttime + user1usedtime - user1hour * 3600 - user1minute * 60;
    
}

void user2timeout_cb (EV_P_ ev_timer *w, int revents)
{   
    user2endtime = time(NULL);
    user2hour = (user2endtime - user2starttime + user2usedtime) / 3600;
    user2minute = (user2endtime - user2starttime + user2usedtime - user2hour * 3600)/60;
    user2second = user2endtime - user2starttime + user2usedtime - user2hour * 3600 - user2minute * 60;
}




//call back function
void user1stop_cb (EV_P_ ev_io *w, int revents)
{
    //儲存用時
    user1usedtime = user1endtime - user1starttime + user1usedtime;
    system("clear");
    printf(" user1遊戲時間：%02d:%02d:%02d\n",user1hour,user1minute,user1second);
    printf(" user2遊戲時間：%02d:%02d:%02d\n\n",user2hour,user2minute,user2second);
    // 停止 watchers
    ev_io_stop (EV_A_ w);
    ev_timer_stop (loop, &timeout_watcher);
    // This causes all nested ev_run's to stop iterating
    ev_break (EV_A_ EVBREAK_ALL);
}

void user2stop_cb (EV_P_ ev_io *w, int revents)
{
    //儲存用時
    user2usedtime = user2endtime - user2starttime + user2usedtime;
    system("clear");
    printf(" user1遊戲時間：%02d:%02d:%02d\n",user1hour,user1minute,user1second);
    printf(" user2遊戲時間：%02d:%02d:%02d\n\n",user2hour,user2minute,user2second);
    // 停止 watchers
    ev_io_stop (EV_A_ w);
    ev_timer_stop (loop, &timeout_watcher);
    // This causes all nested ev_run's to stop iterating
    ev_break (EV_A_ EVBREAK_ALL);
}
