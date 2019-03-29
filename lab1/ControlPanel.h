#pragma once
#include <SFML/Graphics.hpp>

struct ControlPanel {
	bool isClickedOnWorkspace = false;
	bool isClickedOnColorPicker = false;
	bool isMouseReleased = false;
	bool isKeyPressed = false;
	sf::Vector2f clickPosition;
	sf::Vector2f mousePosition;
	sf::Keyboard::Key pressedKey;
};