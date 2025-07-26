# Makefile for Netherite Client project (cross-platform)

# Compiler
CXX = g++

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source and output
SRC = $(SRC_DIR)/main.cpp

# Includes and Libraries
INCLUDES = -I"include"
LIBS = -L"lib" -lSDL3 -lvulkan-1

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g $(INCLUDES)

FINAL_BUILD_CXXFLAGS = -mwindows

# OS detection
ifeq ($(OS),Windows_NT)
	EXE = $(BUILD_DIR)/main.exe
	MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	DEL = del /f /q
	RUN = main.exe
	CXXFLAGS += -Wl,--enable-stdcall-fixup
	COPY = copy lib\SDL3.dll build
else
	EXE = $(BUILD_DIR)/main
	MKDIR = mkdir -p $(BUILD_DIR)
	DEL = rm -f
	RUN = ./main
	COPY = cp ./lib/SDL3.dll ./build/
endif

# Build target
$(EXE): $(SRC)
	$(MKDIR)
	windres src/resource.rc -o src/resource.o
	$(CXX) $(FINAL_BUILD_CXXFLAGS) $(CXXFLAGS) -o $(EXE) $(SRC) $(LIBS) src/resource.o

# Clean target
clean:
	$(DEL) $(EXE)

# Run target
run: $(EXE)
	$(COPY)
	cd build && $(RUN)