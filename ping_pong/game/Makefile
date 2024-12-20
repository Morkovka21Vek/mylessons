.PHONY: clean diff check debug help
COMP_FLAGS := -Wall -pedantic

OBG_FILES := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

PL1_LOWER_CASE := $(shell echo $(PL1) | tr A-Z a-z)
PL2_LOWER_CASE := $(shell echo $(PL2) | tr A-Z a-z)

generate: ping_pong_$(PL1_LOWER_CASE)_$(PL2_LOWER_CASE).out

help:
	$(info ========HELP========)
	$(info Use "make generate PL1=[BOT/KEYBOARD/STD/HTTP] PL2=[BOT/KEYBOARD/STD/HTTP]")
	$(info OR)
	$(info Use "make PL1=[BOT/KEYBOARD/STD/HTTP] PL2=[BOT/KEYBOARD/STD/HTTP]")
	$(info ========HELP========)

ping_pong_$(PL1_LOWER_CASE)_$(PL2_LOWER_CASE).out: $(OBG_FILES)
	g++ $^ -o $@
	@rm ping_pong.o 2> /dev/null

	$(info OUTPUT FILE: $@)

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

