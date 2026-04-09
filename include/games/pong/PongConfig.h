#ifndef ARCADE_GAMES_PONG_PONGCONFIG_H
#define ARCADE_GAMES_PONG_PONGCONFIG_H

namespace arcade {

struct PongConfig {
    static constexpr int screenWidth = 800;
    static constexpr int screenHeight = 600;

    static constexpr int courtMargin = 20;

    static constexpr int paddleHeight = 80;
    static constexpr float leftPaddleSpeed = 200.0f;
    static constexpr float rightPaddleSpeed = 150.0f;
};

}

#endif
