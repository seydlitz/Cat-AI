//contains the defintions for the Settings class

#include "Settings.hpp"

bool Settings::NoisyDebug = false;
bool Settings::Windowed = false;
unsigned int Settings::WindowX = 0;
unsigned int Settings::WindowY = 0;
sf::Color Settings::MaskColor = sf::Color();

unsigned int Settings::BoardSizeX = 0;
unsigned int Settings::BoardSizeY = 0;

//eventually these will be imported, but want to get something running right now.
bool Settings::InitializeSettings(void)
{
	NoisyDebug = true;
	Windowed = true;
	WindowX = 1024;
	WindowY = 768;
	MaskColor = sf::Color(255, 174, 201);

	BoardSizeX = 10;
	BoardSizeY = 10;
	return true;
}