#include "asset_manager.hpp"

#include "constants.hpp"

using namespace flappy_bird;

AssetManager& AssetManager::getInstance() {
    static AssetManager s_assetManager;
    return s_assetManager;
}

void AssetManager::loadAll() {
    m_atlasTexture = LoadTexture("assets/atlas.png");
    m_backgroundTexture = LoadTexture("assets/background.png");
    m_flapSound = LoadSound("assets/sfx_flap.wav");
    m_pointSound = LoadSound("assets/sfx_point.wav");
    m_deathSound = LoadSound("assets/sfx_death.wav");
}

void AssetManager::unloadAll() {
    UnloadSound(m_deathSound);
    UnloadSound(m_pointSound);
    UnloadSound(m_flapSound);
    UnloadTexture(m_backgroundTexture);
    UnloadTexture(m_atlasTexture);
}

Texture2D& AssetManager::getAtlasTexture() {
    return m_atlasTexture;
}

Rectangle AssetManager::getAtlasTextureRect(AtlasTextureRect rect) {
    switch (rect) {
    case AtlasTextureRect::BIRD_FLAP_1:
        return { 0, 0, k_playerSize, k_playerSize };
    case AtlasTextureRect::BIRD_FLAP_2:
        return { k_playerSize, 0, k_playerSize, k_playerSize };
    case AtlasTextureRect::PIPE_TOP:
        return { k_playerSize * 2, 0, k_pipeSize, k_pipeSize };
    case AtlasTextureRect::PIPE_BOTTOM:
        return { k_playerSize * 2 + k_pipeSize, 0, k_pipeSize, k_pipeSize };
    default:
        return { 0, 0, 0, 0 };
    }
}

Texture2D& AssetManager::getBackgroundTexture() {
    return m_backgroundTexture;
}

Sound& AssetManager::getFlapSound() {
    return m_flapSound;
}

Sound& AssetManager::getPointSound() {
    return m_pointSound;
}

Sound& AssetManager::getDeathSound() {
    return m_deathSound;
}