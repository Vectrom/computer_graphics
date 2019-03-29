#define _USE_MATH_DEFINES 
#include <cmath>
#include "RGB.h"

RGB::RGB() {
	init();

	_sprite->setPosition(320, 340);

	_title.setString("RGB");
	_title.setPosition(320, 340);
	std::string buffer;

	_text.setString("B = " + to_string_with_precision(_modifier * 255, 0));
	_text.setPosition(500, 570);
}


RGB::~RGB() {
}

sf::Color RGB::convertColor(const float& radius, const float& alfa) {
	float d = radius / _radius;
	return sf::Color(d * 255, alfa / (2 * M_PI) * 255, _modifier * 255);
}

void RGB::update(const float& newModifier) {
	if (fabs(_modifier - newModifier) > 0.01) {
		_modifier = newModifier;
		_text.setString("B = " + to_string_with_precision(_modifier * 255, 0));
		createColors();
		_texture->update(_colors);
	}
}