#include "../inc/Game.hpp"

int main()
{
    // Init srand
    srand(static_cast<unsigned>(time(NULL)));
    // Init game engine
    Game game;

    // Game Loop
    while (game.running() && !game.getEndGame())
    {

        game.update();
        game.render();
    }
    std::cout << "Game Ended";
    return 0;
}