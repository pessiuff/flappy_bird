#include "pipe_spawner.hpp"

#include "asset_manager.hpp"

#include <random>
#include <raymath.h>

using namespace flappy_bird;

void PipeSpawner::update() {
    static std::random_device s_random_device;
    static std::mt19937 s_random_generator(s_random_device());

    static float spawnTimer = 0.0f;
    spawnTimer += k_renderFrameTime;
    if (spawnTimer >= 2.0f) {
        for (int i = 0; i < 4; i++) {
            Pipe& pipe = m_pipes[i];
            if (pipe.respawn) {
                pipe.respawn = false;
                std::uniform_real_distribution<> top_distribution(1, 7.5);
                pipe.topYScale = top_distribution(s_random_generator);
                pipe.bottomYScale = 10 - pipe.topYScale - 1.5;
                pipe.xPosition = k_renderWidth + k_pipeSize;
                pipe.hasPoint = true;
                break;
            }
        }
        spawnTimer = 0.0f;
    }

    for (int i = 0; i < 4; i++) {
        Pipe& pipe = m_pipes[i];
        if (pipe.respawn) {
            continue;
        }

        pipe.xPosition -= k_renderFrameTime * k_pipeSize * 2;

        if (pipe.xPosition <= -(k_pipeSize * 2)) {
            pipe.respawn = true;
        }
    }
}

void PipeSpawner::draw() {
    AssetManager& assetManager = AssetManager::getInstance();
    Texture2D atlasTexture = assetManager.getAtlasTexture();

    for (int i = 0; i < 4; i++) {
        Pipe& pipe = m_pipes[i];
        if (pipe.respawn) {
            continue;
        }

        NPatchInfo topPipePatchInfo = {
            assetManager.getAtlasTextureRect(AtlasTextureRect::PIPE_TOP),
            0,
            0,
            0,
            48,
            NPATCH_THREE_PATCH_VERTICAL
        };

        Rectangle topPipeRect = {
            pipe.xPosition,
            0,
            k_pipeSize,
            static_cast<float>(k_pipeSize * pipe.topYScale)
        };
        
        DrawTextureNPatch(
            atlasTexture,
            topPipePatchInfo,
            topPipeRect,
            Vector2Zeros,
            0.0f,
            WHITE
        );

        NPatchInfo bottomPipePatchInfo = {
            assetManager.getAtlasTextureRect(AtlasTextureRect::PIPE_BOTTOM),
            0,
            48,
            0,
            0,
            NPATCH_THREE_PATCH_VERTICAL
        };

        Rectangle bottomPipeRect = {
            pipe.xPosition,
            topPipeRect.height + pipe.gap,
            k_pipeSize,
            static_cast<float>(k_pipeSize * pipe.bottomYScale)
        };

        DrawTextureNPatch(
            atlasTexture,
            bottomPipePatchInfo,
            bottomPipeRect,
            Vector2Zeros,
            0.0f,
            WHITE
        );
    }
}

void PipeSpawner::reset() {
    for (int i = 0; i < 4; i++) {
        m_pipes[i].respawn = true;
    }
}

bool PipeSpawner::isCollidingWithPipe(const Rectangle& rect) {
    for (int i = 0; i < 4; i++) {
        Pipe& pipe = m_pipes[i];
        if (pipe.respawn) {
            continue;
        }

        Rectangle topPipeRect = {
            pipe.xPosition,
            0,
            k_pipeSize,
            static_cast<float>(k_pipeSize * pipe.topYScale)
        };

        if (CheckCollisionRecs(rect, topPipeRect)) {
            return true;
        }

        Rectangle bottomPipeRect = {
            pipe.xPosition,
            topPipeRect.height + pipe.gap,
            k_pipeSize,
            static_cast<float>(k_pipeSize * pipe.bottomYScale)
        };

        if (CheckCollisionRecs(rect, bottomPipeRect)) {
            return true;
        }
    }

    return false;
}

bool PipeSpawner::isCollidingWithPoint(const Rectangle& rect) {
    for (int i = 0; i < 4; i++) {
        Pipe& pipe = m_pipes[i];
        if (pipe.respawn || !pipe.hasPoint) {
            continue;
        }

        Rectangle topPipeRect = {
            pipe.xPosition,
            0,
            k_pipeSize,
            static_cast<float>(k_pipeSize * pipe.topYScale)
        };

        Rectangle pointRect = {
            pipe.xPosition,
            topPipeRect.height,
            k_pipeSize,
            static_cast<float>(pipe.gap)  
        };

        if (CheckCollisionRecs(rect, pointRect)) {
            pipe.hasPoint = false;
            return true;
        }
    }

    return false;
}