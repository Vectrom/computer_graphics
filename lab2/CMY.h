#pragma once
#include "ColorRepresentation.h"

class CMY :	public ColorRepresentation {
public:
	CMY();
	~CMY();
	sf::Color convertColor(const float& radius, const float& alfa);
	void update(const float& newModifier);
};

