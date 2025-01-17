.PHONY: clean diff check debug help
COMP_FLAGS := -Wall -pedantic

BUILD_DIR = build
OBG_FILES := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(wildcard *.cpp))

make: ping_pong.out

ping_pong.out: $(OBG_FILES)
	g++ $^ -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	g++ -c $(COMP_FLAGS) -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR) 2> /dev/null
	@rm *.out 2> /dev/null

debug:
	$(info )
	$(info =========================)
	$(info OBG_FILES = $(OBG_FILES))
	$(info =========================)
	$(info )

diff:
	@git diff --name-only HEAD .

check:
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem .

