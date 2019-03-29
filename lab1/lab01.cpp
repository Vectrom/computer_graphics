#include "Menu.h"
#include "ShapesVector.h"
#include "ControlPanel.h"

int main(void) {
	sf::RenderWindow window(sf::VideoMode(800, 650), "Podstawy Grafiki Komputerowej - Lab 1 - Damian Plociennik",sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	Menu menu;
	ControlPanel cp;
	ShapesVector shapes(&window, &menu, &cp);
	sf::Texture texture;
 
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		window.clear(sf::Color::Black);
   
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					cp.isClickedOnColorPicker = cp.isClickedOnWorkspace = false;
					cp.isMouseReleased = false;
					cp.isKeyPressed = true;
					menu.setLastPressedKey(event.key.code);
					cp.pressedKey = event.key.code;
					if (event.key.code == sf::Keyboard::Key::Escape)
						window.close();
					break;
				case sf::Event::MouseButtonPressed:
					cp.clickPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
					cp.isClickedOnColorPicker = menu.isInsideColorPicker(cp.clickPosition);
					cp.isClickedOnWorkspace = menu.isInsideWorkspace(cp.clickPosition);
					break;
				case sf::Event::MouseButtonReleased:
					cp.isMouseReleased = true;
					break;
				case sf::Event::MouseMoved:
					if (menu.isInsideWorkspace(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
						cp.mousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
					break;
			}

		} 
			shapes.drawShapes();

			if (cp.isKeyPressed) {
				if(cp.isClickedOnWorkspace) {
					switch (cp.pressedKey) {
					case sf::Keyboard::Key::L:
						shapes.drawLine();
						break;
					case sf::Keyboard::Key::R:
						shapes.drawRectangle();
						break;
					case sf::Keyboard::Key::A:
						shapes.drawRectangle(true);
						break;
					case sf::Keyboard::Key::C:
						shapes.drawCircle();
						break;
					}
				}
				
				if (cp.isClickedOnColorPicker) {
						switch (cp.pressedKey) {
						case sf::Keyboard::Key::F:
							menu.setForegroundColor(menu.pickColor(cp.clickPosition));
							break;
						case sf::Keyboard::Key::B:
							menu.setBackgroundColor(menu.pickColor(cp.clickPosition));
							break;
						}
						cp.isClickedOnColorPicker = false;
				}

				if (cp.isMouseReleased)
					cp.isClickedOnWorkspace = cp.isMouseReleased = false;

				switch (cp.pressedKey) {
					case sf::Keyboard::Key::W:
						shapes.saveToFile();
						break;
					case sf::Keyboard::Key::O:
						shapes.loadFromFile(texture);
						break;
					case sf::Keyboard::Key::Z:
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
							shapes.undo();
							cp.pressedKey = sf::Keyboard::F15;
						}
						break;
					case sf::Keyboard::Key::Y:
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
							shapes.redo();
							cp.pressedKey = sf::Keyboard::F15;
						}
						break;
				}
			}

		window.draw(menu);
		window.display();
	}
	return 0;
}