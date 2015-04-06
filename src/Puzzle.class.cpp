#include <Puzzle.class.hpp>
#include <iomanip>
#include <utility>

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

/**
 * @description This function get the number of permutations
 *
 * @param {int} list
 * @returns {int}
 */
int Puzzle::_getPermutations (std::list<int> & list)
{
    int                       iter = 0;
    std::list<int>::iterator  it = list.begin();
    std::list<int>::iterator  tmp;

    while (it != list.end()) {
        tmp = std::next(it, 1);
        while (tmp != list.end()) {
            if (*tmp < *it && *tmp != 0) { ++iter; }
            ++tmp;
        }
        ++it;
    }
    return (iter);
}

/**
 * @description Check if the board is solvable
 */
bool Puzzle::isSolvable(void)
{
    std::list<int> serpent = this->_getSerpent(this->_board);
    int nbPermut = this->_getPermutations(serpent);
    std::pair<size_t, size_t> pos = this->_getPos(0, this->_board);
    int dist = this->getManhattanDistance(pos.first, pos.second, this->_board);

    return (dist % 2 == nbPermut % 2);
}

/**
 * @description Build the "serpent", aka the *real* english word for a serpent.
 */
std::list<int> Puzzle::_getSerpent (std::vector<std::vector<int>> & v)
{
    std::list<int>  serpent;
    size_t          deep = 0;
    size_t          len = v.size();
    size_t          y, x;

    while (deep < len) {
        y = x = deep;
        while (x < len - deep) { serpent.push_back(v[y][x++]); } --x; ++y;
        while (y < len - deep) { serpent.push_back(v[y++][x]); } --x; --y;
        while (x > deep) { serpent.push_back(v[y][x--]); }
        while (y > deep) { serpent.push_back(v[y--][x]); }
        ++deep;
    }
    return serpent;
}

int Puzzle::getManhattanDistance (size_t j, size_t i, std::vector<std::vector<int>> & board)
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

std::pair<size_t, size_t> Puzzle::_getPos (int val, std::vector<std::vector<int>> &board)
{
    std::vector<std::vector<int>>::iterator ity;
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
