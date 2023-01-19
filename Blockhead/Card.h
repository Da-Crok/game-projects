//Card.h

# pragma once

#include <string>

class Card {
private:
    std::string m_cardName;
    int m_cardValue;
    bool m_isFaceup;

public:
    Card();
    Card(std::string cardName, int cardValue);
    std::string getName();
    int getValue();
    bool isFaceup();
    void setFaceup(bool isFaceup);


};