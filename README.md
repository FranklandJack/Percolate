# Percolate
Program to calculate the probability of percolating through a grid of a given size and density.


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

- To run:

	1. To run for a single density run any combination of: ```$ ./percolate  -r #rows -c #columns -d density -n #trials```
	and
	```$ ./percolate  --row-count #rows --column-count #columns --density density --trial-count #trials```

		where: 
			If any command line argument is not specified then the default values below will be used:
				1. #rows = 10
				2. #columns = 10
				3. density = 0.5
				4. #trials = 100

	2. To run for a range of densities run: ```$ make range MIN=minimum MAX=maximum INC=increment TRI=#trials ROWS=#rows COLS=#columns```  

		or  any combination of:

		```$ \generatedata.sh -m minimum -M maximum -r #rows -c #columns -n #trials -i increment -p ./percolate```   

		and 

		```$ \generatedata.sh --minimum minimum -maximum maximum --row-count #rows --column-count #columns --trial-count 		
			#trials --increment increment --percolate ./percolate``` 

- To build and run tests run:  ```$ make test ```.
- For a full list of make functionality run: ```$ make help ```.
- To generate documentation run: ```$ doxygen Doxyfile ```.


## Output
1. Running the first executable will output the Monte Carlo estimate of the probability of percolating through a grid of the specified size and density to the command line.

2. Running the second option will output the Monte Carlo estimate of the probability of percolating through a grid of the specified size and density for all values between minimum and maximum incremented by the provided increment to the command line.
The plot of density vs. probability can then be visualised by putting the standard output into a file ```$ make range MIN=minimum MAX=maximum INC=increment TRI=#trials ROWS=#rows COLS=#columns > output.txt``` then using the provided plotting tool ```$ ./plot.py output.txt``` 

## Progress
- [x] source code
- [x] bash tool
- [x] plot tool
- [x] make file
- [ ] unit tests
- [ ] continuous integration
- [x] documentation
