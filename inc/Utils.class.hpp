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
    static Node * isBoardInList (Node *, std::list<Node *> &);
    static void cleanList (std::list<Node *> &);
    static BOARD generateBoard (size_t size, size_t iterations, bool solvable);
    static BOARD generateFinalBoard (size_t size);
    static void printVec (std::string, std::vector<int>);

    class NotFoundException : public std::exception {
        virtual const char * what (void) const throw () {
            return "Not found.";
        }
    };

};

#endif
