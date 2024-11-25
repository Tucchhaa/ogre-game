#include <iostream>

#include "game/galactic_wars_game.hpp"

using namespace std;

int main()
{
    auto game = game::GalacticWarsGame();
    // game.debugMode(true);
    game.configure();
    game.init();
    // game.startMenuScene();
    // game.startDemoScene();
    game.startSpaceScene();

    return 0;
}
