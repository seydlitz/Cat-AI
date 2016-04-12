//contains the declarations for Tile.hpp, which defines a board tile.

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

#include <string>
#include <list>

#include "Object.hpp"

#ifndef TILE_HPP_
#define TILE_HPP_

class Tile
{
private:

	sf::Vector2u MyPosition;
	static unsigned int TileSizeX;
	static unsigned int TileSizeY;

	bool HasObject;
	Object * MyObject;

public:

	static bool InitializeTiles(std::list<Tile> & ThisArray, int ArraySizeX, int ArraySizeY);

	Tile();
	Tile(unsigned int xPos, unsigned int yPos);

	sf::Vector2u GetPosition(void) const;

	const bool AddObject(Object * ThisObject);
	const Object * GetObject(void);
	const bool RemoveObject(void);

	void DrawTile(sf::RenderWindow & Window) const;
};


#endif