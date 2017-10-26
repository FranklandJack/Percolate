#include "Grid2D.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <sstream>

int main(int argc, char const *argv[])
{
    auto start = std::chrono::system_clock::now();

    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);


    // The parameters for the grid will be read from the file which is provided as the first command line argument.
    std::ifstream oscillatorParameters(argv[1]);
    
    // Check we have sucessfully opened the file. 
    if(!oscillatorParameters)
    {
        std::cerr << argv[1] << " could not be opened for reading" <<std::endl;
    }
    
    // First line in file should be the number of rows, the second the columns, the third the density.
    int rows, columns;
    double density; 

    oscillatorParameters >> rows >> columns >> density;
    
    // The number of trials for this run of the program should be the second command line argument.
    std::istringstream ss(argv[2]);

    int trials;

    if(!(ss >> trials))
    {
        std::cerr << "invalid trial number: " << argv[3] << std::endl;
        exit(1);
    }


    // Value to hold the number of trial grids that sucessfully percolate. 
    int percolations = 0;


    // Generate the given number of grids and if they sucessfully percolate we record it.

    for(int iteratrion = 0; iteratrion < trials; ++iteratrion)
    {

    Grid2D myGrid(rows, columns, density, generator);
    

    while(myGrid.update()){}
    
    if(myGrid.test()) 
    {
        ++percolations;
    }
    }


    double probablity = static_cast<double>(percolations)/trials;
    
    std::cout << "The probablity of percolating for a " << rows << " x " << columns << " grid with density " 
    << density << " is " << probablity << std::endl;

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time take to execute (us):   " << elapsed.count() << std::endl << std::endl; 
    

    return 0;
}