# Makefile for Netherite Client project (cross-platform)

# Compiler
CXX = g++

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source and output
SRC = $(SRC_DIR)/main.cpp

# Includes and Libraries
INCLUDES = -IInclude
LIBS = -LLib

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g $(INCLUDES)

# OS detection
ifeq ($(OS),Windows_NT)
	EXE = $(BUILD_DIR)/main.exe
	MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	DEL = del /f /q
	RUN = $(EXE)
	CXXFLAGS += -mwindows
else
	EXE = $(BUILD_DIR)/main
	MKDIR = mkdir -p $(BUILD_DIR)
	DEL = rm -f
	RUN = ./$(EXE)
endif

# Build target
$(EXE): $(SRC)
	$(MKDIR)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC) $(LIBS)

# Clean target
clean:
	$(DEL) $(EXE)

# Run target
run: $(EXE)
	$(RUN)
