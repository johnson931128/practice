# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 專案名稱
project(AStarPathfinding)

# 設定 C++ 標準為 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 尋找 SFML 函式庫
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# 新增可執行檔，來源為 main.cpp
add_executable(AStarGame main.cpp)

# 連結 SFML 函式庫到我們的專案
target_link_libraries(AStarGame PRIVATE sfml-graphics)
