#define _USE_MATH_DEFINES 
#include <cmath>
#include "HSV.h"


HSV::HSV() {
	init();

	_sprite->setPosition(320, 40);

	_title.setString("HSV");
	_title.setPosition(320, 40);
	std::string buffer;

	_text.setString("V = " + to_string_with_precision(_modifier, 3));
	_text.setPosition(500, 270);
}


HSV::~HSV() {
}

sf::Color HSV::convertColor(const float& radius, const float& alfa) {
	float d = radius / _radius;
	float a = alfa * 180.0 / M_PI;

	float c = _modifier * d;
	float x = c * (1 - fabs(fmod(a / 60, 2) - 1));
	float m = _modifier - c;
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

void HSV::update(const float& newModifier) {
	if (fabs(_modifier - newModifier) > 0.01) {
		_modifier = newModifier;
		_text.setString("V = " + to_string_with_precision(_modifier, 3));
		createColors();
		_texture->update(_colors);
	}
}