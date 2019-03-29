#define _USE_MATH_DEFINES 
#include <cmath>
#include "ShapesVector.h"

ShapesVector::ShapesVector(sf::RenderWindow * window, Menu * menu, ControlPanel * cp) : _cp(cp), _menu(menu), _window(window) {}

ShapesVector::~ShapesVector() {
	for (auto &p : _shapes)
		delete p;
}

void ShapesVector::addShape(sf::Drawable * shape) {
	_shapes.push_back(shape);
}

void ShapesVector::drawLine() {
	sf::VertexArray * line = new sf::VertexArray(sf::Lines, 2);
	(*line)[0] = sf::Vertex(_cp->clickPosition, _menu->getForegroundColor());
	(*line)[1] = sf::Vertex(_cp->mousePosition, _menu->getBackgroundColor());

	_window->draw(*line);

	if (_cp->isMouseReleased)
		addShape(line);
	else
		delete line;
}

void ShapesVector::drawRectangle(bool filling) {
	sf::RectangleShape * rectangle = new sf::RectangleShape(_cp->mousePosition - _cp->clickPosition);
	rectangle->setPosition(_cp->clickPosition);
	rectangle->setOutlineColor(_menu->getForegroundColor());
	rectangle->setOutlineThickness(1);
	if (filling)
		rectangle->setFillColor(_menu->getBackgroundColor());
	else
		rectangle->setFillColor(sf::Color::Transparent);

	_window->draw(*rectangle);

	if (_cp->isMouseReleased)
		addShape(rectangle);
	else
		delete rectangle;
}

void ShapesVector::drawCircle() {
	float radius = sqrt(pow(_cp->clickPosition.x - _cp->mousePosition.x, 2) + pow(_cp->clickPosition.y - _cp->mousePosition.y, 2)) / 2;
	float angle = atan2(_cp->mousePosition.y - _cp->clickPosition.y, _cp->mousePosition.x - _cp->clickPosition.x) * (180 / M_PI) - 45;
	sf::CircleShape * circle = new sf::CircleShape(radius);
	circle->setPosition(_cp->clickPosition);
	circle->rotate(angle);
	circle->move(sf::Vector2f((radius - radius * sqrt(2)) * cos((angle + 45) * M_PI / 180), (radius - radius * sqrt(2)) * sin((angle + 45) * M_PI / 180)));
	circle->setOutlineColor(_menu->getForegroundColor());
	circle->setOutlineThickness(1);
	circle->setFillColor(sf::Color::Transparent);
	
	_window->draw(*circle);

	if (_cp->isMouseReleased)
		addShape(circle);
	else
		delete circle;
}

void ShapesVector::drawShapes() {
	for (auto &p : _shapes)
		_window->draw(*p);
}


void ShapesVector::saveToFile() {
	sf::Texture newTexture;
	newTexture.create(_window->getSize().x, _window->getSize().y);
	newTexture.update(*_window);
	sf::Image image;
	image.create(796, 536, sf::Color::Black);
	image.copy(newTexture.copyToImage(), 0, 0, sf::IntRect(2, 62, 796, 536));
	image.saveToFile("result.jpg");
	_cp->isKeyPressed = false;
	_menu->setLastPressedKey();
}

void ShapesVector::loadFromFile(sf::Texture & texture) {
	sf::Image image;
	if (image.loadFromFile("result.jpg")) {
		texture.loadFromImage(image);
		sf::Sprite newWorkspace(texture);
		newWorkspace.setPosition(sf::Vector2f(2, 62));
		addShape(new sf::Sprite(newWorkspace));
	}
	_cp->isKeyPressed = false;
	_menu->setLastPressedKey();
}

void ShapesVector::undo() {
	if (!_shapes.empty()) {
		_deletedShapes.push_back(_shapes.back());
		_shapes.pop_back();
	}
}

void ShapesVector::redo() {
	if (!_deletedShapes.empty()) {
		_shapes.push_back(_deletedShapes.back());
		_deletedShapes.pop_back();
	}
}
