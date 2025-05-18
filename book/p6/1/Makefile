# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src -I./test

# Директории
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
APP_OBJ_DIR = $(BUILD_DIR)/obj/app
TEST_OBJ_DIR = $(BUILD_DIR)/obj/tests
APP_BIN_DIR = $(BUILD_DIR)/app
TEST_BIN_DIR = $(BUILD_DIR)/tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_NO_MAIN = $(filter-out $(SRC_DIR)/main.cpp, $(SRC_FILES))
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)

# Объектные файлы
APP_OBJ = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(APP_OBJ_DIR)/%.o)
TEST_OBJ = $(SRC_NO_MAIN:$(SRC_DIR)/%.cpp=$(TEST_OBJ_DIR)/%.o) \
           $(TEST_FILES:$(TEST_DIR)/%.cpp=$(TEST_OBJ_DIR)/%.o)

# Цели
APP_TARGET = $(APP_BIN_DIR)/my_program
TEST_TARGET = $(TEST_BIN_DIR)/tests

.PHONY: all app test clean dirs

LDFLAGS = -lCatch2Main -lCatch2

# Сборка всех целей
all: clean app test

# ======== Основная программа ========
app: dirs $(APP_TARGET)

$(APP_TARGET): $(APP_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Application built at $@"

$(APP_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ======== Тесты ========
test: dirs $(TEST_TARGET)
	./$(TEST_TARGET) -v high -s

$(TEST_TARGET): $(TEST_OBJ) $(LDFLAGS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Tests built at $@"

$(TEST_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ======== Директории ========
dirs:
	mkdir -p $(APP_OBJ_DIR) $(TEST_OBJ_DIR) $(APP_BIN_DIR) $(TEST_BIN_DIR)

# ======== Очистка ========
clean:
	rm -rf $(BUILD_DIR)
	@echo "Clean complete"
