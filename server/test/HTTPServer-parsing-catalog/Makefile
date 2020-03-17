CFLAGS = -ansi \
		 -pedantic \
		 -g \
		 -std=c++11 \
		 -pthread \
		 -Wall \
		 -Werror \

EXE = test

CC = g++
OFILES = test-parsing.o ../../bin/TCPModule.o \
		 ../../bin/HTTPServer.o ../../bin/Catalog.o \
		 ../../bin/Server.o ../../bin/TCPServer.o \
		 ../../bin/FileReader.o ../../bin/DataModule.o

INCLUDES = ../../includes
SRC = ../../src

all: $(EXE)

$(EXE): $(OFILES)
	$(CC) $(CFLAGS) -o $(EXE) $(OFILES)

test-parsing.o: $(INCLUDES)/HTTPServer.h test-parsing.cpp
	g++ $(CFLAGS) -o test-parsing.o -c test-parsing.cpp

clean:
	rm *.o $(EXE)