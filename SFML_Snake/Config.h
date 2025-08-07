#pragma once

// 使用 constexpr 來定義全域常數
// constexpr 變數是真正的編譯期常數，且隱含為 inline
// 這讓它可以被安全地定義在標頭檔中，而不會引發重複定義的連結錯誤
constexpr float GRID_SIZE = 40.0f;
constexpr float WINDOW_WIDTH = 800.0f;
constexpr float WINDOW_HEIGHT = 600.0f;
