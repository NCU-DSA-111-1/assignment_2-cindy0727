# Datastructure HW_2 SHOGI
## gcc compile c code
1. compile  make
2. execute 
    1. open a new game  ./bin/main -n-s filename.txt
    2. load a game  ./bin/main -l filename.txt

## usage
1. open a new game
    注意：需一次輸入四筆資訊 中間以空白鍵區分如果一次只輸入三筆畫面會提前先被system clear 補輸入沒輸入的資料就行
    
    1. 輸入座標移動棋子：依照指示 user1和user2依據圖上座標輸入座標
        注意：若顯示輸入錯誤 可能為棋子下法有誤 或是悔棋到最原始棋盤了 請重新輸入座標

    2. 悔棋：如果user1輸入完後想悔棋 需在user2輸入時輸入 0 0 0 0 反之相同
        注意：如果悔棋悔到已經儲存的步驟 目前不支援這種方式 儲存出來的歷史紀錄不具參考價值

    3. 儲存：輸入s 0 0 0(小寫s 0 0 0也可以換成其他數字) 可以進行儲存 等待一秒儲存完畢後重新輸入座標
        注意 每次只能輸入一次s 不然會出錯

2. load a game
    1. 輸入f往下一步 輸入b往回一步 直到遊戲結束
    2. 注意事項：如果一次輸入fb會代表往前一步往後一步 然後畫面會跑掉 長得很醜不好看 記得一次輸入一個就好不要貪心
