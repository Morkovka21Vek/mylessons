.PHONY: clean check debug

BUILD_DIR = build
OUT_FILE = ./client
SRC_DIR = src

OBG_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
COMP_FLAGS := -Wall -pedantic

all: $(OUT_FILE)

$(OUT_FILE): $(OBG_FILES)
	gcc $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	gcc -c $(COMP_FLAGS) -o $@ $<

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
	$(info SRC_DIR    = $(SRC_DIR))
	$(info =========================)
	$(info )

check:
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem .
