CC=clang++
CSTD=-std=c++20
WARN=-Wall -Wextra -Wpedantic -Werror
# SOURCE=src/main.cpp src/image.cpp src/vec3.cpp src/ray.cpp src/viewport.cpp src/sphere.cpp src/tracer.cpp src/random.cpp src/lambertian.cpp src/metal.cpp
SOURCE=src/*.cpp src/*/*.cpp
INCLUDE=-Isrc -Isrc/materials -Isrc/math -Isrc/shapes
OUTPUT=ray-trc
DEBUG=-g3 -O0

build: 
	$(CC) $(WARN) $(SOURCE) $(CSTD) $(INCLUDE) -o $(OUTPUT)
debug: 
	$(CC) $(WARN) $(SOURCE) $(DEBUG) $(CSTD) $(INCLUDE) -o $(OUTPUT)
clean:
	rm -rf $(OUTPUT)