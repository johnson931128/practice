#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <vector>
#include <deque> // <--- 新增
#include <random>
#include "Stock.h"
#include "Player.h"

// 【新增】用一個結構來表示一筆交易
struct Transaction {
    int stock_id;
    int amount; // 買入為正數，賣出為負數
    double price_per_share;
};

class Game {
public:
    Game(); 
    void run();

private:
    int time;
    bool money_is_enough;


    Player player;


    std::map<int, Stock> stocks;
    std::mt19937 rng;
    // --- 【新增】進階功能需要的成員變數 ---
    std::vector<Transaction> pending_transactions; // T+1 待交割的交易
    
    double loan_principal;    // 貸款本金
    double loan_remaining;    // 貸款餘額

    std::deque<std::string> trade_history;    // 交易歷史紀錄
    std::deque<double> market_value_history; // 大盤總額歷史紀錄

    // --- 私有輔助函式 ---
    void advance_time();      
    void display_main_menu(); 
    void handle_day_change(); // <--- 【新增】換日結算的函式

    // 操作函式
    void handle_buy();
    void handle_sell();
    void handle_market_trend();
    void handle_history();
    void handle_loan();
};

#endif