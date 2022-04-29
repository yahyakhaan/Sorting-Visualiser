#include<iostream>
#include<SFML/Graphics.hpp>
#include "TextBox.h"

int main()
{
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(900, 900), "SFML Project", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	sf::Font arial;
	arial.loadFromFile("Arial.ttf");
	TextBox textBox1(15, sf::Color::White, false);
	textBox1.setFont(arial);
	textBox1.setPosition({ 100,100 });

	while (window.isOpen())
	{
		sf::Event Event;

		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				window.close();
			}
		}
		window.clear();
		textBox1.drawTo(window);
		window.display();
	}
}