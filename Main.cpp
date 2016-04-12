//contains the main executable function

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

//our files
#include "Object.hpp"
#include "Settings.hpp"
#include "Board.hpp"

int main()
{
	//seeds the prng.
	srand(time(0));

	//keeps program active.
	bool Running = true;
	//load Settings...
	if(!Settings::InitializeSettings())
	{
		std::cout << "Error initializing settings. Exiting...\n";
		std::exit(EXIT_FAILURE);
	}

	//disable SFML error messages
	sf::err().set_rdbuf(NULL);

	//setting up window...
	sf::RenderWindow MainWindow;
	if(Settings::Windowed == false)
	{
		std::vector<sf::VideoMode>FullScreenModes = sf::VideoMode::getFullscreenModes();
		for(auto pMode = FullScreenModes.begin();pMode != FullScreenModes.end();pMode++)
		{
			if(sf::VideoMode(Settings::WindowX, Settings::WindowY) == *pMode)
			{
				MainWindow.create(*pMode, "Cat AI", sf::Style::Fullscreen);
			}
		}
	}
	else
	{
		
		MainWindow.create(sf::VideoMode::VideoMode(Settings::WindowX, Settings::WindowY), "Cat AI", sf::Style::Default);
	}

	//event handler
	sf::Event Event;

	//importing data...
	if(!Object::InitializeObjects())
	{
		std::cout << "Error initializing objects. Exiting...\n";
		std::system("PAUSE");
		std::exit(EXIT_FAILURE);
	}
	if(!Board::InitializeBoard())
	{
		std::cout << "Error initializing board. Exiting...\n";
		std::system("PAUSE");
		std::exit(EXIT_FAILURE);
	}

	while(Running)
	{
		//CLEARING
		//
		//
		MainWindow.clear();

		//PROCESSING
		//
		//
		Running = Board::GameBoard.ProcessTick();

		//EVENT HANDLING
		//
		//
		while(MainWindow.pollEvent(Event))
		{
			if(Event.type == sf::Event::Closed)
			{
				MainWindow.close();
				Running = false;
			}
			else if (Event.type == sf::Event::MouseButtonPressed && Event.mouseButton.button == sf::Mouse::Right)
			{
				sf::Vector2f MousePos = MainWindow.mapPixelToCoords(sf::Mouse::getPosition(MainWindow));
				MainWindow.setView(sf::View(MousePos,MainWindow.getView().getSize()));			
			}
			else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Home)
			{
				MainWindow.setView(MainWindow.getDefaultView());
			}
		}

		//DRAWING
		//
		//
		Board::GameBoard.DrawBoard(MainWindow);

		//DISPLAY
		//
		//
		MainWindow.display();
	}

	std::system("PAUSE");
	return 0;
}