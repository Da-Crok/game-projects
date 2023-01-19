//Player.h

#pragma once

#include "Hand.h"
#include "BetHistory.h"

class Player {
protected:
    int m_id;
    int m_chips;
    Hand m_hand;

public:
    Player();
    Player(int id, int chips);

    /**
     * This should be an abstract method that passes all of the necessary
     * domain information of the game to the player. Other information about
     * the player like the players hand should already be part of the Player object.
     * The method should then return the bet made by the player. This bet represents
     * the amount to be put in the pot, so it would include the amount bet2player
     * which is the previous players raise. A bet of -1 is a command to quit
     * (only comes from the human player). A bet of 0 is a fold IF there is a bet
     * to the player (otherwise, it's just a call).
     *
     * @param opponent
     * @param bh
     * @param bet2player
     * @param canRaise
     * @param pot
     * @return
     */
    virtual int getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) = 0;

    int getID();
    void clearHand();
    void dealCard(Card c);
    Hand& getHand();
    void addChips(int chips);
    int getChips();
    int takeChips(int chips);

};