#pragma once
#include "ColorRepresentation.h"
class RGB :	public ColorRepresentation {
public:
	RGB();
	~RGB();
	sf::Color convertColor(const float& radius, const float& alfa);
	void update(const float& newModifier);
};

