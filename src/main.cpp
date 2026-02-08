#include "game.hpp"

using namespace flappy_bird;

int main() {
    Game& game = Game::getInstance();
    game.run();
    return 0;
}