CC=clang++
CSTD=-std=c++23
SOURCE=src/main.cpp src/image.cpp 
OUTPUT=ray-trc
DEBUG=-g3 -O0

build: 
	$(CC) $(SOURCE) $(CSTD) -o $(OUTPUT)
debug: 
	$(CC) $(SOURCE) $(DEBUG) $(CSTD) -o $(OUTPUT)
clean:
	rm -rf $(OUTPUT)