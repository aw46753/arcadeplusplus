#ifndef ARCADE_GAMES_PONG_PONGSTATE_H
#define ARCADE_GAMES_PONG_PONGSTATE_H

#include "games/pong/Ball.h"
#include "games/pong/Paddle.h"
#include "games/common/GameState.h"

namespace arcade {

struct PongState {
    GameState state = GameState::RUNNING;

    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;

    int leftScore = 0;
    int rightScore = 0;
};

}

#endif
