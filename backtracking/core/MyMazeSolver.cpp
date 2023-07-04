

#include <ics46/factory/DynamicFactory.hpp>
#include "MyMazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <tuple>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver,MyMazeSolver,"My Maze Solver (Required)");

MyMazeSolver::MyMazeSolver()
{


}


Direction MyMazeSolver::move(int chosenDir)
{
    if (chosenDir == 1)
    {
        return Direction::up;
    }
    else if (chosenDir == 2)
    {
        return Direction::down;
    }
    else if (chosenDir == 3)
    {
        return Direction::left;
    }
    else
    {
        return Direction::right;
    }
}


std::tuple<int,int> MyMazeSolver::getCellChosen(Direction randomDir, int x, int y,  MazeSolution& mazeSolution)
{
   if (randomDir == Direction::up)
   {
       y = y-1;
       return {x,y};
   }
   else if (randomDir == Direction::down)
   {
       y = y + 1;
       return {x,y};
   }

   else if (randomDir == Direction::left)
   {
       x = x-1;
       return {x,y};
   }
   else
   {
       x = x + 1;
       return {x,y};
   }

}



void MyMazeSolver::extendPath(const Maze& maze, int x, int y, MazeSolution& mazeSolution)
{
   
    visited[x][y] = true; //current visited cell

    if (!(mazeSolution.isComplete()))
    {
        //check if theres no wall, check if its a wall visited 
        if (  (!maze.wallExists(x,y,move(1))) && visited[x][y-1] == false ) //up
                {
                    mazeSolution.extend(move(1));
                    extendPath(maze, mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second,mazeSolution);

                }
        else if ((!maze.wallExists(x,y,move(2))) && visited[x][y+1] == false ) //down
                {
                    mazeSolution.extend(move(2));
                    extendPath(maze, mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second,mazeSolution);
                
                }
        else if ( (!maze.wallExists(x,y,move(3))) && visited[x-1][y] == false) //left
                {
                    mazeSolution.extend(move(3));
                    extendPath(maze, mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second,mazeSolution);
                }
        else if ( (!maze.wallExists(x,y,move(4))) && visited[x+1][y] == false) //right
                {
                    mazeSolution.extend(move(4));
                    extendPath(maze, mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second,mazeSolution);

                }
        
        else if (mazeSolution.getStartingCell().first != mazeSolution.getCurrentCell().first || mazeSolution.getStartingCell().second != mazeSolution.getCurrentCell().second)

        {   
                mazeSolution.backUp();
                extendPath(maze, mazeSolution.getCurrentCell().first,mazeSolution.getCurrentCell().second,mazeSolution);
        }
        else
        {
             return;       
        }
    }
    else
    {
        return;
    }
}



void MyMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{ 
    mazeSolution.restart();
    visited.resize(maze.getWidth(),std::vector<bool>(maze.getHeight(),false));
    std::tuple<int,int> startCell = mazeSolution.getStartingCell();
    visited[get<0>(startCell)][get<1>(startCell)] = true; //current visited cell
    extendPath(maze,get<0>(startCell), get<1>(startCell),mazeSolution);
}


