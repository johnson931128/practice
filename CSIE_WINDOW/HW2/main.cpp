#include "Game.h"

int main() {
    // 1. 建立一個 Game 物件
    //    當這行程式碼執行時，Game 的建構函式(Game::Game())會被呼叫，
    //    完成所有遊戲的初始設定。
    Game stock_game;

    // 2. 呼叫 run() 函式，啟動遊戲主迴圈
    //    程式會停在這裡，直到玩家選擇退出遊戲為止。
    stock_game.run();

    // 3. 遊戲結束，程式正常退出
    return 0;
}