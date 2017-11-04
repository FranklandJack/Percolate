#include "Grid2D.hpp"
#include <iostream>
#include <chrono>   
#include <sstream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

int main(int argc, char const *argv[])
{
    /*************************************************************************************************************************
     ************************************************* Preparations **********************************************************
     *************************************************************************************************************************/

    // Start the clock so execution time can be calculated. 
    auto start = chrono::system_clock::now();

    // Seed the pseudo random number generator using the system clock.
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());

    // Create a generator that can be fed to any distribution to produce pseudo random numbers according to that distribution. 
    default_random_engine generator(seed);


    /*************************************************************************************************************************
     ******************************************************** Input **********************************************************
     *************************************************************************************************************************/

    // Value to hold the number of rows in the grid.
    int rowCount;

    // Value to hold the number of columns in the grid.
    int colCount;

    // Value to hold the specified density of the grid.
    double density;

    // Value to hold the number of percolation trials.
    int triCount;

    // Set up optional command line argument.
    po::options_description desc("Options for percolation test program");

    desc.add_options()
        // Option 'row-number' and 'r' are equivalent.
        ("row-count,r", po::value<int>(&rowCount)->default_value(100), "The number of rows")
        // Option 'col-number' and 'c' are equivalent.
        ("col-count,c", po::value<int>(&colCount)->default_value(100), "The number of columns")
        // Option 'density' and 'd' are equivalent.
        ("density,d", po::value<double>(&density)->default_value(0.5), "The density of grid")
        // Option 'trial-number' and 'n' are equivalent.
        ("trial-count,n", po::value<int>(&triCount)->default_value(1000), "The number of trials");

    po::variables_map vm;
    po::store(po::parse_command_line(argc,argv,desc), vm);
    po::notify(vm);


    /*************************************************************************************************************************
     ********************************************** Algorithm Stage **********************************************************
     *************************************************************************************************************************/


    // Value to hold the number of trial grids that successfully percolate. 
    int percolations = 0;

    // Generate the given number of grids and if they successfully percolate we record it.
    for(int trial = 0; trial < triCount; ++trial)
    {
        // Construct a new random grid on each trial.
        Grid2D myGrid(rowCount, colCount, density, generator);
    
        // Update the grid until it has finished. 
        while(myGrid.update()){}
        
        // If the grid percolates it is recorded. 
        if(myGrid.test()) 
        {
            ++percolations;
        }
    }

    // Monte-Carlo estimate on the probability of percolation.
    double probablity = static_cast<double>(percolations)/triCount;


    /*************************************************************************************************************************
     ****************************************************** Output  **********************************************************
     *************************************************************************************************************************/
    
    cout << probablity << endl;

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start);
    //cout << "Time take to execute (us):   " << elapsed.count() << endl << endl; 
    

    return 0;
}