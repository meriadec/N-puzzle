#ifndef PUZZLE_CLASS_H
#define PUZZLE_CLASS_H

#include <vector>

class Puzzle {

public:
    Puzzle(void);
    Puzzle(std::vector<std::vector<int>>);
    virtual ~Puzzle(void);

    void print(void);

private:

    Puzzle(Puzzle const & src);
    Puzzle & operator=(Puzzle const & src);

    std::vector<std::vector<int>> _board;

};

#endif
