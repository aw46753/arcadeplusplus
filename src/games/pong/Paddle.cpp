#include "games/pong/Paddle.h"
#include "games/pong/PongConfig.h"

#include "raylib.h"

namespace arcade {

Paddle::Paddle(float y, float speed, bool left)
: y(y), speed(speed), left(left) {}

void Paddle::MoveUp(float dt) {
    y -= speed * dt;
}

void Paddle::MoveDown(float dt) {
    y += speed * dt;
}

void Paddle::Clamp(float minY, float maxY) {
    if (y < minY) {
        y = minY;
    } else if (y > maxY) {
        y = maxY;
    }
}

void Paddle::Draw() const {
    DrawRectangle(left ? 30 : GetScreenWidth() - 40, static_cast<int>(y), 10, PongConfig::paddleHeight, WHITE);
}

}
