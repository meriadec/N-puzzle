#include <Puzzle.class.hpp>
#include <iomanip>
#include <algorithm>
#include <Utils.class.hpp>

Puzzle::Puzzle(Puzzle const &src) {
}

Puzzle::Puzzle(BOARD const & board) : _board(board) {
    this->_buildFinalBoard();
    this->_heuristic = &Puzzle::getSumManhattanDistances;
    this->_buildFinalPositions();
}

Puzzle::Puzzle(void) {
    this->_heuristic = &Puzzle::getSumManhattanDistances;
}

Puzzle::~Puzzle(void) {
}

Puzzle & Puzzle::operator=(Puzzle const &src) {
    return *this;
}

void Puzzle::setHeuristic(std::string & heuristic) {
    if (heuristic == "manhattan") {
        this->_heuristic = &Puzzle::getSumManhattanDistances;
    } else if (heuristic == "hamming") {
        this->_heuristic = &Puzzle::getHammingDistance;
    } else if (heuristic == "third") {
        this->_heuristic = &Puzzle::getThirdHeuristicDistance;
    } else {
        throw UnknownHeuristicException();
    }
}

void Puzzle::setBoard (BOARD board) {
    this->_board = board;
    this->_buildFinalBoard();
    this->_buildFinalPositions();
}

/**
 * @description This function get the number of permutations
 *
 * @param {int} list
 * @returns {int}
 */
int Puzzle::_getPermutations (void)
{
    int permut  = 0;

    std::vector<int> stateList = this->_getVec(this->_board);
    std::vector<int> finalList = this->_getVec(this->_finalBoard);

    for (int nb = 0; nb < stateList.size(); nb++) {

        int stateIndex = static_cast<int>(std::distance(stateList.begin(), std::find(stateList.begin(), stateList.end(), finalList[nb])));

        for (int nb2 = nb + 1; nb2 < stateList.size(); nb2++) {
            int curIndex = static_cast<int>(std::distance(stateList.begin(), std::find(stateList.begin(), stateList.end(), finalList[nb2])));
            if (curIndex < stateIndex) {
                permut++;
            }
        }
    }
    return permut;
}

/**
 * @description Check if the board is solvable
 */
bool Puzzle::isSolvable(void)
{
    int nbPermut = this->_getPermutations();
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

void Puzzle::_buildFinalBoard (void) {
    this->_finalBoard = Utils::generateFinalBoard(this->_board.size());
}

int Puzzle::_getManhattanDistance (size_t j, size_t i, BOARD const & board) const
{
    int val = board[j][i];
    std::pair<size_t, size_t> finalPos = this->_finalPositions.at(val);
    size_t y = finalPos.first, x = finalPos.second;
    return (abs(static_cast<int>(j - y)) + abs(static_cast<int>(i - x)));
}

bool Puzzle::_isTileRightPlaced(int val, BOARD const & board) const {
    return Utils::getPos(val, board) == this->_finalPositions.at(val);
}

std::list<Node *> Puzzle::_getAvailableMoves(Node * parent) {

    // the current board
    BOARD & board = parent->board;

    // the returned list
    std::list<Node *> moves;

    // the position of the empty cell
    std::pair<size_t, size_t> pos = Utils::getPos(0, board);
    size_t j = pos.first, i = pos.second;

    unsigned long size = board.size();

    if (j > 0) {
        Node * newNode = new Node();
        newNode->board = board;
        newNode->board[j][i] = newNode->board[j - 1][i];
        newNode->board[j - 1][i] = 0;
        newNode->parent = parent;
        newNode->h = (this->*_heuristic)(newNode->board);
        newNode->g = parent->g + 1;
        newNode->f = parent->h + parent->g;
        moves.push_back(newNode);
    }
    if (i > 0) {
        Node * newNode = new Node();
        newNode->board = board;
        newNode->board[j][i] = newNode->board[j][i - 1];
        newNode->board[j][i - 1] = 0;
        newNode->parent = parent;
        newNode->h = (this->*_heuristic)(newNode->board);
        newNode->g = parent->g + 1;
        newNode->f = parent->h + parent->g;
        moves.push_back(newNode);
    }
    if (j < size - 1) {
        Node * newNode = new Node();
        newNode->board = board;
        newNode->board[j][i] = newNode->board[j + 1][i];
        newNode->board[j + 1][i] = 0;
        newNode->parent = parent;
        newNode->h = (this->*_heuristic)(newNode->board);
        newNode->g = parent->g + 1;
        newNode->f = parent->h + parent->g;
        moves.push_back(newNode);
    }
    if (i < size - 1) {
        Node * newNode = new Node();
        newNode->board = board;
        newNode->board[j][i] = newNode->board[j][i + 1];
        newNode->board[j][i + 1] = 0;
        newNode->parent = parent;
        newNode->h = (this->*_heuristic)(newNode->board);
        newNode->g = parent->g + 1;
        newNode->f = parent->h + parent->g;
        moves.push_back(newNode);
    }
    return moves;
}

/**
 * Heuristic 1
 */
int Puzzle::getSumManhattanDistances (BOARD const & board) const {
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
int Puzzle::getHammingDistance (BOARD const & board) const {
    int total = static_cast<int>(board.size() * board.size());
    unsigned long len = board.size();

    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len; ++j) {
            if (this->_isTileRightPlaced(board[j][i], board)) {
                total--;
            }
        }
    }
    return total;
}

