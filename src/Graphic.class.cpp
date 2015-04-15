#include <Graphic.class.hpp>
#include <string>

Graphic::Graphic (int w, int h) : _w(w), _h(h)
{
    this->_win = new sf::RenderWindow(sf::VideoMode(this->_w, this->_h), "Yolo");
    this->_font.loadFromFile("./fonts/Menlo-Regular.ttf");
}

Graphic::~Graphic (void) {
}

void Graphic::displaySolution (std::list<Node *> list) {
    static_cast<void>(list);
}

void Graphic::beginDraw (void) {
    this->_win->clear(sf::Color(7, 54, 66));

    sf::RectangleShape squareRight(sf::Vector2f(100, this->_h));
    squareRight.setFillColor(sf::Color(0, 43, 54));
    squareRight.setPosition(this->_w - 100, 0);
    this->_win->draw(squareRight);

    sf::RectangleShape squareLeft(sf::Vector2f(100, this->_h));
    squareLeft.setFillColor(sf::Color(0, 43, 54));
    squareLeft.setPosition(0, 0);
    this->_win->draw(squareLeft);
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
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    this->_win->close();
                    return e_keys::ESC;
                case sf::Keyboard::Left:
                    return e_keys::LEFT;
                case sf::Keyboard::Right:
                    return e_keys::RIGHT;
                default:
                    break;
            }
        }
    }
    return e_keys::NONE;
}

void Graphic::drawCell (int y, int x, int val) {

    sf::Color borderColor(101, 123, 131);
    sf::Color bgColor(88, 110, 117);
    sf::Color textColor(238, 232, 213);

    sf::RectangleShape square(sf::Vector2f(100, 100));

    square.setOutlineColor(borderColor);
    square.setOutlineThickness(2);
    square.setFillColor(bgColor);
    square.setPosition(x * 110 + 100 + 10, y * 110 + 10);
    this->_win->draw(square);

    // text
    std::string valStr = std::to_string(val);
    sf::Text    text(valStr, this->_font);
    sf::Text    shadow(valStr, this->_font);
    int         textX = static_cast<int>(x * 110 + 100 + 10 + 50 - text.getLocalBounds().width / 2);
    int         textY = y * 110 + 10 + 30;

    text.setCharacterSize(30);
    shadow.setCharacterSize(30);
    text.setColor(textColor);
    shadow.setColor(sf::Color(7, 54, 66));
    text.setPosition(textX, textY);
    shadow.setPosition(textX, textY + 2);
    this->_win->draw(shadow);
    this->_win->draw(text);
}
