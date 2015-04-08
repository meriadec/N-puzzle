#include <Puzzle.class.hpp>
#include <iomanip>
#include <algorithm>
#include <Utils.class.hpp>

Puzzle::Puzzle(Puzzle const &src) {
}

Puzzle::Puzzle(BOARD const & board) : _board(board) {
    this->_finalBoard = this->_buildFinalBoard();
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
    int dist = this->_getManhattanDistance(pos.first, pos.second, this->_board);

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
        while (x < len - deep) { serpent.push_back(v[y][x++]); } --x; ++y;
        while (y < len - deep) { serpent.push_back(v[y++][x]); } --x; --y;
        while (x > deep) { serpent.push_back(v[y][x--]); }
        while (y > deep) { serpent.push_back(v[y--][x]); }
        ++deep;
    }
    return serpent;
}

BOARD Puzzle::_buildFinalBoard (void) {
    BOARD       board;
    size_t      deep = 0;
    size_t      len = this->_board.size();
    size_t      y = 0, x = 0;
    int         i = 1;

    for (y = 0; y < len; y++) {
        std::vector<int> row;
        for (x = 0; x < len; x++) {
            row.push_back(0);
        }
        board.push_back(row);
    }
    while (deep < len - 1) {
        y = x = deep;
        while (x < len - deep) { board[y][x++] = i++; } --x; ++y;
        while (y < len - deep) { board[y++][x] = i++; } --x; --y;
        while (x > deep) { board[y][x--] = i++; }
        while (y > deep) { board[y--][x] = i++; }
        ++deep;
    }
    std::pair<size_t, size_t> pos = Utils::getPos(static_cast<int>(len * len), board);
    board[pos.first][pos.second] = 0;
    return board;
}

int Puzzle::_getManhattanDistance (size_t j, size_t i, BOARD & board)
{
    int val = board[j][i];
    std::pair<size_t, size_t> finalPos = Utils::getPos(val, this->_finalBoard);
    size_t y = finalPos.first, x = finalPos.second;
    return (abs(static_cast<int>(j - y)) + abs(static_cast<int>(i - x)));
}

bool Puzzle::_isTileRightPlaced(int val, BOARD & board) {
    return Utils::getPos(val, board) == Utils::getPos(val, this->_finalBoard);
}

std::list<Node> Puzzle::_getAvailableMoves(Node & node) {
    std::list<Node> moves;
    Node newNode;
    BOARD & board = node.board;

    std::pair<size_t, size_t> pos = Utils::getPos(0, board);
    size_t j = pos.first, i = pos.second;
    unsigned long size = board.size();

    if (j > 0) {
        newNode.board = board;
        newNode.board[j][i] = newNode.board[j - 1][i];
        newNode.board[j - 1][i] = 0;
        newNode.parent = &node;
        newNode.h = this->getSumManhattanDistances(newNode.board);
        newNode.g = node.g + 1;
        newNode.f = node.h + node.g;
        moves.push_back(newNode);
    }
    if (i > 0) {
        newNode.board = board;
        newNode.board[j][i] = newNode.board[j][i - 1];
        newNode.board[j][i - 1] = 0;
        newNode.parent = &node;
        newNode.h = this->getSumManhattanDistances(newNode.board);
        newNode.g = node.g + 1;
        newNode.f = node.h + node.g;
        moves.push_back(newNode);
    }
    if (j < size - 1) {
        newNode.board = board;
        newNode.board[j][i] = newNode.board[j + 1][i];
        newNode.board[j + 1][i] = 0;
        newNode.parent = &node;
        newNode.h = this->getSumManhattanDistances(newNode.board);
        newNode.g = node.g + 1;
        newNode.f = node.h + node.g;
        moves.push_back(newNode);
    }
    if (i < size - 1) {
        newNode.board = board;
        newNode.board[j][i] = newNode.board[j][i + 1];
        newNode.board[j][i + 1] = 0;
        newNode.parent = &node;
        newNode.h = this->getSumManhattanDistances(newNode.board);
        newNode.g = node.g + 1;
        newNode.f = node.h + node.g;
        moves.push_back(newNode);
    }
    return moves;
}

/**
 * Heuristic 1
 */
int Puzzle::getSumManhattanDistances (BOARD &board) {
    int dist = 0;
    unsigned long len = board.size();

    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len; ++j) {
            dist += this->_getManhattanDistance(j, i, board);
        }
    }
    return dist;
}

/**
 * Heuristic 2
 */
int Puzzle::getHammingDistance (BOARD &board) {
    int total = 0;
    unsigned long len = board.size();

    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len; ++j) {
            if (this->_isTileRightPlaced(board[j][i], board)) {
                total++;
            }
        }
    }
    return total;
}

/**
 * Solves the puzzle. Obviously.
 */
void Puzzle::solve (void) {
    std::list<Node> closed;
    Node start;
    start.board = this->_board;
    start.parent = NULL;
    start.h = this->getSumManhattanDistances(start.board);
    start.g = 0;
    start.f = start.g + start.h;
    std::list<Node> opened;
    opened.push_back(start);

    while (!opened.empty()) {
        Node current = opened.front();
        if (current.board == this->_finalBoard) {
            Utils::printBoard(current.board);
            std::cout << "SOLVED" << std::endl;
            return;
        } else {
            opened.pop_front();
            closed.push_front(current);
            std::list<Node> moves = this->_getAvailableMoves(current);
            std::list<Node>::iterator it;
            for (it = moves.begin(); it != moves.end(); ++it) {
                if (std::find(opened.begin(), opened.end(), *it) == opened.end() && std::find(closed.begin(), closed.end(), *it) == closed.end()) {
                    Utils::heuristicInsertInList(*it, opened);
                } else {
                    if ((*it).f > current.f + 1) {
                        (*it).g = current.g + 1;
                        if (std::find(closed.begin(), closed.end(), *it) != closed.end()) {
                            closed.remove(*it);
                            Utils::heuristicInsertInList(*it, opened);
                        }
                    }
                }
            }
        }
    }
}

































































