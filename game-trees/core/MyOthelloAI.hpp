#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP
#include <vector>
#include  "OthelloAI.hpp"

namespace ctnguy20
{
    class MyOthelloAI: public OthelloAI
    {
    public:
    
        virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
        int eval(const OthelloGameState& state, int color);
        std::vector<std::pair<int,int>> validMoves(const OthelloGameState& gameS, const OthelloBoard& board);
        int search(const OthelloGameState& state, int depth, int turn);
        std::pair<int,int> getHighest(int current,int best, std::pair<int,int> bestM, int w, int h);
    
    };

}

#endif