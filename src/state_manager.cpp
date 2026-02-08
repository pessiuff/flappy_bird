#include "state_manager.hpp"

#include "asset_manager.hpp"

#include <stdio.h>

using namespace flappy_bird;

StateManager& StateManager::getInstance() {
    static StateManager s_stateManager;
    return s_stateManager;
}

void StateManager::update() {
    switch (m_state) {
        case State::MENU: {
            updateMenu();
            break;
        }
        case State::GAMEPLAY: {
            updateGameplay();
            break;
        }
        default: {
            break;
        }
    }
}

void StateManager::draw() {
    DrawTexture(AssetManager::getInstance().getBackgroundTexture(), 0,0, WHITE);
    
    switch (m_state) {
        case State::MENU: {
            drawMenu();
            break;
        }
        case State::GAMEPLAY: {
            drawGameplay();
            break;
        }
        default: {
            break;
        }
    }
}

void StateManager::updateMenu() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        m_state = State::GAMEPLAY;
        m_score = 0;
        m_player.reset();
        m_spawner.reset();
    }
}

void StateManager::drawMenu() {
    m_player.draw();
    m_spawner.draw();

    char highScoreText[64];
    snprintf(highScoreText, sizeof(highScoreText), "High Score: %d", m_highScore);
    int highScoreTextWidth = MeasureText(highScoreText, 32.0f);
    DrawText(highScoreText, k_renderWidth / 2.0f - highScoreTextWidth / 2.0f, k_renderHeight / 2.0f - 16 - 12, 32.0f, WHITE);

    const char* playText = "Click anywhere to start.";
    int playTextWidth = MeasureText(playText, 24.0f);
    DrawText(playText, k_renderWidth / 2.0f - playTextWidth / 2.0f, k_renderHeight / 2.0f + 12, 24.0f, WHITE);
}

void StateManager::updateGameplay() {
    m_player.update();
    m_spawner.update();

    Rectangle playerCollisionRect = m_player.getCollisionRect();

    // Kill player when in contact with ground.
    if (CheckCollisionPointRec({ playerCollisionRect.x, k_renderHeight - playerCollisionRect.height / 2.5f }, playerCollisionRect)) {
        m_player.kill();
    }

    // Kill player when in contact with a pipe.
    if (m_spawner.isCollidingWithPipe(playerCollisionRect)) {
        m_player.kill();
    }

    if (!m_player.isAlive()) {
        m_state = State::MENU;
        if (m_score > m_highScore) {
            m_highScore = m_score;
        }
        PlaySound(AssetManager::getInstance().getDeathSound());
        return;
    }

    if (m_spawner.isCollidingWithPoint(playerCollisionRect)) {
        m_score += 1;
        PlaySound(AssetManager::getInstance().getPointSound());
    }
}

void StateManager::drawGameplay() {
    m_player.draw();
    m_spawner.draw();

    char scoreText[64];
    snprintf(scoreText, sizeof(scoreText), "Score: %d", m_score);
    DrawText(scoreText, 4, 4, 32.0f, WHITE);
}