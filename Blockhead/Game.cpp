//Game.cpp

#include <iostream>
#include "Game.h"
#include "HumanPlayer.h"
#include "AlphaPlayer.h"
#include "BetaPlayer.h"

using namespace std;

/**
 * Plays a game between a player of type p0 and p1. Chips is the number
 * of chips each player respectively has at start and end of the game.
 * reportFlag is just a flag to turn on and off I/O within the game
 * (so you can do Monte Carlo runs without a lot of output).
 * The method returns true if someone wants to quit the program.
 */
bool Game::playGame(PlayerType p0, PlayerType p1, int &chips0, int &chips1, bool reportFlag) {
    //set up initial conditions
    m_reportFlag = reportFlag;
    bool quit = false;

    deckSetup();

    /**
     * Current architecture supports player IDs 0 and 1 only
     *  Has to do with return values to determine who folds
     */
    Player* player0 = initPlayer(p0, 0, chips0);
    Player* player1 = initPlayer(p1, 1, chips1);

    //play 20 hands
    for(int i=0; i<10; ++i) {
        //player0 starts the bet
        quit = playHand(*player0, *player1);
        chips0 = player0->getChips();
        chips1 = player1->getChips();
        if (quit) {
            return true;
        }

        //player1 starts the bet
        quit = playHand(*player1, *player0);
        chips0 = player0->getChips();
        chips1 = player1->getChips();
        if (quit) {
            return true;
        }
    }

    if(m_reportFlag) {
        cout << "Player " << player0->getID() << " ends the game with " << chips0 << " chips.\n";
        cout << "Player " << player1->getID() << " ends the game with " << chips1 << " chips.\n";
    }

    return false;
}

Player* Game::initPlayer(PlayerType pType, int id, int &chips) {
    if(pType == HUMAN) {
        return new HumanPlayer(id, chips);
    } else if(pType == ALPHA) {
        return new AlphaPlayer(id, chips);
    } else if(pType == BETA) {
        return new BetaPlayer(id, chips);
    } else {
        cout << "\nNo type for player? How did you get here?\n";
        return new HumanPlayer(id, chips);
    }
}

/**
 * returns true if someone wants to quit the game
 *
 * @param p0
 * @param p1
 * @return
 */
bool Game::playHand(Player &p0, Player &p1) {

    //shuffle deck
    shuffleDeck();

    //clear player hands
    p0.getHand().clear();
    p1.getHand().clear();

    //setup pot with buy-in
    m_pot = 0;
    m_pot += p0.takeChips(10);
    m_pot += p1.takeChips(10);

    //deal three cards
    p0.dealCard(m_deck[0]);
    p0.getHand().getCard(0).setFaceup(false);

    p1.dealCard(m_deck[1]);
    p1.getHand().getCard(0).setFaceup(false);

    p0.dealCard(m_deck[2]);
    p1.dealCard(m_deck[3]);
    p0.dealCard(m_deck[4]);
    p1.dealCard(m_deck[5]);

    //betting round
    int roundResult = betRound(p0, p1);

    //if someone wants to quit or folds end the round
    if(roundResult==-1 || roundResult==0 || roundResult==1) {
        return endRound(p0,p1, roundResult);
    }

    p0.dealCard(m_deck[6]);
    p1.dealCard(m_deck[7]);


    //betting round
    roundResult = betRound(p0, p1);

    //if someone wants to quit or folds end the round
    if(roundResult==-1 || roundResult==0 || roundResult==1) {
        return endRound(p0,p1, roundResult);
    }

    p0.dealCard(m_deck[8]);
    p1.dealCard(m_deck[9]);


    //betting round
    roundResult = betRound(p0, p1);

    //if someone wants to quit or folds end the round and determine winner
    if(roundResult==-1 || roundResult==0 || roundResult==1) {
        return endRound(p0,p1, roundResult);
    }

    //decide winner
    if(p0.getHand().evaluate() > p1.getHand().evaluate()) {         //p0 wins
        if(m_reportFlag) {
            cout << "\nPlayer " << p0.getID() << " wins " << m_pot << " chips!\n";
        }
        p0.addChips(m_pot);
        return false;
    } else if(p0.getHand().evaluate() < p1.getHand().evaluate()) {  //p1 wins
        if(m_reportFlag) {
            cout << "\nPlayer " << p1.getID() << " wins " << m_pot << " chips!\n";
        }
        p1.addChips(m_pot);
        return false;
    } else {    //tie, split the pot
        m_pot = m_pot/2;
        if(m_reportFlag) {
            cout << "\nTie! Both players get " << m_pot << " chips!\n";
        }
        p0.addChips(m_pot);
        p1.addChips(m_pot);
        return false;
    }

}

//shuffle the deck
void Game::shuffleDeck() {
    // swap one-by-one from the back of the array
    for(int i=DECK_SIZE-1; i>0; --i) {
        int j = rand() % (i+1);

        Card temp = m_deck[i];
        m_deck[i] = m_deck[j];
        m_deck[j] = temp;
    }
}

/**
 * returns -1 if someone wants to quit
 * returns 0 if p0 folds
 * returns 1 if p1 folds
 * returns 2 if someone calls
 * @param p0
 * @param p1
 * @return
 */
