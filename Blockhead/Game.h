//Game.h

#pragma once

#include "PlayerType.h"
#include "Card.h"
#include "BetHistory.h"
#include "Player.h"

class Game {
private:
    static const int DECK_SIZE = 52;
    int m_pot;
    Card m_deck[DECK_SIZE];
    bool m_reportFlag;
    BetHistory m_betHistory;

    Player* initPlayer(PlayerType pType, int id, int &chips);
    bool playHand(Player& p0, Player& p1);
    void shuffleDeck();
    int betRound(Player& p0, Player& p1);
    void deckSetup();
    bool endRound(Player& p0, Player& p1, int roundResult);
    int playerFolds(Player& player);
    int playerCalls(Player& player, int currentBet, int lastBet);
    void playerRaises(Player& player, int currentBet, int lastBet, int& raises);
    void call(Player& player, int currentBet, int lastBet);

public:
    static const int MAX_RAISE = 10;
    bool playGame(PlayerType p0, PlayerType p1, int &chips0, int &chips1, bool reportFlag);

};