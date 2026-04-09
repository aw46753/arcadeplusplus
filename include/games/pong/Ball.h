#ifndef ARCADE_GAMES_PONG_BALL_H
#define ARCADE_GAMES_PONG_BALL_H

namespace arcade {

class Ball {
	public:
		float x;
		float y;
		float vx;
		float vy;

		Ball() = default;
		Ball(float x, float y, float vx, float vy);

		void Update(float dt);
		void Draw() const;
		void Reset(float x, float y, float vx, float vy);

		void WallBounce(int topY, int bottomY);
		void PaddleBounce(int paddleY, int paddleHeight);
};

}

#endif
