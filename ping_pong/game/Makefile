.PHONY: clean check format debug

CXX := g++

SRC_DIR := .
BUILD_DIR := build
OUT_FILE := ./ping_pong.out

SOURCE_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
OBG_FILES := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCE_FILES))
CXX_FLAGS := -Wall -pedantic -std=c++20 -g -I . -MMD
DEP_FLAGS = -MT $@ -MMD -MP -MF $(BUILD_DIR)/$*.d
LDFLAGS := -lncurses

make: $(OUT_FILE)

-include $(OBG_FILES:.o=.d)

$(OUT_FILE): $(OBG_FILES)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CXX) -c $(CXX_FLAGS) $(DEPFLAGS) -o $@ $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@rm $(OUT_FILE) 2> /dev/null
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
	clang-format --style=file -i *.cpp *.hpp
