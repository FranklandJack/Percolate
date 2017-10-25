#include "Cell.hpp"

Cell::Cell(State state, int value):m_state(state), m_value(value){}

const Cell::State& Cell::getState() const {return m_state;}

int  Cell::getValue() const {return m_value;}

void Cell::setState(Cell::State state) { m_state = state;}

void Cell::setValue(int value) { m_value = value;}