//AlphaPlayer.cpp

/**
 * This is a derived class of Player that evaluates domain information
 * for the current AI player and decides on a player bet. This uses the getBet() method.
 */

#include "AlphaPlayer.h"

AlphaPlayer::AlphaPlayer(int id, int chips) {
    m_id = id;
    m_chips = chips;
}

int AlphaPlayer::getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) {
    int delta = m_hand.evaluate() - opponent.getVisible().evaluate();
    int potFactor = pot / 10;

    if(m_hand.getCount() != Hand::MAX_HAND_SIZE) {     //if there are still cards to draw (hand is not full)
        if(bh.getCount() == 0) {     //if there have been no bets prior
            if(delta > 10) {
                if(canRaise) return bet2player + 10;          //raise 10
                else return bet2player;
            } else if(delta > 5) {
                if(canRaise) return bet2player + 5;           //raise 5
                else return bet2player;
            } else if(delta > 0) {
                if(canRaise) return bet2player + 1;           //raise 1
                else return bet2player;
            }
            else {
                return bet2player;               //call
            }
        } else {    //else there have been prior bets
            if(bet2player==0) {     //prior bet is a check - THIS MEANS AI CANNOT CALL
                if(delta > (5-potFactor)) {
                    if(canRaise) return bet2player + 10;          //raise 10
                    else return bet2player;
                } else if(delta > (0-potFactor)) {
                    if(canRaise) return bet2player + 5;           //raise 5
                    else return bet2player;
                } else {
                    if(canRaise) return bet2player + 1;           //raise 1
                    else return bet2player;               //call - SHOULD NOT HAPPEN
                }
            } else if(bh.getCount()>=2 && bh.getBet(bh.getCount()-1).getAmount()==bh.getBet(bh.getCount()-2).getAmount()) {       //if prior bet is a call
                if(delta > (5-potFactor)) {
                    if(canRaise) return bet2player + 10;         //raise 10
                    else return bet2player;
                } else if(delta > (0-potFactor)) {
                    if(canRaise) return bet2player + 5;          //raise 5
                    else return bet2player;
                } else {
                    return bet2player;
                }
            } else if(bet2player < (1+potFactor*2)) {
                if(delta > (8-potFactor)) {
                    if(canRaise) return bet2player + 10;         //raise 10
                    else return bet2player;
                } else if(delta > (-2-potFactor)) {
                    if(canRaise) return bet2player + 1;          //raise 1
                    else return bet2player;
                } else if(delta > (-4-potFactor)) {
                    if(canRaise) return bet2player;              //call
                } else {
                    return 0;                       //fold
                }
            } else {
                if(delta > (10-potFactor)) {
                    if(canRaise) return bet2player + 10;         //raise 10
                    else return bet2player;
                } else if(delta > (0-potFactor)) {
                    if(canRaise) return bet2player + 1;          //raise 1
                    else return bet2player;
                } else if(delta > (-2-potFactor)) {
                    return bet2player;              //call
                } else {
                    return 0;                       //fold
                }
            }
        }
    } else {        //last betting round
        if(bh.getCount() == 0) {     //if there have been no bets prior
            if(delta > 10) {
                if(canRaise) return bet2player + 10;          //raise 10
                else return bet2player;
            } else if(delta > 5) {
                if(canRaise) return bet2player + 5;           //raise 5
                else return bet2player;
            } else {
                return bet2player;               //call
            }
        } else {    //else there have been prior bets
            if(bet2player==0) {     //prior bet is a check - THIS MEANS AI CANNOT CALL
                if(delta > 10) {
                    if(canRaise) return bet2player + 10;          //raise 10
                    else return bet2player;
                } else if(delta > 5) {
                    if(canRaise) return bet2player + 5;           //raise 5
                    else return bet2player;
                } else {
                    if(canRaise) return bet2player + 1;           //raise 1
                    else return bet2player;               //call - SHOULD NOT HAPPEN
                }
            } else if(bh.getCount()>=2 && bh.getBet(bh.getCount()-1).getAmount()==bh.getBet(bh.getCount()-2).getAmount()) {       //if prior bet is a call
                if(delta > (10-potFactor)) {
                    if(canRaise) return bet2player + 10;         //raise 10
                    else return bet2player;
                } else {
                    return bet2player;          //call
                }
            } else if(bet2player < (1+potFactor*2)) {
                if(delta > (6-potFactor)) {
                    if(canRaise) return bet2player + 10;         //raise 10
                    else return bet2player;
                } else if(delta > 2) {
                    if(canRaise) return bet2player;              //call
                } else {
                    return 0;                   //fold
                }
            } else {
                if(delta > (8-potFactor)) {
                    if(canRaise) return bet2player + 10;         //raise 10
                    else return bet2player;
                } else if(delta > 4) {
                    return bet2player;              //call
                } else {
                    return 0;                       //fold
                }
            }
        }
    }
    return -1;


}