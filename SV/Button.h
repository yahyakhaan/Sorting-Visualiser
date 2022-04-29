#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::RectangleShape button;
	sf::Text text;

	int btnWidth;
	int btnHeight;

	sf::Color bgColor = sf::Color::Red;
	sf::Color textColor = sf::Color::White;

	sf::CircleShape cir1;
	sf::CircleShape cir2;
public:
	Button()
	{
		btnHeight = 250;
		btnWidth = 60;
	}

	void set(std::string btnText, sf::Vector2f buttonSize, sf::Vector2f buttonPos, sf::Font& fonts,bool a )
	{
		btnWidth = buttonSize.x;
		btnHeight = buttonSize.y;

		button.setSize(buttonSize);
		button.setFillColor(bgColor);

		cir1.setFillColor(bgColor);
		cir1.setRadius(btnHeight / 2);
		cir1.setPosition(buttonPos.x - 28, buttonPos.y);

		cir2.setFillColor(bgColor);
		cir2.setRadius(btnHeight / 2);
		cir2.setPosition((buttonPos.x + btnWidth) - cir2.getRadius(), buttonPos.y);

		text.setString(btnText);
		text.setCharacterSize(30);
		text.setFillColor(textColor);
		text.setStyle(sf::Text::Bold);

		this->setFont(fonts);
		this->setPosition(buttonPos);

	}
	Button(std::string btnText, sf::Vector2f buttonSize, sf::Vector2f buttonPos, sf::Font& font, bool circle)
	{
		set(btnText, buttonSize, buttonPos, font, circle);
	}

	void changeTextColor(sf::Color color)
	{
		text.setFillColor(color);
	}

	void setBGColor(sf::Color color)
	{
		button.setFillColor(color);
		cir1.setFillColor(color);
		cir2.setFillColor(color);
	}

	void setSize(sf::Vector2f buttonSize)
	{
		btnHeight = buttonSize.y;
		btnWidth = buttonSize.x;
		button.setSize(buttonSize);
	}

	void setFont(sf::Font& fonts)
	{
		text.setFont(fonts);
	}

	void setBackColor(sf::Color color)
	{
		button.setFillColor(color);
	}

	void setTextColor(sf::Color color)
	{
		text.setFillColor(color);
	}

	void setText(sf::Vector2f point)
	{
		float xPos = point.x;
		float yPos = point.y;
		text.setPosition(xPos, yPos);
	}

	void setPosition(sf::Vector2f point)
	{
		button.setPosition(point);
		// Center text on button:
		float xPos = (point.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
		float yPos = (point.y + btnHeight / 2.2) - (text.getLocalBounds().height / 2) - 5;
		text.setPosition(xPos, yPos);
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(button);
		window.draw(text);
		window.draw(cir1);
		window.draw(cir2);
	}

	bool isMouseOver(sf::RenderWindow& window)
	{
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		int btnPosX = button.getPosition().x;
		int btnPosY = button.getPosition().y;

		int btnxPosWidth = button.getPosition().x + btnWidth;
		int btnyPosHeight = button.getPosition().y + btnHeight;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}
};