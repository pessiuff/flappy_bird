#pragma once

namespace flappy_bird {
    class AssetManager;
    class StateManager;

    class Game {
    public:
        static Game& getInstance();

        void run();

    private:
        Game();
        ~Game() = default;

        AssetManager& m_assetManager;
        StateManager& m_stateManager;
    };
}