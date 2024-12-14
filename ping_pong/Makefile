COMP_FLAGS := -Wall -pedantic

BOT      = ping_pong_bot.out
KEYBOARD = ping_pong_pl2.out
STD      = ping_pong_pl2_std.out
HTTP     = ping_pong_pl2_http.out

OBG_FILES := assets.o draw.o bot.o
#OBG_FILES := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

help:
	$(info )
	$(info ==========HELP==========)
	$(info use  make bbot      for compiling bot version)
	$(info use  make keyboard  for compiling keyboard version)
	$(info use  make std       for compiling idf-monitor version)
	$(info use  make hhttp     for compiling http-socket version)
	$(info ==========HELP==========)
	$(info )


bbot: $(BOT)  
#Эта строчка вызывает ошибку.
#Для обхода можно вызвать make ping_pong_bot.out
#Или переименовать bot например в bbot
keyboard: $(KEYBOARD)
std: $(STD)
hhttp: $(HTTP)

$(BOT): ping_pong_bot.o $(OBG_FILES)
	g++ $^ -o $@

$(KEYBOARD): ping_pong_pl2.o $(OBG_FILES) keyInp.o
	g++ $^ -o $@

$(STD): ping_pong_pl2_std.o $(OBG_FILES) serial_std.o
	g++ $^ -o $@

$(HTTP): ping_pong_pl2_http.o $(OBG_FILES) http.o
	g++ $^ -o $@

all: $(BOT) $(KEYBOARD) $(STD) $(HTTP)

ping_pong_bot.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DBOT -o ping_pong_bot.o

ping_pong_pl2.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DKEYBOARD -o ping_pong_pl2.o

ping_pong_pl2_std.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DSTD -o ping_pong_pl2_std.o

ping_pong_pl2_http.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DHTTP -o ping_pong_pl2_http.o


%.o: %.cpp
	g++ -c $(COMP_FLAGS) $<

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

