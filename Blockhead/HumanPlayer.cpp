//HumanPlayer.cpp

/**
 * This is a derived class of Player that presents domain information to the current
 * human player through I/O and then allows the player to input their bet. Code should
 * be implemented both to communicate to the game player the current status of the game
 * (i.e. current hands showing, pot, bet history, etc.) and to validate the bets of the
 * human player before returning the proper bet value. This uses the getBet() method.
 */

#include <iostream>
#include "HumanPlayer.h"
#include "Game.h"

using namespace std;

HumanPlayer::HumanPlayer(int id, int chips) {
    m_id = id;
    m_chips = chips;
}

int HumanPlayer::getBet(Hand opponent, BetHistory bh, int bet2player, bool canRaise, int pot) {
    Hand opponentVisible = opponent.getVisible();

    cout << "Player " << m_id << "\'s turn\n";
    cout << "-----------------------------\n";

    //display opponent's visible hand
    cout << "OPPONENT\'S HAND:\n";
    for(int i=0; i<opponentVisible.getCount(); ++i) {
        cout << "\t" << opponentVisible.getCard(i).getName() << "\n";
    }

    //display player's hand
    cout << "\nYOUR HAND:\n";
    for(int i=0; i<m_hand.getCount(); ++i) {
        cout << "\t" << m_hand.getCard(i).getName();
        if(!m_hand.getCard(i).isFaceup()) { //let the player know which card is facedown
            cout << " - FACE-DOWN";
        }
        cout << "\n";
    }

    //display pot
    cout << "\nPOT:        " << pot << "\n";
    cout <<   "BET TO YOU: " << bet2player << "\n";

    //print user's options and get input
    int userBet = userIO(bh, bet2player, canRaise);

    cout << "-----------------------------\n";

    if(userBet == -1) {  //someone wants to quit
        return -1;
    } else {
        return (userBet);
    }

}

/**
 * if bet2player==0, bet instead of raise, check instead of call
 * player cannot call if previous bet was a check
 * player can only raise if canRaise==true
 * @param bh
 * @param bet2player
 * @param canRaise
 * @return
 */
int HumanPlayer::userIO(BetHistory bh, int bet2player, bool canRaise) {
    string strIn = ""; //dummy value for looping
    int betMax = bet2player + Game::MAX_RAISE;
    int    intIn = -50;//dummy value for looping
    if(bh.getCount()==0 && bet2player==0) {     //no prior bets, can check
        cout << "[" << bet2player+1 << "-" << betMax << "]: Bet 1-" << betMax << " chips.\n";
        cout << "[0]:  Check.\n";
        cout << "[-1]: Quit.\n";
        while(intIn!=-1 && intIn!=0 && (intIn>betMax || intIn<-1)) {
            cout << "> ";
            getline(cin, strIn);
            try {
                intIn = stoi(strIn);
            } catch(exception& e) {
                cout << "Invalid Input";
            }
            cout << "\n";
        }
    } else if (bet2player==0) {     //check to player, cannot call
        cout << "[" << bet2player+1 << "-" << betMax << "]: Bet 1-" << betMax << " chips.\n";
        cout << "[-1]: Quit.\n";
        while(intIn<-1 || intIn==0 || intIn>betMax) {
            cout << "> ";
            getline(cin, strIn);
            try {
                intIn = stoi(strIn);
            } catch(exception& e) {
                cout << "Invalid Input";
            }
            cout << "\n";
        }
    } else if(canRaise){     //raise to player, can raise
        cout << "[" << bet2player+1 << "-" << betMax << "]: Call and raise 1-" << Game::MAX_RAISE << " chips.\n";
        cout << "[" << bet2player << "]: Call.\n";
        cout << "[0]:  Fold.\n";
        cout << "[-1]: Quit.\n";
        while(intIn!=-1 && intIn!=0 && (intIn<bet2player || intIn>betMax)) {
            cout << "> ";
            getline(cin, strIn);
            try {
                intIn = stoi(strIn);
            } catch(exception& e) {
                cout << "Invalid Input";
            }
            cout << "\n";
        }
    } else {     //raise to player, cannot raise
        cout << "[" << bet2player << "]: Call.\n";
        cout << "[0]:  Fold.\n";
        cout << "[-1]: Quit.\n";
        while(intIn!=-1 && intIn!=0 && intIn!=bet2player) {
            cout << "> ";
            getline(cin, strIn);
            try {
                intIn = stoi(strIn);
            } catch(exception& e) {
                cout << "Invalid Input";
            }
            cout << "\n";
        }
    } //end if-else

    return intIn;
}
