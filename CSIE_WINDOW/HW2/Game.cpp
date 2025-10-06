#include "Game.h"
#include <iostream>
#include <random>
#include <iomanip>


Game::Game() {
    time = 0;
    player.money = 3000.0;

    stocks[2330] = {2330, "TSMC", 1180, 0.01};
    stocks[47]   = {47, "KFC", 144.58, 0.05};
    stocks[58]   = {58, "MYHOTKISS", 2.0, 0.50};

    rng.seed(std::random_device{}());
    std::cout << "Game Initialized." << std::endl;
}

void Game::run() {
    std::cout << "--- Game Start! Advancing initial time... ---" << std::endl;
    for (int i = 0; i < 3; i++){
        advance_time();
    }

    bool game_is_running = true; // <--- 新增一個旗標
    while (game_is_running) { // <--- 迴圈條件改成檢查旗標
        display_main_menu();

        int option;
        std::cin >> option;

        if (std::cin.fail()) {
            std::cout << "Exiting program..." << std::endl;
            break; 
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (option) {
            case 1: handle_buy(); break;
            case 2: handle_sell(); break;
            case 3: handle_market_trend(); break;
            case 4: handle_history(); break;
            case 5: handle_loan(); break;
            default: // 處理 1~5 以外的數字
                std::cout << "Exiting program..." << std::endl;
                game_is_running = false; // <--- 修改旗標，讓迴圈在這次迭代後結束
                break;
        }

        if (game_is_running) { // <--- 只有在遊戲還在繼續時才推進時間
            advance_time();
        }
    }
}

void Game::advance_time() {
    // 待辦 (To-do): 時間推進和股價更新的邏輯
    std::uniform_real_distribution<double> dist(-0.1, 0.1);
    time++;
    for (auto& pair : stocks){
        Stock& stock = pair.second;
        double change = dist(rng);
        stock.price = stock.price * (1.0 + change);
    }
    // 在 advance_time() 的結尾處
    if (time >= 6 && time % 3 == 0) {
        handle_day_change();
    }
}

void Game::display_main_menu() {
    // 待辦 (To-do): 顯示主選單的邏輯
    std::cout << "\n----------------------------------------\n";
    std::cout << "歡迎來到 NCKU 證券交易系統!" << std::endl;

    if (time >= 3){
        std::cout << "Day: " << (time - 3) / 3 + 1 << std::endl;
    }

    std::cout << "Money: " << std::fixed << std::setprecision(2) << player.money << std::endl;
    std::cout << "(1)買股" << std::endl;
    std::cout << "(2)賣股" << std::endl;
    std::cout << "(3)股市走勢" << std::endl;
    std::cout << "(4)歷史交易" << std::endl;
    std::cout << "(5)貸款(有趣的一句話)" << std::endl;
    std::cout << "輸入 1~5 以外字元以退出" << std::endl;
    std::cout << "輸入您的操作: ";
}

void Game::handle_buy() {
    // 1. 顯示所有股票資訊 (這部分不變)
    std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "完整股市:" << std::endl;
    for (auto& pair : stocks){
        Stock& stock = pair.second;
        std::cout << "- " << stock.name << "(" << stock.id << "): " 
                  << std::fixed << std::setprecision(2) << stock.price << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;

    // 2. 讓使用者輸入股票代號，並驗證 (這部分不變)
    int id;
    while (true) {
        std::cout << "輸入希望購買的股票代號 (-1 返回主選單): ";
        std::cin >> id;
        if (std::cin.fail()) {
            std::cout << "未知指令!請重新輸入或是-1回到主頁" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (id == -1) { return; }
        if (stocks.count(id)) { break; } 
        else { std::cout << "未知代碼!請重新輸入或是-1回到主頁" << std::endl; }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 3. 讓使用者輸入購買股數，並驗證 (這部分不變)
    int amount;
    while (true) {
        std::cout << "輸入希望購買的股數 (-1 返回主選單): ";
        std::cin >> amount;
        if (std::cin.fail()) {
            std::cout << "無效輸入!請輸入數字。" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (amount == -1) { return; }
        if (amount > 0) { break; } 
        else { std::cout << "股數必須是正數!請重新輸入。" << std::endl; }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 4. 【T+1 修改】計算交割金額，記錄交易，並印出訊息
    double settlement_amount = stocks.at(id).price * amount;

    // 將這筆「買入」交易加入待辦清單
    pending_transactions.push_back({id, amount, stocks.at(id).price});

    // 印出符合作業範例的成功訊息
    std::cout << "成功買入 " << id << " 共 " << amount << " 股, 交割金額 " 
              << std::fixed << std::setprecision(2) << settlement_amount << std::endl;
}


void Game::handle_sell() {
    // 待辦 (To-do): 處理賣出股票的邏輯
    if (player.shares.empty()){
        std::cout << "你沒有任何持股可以賣出" << std::endl;
        return ;
    }

    std::cout << "持有股票: " << std::endl;
    for (auto& pair : player.shares){
        int stock_id = pair.first;
        int held_amount = pair.second;
        
        const Stock& stock_info = stocks.at(stock_id);
        std::cout << "- " << stock_info.name << "(" << stock_id << "): " 
                << std::fixed << std::setprecision(2) << stock_info.price 
                << " 共 " << held_amount << " 股" << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl;

    int id;
    while (true) {
        std::cout << "輸入希望(全部)售出的股票代號 (-1 返回主選單): ";
        std::cin >> id;

        if (std::cin.fail()) {
            std::cout << "未知指令!請重新輸入或是-1回到主頁" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (id == -1) {
            return; // 返回主選單
        }

        // 檢查玩家是否真的持有這支股票
        if (player.shares.count(id)) {
            break; // 代號有效，跳出迴圈
        } else {
            std::cout << "你並未持有此代號的股票!請重新輸入。" << std::endl;
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int amount_to_sell = player.shares.at(id);
    double current_price = stocks.at(id).price;
    double earnings = current_price * amount_to_sell;


    // 將這筆「賣出」交易加入待辦清單
    pending_transactions.push_back({id, -amount_to_sell, stocks.at(id).price});

    // 印出符合作業範例的成功訊息
    std::cout << "成功賣出 " << id << " 共 " << amount_to_sell << " 股, 交割金額 " 
              << std::fixed << std::setprecision(2) << earnings << std::endl;
}

void Game::handle_market_trend() {
    // 待辦 (To-do): 處理顯示股市走勢的邏輯
    double total_value = 0.0;
    for (auto& pair : stocks){
        Stock& stock = pair.second;
        total_value += stock.price;
    }

    std::cout << "大盤總額: "<< std::fixed << std::setprecision(2) << total_value << std::endl;
}


void Game::handle_day_change(){
    std::cout << "\n--- 國際換日線 ---\n";
    double net_settlement = 0.0;
    double total_dividends = 0.0;

    for (auto& pair : player.shares){
        Stock& stock = stocks.at(pair.first);
        double dividend = stock.price * pair.second * stock.dividend_rate;
        total_dividends += dividend;
    }
    std::cout << "收到股息金額 " << "..." << total_dividends << std::endl;
    player.money += total_dividends;

    for (auto& day : pending_transactions){
        Transaction& transaction = day;
        if (transaction.amount > 0){
            double cost = transaction.price_per_share * transaction.amount;
            net_settlement -= cost;
            player.shares[transaction.stock_id] += transaction.amount;
        }

        if (transaction.amount < 0){
            double earnings = transaction.price_per_share * abs(transaction.amount);
            net_settlement += earnings;
            player.shares[transaction.stock_id] += transaction.amount;
        }
    }
            
    std::cout << "最後交割金額: " << "..." << net_settlement << std::endl;
    player.money += net_settlement;
    pending_transactions.clear();
}







void Game::handle_history() {
    std::cout << "THIS IS HISTORY YAS YAS ME LOVE HISTORY" << std::endl;
}

void Game::handle_loan() {
    std::cout << "老闆，我不想努力了..." << std::endl;
}



