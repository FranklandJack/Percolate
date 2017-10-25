#include "Grid2D.hpp"
#include <iostream>
#include <chrono>
#include <random>

int main(int argc, char const *argv[])
{

    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator(seed);

    Grid2D myGrid(5,5,0.001,generator);

    std::cout << myGrid << std::endl;

    myGrid.printValues();
    while(myGrid.update())
    std::cout << std::endl;
    

    myGrid.printValues();



    int numberChanges = 1;

    
    std::cout << myGrid.test() << std::endl;
    

    return 0;
}