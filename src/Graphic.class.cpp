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
    this->_win->clear(sf::Color(7, 54, 66));
    sf::RectangleShape square(sf::Vector2f(300, this->_h));
    square.setFillColor(sf::Color(0, 43, 54));
    square.setPosition(this->_w - 300, 0);
    this->_win->draw(square);
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

    sf::Color borderColor(101, 123, 131);
    sf::Color bgColor(88, 110, 117);

    sf::RectangleShape square(sf::Vector2f(100, 100));

    square.setOutlineColor(borderColor);
    square.setOutlineThickness(2);
    square.setFillColor(bgColor);
    square.setPosition(y * 110 + 10, x * 110 + 10);
    this->_win->draw(square);
}
