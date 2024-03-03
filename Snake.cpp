#include "Snake.h"

void Snake::initSnake()
{
	snakeBody.clear();
	this->currentDirectionVector = sf::Vector2f(1.0, 0.f);
	this->currentDirection = Direction::Right;

	sf::Color snakeColor = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);

	for (int i = 0; i < this->length; ++i) {
		sf::RectangleShape segment(sf::Vector2f(gbl::cellSize - 1, gbl::cellSize - 1));
		segment.setPosition(this->currentDirectionVector.x - i * gbl::cellSize, this->currentDirectionVector.y);
		segment.setFillColor(snakeColor);
		snakeBody.push_back(segment);
	}
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
	// Convert dx, dy to a Direction enum value for easier comparison
	Direction newDirection;
	if (dx == 1) newDirection = Direction::Right;
	else if (dx == -1) newDirection = Direction::Left;
	else if (dy == 1) newDirection = Direction::Down;
	else if (dy == -1) newDirection = Direction::Up;
	else return; // No valid direction, so just return

	// Check if the new direction is opposite to the current direction
	if ((currentDirection == Direction::Up && newDirection == Direction::Down) ||
		(currentDirection == Direction::Down && newDirection == Direction::Up) ||
		(currentDirection == Direction::Left && newDirection == Direction::Right) ||
		(currentDirection == Direction::Right && newDirection == Direction::Left)) {
		// If trying to move in the opposite direction, ignore the command
		return;
	}

	// Update the current direction and the movement speed
	currentDirection = newDirection; // Update the current direction
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

	// Check for collision with body (skip the head itself)
	for (size_t i = 1; i < snakeBody.size(); ++i) {
		if (headNextPosition == snakeBody[i].getPosition()) {
			collisionWithBody = true;
			break; // Exit the loop early as collision is found
		}
	}

	return collisionWithBody;
}

void Snake::update()
{
	if (clock.getElapsedTime().asSeconds() >= updateInterval) {
		if (!snakeBody.empty()) {
			// Calculate the next position for the head based on the current direction
			sf::Vector2f headNextPosition = snakeBody.front().getPosition() + this->currentDirectionVector * static_cast<float>(gbl::cellSize);

			bool withinBounds = this->checkWithinBoundry(headNextPosition);
			bool collisionWithBody = this->checkBodyCollision(headNextPosition);

			if (withinBounds && !collisionWithBody) {
				// Move the body segments forward from tail
				for (size_t i = snakeBody.size() - 1; i > 0; --i) {
					snakeBody[i].setPosition(snakeBody[i - 1].getPosition());
				}
				snakeBody.front().setPosition(headNextPosition);
			}
			else {
				// Handle collision or boundary violation
				// This could be game over or some other logic
			}
		}
		clock.restart();
	}
}


void Snake::render(sf::RenderTarget& target)
{
	for (const auto& segment : snakeBody) {
		target.draw(segment);
	}
}
