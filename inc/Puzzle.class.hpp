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

    void print(void);

    bool isSolvable (void);

private:

    Puzzle (Puzzle const & src);
    Puzzle & operator= (Puzzle const & src);

    std::vector<std::vector<int>> _board;

    int             _getPermutations (std::list<int> &);
    std::list<int>  _getSerpent (std::vector<std::vector<int>> &);
};

#endif
