//contains the declarations for the Object class, which specifies actionable objects on the board.

#include <string>
#include <iostream>
#include <list>

#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

class Object
{
private:

	//these are set on import

	unsigned int Id;
	std::string Name;
	bool Sentient; //determines whether it can move and react to outside events - a mouse is sentient, cheese is not.
	std::string ImgName; //the name (w/ extension) of the image file for this object.

	//these are dynamic

	sf::Vector2u MyPosition;
	bool HasPrey;
	std::string PreyName;
	bool HasPredator;
	std::string PredatorName;

	//used to set ids for all objects.
	static unsigned int GlobalId;

public:

	static bool InitializeObjects(void);
	static std::list<Object> Objects;

	Object();
	Object(const std::string name, const bool sentient, const std::string imgname);

	int GetId(void) const;
	std::string GetName(void) const;
	bool IsSentient(void) const;
	std::string GetImageName(void) const;
	sf::Vector2u GetPosition(void) const;
	bool GetHasPredator(void) const;
	bool GetHasPrey(void) const;
	std::string GetPredator(void) const;
	std::string GetPrey(void) const;

	void SetPrey(const std::string name);
	void SetPredator(const std::string name);
	void SetPosition(const sf::Vector2u & NewPosition);

	sf::Vector2u MovePrey(const sf::Vector2u & preyPosition);
	sf::Vector2u MovePredator(const sf::Vector2u & predatorPosition);
	sf::Vector2u Move(const sf::Vector2u & preyPosition, const sf::Vector2u & predatorPosition);
};


#endif