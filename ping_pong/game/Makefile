.PHONY: clean diff check debug

BUILD_DIR = build
OUT_FILE = ./ping_pong.out

OBG_FILES := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(wildcard *.cpp))
COMP_FLAGS := -Wall -pedantic


make: $(OUT_FILE)

$(OUT_FILE): $(OBG_FILES)
	g++ $^ -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	g++ -c $(COMP_FLAGS) -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	@rm $(OUT_FILE) 2> /dev/null
	@rm -rf $(BUILD_DIR) 2> /dev/null

debug:
	$(info )
	$(info =========================)
	$(info OBG_FILES  = $(OBG_FILES))
	$(info COMP_FLAGS = $(COMP_FLAGS))
	$(info BUILD_DIR  = $(BUILD_DIR))
	$(info =========================)
	$(info )

diff:
	@git diff --name-only HEAD .

check:
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem .

