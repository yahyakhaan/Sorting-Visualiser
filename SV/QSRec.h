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

class QSRecursive
{
private:
	int* arr;
	int length;
	int unit;
protected:
	sf::RenderWindow* QSRecWindow;
	sf::Time time1;
	sf::Time time2;
	Button exit;
	Button start;
	Button reset;
	sf::Font font;

public:
	QSRecursive()
	{
		QSRecWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Recursive Quick Sort", sf::Style::Titlebar);
		QSRecWindow->clear(sf::Color::Black);

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
			while (QSRecWindow->pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed:
				{
					run = false;
					QSRecWindow->close();
					break;
				}
				case sf::Event::MouseMoved:
				{
					changeColor();
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (start.isMouseOver(*QSRecWindow))
					{
						auto start = chrono::steady_clock::now();
						quickSort(arr,0,length-1,length,unit,time1,QSRecWindow,run);
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
					if (reset.isMouseOver(*QSRecWindow))
					{
						sorted = false;
						initializeRandomAray();
					}
					if (exit.isMouseOver(*QSRecWindow))
					{
						run = false;
						QSRecWindow->close();
					}
					break;
				}
				}
				QSRecWindow->clear();
				initializeRun(arr, sorted);
				start.drawTo(*QSRecWindow);
				reset.drawTo(*QSRecWindow);
				exit.drawTo(*QSRecWindow);
				QSRecWindow->display();
			}
		}
	}

	void swap(int* a, int* b)
	{
		int t = *a;
		*a = *b;
		*b = t;
	}

	int partition(int arr[], int low, int high, int length, int unit, sf::Time time, bool& done, sf::RenderWindow* window)
	{
		int pivot = arr[high]; // pivot
		int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

		for (int j = low; j <= length - 1; j++)
		{
			// If current element is smaller than the pivot
			if (arr[j] < pivot)
			{
				i++; // increment index of smaller element
				for (int k = 0; k < length; k++)
				{
					sf::sleep(time);
					if (k != j)
					{
						sf::RectangleShape bar(sf::Vector2f(unit, -arr[k]));
						bar.setPosition(k * unit, 1080);
						bar.setFillColor(sf::Color::Red);
						QSRecWindow->draw(bar);
					}
				}
				sf::RectangleShape bar(sf::Vector2f(unit, -arr[j]));
				bar.setPosition(j * unit, 1080);
				bar.setFillColor(sf::Color::Yellow);
				QSRecWindow->draw(bar);
				window->display();

				window->clear(sf::Color::Black);

				swap(&arr[i], &arr[j]);
			}
		}
		swap(&arr[i + 1], &arr[high]);
		return (i + 1);
	}

	int partition_r(int arr[], int low, int high, int length, int unit, sf::Time time1, bool& done, sf::RenderWindow* window)
	{
		static unsigned seedq = time(NULL);
		srand(seedq++);

		int random = low + rand() % (high - low);
		int a = arr[random];
		arr[random] = arr[high];
		arr[high] = a;

		return partition(arr, low, high, length, unit, time1, done, window);
	}

	void quickSort(int arr[], int low, int high, int length, int unit, sf::Time time, sf::RenderWindow* window, bool& done)
	{
		if (low < high)
		{
			int pi = partition_r(arr, low, high, length, unit, time, done, window);
			quickSort(arr, low, pi - 1, length, unit, time, window, done);
			quickSort(arr, pi + 1, high, length, unit, time, window, done);
			done = true;
		}
	}

	void close()
	{
		QSRecWindow->close();
	}

	void changeColor()
	{
		if ((start.isMouseOver(*QSRecWindow)))
		{
			start.setBGColor(sf::Color::Green);
		}
		else
		{
			start.setBGColor(sf::Color::Red);
		}
		if ((reset.isMouseOver(*QSRecWindow)))
		{
			reset.setBGColor(sf::Color::Green);
		}
		else
		{
			reset.setBGColor(sf::Color::Red);
		}
		if ((exit.isMouseOver(*QSRecWindow)))
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
		QSRecWindow->clear();
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
			QSRecWindow->draw(bar);
		}
	}
};

