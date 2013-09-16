CC=g++
CFLAGS=-std=c++11 -c -Wall
LDFLAGS=-std=c++11 -lncurses -ltinfo
SOURCES=$(wildcard Homework2/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hw2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
