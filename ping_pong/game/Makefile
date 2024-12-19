.PHONY: clean diff check debug
COMP_FLAGS := -Wall -pedantic

#OBG_FILES := assets.o draw.o bot.o
OBG_FILES := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

PL1_LOWER_CASE := $(shell echo $(PL1) | tr A-Z a-z)
PL2_LOWER_CASE := $(shell echo $(PL2) | tr A-Z a-z)

generate: clean_obg ping_pong_$(PL1_LOWER_CASE)_$(PL2_LOWER_CASE).out

ping_pong_$(PL1_LOWER_CASE)_$(PL2_LOWER_CASE).out: $(OBG_FILES)
	g++ $^ -o $@
	$(info OUTPUT FILE: $@)

#all: $(BOT) $(KEYBOARD) $(STD) $(HTTP)

%.o: %.cpp
	g++ -c $(COMP_FLAGS) \
		-DPL1_$(shell echo $(PL1) | tr a-z A-Z) \
		-DPL2_$(shell echo $(PL2) | tr a-z A-Z) $<

clean:
	@rm *.o 2> /dev/null
	@rm *.out 2> /dev/null

clean_obg:
	@rm *.o 2> /dev/null

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

