#include "Snake.h"

void Snake::initSnake()
{
	snakeBody.clear();
	this->endGame = false;
	this->points = 0;

	// Init Directions
	this->currentDirectionVector = sf::Vector2f(1.0, 0.f);
	this->currentDirection = Direction::Right;

	// Init Snake Body
	this->snakeColor = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);

	for (int i = 0; i < this->length; ++i) {
		sf::RectangleShape segment(sf::Vector2f(gbl::cellSize - 1, gbl::cellSize - 1));
		segment.setPosition(this->currentDirectionVector.x - i * gbl::cellSize, this->currentDirectionVector.y);
		segment.setFillColor(snakeColor);
		snakeBody.push_back(segment);
	}

	// Init Fruit
	this->fruit.setRadius((gbl::cellSize - 3)/2.f);
	this->fruit.setFillColor(sf::Color::Red); 
	this->fruitPosition.x = rand() % gbl::gridWidth * gbl::cellSize;
	this->fruitPosition.y = rand() % gbl::gridHeight * gbl::cellSize;
	this->fruit.setPosition(this->fruitPosition);
}

Snake::Snake()
{
	this->initSnake();
}

Snake::~Snake()
{
}

void Snake::moveSnake(float dx, float dy)
{
	Direction newDirection;
	if (dx == 1) newDirection = Direction::Right;
	else if (dx == -1) newDirection = Direction::Left;
	else if (dy == 1) newDirection = Direction::Down;
	else if (dy == -1) newDirection = Direction::Up;
	else return;

	// Check if the new direction is opposite to the current direction
	if ((currentDirection == Direction::Up && newDirection == Direction::Down) ||
		(currentDirection == Direction::Down && newDirection == Direction::Up) ||
		(currentDirection == Direction::Left && newDirection == Direction::Right) ||
		(currentDirection == Direction::Right && newDirection == Direction::Left)) {
		return;
	}

	// Update the current direction and the movement speed
	currentDirection = newDirection;
	this->currentDirectionVector.x = dx;
	this->currentDirectionVector.y = dy;
}

bool Snake::checkWithinBoundry(sf::Vector2f &headNextPosition)
{
	return headNextPosition.x >= 0 && headNextPosition.x < gbl::gridWidth * gbl::cellSize &&
		headNextPosition.y >= 0 && headNextPosition.y < gbl::gridHeight * gbl::cellSize;
}

bool Snake::checkBodyCollision(sf::Vector2f &headNextPosition)
{
	bool collisionWithBody = false;

	for (size_t i = 1; i < snakeBody.size(); ++i) {
		if (headNextPosition == snakeBody[i].getPosition()) {
			collisionWithBody = true;
			break;
		}
	}

	return collisionWithBody;
}

void Snake::checkFruitCollision()
{
	if (snakeBody.front().getGlobalBounds().intersects(this->fruit.getGlobalBounds())) {
		sf::RectangleShape newSegment(sf::Vector2f(gbl::cellSize - 1, gbl::cellSize - 1));
		newSegment.setPosition(-100, -100); 
		newSegment.setFillColor(this->snakeColor); 
		this->snakeBody.push_back(newSegment);
		this->length++;
		this->points++;
		std::cout << "Points : " << this->points << std::endl;

		// Place the fruit at a new position
		placeFruit();
	}
}

void Snake::placeFruit() {
	bool isColliding;

	// Initialize isColliding outside the loop
	isColliding = true;

	while (isColliding) {
		isColliding = false;
		this->fruitPosition.x = (rand() % gbl::gridWidth) * gbl::cellSize;
		this->fruitPosition.y = (rand() % gbl::gridHeight) * gbl::cellSize;

		// Ensure the fruit does not spawn inside the snake's body
		for (const auto& segment : snakeBody) {
			if (this->fruitPosition == segment.getPosition()) {
				std::cout << "Fruit Body Collision Found";
				isColliding = true;
				break;
			}
		}
	}
	this->fruit.setPosition(this->fruitPosition);
}

void Snake::update()
{
	if (clock.getElapsedTime().asSeconds() >= updateInterval) {
		if (!snakeBody.empty()) {
			// Calculate the next position for the head based on the current direction
			sf::Vector2f headNextPosition = snakeBody.front().getPosition() + this->currentDirectionVector * static_cast<float>(gbl::cellSize);

			bool withinBounds = this->checkWithinBoundry(headNextPosition);
			bool collisionWithBody = this->checkBodyCollision(headNextPosition);
			this->checkFruitCollision();

			if (withinBounds && !collisionWithBody) {
				// Move the body segments forward from tail
				for (size_t i = snakeBody.size() - 1; i > 0; --i) {
					snakeBody[i].setPosition(snakeBody[i - 1].getPosition());
				}
				snakeBody.front().setPosition(headNextPosition);
			}
			else {
				this->endGame = true;
			}
		}
		clock.restart();
	}
}

bool Snake::getEndGame() {
	return this->endGame;
}

void Snake::render(sf::RenderTarget& target)
{
	target.draw(this->fruit);
	for (const auto& segment : this->snakeBody) {
		target.draw(segment);
	}
}