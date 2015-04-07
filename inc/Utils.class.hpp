#ifndef UTILS_CLASS_HPP
#define UTILS_CLASS_HPP

#include <npuzzle.hpp>

class Utils {

public:

    static std::pair<size_t, size_t> getPos(int, BOARD &);
    static int getManhattanDistance (size_t, size_t, BOARD &);
    static void iterBoard(BOARD &, void (*)(void));
    static int getSumManhattanDistances (BOARD &);
    static std::pair<size_t, size_t> getFinalPos(int val, BOARD &);
    static bool isTileRightPlaced(int val, BOARD &);
    static int getHammingDistance(BOARD &);
};

#endif
