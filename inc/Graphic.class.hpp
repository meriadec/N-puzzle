#ifndef GRAPHIC_CLASS_H
#define GRAPHIC_CLASS_H

#include <Node.class.hpp>
#include <npuzzle.hpp>

#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Graphic {

public:
    Graphic(int, int);
    virtual ~Graphic(void);

    void displaySolution (std::list<Node *>);
    e_keys getInput (void);

    void beginDraw (void);
    void endDraw (void);
    void drawCell (int y, int x, int val);
    void drawPos (int pos, int total);
    void drawArrows (bool left, bool right);

private:
    Graphic(void);
    Graphic (Graphic const & src);
    Graphic & operator= (Graphic const & src);

    int _w;
    int _h;

    sf::Font    _font;

    sf::RenderWindow * _win;

};

#endif
