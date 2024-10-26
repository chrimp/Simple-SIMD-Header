CC = g++

CXXFLAGS_RELEASE = -O0 -march=native -std=c++20 -mprefer-vector-width=512 -Wall -Wextra -pedantic -Wno-unused-but-set-variable -Wno-unused-variable
CXXFLAGS_DEBUG = -g -O0 -DDEBUG -march=native -mprefer-vector-width=512 -std=c++20 -Wall -Wextra -pedantic -fsanitize=address -fsanitize=undefined -fstack-protector-all -fno-omit-frame-pointer -Wno-unused-but-set-variable -Wno-unused-variable

MAIN_SOURCES = main.cpp
SINGLE_SOURCES = single.cpp
OBJECT_SOURCES = object.cpp

MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)
SINGLE_OBJECTS = $(SINGLE_SOURCES:.cpp=.o)
OBJECT_OBJECTS = $(OBJECT_SOURCES:.cpp=.o)

RELEASE_DIR = build/release
DEBUG_DIR = build/debug

RELEASE_MAIN_OBJECTS = $(patsubst %.cpp,$(RELEASE_DIR)/%.o,$(MAIN_SOURCES))
RELEASE_SINGLE_OBJECTS = $(patsubst %.cpp,$(RELEASE_DIR)/%.o,$(SINGLE_SOURCES))
RELEASE_OBJECT_OBJECTS = $(patsubst %.cpp,$(RELEASE_DIR)/%.o,$(OBJECT_SOURCES))
DEBUG_MAIN_OBJECTS = $(patsubst %.cpp,$(DEBUG_DIR)/%.o,$(MAIN_SOURCES))

.PHONY: all release object debug clean

all: release object post-build

release: CXXFLAGS = $(CXXFLAGS_RELEASE)
release: $(RELEASE_DIR)/main

object: CXXFLAGS = $(CXXFLAGS_RELEASE)
object: $(RELEASE_DIR)/object

debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
debug: $(DEBUG_DIR)/main

$(RELEASE_DIR)/%.o: %.cpp
	@mkdir -p $(RELEASE_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(DEBUG_DIR)/%.o: %.cpp
	@mkdir -p $(DEBUG_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(RELEASE_DIR)/main: $(RELEASE_MAIN_OBJECTS)
	$(CC) $(CXXFLAGS) $(RELEASE_MAIN_OBJECTS) -o $@

$(RELEASE_DIR)/single: $(RELEASE_SINGLE_OBJECTS)
	$(CC) $(CXXFLAGS) $(RELEASE_SINGLE_OBJECTS) -o $@

$(RELEASE_DIR)/object: $(RELEASE_OBJECT_OBJECTS)
	$(CC) $(CXXFLAGS) $(RELEASE_OBJECT_OBJECTS) -o $@

$(DEBUG_DIR)/main: $(DEBUG_MAIN_OBJECTS)
	$(CC) $(CXXFLAGS) $(DEBUG_MAIN_OBJECTS) -o $@

post-build:
	rm -f $(RELEASE_DIR)/*.o $(DEBUG_DIR)/*.o

clean:
	rm -rf build