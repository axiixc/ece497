CXX = g++
CXXFLAGS = -std=c++11 -g -c -Wall
CXXLINK = -std=c++11 -g

SRC_DIR = src
BUILD_DIR = build
COPY_DIR = /Volumes/192.168.7.2/Homework04

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
EXECUTABLE = hw4

all: $(BUILD_DIR) $(OBJECTS) $(SOURCES)
	$(CXX) $(CXXLINK) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): $(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -fr $(BUILD_DIR) $(EXECUTABLE)

copy:
	mkdir -p $(COPY_DIR)
	cp -r ./src $(COPY_DIR)
	cp ./Makefile $(COPY_DIR)