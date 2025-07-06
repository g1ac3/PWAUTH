CXX = g++
CXXFLAGS = -I. -std=c++11 -Wall
CC = gcc
CFLAGS = -I. -O3 -Wall

# Source files
CPP_SRCS = mypwauth.cpp PWAUTH.cpp
C_SRCS = BLAKE3/c/blake3.c BLAKE3/c/blake3_portable.c BLAKE3/c/blake3_dispatch.c

# Optimized BLAKE3 source files
BLAKE3_OPT_SRCS = BLAKE3/c/blake3_avx2.c BLAKE3/c/blake3_avx512.c BLAKE3/c/blake3_sse2.c BLAKE3/c/blake3_sse41.c

ASSEMBLIES_DIR = assemblies

# Object files
OBJS = $(addprefix $(ASSEMBLIES_DIR)/, $(notdir $(CPP_SRCS:.cpp=.o))) \
       $(addprefix $(ASSEMBLIES_DIR)/, $(notdir $(C_SRCS:.c=.o))) \
       $(addprefix $(ASSEMBLIES_DIR)/, $(notdir $(BLAKE3_OPT_SRCS:.c=.o)))

# Target executable
TARGET = mypwauth

.PHONY: all clean submodules

# Default target
all: submodules $(TARGET)

# Submodules
submodules:
	@echo "Updating Git submodules..."
	git submodule update --init --recursive

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(ASSEMBLIES_DIR)/blake3.o: BLAKE3/c/blake3.c | $(ASSEMBLIES_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASSEMBLIES_DIR)/%.o: %.cpp | $(ASSEMBLIES_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(ASSEMBLIES_DIR)/%.o: %.c | $(ASSEMBLIES_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rules to compile optimized BLAKE3 C source files with specific flags
$(ASSEMBLIES_DIR)/blake3_portable.o: BLAKE3/c/blake3_portable.c | $(ASSEMBLIES_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASSEMBLIES_DIR)/blake3_dispatch.o: BLAKE3/c/blake3_dispatch.c | $(ASSEMBLIES_.c | $(ASSEMBLIES_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ASSEMBLIES_DIR)/blake3_avx2.o: BLAKE3/c/blake3_avx2.c | $(ASSEMBLIES_DIR)
	$(CC) $(CFLAGS) -mavx2 -c $< -o $@

$(ASSEMBLIES_DIR)/blake3_avx512.o: BLAKE3/c/blake3_avx512.c | $(ASSEMBLIES_DIR)
	$(CC) $(CFLAGS) -mavx512f -mavx512vl -c $< -o $@

$(ASSEMBLIES_DIR)/blake3_sse2.o: BLAKE3/c/blake3_sse2.c | $(ASSEMBLIES_DIR)
	$(CC) $(CFLAGS) -msse2 -c $< -o $@

$(ASSEMBLIES_DIR)/blake3_sse41.o: BLAKE3/c/blake3_sse41.c | $(ASSEMBLIES_DIR)
	$(CC) $(CFLAGS) -msse4.1 -c $< -o $@

# Clean up generated files
$(ASSEMBLIES_DIR):
	mkdir -p $(ASSEMBLIES_DIR)

clean:
	@echo "Cleaning up generated files..."
	rm -rf $(ASSEMBLIES_DIR) $(TARGET)
