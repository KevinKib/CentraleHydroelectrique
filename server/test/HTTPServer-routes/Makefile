CFLAGS = -ansi \
		 -pedantic \
		 -g \
		 -std=c++11 \
		 -pthread \
		 -Wall \
		 -Werror \

EXE = test

CC = g++
OFILES = test-routes.o ../../bin/TCPModule.o \
		 ../../bin/HTTPServer.o ../../bin/Catalog.o \
		 ../../bin/Server.o ../../bin/TCPServer.o \
		 ../../bin/FileReader.o ../../bin/DataModule.o

INCLUDES = ../../includes
SRC = ../../src

all: $(EXE)

$(EXE): $(OFILES)
	$(CC) $(CFLAGS) -o $(EXE) $(OFILES)

test-routes.o: $(INCLUDES)/HTTPServer.h test-routes.cpp
	g++ $(CFLAGS) -o test-routes.o -c test-routes.cpp

clean:
	rm *.o $(EXE)