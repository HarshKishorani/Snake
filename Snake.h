#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include <vector>
class Snake
{
private:
	enum class Direction {
		Up,
		Down,
		Left,
		Right
	};

	// Variables
	sf::Vector2f currentDirectionVector;
	float length = 12.f;
	std::vector<sf::RectangleShape> snakeBody;
	Direction currentDirection;

	// Clock
	sf::Clock clock; // Measures elapsed time
	float updateInterval = 0.1f; // Seconds between each update (adjust this to control speed)

	// InitSnake
	void initSnake();

	//Collisions
	bool checkBodyCollision(sf::Vector2f& headNextPosition);
	bool checkWithinBoundry(sf::Vector2f& headNextPosition);
public:
	Snake();
	virtual ~Snake();

	void moveSnake(float dx, float dy);
	void update();
	void render(sf::RenderTarget &target);
};

