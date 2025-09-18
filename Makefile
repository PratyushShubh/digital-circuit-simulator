# Digital Circuit Simulator Makefile
# Author: Piyush
# Version: 1.0

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = circuit
SOURCE = circuit.cpp

# Platform detection
ifeq ($(OS),Windows_NT)
    TARGET_EXT = .exe
    RM = del /Q
    STATIC_FLAGS = -static-libgcc -static-libstdc++
else
    TARGET_EXT = 
    RM = rm -f
    STATIC_FLAGS = 
endif

# Default target
all: $(TARGET)$(TARGET_EXT)

# Build target
$(TARGET)$(TARGET_EXT): $(SOURCE)
	@echo "Compiling Digital Circuit Simulator..."
	$(CXX) $(CXXFLAGS) $(STATIC_FLAGS) -o $@ $<
	@echo "Build complete! Run with: ./$(TARGET)$(TARGET_EXT)"

# Debug build
debug: CXXFLAGS += -DDEBUG -g
debug: $(TARGET)$(TARGET_EXT)

# Clean build files
clean:
	$(RM) $(TARGET)$(TARGET_EXT)
	@echo "Clean complete!"

# Install target (Linux/macOS only)
install: $(TARGET)$(TARGET_EXT)
ifneq ($(OS),Windows_NT)
	cp $(TARGET) /usr/local/bin/
	@echo "Installed to /usr/local/bin/"
else
	@echo "Install target not supported on Windows"
endif

# Test target
test: $(TARGET)$(TARGET_EXT)
	@echo "Running test cases..."
	@if [ -f examples/half_adder_test.txt ]; then \
		echo "Testing Half Adder circuit..."; \
		./$(TARGET)$(TARGET_EXT) < examples/half_adder_test.txt; \
	else \
		echo "Test files not found in examples/ directory"; \
	fi

# Help target
help:
	@echo "Digital Circuit Simulator Makefile"
	@echo "Available targets:"
	@echo "  all     - Build the circuit simulator (default)"
	@echo "  debug   - Build with debug symbols"
	@echo "  clean   - Remove build files"
	@echo "  install - Install to system (Linux/macOS only)"
	@echo "  test    - Run test cases"
	@echo "  help    - Show this help message"

.PHONY: all debug clean install test help