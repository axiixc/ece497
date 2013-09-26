CXX      = g++
CC       = gcc
CPPFLAGS  = -std=c++11 -c -g -Wall
CFLAGS = -c -g -Wall
LDFLAGS = -std=c++11 -lncurses -ltinfo -g

BUILD_DIR = build
SRC_DIR   = Homework2

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
CSOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:.cpp=.o) $(CSOURCES:.c=.o)

EXECUTABLE=hw2

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
				$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: %.cpp
				$(CXX) $(CPPFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.c
				$(CC) $(CFLAGS) $(TOOLS_CFLAGS) $< -o $@

$(BUILD_DIR):
				mkdir -p $@

clean:
				rm $(EXECUTABLE) $(OBJECTS)