#include "games/pong/Ball.h"

#include "raylib.h"

namespace arcade {
Ball::Ball(float x, float y, float vx, float vy)
    : x(x), y(y), vx(vx), vy(vy) {}

void Ball::Update(float dt) {
    x += vx * dt;
    y += vy * dt;
}

void Ball::Draw() const {
    DrawCircle(static_cast<int>(x), static_cast<int>(y), 8, WHITE);
}

void Ball::Reset(float x, float y, float vx, float vy) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
}

void Ball::WallBounce(int topY, int bottomY) {
    if (y <= topY || y >= bottomY) {
        vy = -vy;
    }
}

void Ball::PaddleBounce(int paddleY, int paddleHeight) {
    if (y >= paddleY && y <= paddleY + paddleHeight) {
        vx = -vx;
    }
}

}
