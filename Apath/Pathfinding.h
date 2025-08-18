#pragma once // 防止標頭檔被重複引用

// Node 結構定義了 A* 演算法中每個格點所需要儲存的資訊
struct Node {
    int y = 0; // 格子的列 (row)
    int x = 0; // 格子的行 (column)

    int gCost = 0; // 從起點到當前格子的成本
    int hCost = 0; // 從當前格子到終點的預估成本 (Heuristic)
    int fCost = 0; // gCost + hCost，作為選擇下一個要走哪個格子的依據

    Node* parent = nullptr; // 指向前一個節點，用於回溯路徑

    // Constructor，方便我們用座標來建立一個 Node
    Node(int y_pos, int x_pos) : y(y_pos), x(x_pos) {}

    // 計算 F cost
    void calculateFCost() {
        fCost = gCost + hCost;
    }

    // 重載等號運算子，方便比較兩個 Node 是否在同一個位置
    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};
