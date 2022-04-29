#include<iostream>
#include"Visualiser.h"
#include<SFML/Graphics.hpp>
using namespace std;
void main()
{
    sf::RenderWindow* window;
    Visualiser* visualiser;

    window=new sf::RenderWindow(sf::VideoMode(1950, 1080), "Sorting Visualiser", sf::Style::Titlebar);
    visualiser =new Visualiser(window);

    while (window->isOpen())
    {
        sf::Event Event;
        while (window->pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                {
                    window->close();
                }
                case sf::Event::MouseMoved:
                {
                    visualiser->MouseMoved();
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    visualiser->MouseButtonsPressed();
                    cout << "Pressed" << endl;
                    break;
                }
            }
            window->clear();
            visualiser->Draw();
            window->display();
        }
    }
}