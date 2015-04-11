#ifndef PARSER_CLASS_H
#define PARSER_CLASS_H

#include <string>
#include <npuzzle.hpp>

class Parser {

public:
    Parser(std::string);
    virtual ~Parser(void);
    Parser(Parser const & src);
    Parser & operator=(Parser const & src);

    std::string const & getFileName(void) const;
    int const & getSize(void) const;

    BOARD parseFile(void);

    class MapNotFoundException : public std::exception {
    public:
        virtual const char * what (void) const throw () {
            return "Map not found.";
        }
    };

private:
    Parser();

    std::string _fileName;
    int _size;

};

#endif
