#include <Node.class.hpp>

Node::Node(void) {

}

Node::~Node(void) {

}

Node::Node(Node const &src) {
    *this = src;
}

Node & Node::operator=(Node const &src) {
    this->board = src.board;
    this->f = src.f;
    this->g = src.g;
    this->h = src.h;
    this->parent = src.parent;
    return *this;
}

bool Node::operator==(Node const &src) {
    return this->h == src.h && this->board == src.board;
}
