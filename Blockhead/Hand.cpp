//Hand.cpp

#include <vector>
#include "Hand.h"
#include "Card.h"

void Hand::clear() {
    m_cards.clear();
}

void Hand::addCard(Card& card) {
    m_cards.push_back(card);
}

int Hand::getCount() {
    return m_cards.size();
}

Card& Hand::getCard(int n) {
    return m_cards.at(n);
}

Hand Hand::getVisible() {
    Hand visible;
    visible.clear();

    for (Card card : m_cards) {
        if (card.isFaceup()) {
            visible.addCard(card);
        }
    }

    return visible;
}

int Hand::evaluate() {
    int total = 0;

    for (Card card : m_cards) {
        total += card.getValue();
    }

    return total;
}
