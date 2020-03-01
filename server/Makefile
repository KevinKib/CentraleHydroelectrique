CC = g++
CFLAGS = -Wall \
		 -Werror \
		 -ansi \
		 -pedantic \
		 -std=c++11 \
		 -pthread \

BIN = bin
SRC = src
INCLUDES = includes
EXE = server
OFILES = $(BIN)/main.o \

all: $(EXE)

clean:
	rm -rf $(BIN)/* $(EXE)

$(EXE): $(OFILES)
	$(CC) $(CFLAGS) -o $(EXE) $(OFILES)

$(BIN)/main.o: $(SRC)/main.cpp

	$(CC) $(CFLAGS) -o $(BIN)/main.o -c $(SRC)/main.cpp