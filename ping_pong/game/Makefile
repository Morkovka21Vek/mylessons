.PHONY: clean diff check debug help
COMP_FLAGS := -Wall -pedantic

OBG_FILES := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

make: ping_pong.out

ping_pong.out: $(OBG_FILES)
	g++ $^ -o $@

#all: $(BOT) $(KEYBOARD) $(STD) $(HTTP)

%.o: %.cpp
	g++ -c $(COMP_FLAGS) \
		-DPL1_$(shell echo $(PL1) | tr a-z A-Z) \
		-DPL2_$(shell echo $(PL2) | tr a-z A-Z) $<

clean:
	@rm *.o 2> /dev/null
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

