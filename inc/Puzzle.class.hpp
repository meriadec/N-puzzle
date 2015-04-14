#ifndef PUZZLE_CLASS_H
#define PUZZLE_CLASS_H

#include <npuzzle.hpp>
#include <Node.class.hpp>
#include <vector>
#include <list>
#include <map>

class Puzzle {

typedef int (Puzzle::*h_func)(BOARD const &) const;

public:
    Puzzle(void);
    Puzzle(BOARD const &);
    virtual ~Puzzle(void);

    bool            isSolvable (void);
    int             getSumManhattanDistances (BOARD const &) const;
    int             getHammingDistance (BOARD const &) const;
    int             getThirdHeuristicDistance (BOARD const &) const;
    void            solve (void);
    void            setHeuristic(std::string &);
    void            setBoard(BOARD);
    BOARD           getBoard(void);
    BOARD           getFinalBoard(void);

    class UnknownHeuristicException : public std::exception {
    public:
        virtual const char * what (void) const throw () {
            return "Unknown heuristic.";
        }
    };

private:

    Puzzle (Puzzle const & src);
    Puzzle & operator= (Puzzle const & src);

    BOARD       _board;
    BOARD       _finalBoard;
    h_func      _heuristic;

    std::map<int,std::pair<size_t,size_t>>    _finalPositions;

    int                 _getPermutations (void);
    std::list<int>      _getSerpent (std::vector<std::vector<int>> &);
    std::vector<int>    _getVec (std::vector<std::vector<int>> &);
    void                _buildFinalBoard (void);
    void                _buildFinalPositions (void);
    int                 _getManhattanDistance (size_t, size_t, BOARD const &) const;
    bool                _isTileRightPlaced(int val, BOARD const &) const;
    std::list<Node *>   _getAvailableMoves(Node *);
    bool                _isRightRow (int, size_t) const;
    bool                _isRightCol (int, size_t) const;
};

#endif
