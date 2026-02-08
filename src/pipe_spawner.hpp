#pragma once

#include "constants.hpp"

#include <raylib.h>

namespace flappy_bird {
    struct Pipe {
        bool respawn = true;
        float topYScale = 0.0f;
        float bottomYScale = 0.0f;
        float xPosition = 0.0f;
        int gap = k_pipeSize + k_pipeSize / 2;
        bool hasPoint = true;
    };

    class PipeSpawner {
    public:
        void update();
        void draw();
        void reset();

        bool isCollidingWithPipe(const Rectangle& rect);
        bool isCollidingWithPoint(const Rectangle& rect);

    private:
        Pipe m_pipes[4] {};
    };
};