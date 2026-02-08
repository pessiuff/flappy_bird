#include "game.hpp"

#include <raylib.h>

using namespace flappy_bird;

int main() {
    Game& game = Game::getInstance();
    game.run();
    return 0;
}