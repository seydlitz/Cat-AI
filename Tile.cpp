//contains the class definitions for the Tile.hpp file.

#include "Tile.hpp"
#include "Settings.hpp"

unsigned int Tile::TileSizeX = 0;
unsigned int Tile::TileSizeY = 0;

Tile::Tile()
{
	MyPosition = sf::Vector2u(0,0);
	HasObject = false;
	MyObject = nullptr;
}
Tile::Tile(unsigned int xPos, unsigned int yPos)
{
	MyPosition = sf::Vector2u(xPos, yPos);
	HasObject = false;
	MyObject = nullptr;
}

bool Tile::InitializeTiles(std::list<Tile> & ThisArray, int ArraySizeX, int ArraySizeY)
{
	TileSizeX = 129;
	TileSizeY = 129;
	ThisArray.clear();
	for(int x = 0;x < ArraySizeX;x++)
	{
		for(int y = 0;y < ArraySizeY;y++)
		{
			ThisArray.push_back(Tile(x,y));
		}
	}

	return true;
}

sf::Vector2u Tile::GetPosition(void) const
{return MyPosition;}

const bool Tile::AddObject(Object * ThisObject)
{
	if(HasObject == false)
	{
		HasObject = true;
		MyObject = ThisObject;
		ThisObject->SetPosition(MyPosition);
		return true;
	}
	else return false;
}
const Object * Tile::GetObject(void)
{
	return MyObject;
}

const bool Tile::RemoveObject(void)
{
	if(HasObject == true)
	{
		HasObject = false;
		MyObject = nullptr;
		return true;
	}
	else return false;
}

void Tile::DrawTile(sf::RenderWindow & Window) const
{
	float DrawX = MyPosition.x * TileSizeX;
	float DrawY = MyPosition.y * TileSizeY;
	//eventually draw the tile itself...

	//draw lines at far right and bottom
	sf::VertexArray XLine(sf::PrimitiveType::Lines, 2);
	XLine[0].position = sf::Vector2f(DrawX, DrawY + TileSizeY);
	XLine[0].color = sf::Color::Red;
	XLine[1].position = sf::Vector2f(DrawX + TileSizeX, DrawY + TileSizeY);
	XLine[1].color = sf::Color::Red;
	sf::VertexArray YLine(sf::PrimitiveType::Lines, 2);
	YLine[0].position = sf::Vector2f(DrawX + TileSizeX, DrawY);
	YLine[0].color = sf::Color::Red;
	YLine[1].position = sf::Vector2f(DrawX + TileSizeX, DrawY + TileSizeY);
	YLine[1].color = sf::Color::Red;
	Window.draw(XLine);
	Window.draw(YLine);
	
	//draw object, if any
	if(HasObject)
	{
		sf::Image img;
		if(img.loadFromFile("./db/img/" + MyObject->GetImageName()))
		{
			img.createMaskFromColor(Settings::MaskColor);
			sf::Texture texture;
			texture.loadFromImage(img);
			sf::Sprite ObjectSprite(texture);
			ObjectSprite.setPosition(DrawX, DrawY);
			Window.draw(ObjectSprite);
		}
	}
}