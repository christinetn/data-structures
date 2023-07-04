

#ifndef MYMAZESOLVER_HPP
#define MYMAZESOLVER_HPP

#include "MazeSolver.hpp"
#include <vector>
#include <tuple>
#include <random>
#include "Direction.hpp"

using namespace std;

class MyMazeSolver : public MazeSolver

{
public:
    MyMazeSolver();
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
    void extendPath(const Maze& maze, int x, int y, MazeSolution& mazeSolution);
    std::tuple<int,int> getCellChosen(Direction randomDir, int x, int y,  MazeSolution& mazeSolution);
    Direction move(int chosenDir);
    
private:


    std::random_device device;
    std::default_random_engine engine{device()};
    std::vector<tuple<int,int>> trackMaze;
    std::vector<std::vector<bool>> visited;
};



#endif
