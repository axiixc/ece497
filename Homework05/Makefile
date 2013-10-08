CC = gcc
CFLAGS = -g -c -Wall
CLINK = -g
CXX = g++
CXXFLAGS = -std=c++11 -g -c -Wall
CXXLINK = -std=c++11 -g

SRC_DIR = src
BUILD_DIR = build
COPY_DIR = /Volumes/192.168.7.2/Homework05

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
SOURCESXX = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTSXX = $(SOURCESXX:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXECUTABLE = hw5

all: $(BUILD_DIR) $(OBJECTS) $(SOURCES) $(OBJECTSXX) $(SOURCESXX)
	$(CC) $(CLINK) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTSXX): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -fr $(BUILD_DIR) $(EXECUTABLE)

copy:
	mkdir -p $(COPY_DIR)
	cp -r ./src $(COPY_DIR)
	cp ./Makefile $(COPY_DIR)

scp:
	scp -r $(SRC_DIR) Makefile root@192.168.7.2:~/Homework05/
