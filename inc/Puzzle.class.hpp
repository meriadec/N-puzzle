#ifndef PUZZLE_CLASS_H
#define PUZZLE_CLASS_H

#include <npuzzle.hpp>
#include <vector>
#include <list>

class Puzzle {

public:
    Puzzle(void);
    Puzzle(BOARD const &);
    virtual ~Puzzle(void);

    bool            isSolvable (void);
    int             getSumManhattanDistances (BOARD &);
    int             getHammingDistance (BOARD &);

private:

    Puzzle (Puzzle const & src);
    Puzzle & operator= (Puzzle const & src);

    BOARD   _board;
    BOARD   _finalBoard;

    int             _getPermutations (std::list<int> &);
    std::list<int>  _getSerpent (std::vector<std::vector<int>> &);
    BOARD           _buildFinalBoard (void);
    int             _getManhattanDistance (size_t, size_t, BOARD &);
    bool            _isTileRightPlaced(int val, BOARD &);
};

#endif