int Game::betRound(Player &p0, Player &p1) {
    m_betHistory.clearHistory();        //betHistory is history for a single round
    int raises = 0;
    bool canRaise = true;
    int lastBet = 0;
    int currentBet = 0;

    if(m_reportFlag) {
        cout << "\n A round of betting begins!\n\n";
    }

    while(true) {       //proceeds until a fold, a call, or three raises and a call
        //p0 bets
        currentBet = p0.getBet(p1.getHand(), m_betHistory, lastBet, canRaise, m_pot);
        if(currentBet == -1) {      //human player wants to quit
            return -1;
        }

        if(lastBet==0 && currentBet==0) {           //p0 has checked
            if(m_reportFlag) {
                cout << "Player " << p0.getID() << " checks.\n";
            }
        } else if(currentBet==0 && lastBet>0) {     //p0 folds and bet round ends
            return playerFolds(p0);
        } else if(currentBet == lastBet) {          //p0 calls, update pot and end round
            return playerCalls(p0, currentBet, lastBet);
        } else if(currentBet > lastBet) {           //p0 has raised, update pot and num raises
            playerRaises(p0, currentBet, lastBet, raises);
        }

        m_betHistory.addBet(Bet(currentBet, p0.getID()));    //add bet from p0 to history

        if(raises >= 3) {
            canRaise = false;
        }

        lastBet = currentBet;

        //p1 bets
        currentBet = p1.getBet(p0.getHand(), m_betHistory, lastBet, canRaise, m_pot);
        if(currentBet == -1) {      //human player wants to quit
            return -1;
        }

        if(lastBet==0 && currentBet==0) {           //p1 has checked - should not be legal

            cout << "\n\nPlayer " << p1.getID() << " checks? How did you get here?\n\n";
            return -1;

        } else if(currentBet==0 && lastBet>0) {     //p1 folds and bet round ends
            return playerFolds(p1);
        } else if(currentBet == lastBet) {          //p1 calls, update pot and end round
            return playerCalls(p1,currentBet, lastBet);
        } else if(currentBet > lastBet) {           //p1 has raised, update pot and num raises
            playerRaises(p1, currentBet, lastBet, raises);
        }

        m_betHistory.addBet(Bet(currentBet, p1.getID()));    //add bet from p1 to history

        if(raises >= 3) {
            canRaise = false;
        }

        lastBet = currentBet;
    } //end while
}


//create a standard 52-card deck
void Game::deckSetup() {
    string suit;
    for(int i=0; i<4; ++i) {
        switch (i) {
            case 0:
                suit = "Spades";
                break;
            case 1:
                suit = "Hearts";
                break;
            case 2:
                suit = "Diamonds";
                break;
            case 3:
                suit = "Clubs";
                break;
            default:
                suit = "Spades";
                break;
        }

        m_deck[13*i +  0] = Card("Ace of " + suit,    1);
        m_deck[13*i +  1] = Card("Two of " + suit,    2);
        m_deck[13*i +  2] = Card("Three of " + suit,  3);
        m_deck[13*i +  3] = Card("Four of " + suit,   4);
        m_deck[13*i +  4] = Card("Five of " + suit,   5);
        m_deck[13*i +  5] = Card("Six of " + suit,    6);
        m_deck[13*i +  6] = Card("Seven of " + suit,  7);
        m_deck[13*i +  7] = Card("Eight of " + suit,  8);
        m_deck[13*i +  8] = Card("Nine of " + suit,   9);
        m_deck[13*i +  9] = Card("Ten of " + suit,   10);
        m_deck[13*i + 10] = Card("Jack of " + suit,  10);
        m_deck[13*i + 11] = Card("Queen of " + suit, 10);
        m_deck[13*i + 12] = Card("King of " + suit,  10);
    }


}

bool Game::endRound(Player &p0, Player &p1, int roundResult) {
    if(roundResult == -1) {             //someone wants to quit
        return true;
    } else if(roundResult == 0) {       //p0 folds, p1 wins
        if(m_reportFlag) {
            cout << "\nPlayer " << p1.getID() << " wins " << m_pot << " chips!\n";
        }
        p1.addChips(m_pot);
        return false;
    } else if(roundResult == 1) {       //p1 folds, p0 wins
        if(m_reportFlag) {
            cout << "\nPlayer " << p0.getID() << " wins " << m_pot << " chips!\n";
        }
        p0.addChips(m_pot);
        return false;
    } else {
        cout << "\n\nEnding round when no one folds or wants to quit? How did you get here?\n\n";
        return true;
    }
}

/**
 * Current architecture supports player IDs 0 and 1 only
 * @param player
 * @return
 */
int Game::playerFolds(Player &player) {
    if(m_reportFlag) {
        cout << "Player " << player.getID() << " folds.\n";
    }
    return player.getID();
}

int Game::playerCalls(Player &player, int currentBet, int lastBet) {
    if(m_reportFlag) {
        cout << "Player " << player.getID() << " calls.\n";
    }
    call(player, currentBet, lastBet);

    return 2;
}

void Game::playerRaises(Player& player, int currentBet, int lastBet, int& raises) {
    if(m_reportFlag) {
        cout << "Player " << player.getID();
    }
    //call if there was a previous bet
    if(lastBet!=0){
        call(player,currentBet,lastBet);
        if(m_reportFlag) {
            cout << " calls and";
        }
    }
    //then raise
    if(m_reportFlag) {
        cout << " raises by " << (currentBet-lastBet) << ".\n";
    }
    m_pot += player.takeChips(currentBet-lastBet);
    ++raises;
}

void Game::call(Player &player, int currentBet, int lastBet) {
    if(m_betHistory.getCount()<2) { //if this player has not bet yet
        //player has not bet yet
        m_pot += player.takeChips(lastBet);     //lastBet is the other player's bet, need to match it
    } else {
        //(other player's last bet)-(this player's last bet)
        m_pot += player.takeChips((m_betHistory.getBet(m_betHistory.getCount()-1).getAmount())-(m_betHistory.getBet(m_betHistory.getCount()-2).getAmount()));
    }
}
