#pragma once
#include <SFML/Graphics.hpp>
#include "Slider.h"

class Slider : public sf::Drawable, public sf::Transformable {
public:
	Slider(const int& x, const int& y, const float& startingModifier = 0.5);
	~Slider();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void updatePosition(const sf::Vector2f& position);
	float getModifier() const;

private:
	sf::Texture * _texture;
	sf::Sprite * _sprite;
	int _x;
	int _y;
	sf::VertexArray _line;
	float _modifier;
};

