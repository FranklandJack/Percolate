#include "Grid2D.hpp"     

Cell& Grid2D::operator()(int i, int j)
{
    //assert(i >= 0 && i < m_rows && "Row index is out of range");
    //assert(j >= 0 && j < m_columns && "Column index is out of range");


    // Since there is a boundary/halo all indexing need to be shifted.
    int adjustedi = i + 1;
    int adjustedj = j + 1;


    // This formula will take into account the fact that the grid is in a 1-D array.
    // It corresponds to lining up all the rows starting from the top in one long vector.
    return m_cellArray[adjustedi * (m_columns + 2)+ adjustedj];

}


    
const Cell& Grid2D::operator()(int i, int j) const
{
    assert(i >= 0 && i < m_rows && "Row index is out of range");
    assert(j >= 0 && j < m_columns && "Column index is out of range");


    // Since there is a boundary/halo all indexing need to be shifted.
    int adjustedi = i + 1;
    int adjustedj = j + 1;


    // This formula will take into account the fact that the grid is in a 1-D array.
    // It corresponds to lining up all the rows starting from the top in one long vector.
    return m_cellArray[adjustedi * (m_columns + 2)+ adjustedj];
}


Grid2D::Grid2D(int rows, int columns, double density, std::default_random_engine &generator): m_rows(rows), 
                                                                                              m_columns(columns)
{
    /**
     *
     * To include the halo the number of rows and columns need to be increased by 2
     * so that there is an extra row on the top and bottom and extra column on either side.
     *
     */
    int arraySizeIncBufffer = (m_columns+2)*(m_rows+2);

    // The actual array size doesn't include the halo.
    int arraySize           = m_columns*m_rows;

    // The 1-D array of Cells is allocated dynamically from the heap and includes the halo.
    m_cellArray = new Cell[arraySizeIncBufffer];


    for(int cellIndex = 0; cellIndex < arraySizeIncBufffer; ++cellIndex)
    {
       
        // Initially a Full cell with an m_value of zero is copied into each cell.
        Cell::State  initialState  = Cell::Full;
        int          value         = 0;

        m_cellArray[cellIndex] = Cell(initialState, value);
    }

    // Create the pseudo random number generation to use with the density to determine which cells are filled.

    
    std::uniform_real_distribution<double> acceptance_distribution(0.0, 1.0); 
    
     
    // Then the non-halo cells have their state set according to the denisty provided to the constructor
    for(int i = 0; i < m_rows; ++i)
    {
        for(int j = 0; j < m_columns; ++j)
        {
               

            if(acceptance_distribution(generator) > density)
            {

            // The state of the cell is then set using the operator() overload since this ensures the indexing is correct and consistent. 
            ((*this)(i,j)).setState(Cell::Empty);
            }
        }
    }

    // Then initialise the grid so each empty square has a unique integer
    intialise();

}


        
Grid2D::Grid2D(const Grid2D &sourceGrid): m_rows(sourceGrid.m_rows), 
                                          m_columns(sourceGrid.m_columns)
{
    // Because m_rows and m_columns are not dynamically allocated we can just shallow copy them.
    
    // m_cellArray is a dynamically allocated pointer, we need to deep copy if it is non-null.
    if(nullptr != sourceGrid.m_cellArray)
    {
        /*
        *
        * To include the halo the number of rows and columns need to be increased by 2
        * so that there is an extra row on the top and bottom and extra column on either side.
        *
        */
        int arraySizeIncBufffer = (m_rows+2)*(m_columns+2);

        // The 1-D array of Cells is allocated dynamically from the heap and includes the halo.
        m_cellArray = new Cell[arraySizeIncBufffer];

        for(int cellIndex = 0; cellIndex < arraySizeIncBufffer; ++cellIndex)
        {
       
            // Initially an Full cell with an m_value of zero is copied into each cell. This ensures we get the halo of Full Cells.
            Cell::State  initialState  = Cell::Full;
            int          value         = 0;

        m_cellArray[cellIndex] = Cell(initialState, value);
        }

        // The cells are copied and placed in the newely allocated array, exculding the halo which has been allocated above. 
        for(int i = 0; i < m_rows; ++i)
        {
            for (int j = 0; j < m_columns; ++j)
            {
                (*this)(i,j) = sourceGrid(i,j);
            }
        }

    }

    // If copying from a grid with a null-pointer in its array member variable the new array is made null aswell.
    else
    {
        m_cellArray = nullptr;
    }

    // No need to initialise since the grid we are constructing from must have already been initialised. 
}


      
Grid2D::Grid2D(Grid2D &&sourceGrid): m_rows(sourceGrid.m_rows),
                                     m_columns(sourceGrid.m_columns),
                                     m_cellArray(sourceGrid.m_cellArray)
{
    /**
     * 
     * Ownership of member variables in sourceGrid is transfered to the new grid. 
     *
     * Ownership of the member variables is then removed from the sourceGrid. 
     * Technically since m_columns and m_cellArray are just Integer variables that are non-dynamic they do not need to 
     * have their ownership by the sourceGrid removed, it is only done here for completeness. 
     *
     */
    sourceGrid.m_rows    = 0;
    sourceGrid.m_columns = 0;
    sourceGrid.m_cellArray = nullptr;

    // No need to initialise since the grid we are constructing from must have already been initialised. 

}


     
Grid2D& Grid2D::operator=(const Grid2D &sourceGrid)
{
    // Check against self assignment using memory addresses.
    if(this == &sourceGrid)
    {
        /*
         *
         * If self assignment has occured then the method can return early since there is nothing to do. 
         * Return *this so assignment operations can be chained together.
         *
         */
        return *this;
    }


    /*
     *
     * Current memory held by the m_cellArray must be dealocated to avoid a memory leak. 
     * The same memory cannot be reused since more or less might be required.
     *
     */
    delete [] m_cellArray;

    // Because m_rows and m_columns are not dynamically allocated they are just shallow copied.
    m_rows    = sourceGrid.m_rows;
    m_columns = sourceGrid.m_columns;

    // m_cellArray is a dynamically allocated pointer, we need to deep copy if it is non-null.
    if(nullptr != sourceGrid.m_cellArray)
    {
        /*
        *
        * To include the halo the number of rows and columns need to be increased by 2
        * so that there is an extra row on the top and bottom and extra column on either side.
        *
        */
        int arraySizeIncBufffer = (m_rows+2)*(m_columns+2);

        // The 1-D array of Cells is allocated dynamically from the heap and includes the halo.
        m_cellArray = new Cell[arraySizeIncBufffer];

        for(int cellIndex = 0; cellIndex < arraySizeIncBufffer; ++cellIndex)
        {
       
            // Initially an full cell with an m_value of zero is copied into each cell. This ensures the halo is formed of full cells.
            Cell::State  initialState  = Cell::Full;
            int          value         = 0;

        m_cellArray[cellIndex] = Cell(initialState, value);
        }

        /// The cells are copied and placed in the newely allocated array, exluding the halo which has already been allocated.
        for(int i = 0; i < m_rows; ++i)
        {
            for (int j = 0; j < m_columns; ++j)
            {
                (*this)(i,j) = sourceGrid(i,j);
            }
        }

    }

    // If copying from a grid with a null-pointer in its array member variable the new array is made null aswell.
    else
    {
        m_cellArray = nullptr;
    }

    // Return *this so assignment operations can be chained together. 
    return *this;

}


        
Grid2D& Grid2D::operator=(Grid2D &&sourceGrid)
{
    // Check against self assignment using memory addresses.
    if(&sourceGrid == this)
    {
        // If self assignment has occured then the method can return early since there is nothing to do.
        return *this;
    }

    /*
     *
     * Current memory held by the m_cellArray must be dealocated to avoid a memory leak. 
     * The same memory cannot be reused since more or less might be required.
     *
     */
    delete [] m_cellArray;


    // Ownership of member variables in sourceGrid is transfered to the new grid. 
    m_rows    = sourceGrid.m_rows;
    m_columns = sourceGrid.m_columns;
    m_cellArray = sourceGrid.m_cellArray;

    /*
     * Ownership of the member variables is then removed from the sourceGrid. 
     * Technically since m_columns and m_cellArray are just Integer variables that are non-dynamic they do not need to 
     * have their ownership by the sourceGrid removed, it is only done here for completeness. 
     *
     */
    sourceGrid.m_rows      = 0;
    sourceGrid.m_columns   = 0;
    sourceGrid.m_cellArray = nullptr;

    // Return *this so assignment operations can be chained together.
    return *this;
}


        
Grid2D::~Grid2D()
{
    delete[] m_cellArray;
}


        
int Grid2D::getRows() const
{
    return m_rows;
}


    
int Grid2D::getColumns() const
{
    return m_columns;
}


        
void Grid2D::intialise()
{

    // Counter will take a unique value for every empty Cell.
    int counter = 1;

    for(int i = 0; i < m_rows; ++i)
    {
        for(int j = 0; j < m_columns; ++j)
        {
            if(Cell::Empty == (*this)(i,j).getState())
            {
                (*this)(i,j).setValue(counter++);
            }
        }
    }
}


