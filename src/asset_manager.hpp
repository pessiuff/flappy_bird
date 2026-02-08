#pragma once

#include <raylib.h>

namespace flappy_bird {
    enum class AtlasTextureRect {
        BIRD_FLAP_1,
        BIRD_FLAP_2,
        PIPE_TOP,
        PIPE_BOTTOM,
    };

    class AssetManager {
    public:
        static AssetManager& getInstance();

        void loadAll();
        void unloadAll();

        Texture2D& getAtlasTexture();
        Rectangle getAtlasTextureRect(AtlasTextureRect rect);
        Texture2D& getBackgroundTexture();
        Sound& getFlapSound();
        Sound& getPointSound();
        Sound& getDeathSound();

    private:
        Texture2D m_atlasTexture {};
        Texture2D m_backgroundTexture {};
        Sound m_flapSound {};
        Sound m_pointSound {};
        Sound m_deathSound {};
    };
}