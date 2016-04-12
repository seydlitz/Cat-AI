//contains the declarations of the Board class, which contains the playing surface.

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <string>
#include <list>

#include "Tile.hpp"
#include "Object.hpp"

#ifndef BOARD_HPP_
#define BOARD_HPP_

class Board
{
private:

	unsigned int SizeX;
	unsigned int SizeY;

	std::list<Tile> PlayingBoard;

	sf::Clock MyClock;
	sf::Time Timer;

	//this exists because we only want one board in the game. It is used to prevent any new boards being initialized once set to true.
	static bool AnyBoardExists;

public:

	static bool InitializeBoard(void);
	static Board GameBoard;

	Board();
	Board(unsigned int sizeX, unsigned int sizeY);

	bool ProcessTick(void);
	void DrawBoard(sf::RenderWindow & Window) const;
};

#endif