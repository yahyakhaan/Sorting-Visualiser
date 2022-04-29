#pragma once
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "Button.h"

class InsertionSort
{
private:
	int* arr;
	int length;
	int unit;
protected:
	sf::RenderWindow* insertionWindow;
	sf::Time time1;
	sf::Time time2;
	Button exit;
	Button start;
	Button reset;
	sf::Font font;

public:
	InsertionSort()
	{
		insertionWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "InsertionSort", sf::Style::Titlebar);
		insertionWindow->clear(sf::Color::Black);

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
			while (insertionWindow->pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed:
				{
					run = false;
					insertionWindow->close();
					break;
				}
				case sf::Event::MouseMoved:
				{
					changeColor();
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (start.isMouseOver(*insertionWindow))
					{
						auto start = chrono::steady_clock::now();
						insertionSort(length, arr, unit, time1, run, insertionWindow);
						auto end = chrono::steady_clock::now();
						cout << "Elapsed time in nanoseconds: "
							<< chrono::duration_cast<chrono::nanoseconds>(end - start).count()
							<< " ns" << endl;

						cout << "Elapsed time in microseconds: "
							<< chrono::duration_cast<chrono::microseconds>(end - start).count()
							<< " µs" << endl;

						cout << "Elapsed time in milliseconds: "
							<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
							<< " ms" << endl;

						cout << "Elapsed time in seconds: "
							<< chrono::duration_cast<chrono::seconds>(end - start).count()
							<< " sec";
						sorted = true;
					}
					if (reset.isMouseOver(*insertionWindow))
					{
						sorted = false;
						initializeRandomAray();
					}
					if (exit.isMouseOver(*insertionWindow))
					{
						run = false;
						insertionWindow->close();
					}
					break;
				}
				}
				insertionWindow->clear();
				initializeRun(arr, sorted);
				start.drawTo(*insertionWindow);
				reset.drawTo(*insertionWindow);
				exit.drawTo(*insertionWindow);
				insertionWindow->display();
			}
		}
	}

	void close()
	{
		insertionWindow->close();
	}

	void changeColor()
	{
		if ((start.isMouseOver(*insertionWindow)))
		{
			start.setBGColor(sf::Color::Green);
		}
		else
		{
			start.setBGColor(sf::Color::Red);
		}
		if ((reset.isMouseOver(*insertionWindow)))
		{
			reset.setBGColor(sf::Color::Green);
		}
		else
		{
			reset.setBGColor(sf::Color::Red);
		}
		if ((exit.isMouseOver(*insertionWindow)))
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
		insertionWindow->clear();
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
			insertionWindow->draw(bar);
		}
	}

	void insertionSort(int length, int arr[], int unit, sf::Time time, bool& done, sf::RenderWindow* window)
	{
		bool a = false;
		for (int i = 0; i < length; i++)
		{
			int j = i;
			while (j > 0 && arr[j] < arr[j - 1])
			{
				sf::sleep(time);
				for (int k = 0; k < length; k++)
				{
					if (k != j)
					{
						sf::RectangleShape bar(sf::Vector2f(unit, -arr[k]));
						bar.setPosition(k * unit, 1080);
						bar.setFillColor(sf::Color::Red);
						insertionWindow->draw(bar);
					}
				}
				sf::RectangleShape bar(sf::Vector2f(unit, -arr[j]));
				bar.setPosition(j * unit, 1080);
				bar.setFillColor(sf::Color::Yellow);
				insertionWindow->draw(bar);
				window->display();

				window->clear(sf::Color::Black);

				int a = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = a;
				j--;

			}

			if (i == length - 1)
			{
				done = true;
				a = true;
			}
		}
	}
};
