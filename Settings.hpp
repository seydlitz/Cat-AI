//declarations for Settings class - things like noisy debug, window size, etc.

#include <string>
#include <iostream>

#include <SFML\Graphics.hpp>

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

class Settings
{
public:

	static bool Windowed;
	static unsigned int WindowX;
	static unsigned int WindowY;
	static bool NoisyDebug;
	static sf::Color MaskColor;

	static unsigned int BoardSizeX;
	static unsigned int BoardSizeY;

	static bool InitializeSettings(void);
};

#endif