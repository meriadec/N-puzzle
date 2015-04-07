#include <Puzzle.class.hpp>
#include <iomanip>
#include <Utils.class.hpp>

Puzzle::Puzzle(Puzzle const &src) {
}

Puzzle::Puzzle(BOARD const & board) : _board(board) {
}

Puzzle::Puzzle(void) {
}

Puzzle::~Puzzle(void) {
}

Puzzle & Puzzle::operator=(Puzzle const &src) {
    return *this;
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
    std::pair<size_t, size_t> pos = Utils::getPos(0, this->_board);
    int dist = Utils::getManhattanDistance(pos.first, pos.second, this->_board);

    return (dist % 2 == nbPermut % 2);
}

/**
 * @description Build the "serpent", aka the *real* english word for a serpent.
 */
std::list<int> Puzzle::_getSerpent (BOARD & v)
{
    std::list<int>  serpent;
    size_t          deep = 0;
    size_t          len = v.size();
    size_t          y, x;

    while (deep < len) {
        y = x = deep;
        while (x < len - deep) { serpent.push_back(v[y][x++]); } x = (x > 0 ? --x : x); ++y;
        while (y < len - deep) { serpent.push_back(v[y++][x]); } x = (x > 0 ? --x : x); y = (y > 0 ? --y : y);
        while (x > deep) { serpent.push_back(v[y][x--]); }
        while (y > deep) { serpent.push_back(v[y--][x]); }
        ++deep;
    }
    return serpent;
}
