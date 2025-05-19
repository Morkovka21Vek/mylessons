# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src 

# Директории
SRC_DIR = src
BUILD_DIR = build
APP_OBJ_DIR = $(BUILD_DIR)/obj/app
APP_BIN_DIR = $(BUILD_DIR)/app

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_NO_MAIN = $(filter-out $(SRC_DIR)/main.cpp, $(SRC_FILES))

# Объектные файлы
APP_OBJ = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(APP_OBJ_DIR)/%.o)

# Цели
APP_TARGET = $(APP_BIN_DIR)/my_program

.PHONY: all app clean dirs

LDFLAGS = -lCatch2Main -lCatch2

# Сборка всех целей
all: app

# ======== Основная программа ========
app: dirs $(APP_TARGET)

$(APP_TARGET): $(APP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Application built at $@"

$(APP_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# ======== Директории ========
dirs:
	mkdir -p $(APP_OBJ_DIR) $(APP_BIN_DIR)

# ======== Очистка ========
clean:
	rm -rf $(BUILD_DIR)
	@echo "Clean complete"
