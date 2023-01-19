//BetaPlayer.h

#pragma once

#include "Player.h"

class BetaPlayer: public Player {
public:
    BetaPlayer(int id, int chips);
    int getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) override;
};