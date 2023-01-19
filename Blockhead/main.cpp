//main.cpp
/**
 *  AUTHOR: Duncan Thomas
 *
 *  CSCI477A Project 2 - Phase 1
 *      Blockhead Poker
 */

#include <iostream>
#include <time.h>
#include "Game.h"

using namespace std;

int main() {
    srand(time(nullptr));

    Game game;
    int chips0 = 1000;
    int chips1 = 1000;

    game.playGame(HUMAN,ALPHA,chips0,chips1,false);

    cout << "chips0: " << chips0 << "\n";
    cout << "chips1: " << chips1 << "\n";

    return 0;
}
