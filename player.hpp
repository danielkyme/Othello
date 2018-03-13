#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();


    Move *doMove(Move *opponentsMove, int msLeft);
    int getScore(Move *currentmove, Board* current_board);
    int minimax(Move *currentmove, int depth, bool maximizingPlayer, Board* current_board);
    Move * heuristic(int depth);
    std::vector<Move *> generate_moves(Move *opponentsMove, bool max, Board* current_board);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *newBoard;
    Side mySide;
    Side theirSide;
    bool timeLimit;
    
};

#endif
