#include "Slider.h"

Slider::Slider(const int& x, const int& y, const float& startingModifier) : _texture(new sf::Texture()), _sprite(new sf::Sprite()), _x(x), _y(y), _line(sf::Lines, 2), _modifier(startingModifier) {
	sf::Uint8 * colors = new sf::Uint8[4*_x*_y];
	#pragma omp parallel for
	for (int i = 0; i < _x; i++) {
		for (int j = 0; j <_y ; j++) {
			if (i == 0 || y == 0 || i == _x - 1 || j == _y - 1) {
				colors[4 * (j * _x + i) + 0] = 255;
				colors[4 * (j * _x + i) + 1] = 255;
				colors[4 * (j * _x + i) + 2] = 255;
				colors[4 * (j * _x + i) + 3] = 255;
			}
			else {
				colors[4 * (j * _x + i) + 0] = j * 255 / _y;
				colors[4 * (j * _x + i) + 1] = j * 255 / _y;
				colors[4 * (j * _x + i) + 2] = j * 255 / _y;
				colors[4 * (j * _x + i) + 3] = 255;
			}
		}
	}
	_texture->create(_x, _y);
	_texture->update(colors);
	_line[0] = sf::Vertex(sf::Vector2f(660, 220), sf::Color::Black);
	_line[1] = sf::Vertex(sf::Vector2f(720, 220), sf::Color::Black);
	_sprite->setTexture(*_texture);
	_sprite->setPosition(670, 70);
	delete colors;
}


Slider::~Slider() {
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(_line, states);
	target.draw(*_sprite, states);

}

void Slider::updatePosition(const sf::Vector2f& position) {
	sf::Vector2f sliderPosition = _sprite->getPosition();
	if (sliderPosition.x <= position.x && sliderPosition.x + _x >= position.x && sliderPosition.y <= position.y && sliderPosition.y + _y >= position.y) {
		_line[0].position.y = _line[1].position.y = position.y;
		_modifier = (position.y - sliderPosition.y) / static_cast<double>(_y);
	}	
}

float Slider::getModifier() const {
	return _modifier;
}