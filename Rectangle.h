
#pragma once
class Rectangle {

public:
	Rectangle(float p_x, float p_y, unsigned s_x, unsigned s_y, unsigned col)
	{
		pos_x = p_x;
		pos_y = p_y;

		size_x = s_x;
		size_y = s_y;

		color = col;
	}
	Rectangle()
	{
		pos_x = 0;
		pos_y = 0;

		size_x = 50;
		size_y = 50;

		color = 0xFFFFFFFF;
	}

	unsigned color;

	unsigned size_x;
	unsigned size_y;

	float pos_x;
	float pos_y;

};
