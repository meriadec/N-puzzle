#include <Puzzle.class.hpp>
#include <iostream>
#include <iomanip>

Puzzle::Puzzle(Puzzle const &src) {
}

Puzzle::Puzzle(std::vector<std::vector<int>> board) : _board(board) {
}

Puzzle::Puzzle(void) {
}

Puzzle::~Puzzle(void) {
}

Puzzle &Puzzle::operator=(Puzzle const &src) {
    return *this;
}

void Puzzle::print(void) {
    std::vector<std::vector<int>>::iterator row;
    for (row = this->_board.begin(); row != this->_board.end() ; ++row) {
        std::vector<int>::iterator col;
        for (col = (*row).begin(); col != (*row).end() ; ++col) {
            std::cout << std::setw(2) << (*col) << " ";
        }
        std::cout << std::endl;
    }
}
