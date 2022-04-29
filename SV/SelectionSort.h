#pragma once
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>bubbleWindow
#include "Button.h"

class SelectionSort
{
private:
	int* arr;
	int length;
	int unit;
protected:
	sf::RenderWindow* selectionWindow;
	sf::Time time1;
	sf::Time time2;
	Button exit;
	Button start;
	Button reset;
	sf::Font font;

public:
	SelectionSort()
	{
		selectionWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Selection Sort", sf::Style::Titlebar);
		selectionWindow->clear(sf::Color::Black);

		font.loadFromFile("Extra/Arial.ttf");
		time1 = sf::milliseconds(0.5);

		arr = new int[100];
		initializeRandomAray();

		length = 100;
		unit = 1920 / length;

		start.set("Start", { 150,50 }, { 960,25 }, font, true);
		reset.set("Reset", { 150,50 }, { 750,25 }, font, true);
		exit.set("Close", { 130,50 }, { 70,25 }, font, true);

		bool run = true;
		bool sorted = false;

		while (run)
		{
			sf::Event Event;
			while (selectionWindow->pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed:
				{
					run = false;
					selectionWindow->close();
					break;
				}
				case sf::Event::MouseMoved:
				{
					changeColor();
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (start.isMouseOver(*selectionWindow))
					{
						selectionSort(length, arr, unit, time1, run, selectionWindow);
						sorted = true;
					}
					if (reset.isMouseOver(*selectionWindow))
					{
						sorted = false;
						initializeRandomAray();
					}
					if (exit.isMouseOver(*selectionWindow))
					{
						run = false;
						selectionWindow->close();
					}
					break;
				}
				}
				selectionWindow->clear();
				initializeRun(arr, sorted);
				start.drawTo(*selectionWindow);
				reset.drawTo(*selectionWindow);
				exit.drawTo(*selectionWindow);
				selectionWindow->display();
			}
		}
	}

	void close()
	{
		selectionWindow->close();
	}

	void changeColor()
	{
		if ((start.isMouseOver(*selectionWindow)))
		{
			start.setBGColor(sf::Color::Green);
		}
		else
		{
			start.setBGColor(sf::Color::Red);
		}
		if ((reset.isMouseOver(*selectionWindow)))
		{
			reset.setBGColor(sf::Color::Green);
		}
		else
		{
			reset.setBGColor(sf::Color::Red);
		}
		if ((exit.isMouseOver(*selectionWindow)))
		{
			exit.setBGColor(sf::Color::Green);
		}
		else
		{
			exit.setBGColor(sf::Color::Red);
		}
	}

	void initializeRandomAray()
	{
		delete[] arr;
		arr = new int[100];
		static unsigned seed = time(NULL);
		srand(seed++);
		for (int i = 0; i < 100; i++)
		{
			int a = (rand() % 1000);
			arr[i] = a;
		}
	}

	void initializeRun(int arr[], bool sorted)
	{
		selectionWindow->clear();
		for (int i = 0; i < length; i++)
		{
			sf::RectangleShape bar(sf::Vector2f(unit, -arr[i]));
			bar.setPosition(i * unit, 1080);
			if (sorted)
			{
				bar.setFillColor(sf::Color::Green);
			}
			else
			{
				bar.setFillColor(sf::Color::Red);
			}
			selectionWindow->draw(bar);
		}
	}

	void selectionSort(int length, int arr[], int unit, sf::Time time, bool& done, sf::RenderWindow* window)
	{
		int min_idx = 0;
		for (int i = 0; i < length - 1; i++)
		{
			min_idx = i;

			for (int j = i + 1; j < length; j++)
			{
				sf::sleep(time);

				for (int k = 0; k < length; k++)
				{
					if (k != j)
					{
						sf::RectangleShape bar(sf::Vector2f(unit, -arr[k]));
						bar.setPosition(k * unit, 1080);
						bar.setFillColor(sf::Color::Red);
						selectionWindow->draw(bar);
					}
				}
				sf::RectangleShape bar(sf::Vector2f(unit, -arr[j]));
				bar.setPosition(j * unit, 1080);
				bar.setFillColor(sf::Color::Yellow);
				selectionWindow->draw(bar);
				window->display();

				window->clear(sf::Color::Black);

				if (arr[j] < arr[min_idx])
				{
					min_idx = j;
				}
			}

			int a = arr[min_idx];
			arr[min_idx] = arr[i];
			arr[i] = a;

			if (i == length - 2)
			{
				done = true;
			}
		}
	}
};
