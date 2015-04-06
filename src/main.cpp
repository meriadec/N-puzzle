#include <npuzzle.hpp>
#include <Parser.class.hpp>
#include <Puzzle.class.hpp>

int main (int ac, char **av)
{
  if (ac != 2) {
    std::cerr << "Usage: ./npuzzle <map>" << std::endl;
    return (1);
  }
  Parser parser(av[1]);
  std::vector<std::vector<int>> board = parser.parseFile();
  Puzzle puzzle(board);
  puzzle.print();

  return (0);
}
