.PHONY: clean check debug

OUT_FILE = ./car.out

OBG_FILES := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
COMP_FLAGS := -Wall -pedantic -DDEBUG


make: $(OUT_FILE)

$(OUT_FILE): $(OBG_FILES)
	g++ $^ -o $@

%.o: %.cpp
	g++ -c $(COMP_FLAGS) -o $@ $<

clean:
	@rm -f $(OUT_FILE) *.o 2> /dev/null

debug:
	$(info )
	$(info =========================)
	$(info OBG_FILES  = $(OBG_FILES))
	$(info COMP_FLAGS = $(COMP_FLAGS))
	$(info =========================)
	$(info )

check:
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem .

