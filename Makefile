CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++11 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
TEST    := test

LIBRARIES	:=
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(TEST)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*
