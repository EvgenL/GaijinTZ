


#include "Rectangle.h"

class Block : public Rectangle {
	static const int default_w = 50;
	static const int default_h = 15;

public:
	Block() : Rectangle(0,0, default_w, default_h, 0) {
		color = rand() % 0xFFFFFFF00;
		broken = false;
	}

	bool broken;

};
