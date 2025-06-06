.PHONY: clean check format debug

CXX := g++

SRC_DIR := ./src
TEST_DIR := ./test
BUILD_DIR := build
BUILD_OBJ_SUBDIR := obj_dir
BUILD_DEPS_SUBDIR := deps_dir

APP_BUILD_DIR := $(BUILD_DIR)/app
TEST_BUILD_DIR := $(BUILD_DIR)/test

APP_TARGET := $(APP_BUILD_DIR)/ping_pong.out
TEST_TARGET := $(TEST_BUILD_DIR)/tests

APP_SOURCE_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
APP_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(APP_BUILD_DIR)/$(BUILD_OBJ_SUBDIR)/%.o, $(APP_SOURCE_FILES))
APP_DEPS_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(APP_BUILD_DIR)/$(BUILD_DEPS_SUBDIR)/%.d, $(APP_SOURCE_FILES))

TEST_SOURCE_FILES := $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/$(BUILD_OBJ_SUBDIR)/%.o, $(TEST_SOURCE_FILES)) $(filter-out $(APP_BUILD_DIR)/$(BUILD_OBJ_SUBDIR)/main.o, $(APP_OBJ_FILES))
TEST_DEPS_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/$(BUILD_DEPS_SUBDIR)/%.d, $(TEST_SOURCE_FILES))

CXXFLAGS := -Wall -pedantic -Wextra -std=c++20 -g -I./src -I./test -MMD
APP_DEP_FLAGS := -MT $@ -MMD -MP -MF $(APP_BUILD_DIR)/$(BUILD_DEPS_SUBDIR)/$*.d
TEST_DEP_FLAGS := -MT $@ -MMD -MP -MF $(TEST_BUILD_DIR)/$(BUILD_DEPS_SUBDIR)/$*.d
LDFLAGS := -lncurses -lCatch2Main -lCatch2

all: app test
app: $(APP_TARGET)
rebuild: clean all

-include $(APP_DEPS_FILES) $(TEST_DEPS_FILES)

test: $(TEST_TARGET)
	./$(TEST_TARGET) -v high -s

$(APP_TARGET): $(APP_OBJ_FILES) $(LDFLAGS)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(TEST_TARGET): $(TEST_OBJ_FILES) $(LDFLAGS)
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Tests built at $@"

$(APP_BUILD_DIR)/$(BUILD_OBJ_SUBDIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@mkdir -p $(subst $(BUILD_OBJ_SUBDIR),$(BUILD_DEPS_SUBDIR),$(@D))
	$(CXX) -c $(CXXFLAGS) $(APP_DEP_FLAGS) -o $@ $<

$(TEST_BUILD_DIR)/$(BUILD_OBJ_SUBDIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@mkdir -p $(subst $(BUILD_OBJ_SUBDIR),$(BUILD_DEPS_SUBDIR),$(@D))
	$(CXX) -c $(CXXFLAGS) $(TEST_DEP_FLAGS) -o $@ $<

clean:
	@rm -rf $(BUILD_DIR) 2> /dev/null

debug:
	$(info )
	$(info APP_TARGET = $(APP_TARGET))
	$(info TEST_TARGET = $(TEST_TARGET))
	$(info )
	$(info APP_SOURCE_FILES = $(APP_SOURCE_FILES))
	$(info APP_OBJ_FILES = $(APP_OBJ_FILES))
	$(info APP_DEPS_FILES = $(APP_DEPS_FILES))
	$(info )
	$(info TEST_SOURCE_FILES = $(TEST_SOURCE_FILES))
	$(info TEST_OBJ_FILES = $(TEST_OBJ_FILES))
	$(info TEST_DEPS_FILES = $(TEST_DEPS_FILES))
	$(info )
	$(info CXXFLAGS = $(CXXFLAGS))
	$(info APP_DEP_FLAGS = $(APP_DEP_FLAGS))
	$(info TEST_DEP_FLAGS = $(TEST_DEP_FLAGS))
	$(info LDFLAGS = $(LDFLAGS))
	$(info )

check:
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --suppress=missingInclude .

format:
	find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format --style=file -i {} \;
