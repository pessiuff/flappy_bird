# Flappy Bird

A Flappy Bird clone made with C++ and [raylib](https://github.com/raysan5/raylib) for desktop platforms.

## Build Requirements

- Any C++ compiler and [CMake](https://cmake.org/).
- [Platform specific requirements](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation) for building raylib.

## Example Build Instructions

```bash
git clone https://github.com/pessiuff/flappy_bird.git
cd flappy_bird
cmake -S . -B build
cmake --build build
# You don't have to copy the "assets/" folder near the executable unless you run the executable from root directory like this:
./build/flappy_bird
```
