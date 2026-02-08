#include "state_manager.hpp"
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

    char highScoreText[] = {"High Score: %d"};
    sprintf(highScoreText, highScoreText, m_highScore);
    int highScoreTextWidth = MeasureText(highScoreText, 32.0f);
    DrawText(highScoreText, 720 / 2.0f - highScoreTextWidth / 2.0f, 1280 / 2.0f - 18.0f - 96, 32.0f, BLACK);

    const char* playText = "Click anywhere to start.";
    int playTextWidth = MeasureText(playText, 24.0f);
    DrawText(playText, 720 / 2.0f - playTextWidth / 2.0f, 1280 / 2.0f - 12.0f - 64, 24.0f, BLACK);
}

void StateManager::updateGameplay() {
    m_player.update();
    m_spawner.update();

    Rectangle playerCollisionRect = m_player.getCollisionRect();

    // Kill player when in contact with ground.
    if (playerCollisionRect.y + playerCollisionRect.height >= k_renderHeight) {
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
        return;
    }

    if (m_spawner.isCollidingWithPoint(playerCollisionRect)) {
        m_score += 1;
    }
}

void StateManager::drawGameplay() {
    m_player.draw();
    m_spawner.draw();

    char scoreText[] = {"Score: %d"};
    sprintf(scoreText, scoreText, m_score);
    DrawText(scoreText, 4, 4, 32.0f, BLACK);
}