#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include <vector>
class Snake
{
private:
    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    bool endGame;
    int points;

    // Variables
    sf::Color snakeColor;
    sf::Vector2f currentDirectionVector;
    float length = 2.f;
    std::vector<sf::RectangleShape> snakeBody;
    Direction currentDirection;
    sf::CircleShape fruit;
    sf::Vector2f fruitPosition;

    void placeFruit();

    // Clock
    sf::Clock clock;
    float updateInterval = 0.1f; // Seconds between each update (adjust this to control speed)

    // InitSnake
    void initSnake();

    // Collisions
    bool checkBodyCollision(sf::Vector2f &headNextPosition);
    bool checkWithinBoundry(sf::Vector2f &headNextPosition);
    void checkFruitCollision();

public:
    Snake();
    virtual ~Snake();

    bool getEndGame();
    void moveSnake(float dx, float dy);
    void update();
    void render(sf::RenderTarget &target);
};
