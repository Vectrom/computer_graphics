#include "Menu.h"
#include "font.h"

Menu::Menu() {
	font.loadFromMemory(font_data, font_data_size);
	text = new sf::Text;
	text->setFont(font);
	text->setCharacterSize(12);
	text->setFillColor(sf::Color::White);
	_foregroundColor = sf::Color::Black;
	_backgroundColor = sf::Color::Transparent;

	rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
	rectangle->setFillColor(sf::Color::Transparent);
	rectangle->setOutlineColor(sf::Color::White);
	rectangle->setOutlineThickness(1.0f);
	rectangle->setPosition(2, 62);

	_drawingColorRectangle = new sf::RectangleShape(sf::Vector2f(800 - colors_size_x - 2, colors_size_y / 2 - 2));
	_drawingColorRectangle->setFillColor(_foregroundColor);
	_drawingColorRectangle->setPosition(colors_size_x + 2, 2);
	_fillingColorRectangle = new sf::RectangleShape(sf::Vector2f(800 - colors_size_x - 2, colors_size_y / 2 - 2));
	_fillingColorRectangle->setFillColor(_backgroundColor);
	_fillingColorRectangle->setPosition(colors_size_x + 2, colors_size_y / 2 + 2);

	unsigned int x, y;
	colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
	for (x = 0; x < 255; x++)
		for (y = 0; y < 30; y++) {
			draw_to_color_pixels(x, y, x, 255, 0);
			draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
			draw_to_color_pixels(x + 510, y, 255, 0, x);
			draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
			draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
			draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
		}

	colors_texture = new sf::Texture();
	colors_texture->create(colors_size_x, colors_size_y);
	colors_texture->update(colors_pixels);

	colors_sprite = new sf::Sprite();
	colors_sprite->setTexture(*colors_texture);
	colors_sprite->setPosition(1, 1);
}

void Menu::outtextxy(sf::RenderTarget& target, float x, float y, const wchar_t *str) const {
	text->setPosition(x, y);
	text->setString(str);
	target.draw(*text);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	outtextxy(target, 5, 600, L"f - wybór koloru rysowania");
	outtextxy(target, 5, 615, L"b - wybór koloru wype³niania");
	outtextxy(target, 5, 630, L"l - rysowanie linii");

	outtextxy(target, 200, 600, L"r - rysowanie prostok¹ta");
	outtextxy(target, 200, 615, L"a - rysowanie wype³nionego prostok¹ta");
	outtextxy(target, 200, 630, L"c - rysowanie okrêgu");

	outtextxy(target, 470, 600, L"w - zapis do pliku");
	outtextxy(target, 470, 615, L"o - odczyt z pliku");
	outtextxy(target, 470, 630, L"esc - wyjœcie");

	outtextxy(target, 650, 615, L"Aktualne:");
	outtextxy(target, 705, 615, _lastPressedKey);

	target.draw(*rectangle);
	target.draw(*colors_sprite);

	_drawingColorRectangle->setFillColor(_foregroundColor);
	_fillingColorRectangle->setFillColor(_backgroundColor);

	target.draw(*_drawingColorRectangle);
	target.draw(*_fillingColorRectangle);
}

void Menu::setLastPressedKey(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Key::F)
		_lastPressedKey = L"f";
	else if (key == sf::Keyboard::Key::B)
		_lastPressedKey = L"b";
	else if (key == sf::Keyboard::Key::L)
		_lastPressedKey = L"l";
	else if (key == sf::Keyboard::Key::R)
		_lastPressedKey = L"r";
	else if (key == sf::Keyboard::Key::A)
		_lastPressedKey = L"a";
	else if (key == sf::Keyboard::Key::C)
		_lastPressedKey = L"c";
	else if (key == sf::Keyboard::Key::W)
		_lastPressedKey = L"w";
	else if (key == sf::Keyboard::Key::O)
		_lastPressedKey = L"o";
	else
		_lastPressedKey = L"";
	{

	}
}

bool Menu::isInsideColorPicker(sf::Vector2f mousePosition) const {
	if (mousePosition.x > colors_size_x || mousePosition.y > colors_size_y) return false;
	return true;
}

bool Menu::isInsideWorkspace(sf::Vector2f mousePosition) const {
	if (mousePosition.x < 2 || mousePosition.x > 798 || mousePosition.y < 62 || mousePosition.y > 598) return false;
	return true;
}

sf::Color Menu::pickColor(sf::Vector2f mousePosition) {
	return sf::Color(colors_pixels[static_cast<int>(4 * (mousePosition.y * colors_size_x + mousePosition.x) + 0)],
		colors_pixels[static_cast<int>(4 * (mousePosition.y * colors_size_x + mousePosition.x) + 1)],
		colors_pixels[static_cast<int>(4 * (mousePosition.y * colors_size_x + mousePosition.x) + 2)]);
}

void Menu::setForegroundColor(sf::Color color) {
	_foregroundColor = color;
}

void Menu::setBackgroundColor(sf::Color color) {
	_backgroundColor = color;
}

sf::Color Menu::getForegroundColor() const {
	return _foregroundColor;
}

sf::Color Menu::getBackgroundColor() const {
	return _backgroundColor;
}