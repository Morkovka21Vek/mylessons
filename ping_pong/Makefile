BOT = ping_pong_bot.out
KEYBOARD = ping_pong_pl2.out
STD = ping_pong_pl2_std.out
HTTP = ping_pong_pl2_http.out

COMP_FLAGS := -Wall -pedantic
#CPP_FILES  := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

help:
	$(info )
	$(info ==========HELP==========)
	$(info use  make bot       for compiling bot version)
	$(info use  make keyboard  for compiling keyboard version)
	$(info use  make std       for compiling idf-monitor version)
	$(info ==========HELP==========)
	$(info )


bot: $(BOT)  
#Эта строчка вызывает ошибку.
#Для обхода можно вызвать make ping_pong_bot.out
#Или переименовать bot например в bbot
keyboard: $(KEYBOARD)
std: $(STD)
http:
	g++ -o ping_pong_pl2_http.out ping_pong.cpp assets.cpp bot.cpp http.cpp -Wall -pedantic -DHTTP -lcpr -lcurl -lssl -lcrypto

$(BOT): ping_pong_bot.o assets.o bot.o
	g++ $^ -o $@

$(KEYBOARD): ping_pong_pl2.o assets.o bot.o keyInp.o
	g++ $^ -o $@

$(STD): ping_pong_pl2_std.o assets.o bot.o serial_std.o
	g++ $^ -o $@

$(HTTP): ping_pong_pl2_http.o assets.o bot.o http.o
	g++ $^ -o $@ -lcpr -lcurl -lssl -lcrypto

all: $(BOT) $(KEYBOARD) $(STD) $(HTTP)

ping_pong_bot.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DBOT -o ping_pong_bot.o

ping_pong_pl2.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DKEYBOARD -o ping_pong_pl2.o

ping_pong_pl2_std.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DSTD -o ping_pong_pl2_std.o

ping_pong_pl2_http.o: ping_pong.cpp
	g++ -c $(COMP_FLAGS) $< -DHTTP -lcpr -lcurl -lssl -lcrypto -o ping_pong_pl2_http.o


%.o: %.cpp
	g++ -c $(COMP_FLAGS) $<

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


