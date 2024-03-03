#include "Game.h"

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Snake", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initVariables()
{
	this->endGame = false;
	this->snake = Snake();
}

Game::Game()
{
	this->initWindow();
	this->initVariables();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}


void Game::pollEvents()
{
	// Window Events
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				snake.moveSnake(-1.f,0.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				snake.moveSnake(1.f, 0.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				snake.moveSnake(0.f, -1.f);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				snake.moveSnake(0.f, 1.f);
			}
		}
	}
}


void Game::update()
{
	this->pollEvents();
	this->snake.update();
	this->endGame = this->snake.getEndGame();
}

void Game::render()
{
	this->window->clear(); // Clear Old Frame

	this->snake.render(*this->window);

	this->window->display(); // Render new Frame
}
