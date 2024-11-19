PROGRAMM_NAME := ping_pong.out
OBJECTS_CPP   := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: $(PROGRAMM_NAME)

$(PROGRAMM_NAME): $(OBJECTS_CPP) 
	g++ $^ -o $@

%.o: %.cpp
	g++ -c $< 

clean:
	@rm $(OBJECTS_CPP) 2> /dev/null
	@rm $(PROGRAMM_NAME) 2> /dev/null

.PHONY: all debug

debug:
	$(info )
	$(info ======================================================)
	$(info PROGRAMM_NAME = $(PROGRAMM_NAME))
	$(info OBJECTS_CPP = $(OBJECTS_CPP))
	$(info ======================================================)
	$(info )

diff:
	@git diff --name-only HEAD .

start:
	@./$(PROGRAMM_NAME)
