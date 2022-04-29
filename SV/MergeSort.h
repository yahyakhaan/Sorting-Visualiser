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

class MergeSort
{
private:
	int* arr;
	int length;
	int unit;
protected:
	sf::RenderWindow* mergeWindow;
	sf::Time time1;
	sf::Time time2;
	Button exit;
	Button start;
	Button reset;
	sf::Font font;

public:
	MergeSort()
	{
		mergeWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Merge Sort", sf::Style::Titlebar);
		mergeWindow->clear(sf::Color::Black);

		font.loadFromFile("Extra/Arial.ttf");
		time1 = sf::milliseconds(30);

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
			while (mergeWindow->pollEvent(Event))
			{
				switch (Event.type)
				{
				case sf::Event::Closed:
				{
					run = false;
					mergeWindow->close();
					break;
				}
				case sf::Event::MouseMoved:
				{
					changeColor();
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					if (start.isMouseOver(*mergeWindow))
					{
						auto start = chrono::steady_clock::now();
						mergeSort(length, arr, unit, time1, run, mergeWindow);
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
					if (reset.isMouseOver(*mergeWindow))
					{
						sorted = false;
						initializeRandomAray();
					}
					if (exit.isMouseOver(*mergeWindow))
					{
						run = false;
						mergeWindow->close();
					}
					break;
				}
				}
				mergeWindow->clear();
				initializeRun(arr, sorted);
				start.drawTo(*mergeWindow);
				reset.drawTo(*mergeWindow);
				exit.drawTo(*mergeWindow);
				mergeWindow->display();
			}
		}
	}

	void close()
	{
		mergeWindow->close();
	}

	void changeColor()
	{
		if ((start.isMouseOver(*mergeWindow)))
		{
			start.setBGColor(sf::Color::Green);
		}
		else
		{
			start.setBGColor(sf::Color::Red);
		}
		if ((reset.isMouseOver(*mergeWindow)))
		{
			reset.setBGColor(sf::Color::Green);
		}
		else
		{
			reset.setBGColor(sf::Color::Red);
		}
		if ((exit.isMouseOver(*mergeWindow)))
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
		mergeWindow->clear();
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
			mergeWindow->draw(bar);
		}
	}

	void mergeSort(int length, int arr[], int unit, sf::Time time, bool& done, sf::RenderWindow* window)
	{
		int curr_size;  // For current size of subarrays to be merged
						// curr_size varies from 1 to n/2
		int left_start; // For picking starting index of left subarray
						// to be merged
		int n = length;

		int i = 0;
		// Merge subarrays in bottom up manner.  First merge subarrays of
		// size 1 to create sorted subarrays of size 2, then merge subarrays
		// of size 2 to create sorted subarrays of size 4, and so on.
		for (i = 0, curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size, i++)
		{
			// Pick starting point of different subarrays of current size
			for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
			{
				// Find ending point of left subarray. mid+1 is starting
				// point of right
				int mid = min(left_start + curr_size - 1, n - 1);

				int right_end = min(left_start + 2 * curr_size - 1, n - 1);
				sf::sleep(time);
				for (int k = 0; k < length; k++)
				{
					if (k != left_start)
					{
						sf::RectangleShape bar(sf::Vector2f(unit, -arr[k]));
						bar.setPosition(k * unit, 1080);
						bar.setFillColor(sf::Color::Red);
						mergeWindow->draw(bar);
					}
				}
				sf::RectangleShape bar(sf::Vector2f(unit, -arr[left_start]));
				bar.setPosition(left_start * unit, 1080);
				bar.setFillColor(sf::Color::Yellow);
				mergeWindow->draw(bar);
				window->display();

				window->clear(sf::Color::Black);

				merge(arr, left_start, mid, right_end);
				done = true;
			}
		}
	}

	/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
	void merge(int arr[], int l, int m, int r)
	{
		int i, j, k;
		int n1 = m - l + 1;
		int n2 = r - m;

		/* create temp arrays */
		int* L = new int[n1];
		int* R = new int[n2];

		/* Copy data to temp arrays L[] and R[] */
		for (i = 0; i < n1; i++)
			L[i] = arr[l + i];
		for (j = 0; j < n2; j++)
			R[j] = arr[m + 1 + j];

		/* Merge the temp arrays back into arr[l..r]*/
		i = 0;
		j = 0;
		k = l;
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				arr[k] = L[i];
				i++;
			}
			else
			{
				arr[k] = R[j];
				j++;
			}
			k++;
		}

		/* Copy the remaining elements of L[], if there are any */
		while (i < n1)
		{
			arr[k] = L[i];
			i++;
			k++;
		}

		/* Copy the remaining elements of R[], if there are any */
		while (j < n2)
		{
			arr[k] = R[j];
			j++;
			k++;
		}
	}
};