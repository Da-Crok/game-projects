//BetHistory.h

#pragma once

#include <vector>
#include "Bet.h"

class BetHistory {
private:
    std::vector<Bet> history;

public:
    void clearHistory();
    void addBet(Bet);
    int getCount();
    Bet getBet(int);

};