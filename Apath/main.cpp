#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> // 用於在終端機輸出除錯訊息

int main() {
    const int GRID_SIZE = 10;
    const int WINDOW_SIZE = 500;
    const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "A* Pathfinding");
    window.setFramerateLimit(60);

    std::vector<std::vector<sf::RectangleShape>> grid(
        GRID_SIZE,
        std::vector<sf::RectangleShape>(GRID_SIZE)
    );

    // ... (省略格子的初始化迴圈，內容不變) ...
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            grid[i][j].setPosition(i * CELL_SIZE, j * CELL_SIZE);
            grid[i][j].setFillColor(sf::Color(30, 30, 30));
            grid[i][j].setOutlineColor(sf::Color(80, 80, 80));
            grid[i][j].setOutlineThickness(1.0f);
        }
    }

    sf::RectangleShape player;
    player.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    player.setFillColor(sf::Color::Red);
    int playerRow = GRID_SIZE / 2;
    int playerCol = GRID_SIZE / 2;
    player.setPosition(playerCol * CELL_SIZE, playerRow * CELL_SIZE);

    // --- 1. 新增變數來儲存目標位置 ---
    sf::Vector2i targetPos = {-1, -1}; // 初始化為一個無效的位置


    // 主遊戲迴圈
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // --- 2. 新增滑鼠點擊事件的處理 ---
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // 取得滑鼠點擊的像素座標
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // 將像素座標轉換為網格座標 (col, row)
                    int col = mousePos.x / CELL_SIZE;
                    int row = mousePos.y / CELL_SIZE;

                    // 檢查點擊是否在網格範圍內
                    if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE) {

                        // 如果之前有目標，先將其顏色恢復
                        if (targetPos.x != -1) {
                            grid[targetPos.x][targetPos.y].setFillColor(sf::Color(30, 30, 30));
                        }

                        // 設定新的目標位置並改變顏色
                        targetPos = {col, row};
                        grid[targetPos.x][targetPos.y].setFillColor(sf::Color::Green);

                        std::cout << "New target set at: (" << col << ", " << row << ")\n";
                    }
                }
            }
        }

        // ... (清除畫面和繪製的程式碼不變) ...
        window.clear(sf::Color(50, 50, 50));

        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                window.draw(grid[i][j]);
            }
        }

        window.draw(player);

        window.display();
    }

    return 0;
}
