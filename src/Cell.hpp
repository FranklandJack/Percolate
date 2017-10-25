#ifndef Cell_hpp
#define Cell_hpp

/**
 *
 * \class Cell
 *
 * A cell is considered as an element of a grid. Each cell is either full or empty. 
 * If it is empty then it has a uniquie number acciocated to it that is updated when 
 * we test for percolation.
 *
 */

class Cell
{   
    public:


        /**
        *
        * \enum State
        *
        * Enumerated data type for whether a cell is full or empty 
        * Full=0, and Empty=1.
        *
        */
        enum State
        {
            Full,
            Empty
        };
    
    private:


        /// Member variable telling us whether cell is full or empty.
        State m_state;


        /// Memeber variable which is the asscoiated number with the cell for perculation algorithms.
        int m_value;


    public:


        /*
         *
         * \brief Getter for state of cell.
         *
         * \return const State enumeration type reference representing state of cell.
         *
         */
        const State& getState() const;


        /*
         *
         * \brief Getter for value accociated to cell.
         *
         * \return Integer value representing value accociated with the cell.
         *
         */
        int getValue() const;


        /*
         *
         * \brief Setter for state of cell.
         *
         * \param state State enumeration type representing state of cell to be set.
         *
         */
        void setState(State state);

        /*
         *
         * \brief Setter for value accociated to cell.
         *
         * \param value integer representing value accociated to the cell to be set.
         *
         */
        void setValue(State state);


}       
#endif /* Cell_hpp */