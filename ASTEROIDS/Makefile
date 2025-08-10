# 編譯器設定
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# 連結器設定 (SFML)
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# 專案檔案設定
SRCS = main.cpp Game.cpp Player.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = asteroids

# 預設目標
all: $(TARGET)

# 連結規則
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# 編譯規則
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理規則
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
