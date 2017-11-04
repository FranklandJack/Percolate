#!/usr/bin/env python3

# For plotting input.
import matplotlib.pyplot as plt

# For accessing command line arguments
import sys 


if __name__ == "__main__":

    # Get file from the first command line argument.
    filein = open(sys.argv[1],"r")

    # Read lines into buffer.
    inputData = filein.readlines()

    # First line of file should be the number of rows and columns.
    # Split first line on an empty string to get row and column numbers into a tuple.
    rowcolToken = inputData[0].split(" ")
    rowCount    = rowcolToken[0]
    colCount = rowcolToken[1]

    # Prepare lists to hold data.
    xData = []
    yData = []

    # Loop through remainder of file getting x coordinate from first column, y coordinate from second.
    for line in range(1,len(inputData)):

        # Use same splitting method as above to access x and y
        token = inputData[line].split(" ")
        x     = token[0]
        y     = token[1]

        # add data to lists defined above
        xData.append(x)
        yData.append(y)

    # close file for safety.
    filein.close()

    # Set plot customisation.
    plt.plot(xData,yData,color="black", linewidth = 0.5, linestyle='-', markersize = 1)
    
    # Show axis labels and title.
    plt.xlabel(r'$\rho$')
    plt.ylabel('Probability of Percolation')
    plt.suptitle('Density of Grid vs. Probability of Percolation', fontsize=14, fontweight='bold')
    plt.title('#rows = ' + str(rowCount) + ' ' + '#columns = ' + str(colCount))


    # Show the plot.
    plt.show()

    plotName = 'Probability_Plot_'+str(rowCount)+'_'+str(colCount)
    # Save the plot with file name the same as its title.
    plt.savefig(plotTitle)
