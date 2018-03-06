// git test1 daniel kymealdkfalksdfjad
// git ankusheas
#include "player.hpp"
#include <time.h>
#include <vector>
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    mySide = side;
    if(side == BLACK)
    {
        theirSide = WHITE;
    }
    else
    {
        theirSide = BLACK;
    }
    newBoard = new Board();


    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete newBoard;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    /*

     time_t begin_time;
     time_t curr_time;
     double diff_time;

     if (msLeft == -1) {
         timeLimit = 0;
     }
     else {
         timeLimit = 1;
     }

     if (timeLimit == 1) {
        time(&begin_time);
     }
     */ 

    int depth = 4;
    Move* best_move = new Move(0,0);

     newBoard->doMove(opponentsMove, theirSide);


     if(!newBoard->hasMoves(mySide) || newBoard->isDone())
     {
         return nullptr;
     }

     if (testingMinimax) {
        depth = 2;
     }



     best_move = heuristic(depth);

     newBoard->doMove(best_move, mySide);
     return best_move;

}

int Player::getScore(Move *currentmove, Board* &current_board)
{
    Board *temp = current_board->copy();
    current_board->doMove(currentmove, mySide);
    int score;
    if(mySide == WHITE)
    {
        score = current_board->countWhite() - current_board->countBlack();
    }
    else
    {
        score = current_board->countBlack() - current_board->countWhite();
    }

    //check if corner, dark green
    if((currentmove->getX() == 0 && currentmove->getY() == 0) || (currentmove->getX() == 7 && currentmove->getY() == 0)
        || (currentmove->getX() == 0 && currentmove->getY() == 7) || (currentmove->getX() == 7 && currentmove->getY() == 7))
    {
        score = score * 3;
    }
    // check dark red
    else if((currentmove->getX() == 1 && currentmove->getY() == 1) || (currentmove->getX() == 6 && currentmove->getY() == 1)
        || (currentmove->getX() == 1 && currentmove->getY() == 6) || (currentmove->getX() == 6 && currentmove->getY() == 6))
    {
        score = score * -3;
    }
    //check light red
    else if((currentmove->getX() == 1 && currentmove->getY() == 0) || (currentmove->getX() == 0 && currentmove->getY() == 1)
        || (currentmove->getX() == 6 && currentmove->getY() == 0) || (currentmove->getX() == 7 && currentmove->getY() == 1)
        || (currentmove->getX() == 6 && currentmove->getY() == 7) || (currentmove->getX() == 7 && currentmove->getY() == 6)
        || (currentmove->getX() == 6 && currentmove->getY() == 6) || (currentmove->getX() == 1 && currentmove->getY() == 7))
    {
        score = score * -2;
    }
    else if(currentmove->getX() == 0 || currentmove->getX() == 7 || currentmove->getY() == 0 || currentmove->getY() == 7 )
    {
        score = score * 2;
    }
    current_board = temp;
    return score;
}

int Player::minimax(Move *currentmove, int depth, bool maximizingPlayer, Board* current_board) {
    

    std::vector<Move *> possibleMoves, subset;
    possibleMoves = generate_moves(currentmove, maximizingPlayer, current_board);
    int best;

    if ((possibleMoves.size() == 0) || (depth == 0)) {
        return getScore(currentmove, current_board);
    }

    if (maximizingPlayer) {
        int bestValue = -10000;
        for (unsigned int i = 0; i < possibleMoves.size(); i++) {
            best = minimax(possibleMoves[i], depth - 1, !maximizingPlayer, current_board);
        }
        if (best > bestValue) {
            return best;
        }
        return bestValue;
    }

    else {
        int bestValue = 100000;
        for (unsigned int i = 0; i < possibleMoves.size(); i++) {
            best = minimax(possibleMoves[i], depth - 1, !maximizingPlayer, current_board);
        }
        if (best < bestValue) {
            return best;
        }
        return bestValue;
    }

}

Move * Player::heuristic(int depth) {
    std::vector<Move *> possibleMoves;
    std::vector<int> scores;    
    Move *mine = new Move(1, 1);
    int index;

     for(int i = 0; i < 8; i++)
     {
         for(int j = 0; j < 8; j++)
         {
             /*
             if (timeLimit == 1) {
                time(&curr_time);
                diff_time = difftime(curr_time, begin_time);

                if (diff_time > (double) (msLeft - 1)) {
                    return nullptr;
                }
             }
             */

             mine->setX(i);
             mine->setY(j);
             if(newBoard->checkMove(mine, mySide))
             {
                 Move *addmine = new Move(i, j);
                 possibleMoves.push_back(addmine);
                 Board *temp = new Board;
                 temp = newBoard->copy();
                 scores.push_back(minimax(possibleMoves.back(), depth, true, temp));
             }
         }
     }

     int max = -10000;
     for (unsigned int i = 0; i < scores.size(); i++) {
        if (scores[i] > max) {
            max = scores[i];
            index = i;
        }
     }

     return possibleMoves[index];
}

std::vector <Move *> Player::generate_moves(Move *currentMove, bool max_or_min, Board* &current_board) {
    
    if (max_or_min) {
        current_board->doMove(currentMove, mySide);   
    }
    else {
        current_board->doMove(currentMove, theirSide);
    }

    std::vector<Move *> possibleMoves;
    Move *mine = new Move(1, 1);

     for(int i = 0; i < 8; i++)
     {
         for(int j = 0; j < 8; j++)
         {
             /*
             if (timeLimit == 1) {
                time(&curr_time);
                diff_time = difftime(curr_time, begin_time);

                if (diff_time > (double) (msLeft - 1)) {
                    return nullptr;
                }
             }
             */

             mine->setX(i);
             mine->setY(j);
             if(current_board->checkMove(mine, mySide))
             {
                 Move *addmine = new Move(i, j);
                 possibleMoves.push_back(addmine);
             }
         }
     }

    return possibleMoves;

}