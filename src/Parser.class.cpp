#include <Parser.class.hpp>
#include <fstream>

Parser::Parser() {
    return;
}

Parser::Parser(std::string fileName) : _fileName(fileName) {
    return;
}

Parser::~Parser(void) {
    return;
}

Parser::Parser(Parser const &src) {
    *this = src;
    return;
}

Parser & Parser::operator=(Parser const &src) {
    this->_fileName = src.getFileName();
    return *this;
}

std::string const & Parser::getFileName(void) const {
    return this->_fileName;
}

int const & Parser::getSize(void) const {
    return this->_size;
}

std::vector<std::vector<int>> const & Parser::getBoard(void) const {
    return this->_board;
}

void Parser::parseFile(void) {
    if (this->_fileName.empty()) {
        return;
    }

    std::ifstream file(this->_fileName);
    std::string line;
    while (std::getline(file, line)) {
        // parse the file
        /*if (line[0] != '#') {

        }*/
    }
}
