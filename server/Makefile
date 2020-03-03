CC = g++
CFLAGS = -Wall \
		 -Werror \
		 -ansi \
		 -pedantic \
		 -std=c++11 \
		 -pthread \
		 -g

BIN = bin
SRC = src
INCLUDES = includes
EXE = server
OFILES = $(BIN)/main.o \
		 $(BIN)/Server.o \
		 $(BIN)/TCPServer.o \
		 $(BIN)/FileReader.o \
		 $(BIN)/HTTPServer.o \
		 $(BIN)/Catalog.o \

all: $(EXE)

clean:
	rm -rf $(BIN)/* $(EXE)

$(EXE): $(OFILES)
	$(CC) $(CFLAGS) -o $(EXE) $(OFILES)

$(BIN)/Catalog.o: $(INCLUDES)/Catalog.h $(SRC)/Catalog.cpp $(INCLUDES)/TCPServer.h
	$(CC) $(CFLAGS) -o $(BIN)/Catalog.o -c $(SRC)/Catalog.cpp

$(BIN)/FileReader.o: $(INCLUDES)/FileReader.h $(SRC)/FileReader.cpp
	$(CC) $(CFLAGS) -o $(BIN)/FileReader.o -c $(SRC)/FileReader.cpp

$(BIN)/HTTPServer.o: $(INCLUDES)/HTTPServer.h $(SRC)/HTTPServer.cpp $(INCLUDES)/Server.h $(INCLUDES)/FileReader.h
	$(CC) $(CFLAGS) -o $(BIN)/HTTPServer.o -c $(SRC)/HTTPServer.cpp

$(BIN)/main.o: $(SRC)/main.cpp $(INCLUDES)/HTTPServer.h $(INCLUDES)/TCPServer.h
	$(CC) $(CFLAGS) -o $(BIN)/main.o -c $(SRC)/main.cpp


$(BIN)/TCPServer.o: $(INCLUDES)/TCPServer.h $(SRC)/TCPServer.cpp $(INCLUDES)/Server.h
	$(CC) $(CFLAGS) -o $(BIN)/TCPServer.o -c $(SRC)/TCPServer.cpp

$(BIN)/Server.o: $(INCLUDES)/Server.h $(SRC)/Server.cpp
	$(CC) $(CFLAGS) -o $(BIN)/Server.o -c $(SRC)/Server.cpp