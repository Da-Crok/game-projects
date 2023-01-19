//BetHistory.cpp

#include <vector>
#include "BetHistory.h"
#include "Bet.h"

using namespace std;

void BetHistory::clearHistory() {
    history.clear();
}

void BetHistory::addBet(Bet bet) {
    history.push_back(bet);
}

int BetHistory::getCount() {
    return history.size();
}

Bet BetHistory::getBet(int n) {
    return history.at(n);
}
