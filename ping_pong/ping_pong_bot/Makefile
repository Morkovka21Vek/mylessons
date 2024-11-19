PROGRAMM_NAME := ping_pong.out
CPP_FILES 		:= $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: $(PROGRAMM_NAME)

$(PROGRAMM_NAME): $(CPP_FILES)
	g++ $^ -o $@

%.o: %.cpp
	g++ -c $<

clean:
	@rm *.o 2> /dev/null
	@rm $(PROGRAMM_NAME) 2> /dev/null

debug:
	$(info )
	$(info =========================)
	$(info PROGRAMM_NAME = $(PROGRAMM_NAME))
	$(info CPP_FILES = $(CPP_FILES))
	$(info =========================)
	$(info )

diff:
	@git diff --name-only HEAD .

start:
	./$(PROGRAMM_NAME)

