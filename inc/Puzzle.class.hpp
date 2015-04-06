#ifndef PUZZLE_CLASS_H
#define PUZZLE_CLASS_H

#include <npuzzle.hpp>
#include <vector>
#include <list>

class Puzzle {

public:
    Puzzle(void);
    Puzzle(std::vector<std::vector<int>>);
    virtual ~Puzzle(void);

    void print(void);

    bool isSolvable (void);
    int getManhattanDistance (size_t, size_t, std::vector<std::vector<int>> &);

private:

    Puzzle (Puzzle const & src);
    Puzzle & operator= (Puzzle const & src);

    std::vector<std::vector<int>> _board;

    int             _getPermutations (std::list<int> &list);
    std::list<int>  _getSerpent (std::vector<std::vector<int>> &);
    std::pair<size_t, size_t> _getPos (int val, std::vector<std::vector<int>> &board);
};

#endif
