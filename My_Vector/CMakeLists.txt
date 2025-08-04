cmake_minimum_required(VERSION 3.10)
project(MyVectorProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 將 IntVector.cpp 和 main.cpp 一起編譯成一個名為 "my_app" 的執行檔
add_executable(my_app main.cpp)
