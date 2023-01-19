//Card.cpp

#include "Card.h"

using namespace std;

/**
 * compiler doesn't like Game::m_deck having no default constructor
 */
Card::Card() {
    m_cardName = "";
    m_cardValue = 0;
    m_isFaceup = true;
}

Card::Card(string cardName, int cardValue) {
    m_cardName = cardName;
    m_cardValue = cardValue;
    m_isFaceup = true;
}

string Card::getName() {
    return m_cardName;
}

int Card::getValue() {
    return m_cardValue;
}

bool Card::isFaceup() {
    return m_isFaceup;
}

void Card::setFaceup(bool isFaceup) {
    this->m_isFaceup = isFaceup;
}
