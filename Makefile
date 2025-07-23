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
LIBS = -L"lib" -lSDL3

# Optional Vulkan
VULKAN_DIR = C:/VulkanSDK
VULKAN_LIB = -L$(VULKAN_DIR)/Lib

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -g $(INCLUDES)

# OS detection
ifeq ($(OS),Windows_NT)
	EXE = $(BUILD_DIR)/main.exe
	MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	DEL = del /f /q
	RUN = main.exe
	CXXFLAGS += -mwindows
else
	EXE = $(BUILD_DIR)/main
	MKDIR = mkdir -p $(BUILD_DIR)
	DEL = rm -f
	RUN = ./main
endif

# Build target
$(EXE): $(SRC)
	$(MKDIR)
	windres src/resource.rc -o src/resource.o
	$(CXX) $(CXXFLAGS) -o $(EXE) $(SRC) $(LIBS) $(VULKAN_LIB) src/resource.o

# Clean target
clean:
	$(DEL) $(EXE)

# Run target
run: $(EXE)
	cd build && $(RUN)
