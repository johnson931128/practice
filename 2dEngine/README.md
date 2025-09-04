# C++ & SFML 2D 物理引擎

這是一個從零開始，使用現代 C++ 和 SFML 函式庫打造 2D 物理引擎的專案。

## 專案計畫 (Project Plan)

這個專案被分為數個階段，以便循序漸進地完成。

### ✅ Phase 0: 環境設定 (Environment Setup)
- **狀態:** 已完成
- **目標:** 建立一個可以編譯並執行 C++ 與 SFML 程式的開發環境。

### ✅ Phase 1: 基礎數學與物件結構 (Basic Math & Object Structure)
- **狀態:** 已完成
- **目標:** 建立物理引擎所需的基本資料結構。
- **產出:** `Vector2D` 和 `RigidBody` 類別。

### ➡️ Phase 2: 物理世界與時間步進 (Physics World & Time Stepping)
- **狀態:** **目前階段**
- **目標:** 建立一個 `PhysicsWorld` 類別來管理所有物理物件，並實作時間推進的物理更新迴圈。

### ⬜ Phase 3: SFML 可視化 (SFML Visualization)
- **狀態:** 未開始
- **目標:** 將物理引擎的計算結果透過 SFML 繪製到螢幕上，讓我們能「看見」物理模擬。

### ⬜ Phase 4: 碰撞偵測 (Collision Detection)
- **狀態:** 未開始
- **目標:** 實作演算法來偵測兩個物理物件是否發生重疊。

### ⬜ Phase 5: 碰撞反應 (Collision Resolution)
- **狀態:** 未開始
- **目標:** 當碰撞發生時，計算並應用衝量，使物體能真實地彈開。

### ⬜ Phase 6: 擴展與優化 (Expansion and Optimization)
- **狀態:** 未開始
- **目標:** 增加旋轉、摩擦力等進階功能，並使用空間分割等技術優化效能。
