#include <SFML/Graphics.hpp>
#include <vector> // <--- 1. 引入 vector 標頭檔

int main() {
    // --- 2. 新增地圖與格子常數 ---
    const int GRID_SIZE = 10;
    const int WINDOW_SIZE = 500; // 視窗大小 (寬度和高度相同)
    const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE; // 計算每個格子的大小

    // 建立視窗 (使用新的常數)
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "A* Pathfinding");
    window.setFramerateLimit(60);

    // --- 3. 建立並初始化二維格子地圖 ---
    std::vector<std::vector<sf::RectangleShape>> grid(
        GRID_SIZE,
        std::vector<sf::RectangleShape>(GRID_SIZE)
    );

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            grid[i][j].setPosition(i * CELL_SIZE, j * CELL_SIZE);
            grid[i][j].setFillColor(sf::Color(30, 30, 30)); // 格子顏色
            grid[i][j].setOutlineColor(sf::Color(80, 80, 80)); // 格子邊線顏色
            grid[i][j].setOutlineThickness(1.0f);
        }
    }

    // 主遊戲迴圈
    while (window.isOpen()) {
        // 事件處理
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 清除畫面
        window.clear(sf::Color(50, 50, 50));

        // --- 4. 在迴圈中繪製所有格子 ---
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                window.draw(grid[i][j]);
            }
        }

        // 顯示畫面
        window.display();
    }

    return 0;
}
