#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable {
public:
	Menu();

	void outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setLastPressedKey(sf::Keyboard::Key key = sf::Keyboard::Key::F15);

	bool isInsideColorPicker(sf::Vector2f mousePosition) const;

	bool isInsideWorkspace(sf::Vector2f mousePosition) const;

	sf::Color pickColor(sf::Vector2f mousePosition);

	void setForegroundColor(sf::Color color);

	void setBackgroundColor(sf::Color color);

	sf::Color getForegroundColor() const;

	sf::Color getBackgroundColor() const;

private:
	sf::Font font;
	sf::Text *text;
	sf::RectangleShape *rectangle;
	sf::RectangleShape *_drawingColorRectangle;
	sf::RectangleShape *_fillingColorRectangle;
	sf::Color _foregroundColor;
	sf::Color _backgroundColor;
	wchar_t * _lastPressedKey = L"";


	sf::Texture *colors_texture;
	sf::Sprite *colors_sprite;
	sf::Uint8 *colors_pixels;
	const unsigned int colors_size_x = 765;
	const unsigned int colors_size_y = 60;
	inline void draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
		colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
		colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
		colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
		colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
	}
};