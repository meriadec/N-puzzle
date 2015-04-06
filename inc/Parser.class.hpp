#ifndef PARSER_CLASS_H
#define PARSER_CLASS_H

#include <string>
#include <vector>

class Parser {

public:
    Parser(std::string);
    virtual ~Parser(void);
    Parser(Parser const & src);
    Parser & operator=(Parser const & src);

    std::string const & getFileName(void) const;
    int const & getSize(void) const;

    std::vector<std::vector<int>> parseFile(void);

private:
    Parser();

    std::string _fileName;
    int _size;

};

#endif
