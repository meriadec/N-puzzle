#include <Utils.class.hpp>

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
    // FIXME
    throw std::exception();
}

std::pair<size_t, size_t> Utils::getFinalPos(int val, BOARD & board) {
    size_t          deep = 0;
    size_t          len = board.size();
    size_t          y = 0, x = 0;
    bool            found = false;

    while (deep < len && !found) {
        y = x = deep;
        while (x < len - deep) { if (board[y][x] == val) { found = true; break; } ++x; } --x; ++y;
        while (y < len - deep) { if (board[y][x] == val) { found = true; break; } y++; } --x; --y;
        while (x > deep) { if (board[y][x] == val) { found = true; break; } x--; }
        while (y > deep) { if (board[y][x] == val) { found = true; break; } y--; }
        ++deep;
    }
    return std::make_pair(y, x);
}

int Utils::getManhattanDistance (size_t j, size_t i, BOARD & board)
{
    int             val = board[j][i];
    size_t          deep = 0;
    size_t          len = board.size();
    size_t          y = 0, x = 0;
    bool            found = false;

    while (deep < len && !found) {
        y = x = deep;
        while (x < len - deep) { if (board[y][x] == val) { found = true; break; } ++x; } --x; ++y;
        while (y < len - deep) { if (board[y][x] == val) { found = true; break; } y++; } --x; --y;
        while (x > deep) { if (board[y][x] == val) { found = true; break; } x--; }
        while (y > deep) { if (board[y][x] == val) { found = true; break; } y--; }
        ++deep;
    }
    return (abs(static_cast<int>(j - y)) + abs(static_cast<int>(i - x)));
}

bool Utils::isTileRightPlaced(int val, BOARD & board) {
    return Utils::getPos(val, board) == Utils::getFinalPos(val, board);
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

/**
 * Heuristic 1
 */
int Utils::getSumManhattanDistances(BOARD & board) {
    int dist = 0;
    unsigned long len = board.size();

    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len; ++j) {
            dist += Utils::getManhattanDistance(j, i, board);
        }
    }
    return dist;
}

/**
 * Heuristic 2
 */
int Utils::getHammingDistance(BOARD & board) {
    int total = 0;
    unsigned long len = board.size();

    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len; ++j) {
            if (Utils::isTileRightPlaced(board[j][i], board)) {
                total++;
            }
        }
    }
    return total;
}
