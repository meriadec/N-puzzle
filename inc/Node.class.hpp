#ifndef NODE_CLASS_H
#define NODE_CLASS_H

#include <npuzzle.hpp>

class Node {

public:
    Node(void);
    virtual ~Node(void);
    Node (Node const & src);
    Node & operator= (Node const & src);
    bool operator== (Node const & src);

    BOARD   board;
    Node *  parent;
    int     h;
    int     g;
    int     f;

};

#endif
