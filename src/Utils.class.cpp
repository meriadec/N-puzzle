#include <Utils.class.hpp>
#include <iomanip>

std::pair<size_t, size_t> Utils::getPos(int val, BOARD const & board) {
    BOARD::const_iterator ity;
    std::vector<int>::const_iterator itx;
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

void Utils::printBoard(BOARD const & board) {
    BOARD::const_iterator row;
    for (row = board.begin(); row != board.end() ; ++row) {
        std::vector<int>::const_iterator col;
        for (col = (*row).begin(); col != (*row).end() ; ++col) {
            std::cout << std::setw(2) << (*col) << " ";
        }
        std::cout << std::endl;
    }
}

void Utils::heuristicInsertInList(Node * node, std::list<Node *> & list) {
    std::list<Node *>::iterator it;
    for (it = list.begin(); it != list.end(); ++it) {
        if (node->h < (*it)->h) {
            list.insert(it, node);
            return;
        }
    }
    list.insert(it, node);
}

void Utils::printInfos (Node * node, t_infos & infos) {

    std::list<Node *> list;

    while (node) {
        list.push_front(node);
        node = node->parent;
    }

    for (std::list<Node *>::iterator it = list.begin(); it != list.end(); ++it) {
        Utils::printBoard((*it)->board);
        std::cout << std::endl;
    }

    std::cout << "\033[35m-- STATISTICS ----------\033[0m" << std::endl;
    std::cout << "complexity in time: \033[33m" << infos.timeCpl << "\033[0m" << std::endl;
    std::cout << "complexity in size: \033[33m" << infos.sizeCpl << "\033[0m" << std::endl;
    std::cout << "number of moves   : \033[33m" << list.size() - 1 << "\033[0m" << std::endl;
    std::cout << "\033[35m------------------------\033[0m" << std::endl << std::endl;
}

Node * Utils::isBoardInList (Node *node, std::list<Node *> &list) {
    for (std::list<Node *>::iterator it = list.begin(); it != list.end(); ++it) {
        if ((*it)->h == node->h && (*it)->board == node->board) {
            return *it;
        }
    }
    return NULL;
}

void Utils::cleanList (std::list<Node *> & list) {
    for (std::list<Node *>::iterator it = list.begin(); it != list.end(); ++it) {
        delete *it;
    }
}

BOARD Utils::generateBoard (size_t size, size_t iterations) {
    BOARD board = Utils::generateFinalBoard(size);
    int tmp = board[0][1];
    board[0][1] = board[1][0];
    board[1][0] = tmp;
    return board;
}

BOARD Utils::generateFinalBoard (size_t len) {
    BOARD board;

    size_t      deep = 0;
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
