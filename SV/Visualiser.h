#pragma once
#include"Button.h"
#include"BubbleSort.h"
#include"InsertionSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"
#include "QSRec.h"
#include "QuickSortIterative.h"
#include<iostream>
#include<SFML/Graphics.hpp>
class Visualiser
{
private:
    BubbleSort *bubbleSort;
    InsertionSort* insertionSort;
    SelectionSort* selectionSort;
    MergeSort* mergeSort;
    QSRecursive* QSRec;
    QuickSortIterative* QSItr;

    Button mainButton[8];
    Button heading;

    sf::Font font;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RenderWindow* window;

    void LoadFromFile()
    {
        if (!texture.loadFromFile("Extra/3a.png"))
        {
            std::cout << "Background Image not found!\n";
            system("pause");
            exit(1);
        }
        if (!font.loadFromFile("Extra/f2.ttf"))
        {
            std::cout << "Font File not found!\n";
            system("pause");
            exit(1);
        }
    }

    void Intialize()
    {
        sprite.setTexture(texture);
        mainButton[1].set("Bubble Sort", { 270,50 }, { 280,380 }, font, true);
        mainButton[2].set("Insertion Sort", { 270,50 }, { 820,380 }, font, true);
        mainButton[3].set("Selection Sort", { 270,50 }, { 1420,380 }, font, true);
        mainButton[4].set("Merge Sort", { 270,50 }, { 820,810 }, font, true);
        mainButton[5].set("Quick Sort Recursive", { 370,50 }, { 1100,600 }, font, true);
        mainButton[6].set("Quick Sort Iterative", { 370,50 }, { 450, 600 }, font, true);
        mainButton[7].set("Exit", { 110,50 }, { 1750,850 }, font, true);   
    }

public:
    Visualiser(sf::RenderWindow* window_p):window(window_p)
    {
        LoadFromFile();
        Intialize();
    }

    void MouseMoved()
    {
        for (int i = 1; i < 8; i++)
        {
            if (mainButton[i].isMouseOver(*window))
            {
                //mainButton[i].setBoxColor(sf::Color::Green);
                mainButton[i].setBGColor(sf::Color::Green);
            }
            else
            {
                //mainButton[i].setBoxColor(sf::Color::White);
                mainButton[i].setBGColor(sf::Color::Red);
            }    
        }
    }

    void MouseButtonsPressed()
    {
        for (int i = 1; i < 8; i++)
        {
            if (mainButton[i].isMouseOver(*window))
            {
                switch (i)
                {
                case 1:
                {
                    bubbleSort = new BubbleSort();
                    break;
                }
                case 2:
                    insertionSort = new InsertionSort();
                    break;
                case 3:
                {
                    selectionSort = new SelectionSort();
                    break;
                }
                case 4:
                {
                    mergeSort = new MergeSort();
                    break;
                }
                case 5:
                {
                    QSRec = new QSRecursive();
                    break;
                }
                case 6:
                {
                    QSItr = new QuickSortIterative();
                    break;
                }
                case 7:
                    window->close();
                }
            }
        }
    }

    void Draw()
    {
        window->draw(sprite);
        heading.drawTo(*window);
        mainButton[1].drawTo(*window);
        mainButton[2].drawTo(*window);
        mainButton[3].drawTo(*window);
        mainButton[4].drawTo(*window);
        mainButton[5].drawTo(*window);
        mainButton[6].drawTo(*window);
        mainButton[7].drawTo(*window);
    }
};

