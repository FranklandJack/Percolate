# Percolate
Programs to calculate the probability of percolating through a grid of a given size and density.


## Introduction
It is considered possible to percolate through a grid if it is possible to get from the top of the grid to the bottom by moving through neighbouring empty cells. Cells are considered neighbours if they are touching vertically or adjacently i.e. diagonally touching cells are not considered neighbours.

The algorithm for testing for percolation is as follows:
1. Initialise each empty empty cell in the grid with a unique positive integer.
2. Loop over every empty cell in the grid and replace the number assigned to that cell with the maximum of the numbers associated with each of its empty neighbouring cells.
3. Repeat step 2 until the numbers associated with each cell stop changing. 
4. Each cluster (set of cells that can all be reached from one another by moving through neighbouring empty cells) will now contain a unique number; if the same number appears at the top and bottom of the grid, they are in the same cluster and it is therefore possible to percolate through the grid.   

Initially this will only be for 2D grids. Once this is working and tested I will try it for 3D grids.

## Instructions 

- To build run:  ```$ make```.
- To run run: ```$ ./percolate  r c d n```.
where: 
	1. r = number of rows.
	2. c = number of columns.
	3. d = density of grid (0 < d < 1).
	4. n = number of trail grids to check percolation for at specified density.

- To build and run tests run:  ```$ make test ```.
- For a full list of make functionality run: ```$ make help ```.
- To generate documentation run: ```$ doxygen Doxyfile ```.


## Output
The executable will print the probability of percolating through a grid of the specified size and density. 

## Progress
- [x] source code
- [x] bash tool
- [x] plot tool
- [x] make file
- [ ] unit tests
- [ ] continuous integration
- [x] documentation
