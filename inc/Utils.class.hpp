#ifndef UTILS_CLASS_HPP
#define UTILS_CLASS_HPP

#include <npuzzle.hpp>
#include <list>

class Utils {

public:

    static std::pair<size_t, size_t> getPos(int, BOARD &);
    static int getManhattanDistance (size_t, size_t, BOARD &);
    static void iterBoard(BOARD &, void (*)(void));
    static int getSumManhattanDistances (BOARD &);
    static std::pair<size_t, size_t> getFinalPos(int val, BOARD &);
    static bool isTileRightPlaced(int val, BOARD &);
    static int getHammingDistance(BOARD &);
    static std::list<BOARD> getAvailableMoves(BOARD &);
    static void printBoard(BOARD &);

    class NotFoundException : public std::exception {
        virtual const char * what (void) const throw () {
            return "Error: Not found.";
        }
    };
};

#endif
