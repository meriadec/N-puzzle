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
