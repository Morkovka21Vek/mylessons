.PHONY: clean check format debug

CXX := g++

SRC_DIR := .
BUILD_DIR := build
BUILD_OBJ_SUBDIR := obj_dir
BUILD_DEPS_SUBDIR := deps_dir
OUT_FILE := $(BUILD_DIR)/ping_pong.out

SOURCE_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
OBG_FILES := $(patsubst %.cpp, $(BUILD_DIR)/$(BUILD_OBJ_SUBDIR)/%.o, $(SOURCE_FILES))
DEPS_FILES := $(patsubst %.cpp, $(BUILD_DIR)/$(BUILD_DEPS_SUBDIR)/%.d, $(SOURCE_FILES))
CXX_FLAGS := -Wall -pedantic -std=c++20 -g -I . -MMD
DEP_FLAGS = -MT $@ -MMD -MP -MF $(BUILD_DIR)/$(BUILD_DEPS_SUBDIR)/$*.d
LDFLAGS := -lncurses

build: $(OUT_FILE)
rebuild: clean build

-include $(DEPS_FILES)

$(OUT_FILE): $(OBG_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(BUILD_OBJ_SUBDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@mkdir -p $(subst $(BUILD_OBJ_SUBDIR),$(BUILD_DEPS_SUBDIR),$(@D))
	$(CXX) -c $(CXX_FLAGS) $(DEP_FLAGS) -o $@ $<

clean:
	@rm -rf $(BUILD_DIR) 2> /dev/null

debug:
	$(info )
	$(info SRC_DIR       = $(SRC_DIR))
	$(info SOURCE_FILES  = $(SOURCE_FILES))
	$(info OBG_FILES     = $(OBG_FILES))
	$(info CXX_FLAGS     = $(CXX_FLAGS))
	$(info BUILD_DIR     = $(BUILD_DIR))
	$(info )

check:
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --suppress=missingInclude .

format:
	find . -type f \( -name "*.cpp" -o -name "*.hpp" \) -exec clang-format --style=file -i {} \;
