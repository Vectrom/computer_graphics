#define _USE_MATH_DEFINES 
#include <cmath>
#include "CMY.h"

CMY::CMY() {
	init();

	_sprite->setPosition(20, 340);

	_title.setString("CMY");
	_title.setPosition(20, 340);
	std::string buffer;

	_text.setString("Y = " + to_string_with_precision(_modifier * 100, 0) + "%");
	_text.setPosition(200, 570);
}

CMY::~CMY() {
}

sf::Color CMY::convertColor(const float& radius, const float& alfa) {
	float d = radius / _radius;
	return sf::Color((1 - (d)) * 255, (1 - (alfa / (2 * M_PI))) * 255, (1 - _modifier) * 255);
}

void CMY::update(const float& newModifier) {
	if (fabs(_modifier - newModifier) > 0.01) {
		_modifier = newModifier;
		_text.setString("Y = " + to_string_with_precision(_modifier * 100, 0) + "%");
		createColors();
		_texture->update(_colors);
	}
}