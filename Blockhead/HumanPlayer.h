//HumanPlayer.h

#pragma once

#include "Player.h"

class HumanPlayer: public Player {
public:
    HumanPlayer(int id, int chips);
    int getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) override;
    int userIO(BetHistory bh, int bet2player, bool canRaise);
};