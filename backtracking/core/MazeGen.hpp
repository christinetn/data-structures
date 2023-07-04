#ifndef MAZEGEN_HPP
#define MAZEGEN_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <vector>
#include <tuple>
#include <random>
#include "Direction.hpp"
using namespace std;

class Generator: public MazeGenerator

{
public:
    Generator();
    void generateMaze(Maze& maze) override;
    void movePath(Maze& maze, int x, int y);
    int chooseDir(std::vector<int>valid);
    tuple<int,int> getCellChosen(Direction randomDir, int x, int y);
    Direction randomDirection(int x, int y);


private:
    std::random_device device;
    std::default_random_engine engine{device()};
    std::vector<tuple<int,int>> trackMaze;
    std::vector<std::vector<bool>> visited;



};




#endif