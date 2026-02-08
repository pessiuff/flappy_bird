#include "player.hpp"

#include "asset_manager.hpp"

#include <raymath.h>

using namespace flappy_bird;

void Player::update() {
    if (!m_isAlive) {
        return;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        m_fallSpeed = -384.0f;
    }

    if (m_fallSpeed < 640.0f) {
        if (m_fallSpeed < 0.0f) {
            m_fallSpeed += k_renderFrameTime * 768.0f;
        } else {
            m_fallSpeed += k_renderFrameTime * 640.0f;
        }
    }

    bool is_falling = m_fallSpeed > 0.0f;

    if (is_falling) {
        m_rotation += GetFrameTime() * 180.0f;
    } else {
        m_rotation -= GetFrameTime() * 720.0f;
    }
    m_rotation = Clamp(m_rotation, -45.0f, 90.0f);

    float expected_y_position = m_position.y + k_renderFrameTime * m_fallSpeed;
    m_position.y = Clamp(expected_y_position, 0.0f + k_playerSize / 4.0f, k_renderHeight - k_playerSize / 4.0f);
}

void Player::draw() {
    AssetManager& assetManager = AssetManager::getInstance();
    Texture2D atlasTexture = assetManager.getAtlasTexture();
    
    static float animationTimer = 0.0f;
    animationTimer += GetFrameTime();
    if (animationTimer >= 1.0f) {
        animationTimer = 0.0f;
    }

    AtlasTextureRect currentFrame;
    if (animationTimer < 0.5f) {
        currentFrame = AtlasTextureRect::BIRD_FLAP_1;
    } else {
        currentFrame = AtlasTextureRect::BIRD_FLAP_2;
    }

    DrawTexturePro(atlasTexture, assetManager.getAtlasTextureRect(currentFrame), { m_position.x, m_position.y, k_playerSize, k_playerSize }, { k_playerSize / 2.0f, k_playerSize / 2.0f }, m_rotation, WHITE);
}

void Player::reset() {
    m_isAlive = true;
    m_position = { k_renderWidth / 4.0f, k_renderHeight / 2.0f };
    m_fallSpeed = 0.0f;
    m_rotation = 0.0f;
}

void Player::kill() {
    m_isAlive = false;
}

bool Player::isAlive() {
    return m_isAlive;
}

Rectangle Player::getCollisionRect() {
    return { m_position.x - k_playerSize / 5.0f, m_position.y - k_playerSize / 5.0f, k_playerSize / 2.5f, k_playerSize / 2.5f };
}
