#pragma once
#include "Snake.h"

class Game
{
private:
	// Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	// Variables
	bool endGame;
	Snake snake;

	// Init Functions
	void initWindow();
	void initVariables();
public:
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	void pollEvents();
	void update();
	void render();
};