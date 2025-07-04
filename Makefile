CXX = g++
CXXFLAGS = -I. -std=c++11 -Wall
CC = gcc
CFLAGS = -I. -O3 -Wall

# Source files
CPP_SRCS = mypwauth.cpp PWAUTH.cpp
C_SRCS = BLAKE3/c/blake3.c BLAKE3/c/blake3_portable.c BLAKE3/c/blake3_dispatch.c

# Optimized BLAKE3 source files
BLAKE3_OPT_SRCS = BLAKE3/c/blake3_avx2.c BLAKE3/c/blake3_avx512.c BLAKE3/c/blake3_sse2.c BLAKE3/c/blake3_sse41.c

# Object files
OBJS = $(CPP_SRCS:.cpp=.o) $(C_SRCS:.c=.o) $(BLAKE3_OPT_SRCS:.c=.o)

# Target executable
TARGET = mypwauth

.PHONY: all clean submodules

# Default target
all: $(TARGET)

# Submodules
submodules:
	@echo "Updating Git submodules..."
	git submodule update --init --recursive

$(TARGET): submodules $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile C++ source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile generic C source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rules to compile optimized BLAKE3 C source files with specific flags
BLAKE3/c/blake3_avx2.o: BLAKE3/c/blake3_avx2.c
	$(CC) $(CFLAGS) -mavx2 -c $< -o $@

BLAKE3/c/blake3_avx512.o: BLAKE3/c/blake3_avx512.c
	$(CC) $(CFLAGS) -mavx512f -mavx512vl -c $< -o $@

BLAKE3/c/blake3_sse2.o: BLAKE3/c/blake3_sse2.c
	$(CC) $(CFLAGS) -msse2 -c $< -o $@

BLAKE3/c/blake3_sse41.o: BLAKE3/c/blake3_sse41.c
	$(CC) $(CFLAGS) -msse4.1 -c $< -o $@

# Clean up generated files
clean:
	@echo "Cleaning up object files..."
	rm -f $(TARGET) $(OBJS)