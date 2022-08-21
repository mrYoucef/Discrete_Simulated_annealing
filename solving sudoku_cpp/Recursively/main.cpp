
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <random>

typedef std::vector<std::vector<unsigned char>> Game;

unsigned int checkCell(const Game & game, int col, int row, int value)
{
    //check row
    for(int i = 0 ; i < game.size() ; i++)
    {
        if(game.at(i).at(row) == value && i != col)
            return 0;
    }

    //check colome
    for(int i = 0 ; i < game.size() ; i++)
    {
        if(game.at(col).at(i) == value && i != row)
            return 0;
    }

    //check block 3x3
    int blockRow = row /3;
    int blockCol = col /3;

    for(int i = blockRow * 3 ; i < blockRow * 3 + 3 ; i++)
    {
        for(int j = blockCol * 3 ; j < blockCol * 3 + 3 ; j++)
        {
            if(game.at(j).at(i) == value && !(i == row && j == col))
                return 0;
        }
    }
    return 1;
}


void print_matrix(const Game & matrix)
{
    for(int i = 0 ; i < matrix.size();i++)
    {
        std::cout <<std::endl;
        if(i % 3==0)
            std::cout << "---------------------" << std::endl;

        for(int j =0; j< matrix.at(i).size();j++)
        {
            if( j % 3== 0)
                std::cout << "|";
            std::cout << matrix.at(i).at(j) + 0 << " ";
        }

    }
}

bool solver(Game & game , int cellNumber)
{
    int row = cellNumber%9;
    int col = cellNumber/9;
    //print_SelectedSol(game);
    if(cellNumber > 80)
        return true;

    if(game.at(col).at(row)!= 0)
        return solver(game, cellNumber+1);

    for(int i = 1  ; i <  10; i++)
    {
        if(checkCell(game, col , row , i))
        {
            game.at(col).at(row)= i;
            if(solver(game, cellNumber+1))
            {
                return true ;
            }
             game.at(col).at(row) = 0;
        }
    }


    game.at(col).at(row) = 0;
    return false;


}

int main(int argc, char *argv[])
{
    std::vector<std::vector<unsigned char>> matrix= {{0,3,0 ,1,0,0, 0,0,8},
                                                    {0,0,0 ,0,0,5, 0,4,9},
                                                    {0,0,0 ,0,0,0, 0,0,6},

                                                    {0,0,0 ,3,2,0, 0,6,0},
                                                    {0,0,7 ,0,0,0, 0,0,2},
                                                    {0,0,0 ,0,1,4, 0,9,0},

                                                    {3,7,0 ,0,5,8, 0,0,0},
                                                    {0,0,1 ,7,4,0, 0,0,5},
                                                    {5,0,6 ,0,0,0, 0,0,0}};

    std::vector<std::vector<unsigned char>> matrix2= {{0,0,0 ,5,0,0, 0,0,0},
                                                     {8,5,0 ,0,0,0, 0,0,0},
                                                     {4,0,7 ,0,1,6, 5,0,0},

                                                     {0,0,5 ,0,0,8, 0,0,0},
                                                     {0,0,0 ,0,6,0, 0,0,5},
                                                     {0,6,0 ,2,0,7, 0,0,3},

                                                     {0,7,8 ,0,0,0, 0,2,0},
                                                     {0,2,3 ,0,9,0, 7,0,0},
                                                     {0,9,0 ,0,0,0, 0,6,0}};

    std::vector<std::vector<unsigned char>> matrix3= {{0,0,0 ,7,0,0, 0,2,0},
                                                     {3,0,0 ,0,0,0, 0,8,1},
                                                     {0,5,1 ,0,0,0, 0,0,0},

                                                     {7,2,0 ,6,4,0, 0,0,0},
                                                     {9,0,0 ,0,0,0, 5,0,7},
                                                     {4,0,0 ,5,7,0, 8,0,2},

                                                     {0,9,0 ,2,0,1, 0,0,0},
                                                     {0,4,0 ,0,0,0, 0,0,0},
                                                     {0,0,8 ,0,0,4, 0,0,0}};





    print_matrix(matrix3);
    const auto start =std::chrono::system_clock::now();
    solver(matrix3,0);
    const auto end = std::chrono::system_clock::now();
    print_matrix(matrix3);

    std::cout << std::endl << "solved in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us                                                                                   s" ;


    return 0;
}
