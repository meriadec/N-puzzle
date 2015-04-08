#include <Utils.class.hpp>
#include <iomanip>
#include <Puzzle.class.hpp>

std::pair<size_t, size_t> Utils::getPos(int val, BOARD & board) {
    BOARD::iterator ity;
    std::vector<int>::iterator itx;
    size_t y = 0, x;

    for (ity = board.begin(); ity != board.end(); ity++) {
        x = 0;
        for (itx = board[y].begin(); itx != board[y].end(); itx++) {
            if (board[y][x] == val) {
                return std::make_pair(y, x);
            }
            ++x;
        }
        ++y;
    }
    throw Utils::NotFoundException();
}

void Utils::iterBoard(BOARD & board, void (*func)(void)) {
    BOARD::iterator row;
    for (row = board.begin(); row != board.end() ; ++row) {
        std::vector<int>::iterator col;
        for (col = (*row).begin(); col != (*row).end() ; ++col) {
            func();
        }
    }
}

void Utils::printBoard(BOARD & board) {
    BOARD::iterator row;
    for (row = board.begin(); row != board.end() ; ++row) {
        std::vector<int>::iterator col;
        for (col = (*row).begin(); col != (*row).end() ; ++col) {
            std::cout << std::setw(2) << (*col) << " ";
        }
        std::cout << std::endl;
    }
}

void Utils::heuristicInsertInList(Node & node, std::list<Node> & list) {
    std::list<Node>::iterator it;
    for (it = list.begin(); it != list.end(); ++it) {
        if (node.h < (*it).h) {
            list.insert(it, node);
            return;
        }
    }
    list.insert(it, node);
}
