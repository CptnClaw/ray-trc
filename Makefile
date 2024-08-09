CC=clang++
CSTD=-std=c++23
WARN=-Wall -Wextra -Wpedantic -Werror
SOURCE=src/main.cpp src/image.cpp src/vec3.cpp src/ray.cpp src/viewport.cpp
OUTPUT=ray-trc
DEBUG=-g3 -O0

build: 
	$(CC) $(WARN) $(SOURCE) $(CSTD) -o $(OUTPUT)
debug: 
	$(CC) $(WARN) $(SOURCE) $(DEBUG) $(CSTD) -o $(OUTPUT)
clean:
	rm -rf $(OUTPUT)