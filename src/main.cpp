#include "Grid2D.hpp"
#include <iostream>
int main(int argc, char const *argv[])
{
    Grid2D myGrid(5,5,0.0);

    int numberChanges = 1;

    while(myGrid.update());
    std::cout << myGrid.test() << std::endl;
    

    return 0;
}