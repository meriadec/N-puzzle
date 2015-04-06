#include <Parser.class.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

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

std::vector<std::vector<int>> Parser::parseFile(void) {
    if (this->_fileName.empty()) {
        // FIXME
        throw new std::exception();
    }
    std::ifstream file(this->_fileName);
    std::string line;
    std::vector<std::vector<int>> board;
    int i = 0;
    while (std::getline(file, line)) {
        unsigned long com = line.find('#');
        if (com != std::string::npos) {
            line = line.substr(0, com);
        }
        if (!line.empty()) {
            if (i == 0) {
                this->_size = std::stoi(line);
            } else {
                std::vector<int> row;
                std::string delimiter = " ";
                size_t pos = 0;
                std::string token;
                while ((pos = line.find(delimiter)) != std::string::npos) {
                    token = line.substr(0, pos);
                    if (!token.empty()) {
                        row.push_back(std::stoi(token));
                    }
                    line.erase(0, pos + delimiter.length());
                }
                if (!line.empty()) {
                    row.push_back(std::stoi(line));
                }
                board.push_back(row);
            }
            i++;
        }
    }
    return board;
}
