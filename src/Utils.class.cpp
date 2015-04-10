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
