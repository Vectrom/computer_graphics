#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>

class ColorRepresentation : public sf::Drawable, public sf::Transformable {
public:
	ColorRepresentation() : _radius(120), _texture(new sf::Texture), _sprite(new sf::Sprite), _colors(new sf::Uint8[16*_radius*_radius]) {}
	~ColorRepresentation();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void init();
	void createColors();
	virtual sf::Color convertColor(const float& radius, const float& alfa) = 0;
protected:
	float _modifier;
	const int _radius = 100;
	sf::Texture * _texture;
	sf::Sprite * _sprite;
	sf::Font _font;
	sf::Text _title;
	sf::Text _text;
	sf::Uint8 * _colors;
};

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}
