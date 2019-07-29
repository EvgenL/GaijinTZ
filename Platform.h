
#include "Rectangle.h"

class Platform : public Rectangle
{
public:

	Platform()
	{
		size_x = 70;
		size_y = 20;

		color = 0xFFFFFFF00;
	}

	/*void check_collisions(Bonus *bonuses, Ball *balls)
	{
		
	}*/

	void tick_bonuses(float dt)
	{
		
	}

	void move(int input)
	{
		pos_x += input / 10.0f;
	}
};
