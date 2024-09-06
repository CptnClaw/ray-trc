CC=clang++
CSTD=-std=c++17
WARN=-Wall -Wextra -Wpedantic -Werror
SOURCE=src/*.cpp src/*/*.cpp
INCLUDE=-Isrc -Isrc/materials -Isrc/math -Isrc/shapes -Isrc/bvh
OUTPUT=ray-trc
DEBUG=-g3 -O0
RELEASE=-g -O3

build: 
	$(CC) $(CSTD) $(WARN) $(SOURCE) $(RELEASE) $(INCLUDE) -o $(OUTPUT)
sah: 
	$(CC) $(CSTD) $(WARN) $(SOURCE) $(RELEASE) $(INCLUDE) -DSPLIT_USING_SAH -o $(OUTPUT)
debug: 
	$(CC) $(CSTD) $(WARN) $(SOURCE) $(DEBUG) $(INCLUDE) -o $(OUTPUT)
clean:
	rm -rf $(OUTPUT)