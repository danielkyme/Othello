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
     std::vector<Move *> possibleMoves;
     std::vector<int> scores;

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



     newBoard->doMove(opponentsMove, theirSide);
     if(!newBoard->hasMoves(mySide) || newBoard->isDone())
     {
         return nullptr;
     }
     Move *mine = new Move(1, 1);

     for(int i = 0; i < 8; i++)
     {
         for(int j = 0; j < 8; j++)
         {
             if (timeLimit == 1) {
                time(&curr_time);
                diff_time = difftime(curr_time, begin_time);

                if (diff_time > (double) (msLeft - 1)) {
                    return nullptr;
                }
             }

             mine->setX(i);
             mine->setY(j);
             if(newBoard->checkMove(mine, mySide))
             {
<<<<<<< HEAD
                 std::cerr << mine->getX() << mine->getY() << std::endl;
                 possibleMoves.push_back(mine);
                 std::cerr << possibleMoves[0]->getX() << possibleMoves[0]->getY() << std::endl;
                 int s = getScore(mine);
                 std::cerr << possibleMoves[0]->getX() << possibleMoves[0]->getY() << std::endl;
                 score.push_back(s);
                 std::cerr << possibleMoves[0]->getX() << possibleMoves[0]->getY() << std::endl;
                 Move *addmine = new Move(i, j);
                 possibleMoves.push_back(addmine);

                 int s = getScore(addmine);
                 scores.push_back(s);
             }
         }
     }
     int max = -10000;
     int index;

     for(unsigned int i = 0; i < scores.size(); i++)
     {
         if(scores[i] > max)
         {
             max = scores[i];
             index = i;
         }
     }

     newBoard->doMove(possibleMoves[index], mySide);
     return possibleMoves[index];


}

int Player::getScore(Move *currentmove)
{
    Board *temp = newBoard->copy();
    newBoard->doMove(currentmove, mySide);
    int score;
    if(mySide == WHITE)
    {
        score = newBoard->countWhite() - newBoard->countBlack();
    }
    else
    {
        score = newBoard->countBlack() - newBoard->countWhite();
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
    newBoard = temp;
    return score;
}
