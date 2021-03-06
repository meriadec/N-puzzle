#include <Utils.class.hpp>
#include <stdlib.h>
#include <Graphic.class.hpp>
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
        if (node->f <= (*it)->f) {
            list.insert(it, node);
            return;
        }
    }
    list.insert(it, node);
}

void Utils::printInfos (Node * node, t_infos & infos) {

    std::list<Node *> list;
    Graphic graphic(infos.boardSize * 110 + 10 + 200, infos.boardSize * 110 + 10 + 100);

    while (node) {
        list.push_front(node);
        node = node->parent;
    }

    std::cout << "\033[35m-- STATISTICS ----------\033[0m" << std::endl;
    std::cout << "complexity in time: \033[33m" << infos.timeCpl << "\033[0m" << std::endl;
    std::cout << "complexity in size: \033[33m" << infos.sizeCpl << "\033[0m" << std::endl;
    std::cout << "number of moves   : \033[33m" << list.size() - 1 << "\033[0m" << std::endl;
    std::cout << "\033[35m------------------------\033[0m" << std::endl << std::endl;

    std::list<Node *>::iterator it = list.begin();
    while (1) {

        Node * current = *it;
        graphic.beginDraw();
        for (size_t y = 0; y < current->board.size(); ++y) {
            for (size_t x = 0; x < current->board[y].size(); ++x) {
                if (current->board[y][x] != 0) {
                    graphic.drawCell(y, x, current->board[y][x]);
                }
            }
        }
        graphic.drawPos(static_cast<int>(std::distance(list.begin(), it)), static_cast<int>(list.size()));
        graphic.drawArrows(it != list.begin(), it != std::prev(list.end(), 1));
        graphic.endDraw();
        e_keys ret = graphic.getInput();
        if (ret == e_keys::ESC) {
            return;
        } else if (ret == e_keys::LEFT && it != list.begin()) {
            it--;
        } else if (ret == e_keys::RIGHT && it != std::prev(list.end(), 1)) {
            it++;
        }
    }

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

BOARD Utils::generateBoard (size_t size, size_t iterations, bool solvable) {
    BOARD board = Utils::generateFinalBoard(size);
    if (!solvable) {
        board[0][0] = 2;
        board[0][1] = 1;
    }
    for (size_t iter = 0; iter < iterations; ++iter) {
        std::pair<size_t,size_t> pos = Utils::getPos(0, board);
        std::vector<std::pair<size_t,size_t>> moves;
        if (pos.first > 0) { moves.push_back(std::make_pair(pos.first - 1, pos.second)); }
        if (pos.second > 0) { moves.push_back(std::make_pair(pos.first, pos.second - 1)); }
        if (pos.first < size - 1) { moves.push_back(std::make_pair(pos.first + 1, pos.second)); }
        if (pos.second < size - 1) { moves.push_back(std::make_pair(pos.first, pos.second + 1)); }
        std::pair<size_t,size_t> chosen = moves[static_cast<int>(rand() % moves.size())];
        int val = board[chosen.first][chosen.second];
        board[chosen.first][chosen.second] = 0;
        board[pos.first][pos.second] = val;
    }
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

void Utils::printVec (std::string string, std::vector<int> vector) {
    std::cout << "[" << string << "]" << std::endl;
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
        std::cout << (*it) << " ";
    }
    std::cout << std::endl << std::endl;
}
