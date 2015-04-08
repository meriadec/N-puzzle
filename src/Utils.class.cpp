#include <Utils.class.hpp>
#include <iomanip>

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

std::list<BOARD> Utils::getAvailableMoves(BOARD & board) {
    std::list<BOARD> moves;
    BOARD newBoard;

    std::pair<size_t, size_t> pos = Utils::getPos(0, board);
    size_t j = pos.first, i = pos.second;
    unsigned long size = board.size();

    if (j > 0) {
        newBoard = board;
        newBoard[j][i] = newBoard[j - 1][i];
        newBoard[j - 1][i] = 0;
        moves.push_back(newBoard);
    }
    if (i > 0) {
        newBoard = board;
        newBoard[j][i] = newBoard[j][i - 1];
        newBoard[j][i - 1] = 0;
        moves.push_back(newBoard);
    }
    if (j < size - 1) {
        newBoard = board;
        newBoard[j][i] = newBoard[j + 1][i];
        newBoard[j + 1][i] = 0;
        moves.push_back(newBoard);
    }
    if (i < size - 1) {
        newBoard = board;
        newBoard[j][i] = newBoard[j][i + 1];
        newBoard[j][i + 1] = 0;
        moves.push_back(newBoard);
    }
    return moves;
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
