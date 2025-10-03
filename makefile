# Compiler
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++11

# Source and output folders
SRC_DIR = src
BIN_DIR = bin

# Executables
TARGETS = $(BIN_DIR)/extract_flow $(BIN_DIR)/fluvial_Qr

all: $(TARGETS)

# Rules to build each program
$(BIN_DIR)/extract_flow: $(SRC_DIR)/extract_flow.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/fluvial_Qr: $(SRC_DIR)/fluvial_Qr.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

# Create bin directory if it doesn’t exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean rule
clean:
	rm -rf $(BIN_DIR)
