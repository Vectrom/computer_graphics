#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "HSL.h"
#include "CMY.h"
#include "HSV.h"
#include "RGB.h"
#include "Slider.h"

extern unsigned char font_data[423992];
extern unsigned int font_data_size;
int main() {
 sf::RenderWindow window(sf::VideoMode(750, 650), "Podstawy Grafiki Komputerowej - Lab 2 - Damian Plociennik", sf::Style::Titlebar | sf::Style::Close);
 sf::Clock clock;
 sf::Time time = sf::Time::Zero;
 unsigned int FPS = 0 , frame_counter = 0;
 sf::Text FPSText;
 HSL hsl;
 CMY cmy;
 RGB rgb;
 HSV hsv;
 Slider slider(40, 300);
 sf::Font font;
 font.loadFromMemory(font_data, font_data_size);
 FPSText.setFont(font);
 FPSText.setCharacterSize(13);
 FPSText.setStyle(sf::Text::Regular);
 FPSText.setFillColor(sf::Color::Black);
 FPSText.setPosition(670, 440);

 clock.restart().asMilliseconds();
  while (window.isOpen())  {
  sf::Event event;
  window.clear(sf::Color::White);

  while (window.pollEvent(event))  {
	  switch (event.type) {
	  case sf::Event::Closed:
		  window.close();
		  break;
	  case sf::Event::MouseMoved:
		  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			  slider.updatePosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
		  break;
	  }

  }
  float modifier = slider.getModifier();
  hsl.update(modifier);
  window.draw(hsl);
  cmy.update(modifier);
  window.draw(cmy);
  rgb.update(modifier);
  window.draw(hsv);
  hsv.update(modifier);
  window.draw(rgb);

  window.draw(slider);


  FPSText.setString("FPS: " + to_string_with_precision(FPS, 0));
  window.draw(FPSText);

  if (clock.getElapsedTime().asSeconds() >= 1.0f) {
	  FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
   clock.restart();
   frame_counter = 0;
  }
  frame_counter++;
  
  window.display();
 }
}