int Grid2D::update()
{
    // Need a value to store the old values in cells to check whether its changed.
    int oldValue;

    // Need a counter to see how many cells change so we can return it.
    int cellsChanged = 0;

    for(int i = 0; i < m_rows; ++i)
    {
        for(int j = 0; j < m_columns; ++j)
        {
            

            if(Cell::Empty == (*this)(i,j).getState())
            {
                oldValue = (*this)(i,j).getValue();


                // Check above.
                (*this)(i,j).setValue((*this)(i-1,j).getValue() > (*this)(i,j).getValue() ? (*this)(i-1,j).getValue() : (*this)(i,j).getValue());

                // Check below.
                (*this)(i,j).setValue((*this)(i+1,j).getValue() > (*this)(i,j).getValue() ? (*this)(i+1,j).getValue() : (*this)(i,j).getValue()); 

                // Check the left.
                (*this)(i,j).setValue((*this)(i,j-1).getValue() > (*this)(i,j).getValue() ? (*this)(i,j-1).getValue() : (*this)(i,j).getValue()); 

                // Check the right.
                (*this)(i,j).setValue((*this)(i,j+1).getValue() > (*this)(i,j).getValue() ? (*this)(i,j+1).getValue() : (*this)(i,j).getValue());

                if((*this)(i,j).getValue() != oldValue)
                {
                    ++cellsChanged;
                } 
            }
        }
    }

    return cellsChanged;
}


       
bool Grid2D::test()
{
    for(int top = 0; top < m_columns; ++top)
    {
        if(Cell::Empty == (*this)(0,top).getState())
        {
            for(int bottom = 0; bottom < m_columns; ++bottom)
            {
                if((*this)(0,top).getValue() == (*this)(m_rows-1,bottom).getValue())
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::ostream& operator<<(std::ostream& out, const Grid2D& grid)
{
    for(int i = 0; i < grid.getRows(); ++i)
    {
        for(int j = 0; j < grid.getColumns(); ++j)
        {
            out << static_cast<int>(grid(i,j).getState()) << ' ';
        }

        out << std::endl;
    }
    return out;
}


void Grid2D::printValues()
{
    for(int i = 0; i < m_rows; ++i)
    {
        for(int j = 0; j < m_columns; ++j)
        {
            std::cout << static_cast<int>((*this)(i,j).getValue()) << ' ';
        }

        std::cout << std::endl;
    }
}