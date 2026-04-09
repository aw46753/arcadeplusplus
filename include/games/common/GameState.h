#ifndef ARCADE_GAMES_COMMON_GAMESTATE_H
#define ARCADE_GAMES_COMMON_GAMESTATE_H

namespace arcade {

enum class GameState {
    RUNNING,
    PAUSED,
    WIN,
    LOSE,
    EXIT
};

}

#endif
