#pragma once
#include "ColorRepresentation.h"

class HSL :	public ColorRepresentation {
public:
	HSL();
	~HSL();
	sf::Color convertColor(const float& radius, const float& alfa);
	void update(const float& newModifier);
};

