#include <npuzzle.hpp>
#include <Parser.class.hpp>
#include <Puzzle.class.hpp>
#include <Utils.class.hpp>

int main (int ac, char **av)
{
  if (ac != 2) {
    std::cerr << "Usage: ./npuzzle <map>" << std::endl;
    return (1);
  }
  try {
    Parser parser(av[1]);
    BOARD board = parser.parseFile();
    Puzzle puzzle(board);
    Utils::printBoard(board);
    std::cout << Utils::getSumManhattanDistances(board) << std::endl;
    std::cout << Utils::getHammingDistance(board) << std::endl;
  } catch (Parser::MapNotFoundException & e) {
    std::cout << e.what() << std::endl;
  }

  return (0);
}
