#include <Puzzle.class.hpp>
#include <iomanip>
#include <Utils.class.hpp>

Puzzle::Puzzle(Puzzle const &src) {
}

Puzzle::Puzzle(BOARD const & board) : _board(board) {
    this->_buildFinalBoard();
    this->_heuristic = &Puzzle::getSumManhattanDistances;
    this->_buildFinalPositions();
}

Puzzle::Puzzle(void) {
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

    return (dist == 1 || dist % 2 == nbPermut % 2);
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
    BOARD &     board = this->_finalBoard;
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
        std::cout << "This puzzle is not solvable sorry!" << std::endl;
        return;
    }

    std::cout << std::endl << "\033[037mSearch in progress...\033[0m" << std::endl << std::endl;

    // informations about the algorithm
    t_infos infos;
    infos.sizeCpl = 0;
    infos.timeCpl = 0;
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
            for (std::list<Node *>::iterator it = moves.begin(); it != moves.end(); ++it) {

                // search move in sets
                Node * stateInOpen = Utils::isBoardInList(*it, opened);
                Node * stateInClose = Utils::isBoardInList(*it, closed);

                if (!stateInOpen && !stateInClose) {

                    // push in opened if current move is neither in opened, neither in closed
                    Utils::heuristicInsertInList(*it, opened);

                } else {

                    // comparing things
                    if ((*it)->g > current->g + 1) {

                        (*it)->g = current->g + 1;

                        Node * searched = Utils::isBoardInList(*it, closed);

                        if (searched) {
                            closed.remove(searched);
                            Utils::heuristicInsertInList(*it, opened);
                        } else { delete *it; }

                    } else { delete *it; }
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
