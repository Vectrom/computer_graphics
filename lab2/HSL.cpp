#define _USE_MATH_DEFINES 
#include <cmath>
#include "HSL.h"

HSL::HSL() : ColorRepresentation() {
	init();

	_sprite->setPosition(20, 40);

	_title.setString("HSL");
	_title.setPosition(20, 40);

	_text.setString("L = " + to_string_with_precision(_modifier, 3));
	_text.setPosition(200, 270);
}


HSL::~HSL() {
}

sf::Color HSL::convertColor(const float& radius, const float& alfa) {
	float d = radius / _radius;
	float a = alfa * 180.0 / M_PI;

	float c = (1 - fabs(2 * _modifier - 1)) * d;
	float x = c * (1 - fabs(fmod(a / 60, 2) - 1));
	float m = _modifier - c / 2;
	float r, g, b;

	if (a < 60.) { 
		r = c;
		g = x;
		b = 0; 
	}
	else if (a < 120.) {
		r = x;
		g = c;
		b = 0;
	}
	else if (a < 180.) {
		r = 0;
		g = c;
		b = x;
	}
	else if (a < 240.) {
		r = 0;
		g = x;
		b = c;
	}
	else if (a < 300.) {
		r = x;
		g = 0;
		b = c;
	}
	else {
		r = c;
		g = 0;
		b = x;
	}

	return sf::Color((r + m) * 255, (g + m) * 255, (b + m) * 255);
}

void HSL::update(const float& newModifier) {
	if (fabs(_modifier - newModifier) > 0.01) {
		_modifier = newModifier;
		_text.setString("L = " + to_string_with_precision(_modifier, 3));
		createColors();
		_texture->update(_colors);
	}
}