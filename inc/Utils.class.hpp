#ifndef UTILS_CLASS_HPP
#define UTILS_CLASS_HPP

#include <npuzzle.hpp>
#include <Node.class.hpp>
#include <list>

class Utils {

public:

    static std::pair<size_t, size_t> getPos(int, BOARD const &);
    static void printBoard(BOARD const &);
    static void printInfos(Node *, t_infos & infos);
    static void heuristicInsertInList(Node *, std::list<Node *> &);
    static bool isBoardInList (Node *, std::list<Node *> &);
    static void cleanList (std::list<Node *> &);

    class NotFoundException : public std::exception {
        virtual const char * what (void) const throw () {
            return "Error: Not found.";
        }
    };

};

#endif
