#include "games/pong/PongScene.h"

#include <string>

#include "games/pong/PongConfig.h"
#include "raylib.h"

namespace arcade {

namespace {

float getCenteredPaddleY() {
    return (static_cast<float>(GetScreenHeight()) - PongConfig::paddleHeight)/2.0f;
}

float getCenteredBallX() {
    return static_cast<float>(GetScreenWidth())/2.0f;
}

float getCenteredBallY() {
    return static_cast<float>(GetScreenHeight())/2.0f + 40.0f;
}

}

PongScene::PongScene() {
    state_.state = GameState::RUNNING;

    state_.leftPaddle = {getCenteredPaddleY(), PongConfig::leftPaddleSpeed, true};
    state_.rightPaddle = {getCenteredPaddleY(), PongConfig::rightPaddleSpeed, false};
    state_.ball = {getCenteredBallX(), getCenteredBallY(), 200.0f, 200.0f};
}

void PongScene::onEnter() {
    state_.state = GameState::RUNNING;

    state_.leftPaddle = {getCenteredPaddleY(), PongConfig::leftPaddleSpeed, true};
    state_.rightPaddle = {getCenteredPaddleY(), PongConfig::rightPaddleSpeed, false};
    state_.ball = {getCenteredBallX(), getCenteredBallY(), 200.0f, 200.0f};

    state_.leftScore = 0;
    state_.rightScore = 0;
}

void PongScene::onExit() {
    state_.state = GameState::EXIT;
}

void PongScene::update(float dt) {
    if (IsKeyPressed(KEY_P) &&
        state_.state != GameState::WIN &&
        state_.state != GameState::LOSE) {
        if (state_.state == GameState::PAUSED) {
            state_.state = GameState::RUNNING;
        } else {
            state_.state = GameState::PAUSED;
        }
    }

    if (state_.state == GameState::PAUSED ||
        state_.state == GameState::WIN ||
        state_.state == GameState::LOSE) {
        return;
    }

    if (IsKeyDown(KEY_W)) {
        state_.leftPaddle.MoveUp(dt);
    }
    
    if (IsKeyDown(KEY_S)) {
        state_.leftPaddle.MoveDown(dt);
    }

    if (state_.ball.y < state_.rightPaddle.y + 30) {
        state_.rightPaddle.MoveUp(dt);
    } 
    
    if (state_.ball.y > state_.rightPaddle.y + 30) {
        state_.rightPaddle.MoveDown(dt);
    }

    const float screenWidth = static_cast<float>(GetScreenWidth());
    const float screenHeight = static_cast<float>(GetScreenHeight());

    state_.leftPaddle.Clamp(100.0f, screenHeight - 80.0f);
    state_.rightPaddle.Clamp(100.0f, screenHeight - 80.0f);

    state_.ball.Update(dt);
    state_.ball.WallBounce(108, static_cast<int>(screenHeight) - 28);

    if (state_.ball.x <= 28) {
        state_.rightScore += 1;

        if (state_.rightScore >= 11) {
            state_.state = GameState::LOSE;
            state_.ball.vx = 0.0f;
            state_.ball.vy = 0.0f;
            return;
        }

        resetRound(true);
        return;
    }

    if (state_.ball.x >= screenWidth - 28.0f) {
        state_.leftScore += 1;

        if (state_.leftScore >= 11) {
            state_.state = GameState::WIN;
            state_.ball.vx = 0.0f;
            state_.ball.vy = 0.0f;
            return;
        }

        resetRound(false);
        return;
    }

    if (state_.ball.vx < 0.0f && state_.ball.x <= 48.0f) {
        state_.ball.PaddleBounce(state_.leftPaddle.y, PongConfig::paddleHeight);
    } else if (state_.ball.vx > 0.0f && state_.ball.x >= screenWidth - 48.0f) {
        state_.ball.PaddleBounce(state_.rightPaddle.y, PongConfig::paddleHeight);
    }
}

void PongScene::render() {
    const int screenWidth = GetScreenWidth();
    DrawText("PONG", screenWidth/2 - MeasureText("PONG", 60)/2, 20, 60, RAYWHITE);

    drawCourt();
    drawScore();
    drawEntities();
    drawStateMessage();
}

void PongScene::resetRound(bool moveRight) {
    state_.leftPaddle.y = getCenteredPaddleY();
    state_.rightPaddle.y = getCenteredPaddleY();
    state_.ball.Reset(getCenteredBallX(), getCenteredBallY(), moveRight ? 200.0f : -200.0f, 200.0f);
}

void PongScene::drawCourt() const {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    DrawRectangleLines(PongConfig::courtMargin,
                       PongConfig::courtMargin + 80,
                       screenWidth - PongConfig::courtMargin * 2,
                       screenHeight - PongConfig::courtMargin * 2 - 80,
                       RAYWHITE);

    for (int y = PongConfig::courtMargin + 80; y < screenHeight - PongConfig::courtMargin; y += 35) {
        DrawLine(screenWidth/2, y, screenWidth/2, y + 25, RAYWHITE);
    }
}

void PongScene::drawScore() const {
    const int screenWidth = GetScreenWidth();
    const int fontSize = 40;
    const int leftTextWidth = MeasureText(std::to_string(state_.leftScore).c_str(), fontSize);
    const int rightTextWidth = MeasureText(std::to_string(state_.rightScore).c_str(), fontSize);

    DrawText(
        std::to_string(state_.leftScore).c_str(),
        screenWidth/4 - leftTextWidth/2 + 10,
        120,
        fontSize,
        RAYWHITE
    );
    DrawText(
        std::to_string(state_.rightScore).c_str(),
        3 * screenWidth/4 - rightTextWidth/2 - 10,
        120,
        fontSize,
        RAYWHITE
    );
}

void PongScene::drawEntities() const {
    state_.leftPaddle.Draw();
    state_.rightPaddle.Draw();
    state_.ball.Draw();
}

void PongScene::drawStateMessage() const {
    const char* message = nullptr;
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    if (state_.state == GameState::PAUSED) {
        message = "PAUSED";
    } else if (state_.state == GameState::WIN) {
        message = "YOU WIN";
    } else if (state_.state == GameState::LOSE) {
        message = "YOU LOSE";
    }

    if (message == nullptr) {
        return;
    }

    const int fontSize = 40;
    const int textWidth = MeasureText(message, fontSize);

    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));

    DrawRectangle(
        screenWidth/2 - textWidth/2 - 10,
        screenHeight/2 - fontSize/2 - 10,
        textWidth + 20,
        fontSize + 20,
        BLACK
    );

    DrawRectangleLines(
        screenWidth/2 - textWidth/2 - 10,
        screenHeight/2 - fontSize/2 - 10,
        textWidth + 20,
        fontSize + 20,
        RAYWHITE
    );

    DrawText(
        message,
        screenWidth/2 - textWidth/2,
        screenHeight/2 - fontSize/2,
        fontSize,
        RAYWHITE
    );
}

WindowConfig PongScene::getWindowConfig() const {
    return {
        PongConfig::screenWidth,
        PongConfig::screenHeight,
        "arcade++ (PONG)",
    };
}

}
