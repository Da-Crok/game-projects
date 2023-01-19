//AlphaPlayer.h

#pragma once

#include "Player.h"

class AlphaPlayer: public Player {
public:
    AlphaPlayer(int id, int chips);
    int getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) override;
};