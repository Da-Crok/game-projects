//Player.cpp

#include "Player.h"

Player::Player() {
    m_id = -1;
    m_chips = 0;
}

Player::Player(int id, int chips) {
    m_id = id;
    m_chips = chips;
}

int Player::getID() {
    return m_id;
}

void Player::clearHand() {
    m_hand.clear();
}

void Player::dealCard(Card c) {
    m_hand.addCard(c);
}

Hand& Player::getHand() {
    return m_hand;
}

void Player::addChips(int chips) {
    m_chips += chips;
}

int Player::getChips() {
    return m_chips;
}

int Player::takeChips(int chips) {
    m_chips -= chips;
    return chips;
}