# ... (前面的 cmake_minimum_required, project, set, find_package 都維持不變) ...
cmake_minimum_required(VERSION 3.10)
project(AStarPathfinding)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# 修改這一行，加入新的檔案
add_executable(AStarGame main.cpp Game.cpp) # <--- 把 Game.cpp 加進來

# ... (target_link_libraries 維持不變) ...
target_link_libraries(AStarGame PRIVATE sfml-graphics)
