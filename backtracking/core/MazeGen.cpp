

#include <ics46/factory/DynamicFactory.hpp>
#include "MazeGen.hpp"
#include <iostream>
#include <string>
#include <algorithm>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator,Generator,"My Maze Generator (Required)");

Generator::Generator()
{


}


Direction move(int chosenDir)
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



tuple<int,int> Generator::getCellChosen(Direction randomDir, int x, int y)
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


int Generator::chooseDir(std::vector<int>valid)
{
    int chosenDir = 0;
    std::uniform_int_distribution <int> distribution{1,4};
    
    while (chosenDir == 0)
    {
         for (int i = 0; i < 1; ++i)
            {
                int value = distribution(engine);
                if (std::find(valid.begin(),valid.end(),value) != valid.end())
                {
                    chosenDir = value;
                    return chosenDir;
                }
            }
    }
    return chosenDir;

}


void Generator::movePath(Maze& maze, int x, int y)
{
    visited[x][y] = true;
   
    std::vector<int> validDir;

    do
    {
        //check 4 directions
        validDir.clear();


        if ( y-1 >= 0 && visited[x][y-1] == false ) //up
            {
                validDir.push_back(1);
            }
        if (y < maze.getHeight() -1  && visited[x][y+1] == false ) //down
            {
                validDir.push_back(2);
            }
        if (x-1 >= 0 && visited[x-1][y] == false) //left
            {
                validDir.push_back(3);
            }
        if (x < maze.getWidth() -1  && visited[x+1][y] == false) //right
            {
                validDir.push_back(4);
            }

        //base case

        if (validDir.size() == 0 )
        {
            return;
        }

        if (validDir.size() > 0)
        {
            int value = chooseDir(validDir);

            //choose unvisited adjacent cells at random
            Direction randomDir = move(value);
            //find new cell
            tuple<int,int>newCell = getCellChosen(randomDir,x,y);

            int cellChosenX = get<0>(newCell);
            int cellChosenY = get<1>(newCell);

            //remove wall between current cell and cell chosen
            
            maze.removeWall(x,y,randomDir);

            //recursively call, with chosen cell becoming current cell
            movePath(maze,cellChosenX,cellChosenY);
        }
       
    } while (validDir.size() > 0 );


}



void Generator::generateMaze(Maze& maze)
{ 
    maze.addAllWalls();
    visited.resize(maze.getWidth(),std::vector<bool>(maze.getHeight(),false));
    visited[0][0] = true; //current visited cell
    movePath(maze,0,0);

}

