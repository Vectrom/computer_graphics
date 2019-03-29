#pragma once
#include "ColorRepresentation.h"
class HSV :	public ColorRepresentation {
public:
	HSV();
	~HSV();
	sf::Color convertColor(const float& radius, const float& alfa);
	void update(const float& newModifier);
};

