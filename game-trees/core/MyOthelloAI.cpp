#include <ics46/factory/DynamicFactory.hpp>
#include "MyOthelloAI.hpp"
#include <vector>
#include <iostream>
ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, ctnguy20::MyOthelloAI, "NguOthelloAI(Required)");



std::pair<int, int> ctnguy20::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
    int bestEval = -9999;
    std::pair<int, int> bestM;
    int turn;

    if (state.isWhiteTurn())
    {
        turn = 0;
    }

    else
    {
        turn = 1;
    }
   
    for (int w = 0; w < state.board().width(); w++)
    {
        for (int h = 0; h < state.board().height(); h++)
        {
            if (state.isValidMove(w,h))
            {
                std::unique_ptr<OthelloGameState> cloneS = state.clone();
                cloneS -> makeMove(w,h);
                int current = search(*cloneS, 3, turn);

                if (current >= bestEval)
                {
                    bestEval= current;
                    bestM = std::pair(w,h);
                }
            }
        }
    }
    return bestM;    
}



int ctnguy20::MyOthelloAI::eval(const OthelloGameState& state, int color)
{
    
    if (color == 1)
    {
        return state.blackScore() - state.whiteScore();
    }
    else
    {
        return state.whiteScore() - state.blackScore();
    }

    return 0;
}


int ctnguy20::MyOthelloAI::search(const OthelloGameState& s, int depth, int turn)
{
    if (s.isGameOver())
    {
        return eval(s,turn);
    }

    if (depth==0)
    {
        return eval(s,turn);
    }

    else
    {
        int myTurn = -9999;
        int oppTurn = 9999;

        if (turn == 0 && s.isWhiteTurn()) 
        {
            for (int w = 0; w < s.board().width(); w++)
            {
                for (int h = 0; h < s.board().height(); h++)
                {
                    if (s.isValidMove(w,h))
                    {
                        std::unique_ptr<OthelloGameState> cloneS = s.clone();
                        cloneS -> makeMove(w,h);
                        int curr = search(*cloneS, turn, depth-1);
                        if (myTurn < curr)
                        {
                              myTurn = curr; 
                        }
                    }
                }        
            }
            return myTurn;
        }
        else 
        {
            for (int w = 0; w < s.board().width(); w++)
            {
                for (int h = 0; h < s.board().height(); h++)
                {
                    if (s.isValidMove(w,h))
                    {
                        std::unique_ptr<OthelloGameState> cloneS = s.clone();
                        cloneS -> makeMove(w,h);
                        int curr = search(*cloneS, turn, depth-1);
                        if (oppTurn > curr)
                            {
                                oppTurn = curr;
                            }
                    }  
                }   
            }
            return oppTurn;
        }     
    }
}



std::vector<std::pair<int,int>> ctnguy20::MyOthelloAI::validMoves(const OthelloGameState& gameS, const OthelloBoard& board)
{
    std::vector<std::pair<int,int>> places;
    for (int w = 0; w < board.width(); w ++)
    {
        for (int h = 0; h < board.height(); h++)
        {
            if (gameS.isValidMove(w,h))
            {
                places.push_back(std::pair<int,int> (w,h));
            }
        }
    }
    return places;
}