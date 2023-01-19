//Bet.cpp

#include "Bet.h"

Bet::Bet(int amount, int player) {
    m_amount = amount;
    m_player = player;
}

int Bet::getAmount() {
    return m_amount;
}

int Bet::getPlayer() {
    return m_player;
}