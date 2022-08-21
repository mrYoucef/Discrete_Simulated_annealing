#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <math.h>
#include <cstdlib>
#include <chrono>
#include <random>
struct Cell
{
    unsigned int solution = 0;
    bool given = false;
};

typedef std::vector<std::vector<Cell>> Game;

void print_matrix(const std::vector<std::vector<Cell>> & matrix)
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
            std::cout << matrix.at(i).at(j).solution<< " ";
        }

    }
}

void fillTheBoard(Game & game)
{
    int numbers [9];
    for(int i = 0 ; i< 9 ; i++)
        numbers[i] = 9;

    for(int i = 0 ; i < game.size();i++)
    {
        for(int j =0; j< game.at(i).size();j++)
        {
            if(game.at(i).at(j).given)
                numbers[game.at(i).at(j).solution - 1] --;
        }

    }


    for(int i = 0 ; i < game.size();i++)
    {
        for(int j =0; j< game.at(i).size();j++)
        {
            if(!game.at(i).at(j).given)
            {
                int rand;
                do
                {
                    rand = std::rand() % 9;
                }
                while(numbers[rand] == 0);
                game.at(i).at(j).solution = rand+1;
                numbers[rand] --;
            }
        }

    }

}

unsigned int checkDuplicates(const Game & game, int col, int row, int value)
{
    int duplicates = 0 ;
    //check row
    for(int i = 0 ; i < game.size() ; i++)
    {
        if(game.at(i).at(row).solution == value && i != col)
            duplicates++;
    }

    //check colome
    for(int i = 0 ; i < game.size() ; i++)
    {
        if(game.at(col).at(i).solution == value && i != row)
            duplicates ++;
    }

    //check block 3x3
    int blockRow = row /3;
    int blockCol = col /3;

    for(int i = blockRow * 3 ; i < blockRow * 3 + 3 ; i++)
    {
        for(int j = blockCol * 3 ; j < blockCol * 3 + 3 ; j++)
        {
            if(game.at(j).at(i).solution == value && !(i == row && j == col))
                duplicates = duplicates+2;
        }   }
    return duplicates;
}

float calculate_energy(const Game & game)
{
    int eng = 0;
    for(int i = 0 ; i < game.size();i++)
    {
        for(int j =0; j< game.at(i).size();j++)
        {
            Cell cell  = game.at(i).at(j);
            eng += checkDuplicates(game,i,j,cell.solution);
        }
    }
    return float(eng);
}

void swap2RandomCells(Game & game)
{
    int row1 ;
    int col1 ;
    int row2 ;
    int col2 ;

    do
    {
        row1 = rand()% 9 ;
        col1 = rand()% 9 ;
    }
    while(game.at(col1).at(row1).given);
    do
    {
        row2 = rand()% 9 ;
        col2 = rand()% 9 ;
    }
    while(game.at(col2).at(row2).given);

    unsigned int temp =  game.at(col1).at(row1).solution;
    game.at(col1).at(row1).solution = game.at(col2).at(row2).solution ;
    game.at(col2).at(row2).solution = temp;

}

float calculate_t0(const Game & game, float th)
{
    Game new_game = game ;
    float delta = 0 ;
    for(int i = 0 ; i < 100 ; i++ )
    {
        float e = calculate_energy(new_game);
        swap2RandomCells(new_game);
        delta += abs(e - calculate_energy(new_game));
    }

    return -delta/100/log(th);
}

float calculate_probability(float deltaEng, float temp)
{
    return exp(-deltaEng/temp);
}

Game convertData(const std::vector<std::vector<unsigned int>> & matrix)
{
    std::vector<std::vector<Cell>> converted ;
    for(int i = 0 ; i < matrix.size();i++)
    {
        std::vector<Cell> cellRoW;

        for(int j =0; j< matrix.at(i).size();j++)
        {
            Cell cell;
            cell.solution = matrix.at(i).at(j);
            if(cell.solution > 0)
                cell.given = true;
            else
                cell.given = false;

            cellRoW.push_back(cell);
        }
        converted.push_back(cellRoW);
    }
    return converted;
}

