BOT = ping_pong_bot.out
KEYBOARD = ping_pong_pl2.out
STD = ping_pong_pl2_std.out

COMP_FLAGS := -Wall -pedantic
COMP_MODE = 
#CPP_FILES  := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

help:
	$(info )
	$(info ==========HELP==========)
	$(info use  make bot       for compiling bot version)
	$(info use  make keyboard  for compiling keyboard version)
	$(info use  make std       for compiling idf-monitor version)
	$(info ==========HELP==========)
	$(info )


bot_comp: $(BOT)
keyboard: $(KEYBOARD)
std: $(STD)

$(BOT): COMP_MODE = -DBOT
$(BOT): ping_pong_bot.o assets.o bot.o
	g++ $^ -o $@

$(KEYBOARD): COMP_MODE = -DKEYBOARD
$(KEYBOARD): ping_pong_pl2.o assets.o bot.o keyInp.o
	g++ $^ -o $@

$(STD): COMP_MODE = -DSTD
$(STD): ping_pong_pl2_std.o assets.o bot.o serial_std.o
	g++ $^ -o $@

all: $(BOT) $(KEYBOARD) $(STD)

ping_pong_bot.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DBOT -o ping_pong_bot.o

ping_pong_pl2.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DKEYBOARD -o ping_pong_pl2.o

ping_pong_pl2_std.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DSTD -o ping_pong_pl2_std.o

%.o: %.cpp
	g++ -c $(COMP_FLAGS) $< $(COMP_MODE)

clean:
	@rm *.o 2> /dev/null
	@rm *.out 2> /dev/null

pretty:
	@rm *.o 2> /dev/null

debug:
	$(info )
	$(info =========================)
	$(info CPP_FILES = $(CPP_FILES))
	$(info =========================)
	$(info )

diff:
	@git diff --name-only HEAD .

run_std_pl2:
	idf.py monitor | ./ping_pong_pl2.out


