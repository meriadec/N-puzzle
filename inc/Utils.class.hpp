#ifndef UTILS_CLASS_HPP
#define UTILS_CLASS_HPP

#include <npuzzle.hpp>
#include <Node.class.hpp>
#include <list>

class Utils {

public:

    static std::pair<size_t, size_t> getPos(int, BOARD const &);
    static void iterBoard(BOARD &, void (*)(void));
    static void printBoard(BOARD const &);
    static void heuristicInsertInList(Node &, std::list<Node> &);

    class NotFoundException : public std::exception {
        virtual const char * what (void) const throw () {
            return "Error: Not found.";
        }
    };

};

#endif
