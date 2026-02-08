#include "game.hpp"

#include "asset_manager.hpp"
#include "state_manager.hpp"

#include <raylib.h>

using namespace flappy_bird;

Game& Game::getInstance() {
    static Game s_game;
    return s_game;
}

void Game::run() {
    InitWindow(k_renderWidth, k_renderHeight, "Flappy Bird");
    InitAudioDevice();
    SetTargetFPS(k_renderFPS);

    m_assetManager.loadAll();
    
    while (!WindowShouldClose()) {
        m_stateManager.update();

        BeginDrawing();
        ClearBackground(WHITE);
        m_stateManager.draw();
        EndDrawing();
    }

    m_assetManager.unloadAll();

    CloseWindow();
}

Game::Game() : m_assetManager(AssetManager::getInstance()), m_stateManager(StateManager::getInstance()) {

}