cmake_minimum_required(VERSION 3.15)
project(Blockhead)

set(CMAKE_CXX_STANDARD 14)

add_executable(Blockhead main.cpp Card.h Card.cpp Bet.cpp Bet.h Hand.h Hand.cpp BetHistory.h BetHistory.cpp PlayerType.h Player.h Player.cpp HumanPlayer.h HumanPlayer.cpp AlphaPlayer.cpp AlphaPlayer.h BetaPlayer.cpp BetaPlayer.h Game.cpp Game.h)