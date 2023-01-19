//Hand.h

#pragma once

#include <vector>
#include "Card.h"

class Hand {
private:
    std::vector<Card> m_cards;

public:
    static const int MAX_HAND_SIZE = 5;
    void clear();
    void addCard(Card& card);
    int getCount();
    Card& getCard(int);
    Hand getVisible();
    int evaluate();

};