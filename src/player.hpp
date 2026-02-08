#pragma once

#include "constants.hpp"

#include <raylib.h>

namespace flappy_bird {
    class Player {
    public:
        void update();
        void draw();
        void reset();
        void kill();
        bool isAlive();
        Rectangle getCollisionRect();

    private:
        bool m_isAlive = true;
        Vector2 m_position { k_renderWidth / 4.0f, k_renderHeight / 2.0f };
        float m_fallSpeed = 0.0f;
        float m_rotation = 0.0f;
    };
}