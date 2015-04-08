#ifndef PUZZLE_CLASS_H
#define PUZZLE_CLASS_H

#include <npuzzle.hpp>
#include <Node.class.hpp>
#include <vector>
#include <list>
#include <map>

class Puzzle {

public:
    Puzzle(void);
    Puzzle(BOARD const &);
    virtual ~Puzzle(void);

    bool            isSolvable (void);
    int             getSumManhattanDistances (BOARD &);
    int             getHammingDistance (BOARD &);
    void            solve (void);

private:

    Puzzle (Puzzle const & src);
    Puzzle & operator= (Puzzle const & src);

    BOARD   _board;
    BOARD   _finalBoard;

    std::map<int,std::pair<size_t,size_t>>    _finalPositions;

    int                 _getPermutations (std::list<int> &);
    std::list<int>      _getSerpent (std::vector<std::vector<int>> &);
    void                _buildFinalBoard (void);
    void                _buildFinalPositions (void);
    int                 _getManhattanDistance (size_t, size_t, BOARD &);
    bool                _isTileRightPlaced(int val, BOARD &);
    std::list<Node>     _getAvailableMoves(Node &);
};

#endif
