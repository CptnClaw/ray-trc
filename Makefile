CC=clang++
WARN=-Wall -Wextra -Wpedantic -Werror
SOURCE=src/*.cpp src/*/*.cpp
INCLUDE=-Isrc -Isrc/materials -Isrc/math -Isrc/shapes -Isrc/bvh
OUTPUT=ray-trc
DEBUG=-g3 -O0
RELEASE=-g -O3

build: 
	$(CC) $(WARN) $(SOURCE) $(RELEASE) $(INCLUDE) -o $(OUTPUT)
debug: 
	$(CC) $(WARN) $(SOURCE) $(DEBUG) $(INCLUDE) -o $(OUTPUT)
clean:
	rm -rf $(OUTPUT)