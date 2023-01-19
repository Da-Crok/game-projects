//Bet.h

#pragma once

class Bet {
private:
    int m_player;
    int m_amount;

public:
    Bet(int amount, int player);
    int getPlayer();
    int getAmount();

};