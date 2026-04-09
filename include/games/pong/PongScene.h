#ifndef ARCADE_GAMES_PONG_PONGSCENE_H
#define ARCADE_GAMES_PONG_PONGSCENE_H

#include "app/Scene.h"
#include "games/pong/PongState.h"

namespace arcade {

class PongScene : public Scene {
	public:
		PongScene();

		void onEnter() override;
		void onExit() override;
		void update(float dt) override;
		void render() override;
		WindowConfig getWindowConfig() const override;

	private:
		void resetRound(bool moveRight);
		void drawCourt() const;
		void drawScore() const;
		void drawEntities() const;
		void drawStateMessage() const;

		PongState state_;
};

}

#endif
