#ifndef Grid2D_hpp
#define Grid2D_hpp


/// For the cells in the array.
#include "Cell.hpp"


/// For seeding pseudo random numbers.
#include <chrono>


/// For generating psuedo random numbers.
#include <random>


/// For bounds checking.
#include <cassert>


/**
 *
 * \class Grid2D
 *
 * 2D grid consisting of filled cells and unfilled cells and the accociated methods
 * to test for perculation through the grid. The grid is indexed like a matric (i,j) 
 * is the ith row jth column from the top left. The grid is actually implemented as 
 * 1-D dynamically allocated arrary and is surrounded by a ring of filled cells which 
 * act as a boundary.
 *
 */

class Grid2D
{
    private:


        /// Member variable to hold the number of rows. This does not include the buffer rows.
        int m_rows;


        /// Member variable to hold the number of columns. This does not include the buffer columns.
        int m_columns;

        /// Member variable to hold the array of cells.
        Cell *m_cellArray;


    public:


        /**
        *
        * \brief For accessing elements of the grid.
        *
        * By overloading the () operator we are able to access elements of the m_cellArray as if they were 
        * members of a 2D array rather than a 1-D one. This conceptually simplifies the code were specific 
        * cells are accessed. the indexing system (i,j) follows that of a matrix starting from 0.
        * 
        * \param i Integer value representing the the row to be accessed.
        * 
        * \param j Integer value representing the column to be accessed. 
        *
        * \return Cell refernce to the cell at (i,j) in the matrix.
        *
        */
        Cell& operator()(int i, int j);


        /**
        *
        * \brief For accessing elements of a constant  grid.
        *
        * This works in exactly the same way as the opertor() for non-constant grids. It has to be overloaded
        * twice however so that it can deal with constant grids as well.
        * 
        * \param i Integer value representing the the row to be accessed.
        * 
        * \param j Integer value representing the column to be accessed. 
        *
        * \return Constant Cell refernce to the cell at (i,j) in the matrix.
        *
        */
        const Cell& operator()(int i, int j) const;




        /**
         *
         * \brief Constructor to create a Grid2D instance from dimensions and density.
         *
         * The m_cellArray is allocated dynamically since the dimensions and density will not be known at 
         * compile time. The array could also be very large, so it should be allocated from the heap anyway.
         *
         *
         *
         * \param rows Integer representing the number of rows in the array, this should not include the buffer rows since this is all implemented internally.
         *
         * \param columns Integer representing the number of columns in the array, this should not include the buffer columns since this is all implemented internally.
         *
         * \param density Floating point value between 0 and 1 representing the density of filled squares within the grid.
         */
        Grid2D(int rows, int columns, double density);


        /**
         *
         * \brief Copy constructor to create Grid2D instance from source Grid2D instance. 
         *
         * Deep copying is neccasary since we have dynamic memory allocation int the constructor.
         * Otherwise deferencing of dangling pointers may occur when we release memory at the end of a scope.
         *
         * \param sourceGrid constant Grid2D reference instance to be copied from. 
         *
         */
        Grid2D(const Grid2D &sourceGrid);


        /**
         *
         * \brief Move constructor to create a Grid2D instance from a source. 
         *
         * This is more performant when we are copying from R-Value references and will be called 
         * automatically in those cases.
         *
         * \param sourceGrid R-Value reference from which the new Grid2D object will take ownership of the 
         * member variables memory. 
         *
         */
        Grid2D(Grid2D &&sourceGrid);


        /**
         *
         * \brief Copy assignment operator for assigning a previously initialised Grid2D instance.
         *
         * Deep copying is neccasary since we have dynamic memory allocation int the constructor.
         * Otherwise deferencing of dangling pointers may occur when we release memory at the end of a scope.
         *
         * \param srouceGrid constant Grid 2D reference instance from which the current Grid2D instance should be intialized. 
         *
         * \return Grid2D reference corresponding to *this so assignment operations can be chained together.
         *
         */
        Grid2D& operator=(const Grid2D &sourceGrid);


        /**
         * 
         * \brief Move assignment operator for assigning previously intialised Grid2D instance. 
         *
         * This is more performant when we are assigning from R-Value references and will be called 
         * automatically in those cases.
         *
         * \param sourceGrid R-Value reference from which the (*this) Grid2D object will take ownership of the 
         * member variables memory.
         *
         * \return Grid2D reference corresponding to *this so assignment operations can be chained together. 
         *
         */
        Grid2D& operator=(Grid2D &&sourceGrid);


        /**
         *
         * \brief Destructor for grid must be explicitly implemented since there is dynamic memory assignemnt. 
         *
         */
        ~Grid2D();


        /**
         *
         * \brief Getter for the number of rows in the grid.
         * 
         * \return Integer value representing the number of rows in the grid.
         *
         */
        int getRows() const;


        /**
         *
         * \brief Getter for the number of columns in the grid.
         * 
         * \return Integer value representing the number of columns in the grid.
         *
         */
        int getColumns() const;


        /**
         *
         * \brief Intialises the grid ready for the update in the perculation test. 
         *
         * Sets the m_value of each cell to a unique integer.
         *
         */
        void intialise();


        /**
         * 
         * \brief Updates the m_value in each cell inline with the perculation algorithm.
         *
         * Looks for clusters (empty cells that are connected by either adjacent cells or cells that are
         * ontop of one another) until they are all found, by looking at each empty cell, replacing its 
         * m_value with the maximum of its four nearest neighbours.
         *
         * \return Integer value representing the number of cells that have changed. 
         *
         */
        int update();


        /**
         *
         * \brief Tests to see whether precolation has occured. 
         *
         * If perculation has occured there will be a cluster with that reaches from the top to the bottom of the Grid.
         * Since we know that each cluster has the same number accociated to each of its cells after the updates have stopped
         * we can just check whether any of the cells in the last row have the same accociated number as any in the first row.  
         *
         * \return Boolean representing whether preculation has occured. True if percolated, false otherwise. 
         *
         */
        bool test();









};

#endif /* Grid2D_hpp */