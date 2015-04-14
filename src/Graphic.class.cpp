#include <Graphic.class.hpp>

Graphic::Graphic (int w, int h) : _w(w), _h(h)
{
    this->_win = new sf::RenderWindow(sf::VideoMode(this->_w, this->_h), "Yolo");
}

Graphic::~Graphic (void) {
}

void Graphic::displaySolution (std::list<Node *> list) {
    static_cast<void>(list);
}

void Graphic::beginDraw (void) {
    this->_win->clear(sf::Color::Black);
}

void Graphic::endDraw (void) {
    this->_win->display();
}

e_keys Graphic::getInput (void) {
    sf::Event event;
    while (this->_win->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            this->_win->close();
            return e_keys::ESC;
        }
    }
    return e_keys::NONE;
}

void Graphic::drawCell (int y, int x, int val) {

    sf::RectangleShape square(sf::Vector2f(100, 100));
    sf::Color color(130, 240, 255);

    square.setFillColor(color);
    square.setPosition(x, y);
    this->_win->draw(square);
}