/**
 * Heuristic 3
 */
int Puzzle::getThirdHeuristicDistance (BOARD const & board) const {
    int total = static_cast<int>(board.size() * board.size()) * 2;
    unsigned long len = board.size();

    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len; ++j) {
            if (this->_isRightRow(board[j][i], j)) { total--; }
            if (this->_isRightCol(board[j][i], i)) { total--; }
        }
    }
    return total;
}

/**
 * Solves the puzzle. Obviously.
 */
void Puzzle::solve (void) {

    if (!this->isSolvable()) {
        Utils::printBoard(this->_board);
        std::cout << "\nThis puzzle is not solvable sorry!\n" << std::endl;
        return;
    }

    std::cout << std::endl << "\033[037mSearch in progress...\033[0m" << std::endl << std::endl;

    // informations about the algorithm
    t_infos infos;
    infos.sizeCpl = 0;
    infos.timeCpl = 0;
    infos.boardSize = static_cast<int>(this->_board.size());
    size_t tmp;

    // lists used in algorithm
    std::list<Node *> closed;
    std::list<Node *> opened;

    // first node, initial state
    Node * start = new Node();
    start->board = this->_board;
    start->parent = NULL;
    start->h = (this->*_heuristic)(start->board);
    start->g = 0;
    start->f = start->g + start->h;

    // pushing first node in opened set
    opened.push_back(start);

    while (!opened.empty()) {

        // increment the time complexity
        ++infos.timeCpl;

        // increment the size complexity
        tmp = opened.size() + closed.size();
        if (tmp > infos.sizeCpl) { infos.sizeCpl = tmp; }

        // get current node, on top of the opened list
        Node * current = opened.front();

        if (current->h == 0) {

            // the puzzle is solved
            Utils::printInfos(current, infos);

            // clean nodes in each lists
            Utils::cleanList(opened);
            Utils::cleanList(closed);

            return;

        } else {

            // removing first node of opened set
            opened.pop_front();

            // getting all availables moves
            std::list<Node *> moves = this->_getAvailableMoves(current);

            // looping in them
            for (std::list<Node *>::iterator move = moves.begin(); move != moves.end(); ++move) {

                if (Utils::isBoardInList(*move, closed)) { continue; }

                Node * stateInOpen = Utils::isBoardInList(*move, opened);

                if (!stateInOpen) {
                    Utils::heuristicInsertInList(*move, opened);
                }
            }
        }

        // pushing current node in closed
        closed.push_front(current);

    }
}

void Puzzle::_buildFinalPositions (void) {
    int     i;
    int     max = static_cast<int>(this->_finalBoard.size() * this->_finalBoard.size());

    for (i = 0; i < max; i++) { this->_finalPositions[i] = Utils::getPos(i, this->_finalBoard); }
}

bool Puzzle::_isRightRow (int val, size_t row) const {
    size_t len = this->_finalBoard.size();
    for (size_t i = 0; i < len; i++) {
        if (this->_finalBoard[row][i] == val) { return true; }
    }
    return false;
}

bool Puzzle::_isRightCol (int val, size_t col) const {
    size_t len = this->_finalBoard.size();
    for (size_t i = 0; i < len; i++) {
        if (this->_finalBoard[i][col] == val) { return true; }
    }
    return false;
}

BOARD Puzzle::getBoard (void) {
    return this->_board;
}

BOARD Puzzle::getFinalBoard (void) {
    return this->_finalBoard;
}

/**
 * Get list in noob order
 */
std::vector<int> Puzzle::_getVec (std::vector<std::vector<int>> & board) {
    std::vector<int> vec;
    size_t len = board.size();
    for (size_t j = 0; j < len; j++) {
        for (size_t i = 0; i < len; i++) {
            vec.push_back(board[j][i]);
        }
    }
    return vec;
}
