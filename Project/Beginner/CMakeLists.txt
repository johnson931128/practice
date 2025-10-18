# 指定 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 設定專案名稱
project(CGPACalculator)

# 設定 C++ 標準為 C++17 (或你偏好的更新版本，例如 C++20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 新增可執行檔目標，它會由 main.cpp 編譯而成
add_executable(cgpa_calculator main.cpp)

# (可選) 啟用 C++20 Module 支持 (如果你的編譯器支援且你想使用)
# set(CMAKE_CXX_EXPERIMENTAL_MODULES ON)

# (可選) 設定輸出目錄 (方便管理編譯好的執行檔)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
