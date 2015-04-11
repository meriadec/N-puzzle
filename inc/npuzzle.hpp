#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

#include <iostream>
#include <vector>

#define BOARD std::vector<std::vector<int>>

typedef struct      s_infos
{
    size_t      timeCpl;
    size_t      sizeCpl;
}                   t_infos;

class BadMapDimensionsException : public std::exception {
    virtual const char * what (void) const throw () { return "Wrong dimensions."; }
};

class IterationsTooSmallException : public std::exception {
    virtual const char * what (void) const throw () { return "iterations need to be > 0"; }
};

class MissingArgException : public std::exception {
    virtual const char * what (void) const throw () { return "Missing argument."; }
};

#endif
