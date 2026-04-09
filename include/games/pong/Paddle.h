#ifndef ARCADE_GAMES_PONG_PADDLE_H
#define ARCADE_GAMES_PONG_PADDLE_H

namespace arcade {

class Paddle {
	public:
		float y = 0.0f;
		float speed = 0.0f;
		bool left = true;

		Paddle() = default;
		Paddle(float y, float speed, bool left);

		void MoveUp(float dt);
		void MoveDown(float dt);
		void Clamp(float minY, float maxY);
		void Draw() const;
};

}

#endif
