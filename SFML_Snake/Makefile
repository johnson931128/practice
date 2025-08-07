# 編譯器設定
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# SFML 連結器設定
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# 專案檔案設定
SRCS = main.cpp Game.cpp Snake.cpp Food.cpp
OBJS = $(SRCS:.cpp=.o) # 根據 SRCS 自動產生 OBJS 列表 (main.o Game.o)
TARGET = snake

# 預設目標
all: $(TARGET)

# 連結規則：告訴 make 如何從 .o 檔案生成執行檔
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# 編譯規則：告訴 make 如何從 .cpp 檔案生成 .o 檔案
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理規則
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