int main(int argc, char *argv[])
{
    std::vector<std::vector<unsigned int>> matrix= {{0,3,0 ,1,0,0, 0,0,8},
                                                    {0,0,0 ,0,0,5, 0,4,9},
                                                    {0,0,0 ,0,0,0, 0,0,6},

                                                    {0,0,0 ,3,2,0, 0,6,0},
                                                    {0,0,7 ,0,0,0, 0,0,2},
                                                    {0,0,0 ,0,1,4, 0,9,0},

                                                    {3,7,0 ,0,5,8, 0,0,0},
                                                    {0,0,1 ,7,4,0, 0,0,5},
                                                    {5,0,6 ,0,0,0, 0,0,0}};

    std::vector<std::vector<unsigned int>> matrix2= {{0,0,0 ,5,0,0, 0,0,0},
                                                     {8,5,0 ,0,0,0, 0,0,0},
                                                     {4,0,7 ,0,1,6, 5,0,0},

                                                     {0,0,5 ,0,0,8, 0,0,0},
                                                     {0,0,0 ,0,6,0, 0,0,5},
                                                     {0,6,0 ,2,0,7, 0,0,3},

                                                     {0,7,8 ,0,0,0, 0,2,0},
                                                     {0,2,3 ,0,9,0, 7,0,0},
                                                     {0,9,0 ,0,0,0, 0,6,0}};

    std::vector<std::vector<unsigned int>> matrix3= {{0,0,0 ,7,0,0, 0,2,0},
                                                     {3,0,0 ,0,0,0, 0,8,1},
                                                     {0,5,1 ,0,0,0, 0,0,0},

                                                     {7,2,0 ,6,4,0, 0,0,0},
                                                     {9,0,0 ,0,0,0, 5,0,7},
                                                     {4,0,0 ,5,7,0, 8,0,2},

                                                     {0,9,0 ,2,0,1, 0,0,0},
                                                     {0,4,0 ,0,0,0, 0,0,0},
                                                     {0,0,8 ,0,0,4, 0,0,0}};


    Game game = convertData(matrix);
    print_matrix(game);
    fillTheBoard(game);
    print_matrix(game);

    std::cout << calculate_t0(game,0.5);

    int N=1000; //thermodynamic equilibrium
    int Ni_e=0; // Ni_e total number of accepted transformations
    int Ni_a=0;  // Ni_a total number of preformed transforamtions

    int Na_max=12*N; //number of accepted transformations
    int Ne_max=100*N; //number of preformed transforamtions

    int Na=0;  //to compute the accepted transformations
    int Ne=0;  //to compute preformed transformations
    int N0=0;  //to check the if the system didn't change
    float E_old=0; //to do energie comparisons
    float tho = 0.9;

    float T= calculate_t0(game,tho);
    float E=calculate_energy(game);

    unsigned int itiaraions = 0 ;

    const auto start =std::chrono::system_clock::now();

    while(N0 < 3 && E != 0)
    {
        itiaraions++;
        // changing a random cell
        int row1 ;
        int col1 ;
        int row2 ;
        int col2 ;

        do
        {
            row1 = rand()% 9 ;
            col1 = rand()% 9 ;
        }
        while(game.at(col1).at(row1).given);
        do
        {
            row2 = rand()% 9 ;
            col2 = rand()% 9 ;
        }
        while(game.at(col2).at(row2).given);

        unsigned int temp =  game.at(col1).at(row1).solution;
        game.at(col1).at(row1).solution = game.at(col2).at(row2).solution ;
        game.at(col2).at(row2).solution = temp;
        float E_new=calculate_energy(game);
        Ne=Ne+1;
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if (E_new < E||calculate_probability(E_new-E,T)>r)
        {
            Na=Na+1;
            E=E_new;
        }
        else
        {
            game.at(col2).at(row2).solution = game.at(col1).at(row1).solution ;
            game.at(col1).at(row1).solution = temp;
        }

        if(Na >= Na_max  || Ne>=Ne_max)
        {
            Ni_e=Ni_e+Ne;
            Ni_a=Ni_a+Na;
            Na=0;
            Ne=0;

            if(E_old==E)
                N0=N0+1;
            else
            {
                N0=0;
                T=0.9*T;
            }
            E_old=E;
        }
    }

    const auto end = std::chrono::system_clock::now();
    print_matrix(game);
    if(E)
        std::cout << std::endl << "solved in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us                                                                                   s" ;
    else
        std::cout << std::endl << "no solution found";
    return 0;
}
