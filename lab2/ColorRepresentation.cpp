#define _USE_MATH_DEFINES 
#include <cmath>
#include "ColorRepresentation.h"
#include "font.h"

ColorRepresentation::~ColorRepresentation() {
	if (_colors)
		delete[] _colors;
}

void ColorRepresentation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(_title, states);
	target.draw(_text, states);
	target.draw(*_sprite, states);

}

void ColorRepresentation::init() {
	_font.loadFromMemory(font_data, font_data_size);

	_text.setFont(_font);
	_text.setCharacterSize(13);
	_text.setStyle(sf::Text::Regular);
	_text.setFillColor(sf::Color::Black);
	_text.setOutlineColor(sf::Color::Black);
	_text.setPosition(0, 0);

	_title.setFont(_font);
	_title.setCharacterSize(13);
	_title.setStyle(sf::Text::Regular);
	_title.setFillColor(sf::Color::Black);
	_title.setOutlineColor(sf::Color::Black);
	_title.setPosition(0, 0);

	_texture->create(2 * _radius, 2 * _radius);
	createColors();
	_sprite->setTexture(*_texture);
}

void ColorRepresentation::createColors() {
#pragma omp parallel for
	for (int i = 0; i < 2 * _radius; i++) {
		for (int j = 0; j < 2 * _radius; j++) {

			double i2 = i - _radius;
			double j2 = _radius - j;

			float angle = atan2(j2, i2);

			if (angle < 0)
				angle += 2 * M_PI;

			float dist = sqrt(j2*j2 + i2*i2);

			if (dist <= _radius) {
				sf::Color newColor = convertColor(dist, angle);
				_colors[4 * (j * 2 * _radius + i) + 0] = newColor.r;
				_colors[4 * (j * 2 * _radius + i) + 1] = newColor.g;
				_colors[4 * (j * 2 * _radius + i) + 2] = newColor.b;
				_colors[4 * (j * 2 * _radius + i) + 3] = 255;
			}
			else {
				for(int k = 0; k < 4; k++)
					_colors[4 * (j * 2 * _radius + i) + k] = 0;
			}
		}
	}
	_texture->update(_colors);
}