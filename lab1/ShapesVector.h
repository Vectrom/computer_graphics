#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ControlPanel.h"
#include "Menu.h"

class ShapesVector {
public:
	ShapesVector(sf::RenderWindow * window, Menu * menu, ControlPanel * cp);

	~ShapesVector();

	void addShape(sf::Drawable * shape);

	void drawLine();

	void drawRectangle(bool filling = false);

	void drawCircle();

	void drawShapes();

	void saveToFile();

	void loadFromFile(sf::Texture& texture);

	void undo();

	void redo();

private:
	ControlPanel * _cp;
	Menu * _menu;
	sf::RenderWindow * _window;
	std::vector <sf::Drawable *> _shapes;
	std::vector <sf::Drawable *> _deletedShapes;
};