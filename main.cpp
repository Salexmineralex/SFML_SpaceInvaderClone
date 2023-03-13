#include <SFML/Graphics.hpp>

#include "game.h"
#include <iostream>


int main()
{

    Game game;
    game.init();

    while (game.wantsToQuitGame() == false)
    {
        game.run();
    }

 
    return 0;
}




