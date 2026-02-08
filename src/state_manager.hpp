#pragma once

#include "player.hpp"
#include "pipe_spawner.hpp"

namespace flappy_bird {
    enum class State {
        MENU,
        GAMEPLAY
    };

    class StateManager {
    public:
        static StateManager& getInstance();

        void update();
        void draw();

    private:
        State m_state = State::MENU;
        Player m_player {};
        PipeSpawner m_spawner {};
        int m_score = 0;
        int m_highScore = 0;

        void updateMenu();
        void drawMenu();
        void updateGameplay();
        void drawGameplay();
    };
}