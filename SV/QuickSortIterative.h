#pragma once
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include "Button.h"
#include <chrono>
using namespace std;

class QuickSortIterative
{
private:
	int* arr;
	int length;
	int unit;
protected:
	sf::RenderWindow* QSItrWindow;
	sf::Time time1;
	sf::Time time2;
	Button exit;
	Button start;
	Button reset;
	sf::Font font;

public:
	QuickSortIterative()
	{
		QSItrWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Iterative Quick Sort", sf::Style::Titlebar);
		QSItrWindow->clear(sf::Color::Black);

		font.loadFromFile("Extra/Arial.ttf");
		time1 = sf::milliseconds(0.8);

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
			while (QSItrWindow->pollEvent(Event))
			{
				switch (Event.type)
				{
					case sf::Event::Closed:
					{
						run = false;
						QSItrWindow->close();
						break;
					}
					case sf::Event::MouseMoved:
					{
						changeColor();
						break;
					}
					case sf::Event::MouseButtonPressed:
					{
						if (start.isMouseOver(*QSItrWindow))
						{
							auto start = chrono::steady_clock::now();
							quickSort1(arr, 0, length - 1, length, unit, time1, QSItrWindow, run);
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
						if (reset.isMouseOver(*QSItrWindow))
						{
							sorted = false;
							initializeRandomAray();
						}
						if (exit.isMouseOver(*QSItrWindow))
						{
							run = false;
							QSItrWindow->close();
						}
						break;
					}
				}
				QSItrWindow->clear();
				initializeRun(arr, sorted);
				start.drawTo(*QSItrWindow);
				reset.drawTo(*QSItrWindow);
				exit.drawTo(*QSItrWindow);
				QSItrWindow->display();
			}
		}
	}

	void swap1(int* a, int* b)
	{
		int t = *a;
		*a = *b;
		*b = t;
	}

	/* This function is same in both iterative and recursive*/
	int partition1(int arr[], int l, int h, int length, int unit, sf::Time time, bool& done, sf::RenderWindow* window)
	{
		int x = arr[h];
		int i = (l - 1);

		for (int j = l; j <= h - 1; j++) {
			if (arr[j] <= x) {
				i++;
				for (int k = 0; k < length; k++)
				{
					sf::sleep(time);
					if (k != j)
					{
						sf::RectangleShape bar(sf::Vector2f(unit, -arr[k]));
						bar.setPosition(k * unit, 1080);
						bar.setFillColor(sf::Color::Red);
						QSItrWindow->draw(bar);
					}
				}
				sf::RectangleShape bar(sf::Vector2f(unit, -arr[j]));
				bar.setPosition(j * unit, 1080);
				bar.setFillColor(sf::Color::Yellow);
				QSItrWindow->draw(bar);
				window->display();

				window->clear(sf::Color::Black);
				swap1(&arr[i], &arr[j]);
			}
		}
		swap1(&arr[i + 1], &arr[h]);
		return (i + 1);
	}

	int partition_r1(int arr[], int low, int high, int length, int unit, sf::Time time1, bool& done, sf::RenderWindow* window)
	{
		static unsigned seedq = time(NULL);
		srand(seedq++);

		int random = low + rand() % (high - low);

		int a = arr[random];
		arr[random] = arr[high];
		arr[high] = a;

		return partition1(arr, low, high, length, unit, time1, done, window);
	}

	void quickSort1(int arr[], int l, int h, int length, int unit, sf::Time time, sf::RenderWindow* window, bool& done)
	{
		int* stack = new int[h - l + 1];

		// initialize top of stack
		int top = -1;

		// push initial values of l and h to stack
		stack[++top] = l;
		stack[++top] = h;

		// Keep popping from stack while is not empty
		while (top >= 0) {
			// Pop h and l
			h = stack[top--];
			l = stack[top--];

			// Set pivot element at its correct position
			// in sorted array
			int p = partition_r1(arr, l, h, length, unit, time, done, window);

			// If there are elements on left side of pivot,
			// then push left side to stack
			if (p - 1 > l) {
				stack[++top] = l;
				stack[++top] = p - 1;
			}

			// If there are elements on right side of pivot,
			// then push right side to stack
			if (p + 1 < h) {
				stack[++top] = p + 1;
				stack[++top] = h;
			}
		}
		done = true;
	}
	void close()
	{
		QSItrWindow->close();
	}

	void changeColor()
	{
		if ((start.isMouseOver(*QSItrWindow)))
		{
			start.setBGColor(sf::Color::Green);
		}
		else
		{
			start.setBGColor(sf::Color::Red);
		}
		if ((reset.isMouseOver(*QSItrWindow)))
		{
			reset.setBGColor(sf::Color::Green);
		}
		else
		{
			reset.setBGColor(sf::Color::Red);
		}
		if ((exit.isMouseOver(*QSItrWindow)))
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
		QSItrWindow->clear();
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
			QSItrWindow->draw(bar);
		}
	}
};