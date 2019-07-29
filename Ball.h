
#include "Rectangle.h"
#include "Platform.h"

class Ball : public Rectangle
{
private:

	const int ball_size = 15;

	float vel_x, vel_y;

	int bounds[4];

public:
	Ball(float p_x, float p_y, float v_x, float v_y) : Rectangle()
	{
		pos_x = p_x;
		pos_y = p_y;

		vel_x = v_x;
		vel_y = v_y;

		size_x = ball_size;
		size_y = ball_size;
	}

	const float max_vel_x = 100.0f;
	const float max_vel_y = 100.0f;
	void move(float dt)
	{
		pos_x +=vel_x * dt;
		pos_y += vel_y * dt;

		bounds[0] = pos_x;
		bounds[1] = pos_x + size_x;
		bounds[2] = pos_y;
		bounds[3] = pos_y + size_y;
	}

	void check_collisions(Block objects[40], int count, Platform platform, int max_x, int max_y)
	{
		float top, right, bot, left;
		top = pos_y;
		bot = pos_y + size_y;
		left = pos_x;
		right = pos_x + size_x;

		if (top <= 0)
			vel_y = -vel_y;
		if (bot >= max_y - 1) // todo if ball falls to lower bound -> lose
			vel_y = -vel_y;

		if (left <= 0)
			vel_x = -vel_x;
		if (right >= max_x - 1)
			vel_x = -vel_x;

		float c_x, c_y;
		c_x = pos_x + size_x / 2.0f;
		c_y = pos_y + size_y / 2.0f;

		for (int i = 0; i < count; i++)
		{
			Block b = objects[i];

			if (b.broken) 
				continue;

			if (c_x > b.pos_x && c_x < b.pos_x + b.size_x
				&& ((bot <= b.pos_y && bot >= b.pos_y + b.size_y)
					||
					(top >= b.pos_y && top <= b.pos_y + b.size_y)))
			{
				vel_y = -vel_y;

				objects[i].broken = true;
			}

			if (c_y > b.pos_y && c_y < b.pos_y + b.size_y
				&& ((right <= b.pos_x && right >= b.pos_x + b.size_x)
					||
					(left >= b.pos_x && left <= b.pos_x + b.size_x)))
			{
				vel_x = -vel_x;

				objects[i].broken = true;
			}
		}

		if (bot > platform.pos_y  &&
			c_x > platform.pos_x && c_x < platform.pos_x + platform.size_x)
		{
			vel_y = -vel_y;
		}
	}


};
