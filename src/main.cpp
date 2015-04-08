#include <npuzzle.hpp>
#include <Parser.class.hpp>
#include <Puzzle.class.hpp>
#include <string>

int main (int ac, char **av)
{
  if (ac < 2) {
    std::cerr << "Usage: ./npuzzle <map> [-h <manhattan|hamming>]" << std::endl;
    return (1);
  }
  try {
    Parser parser(av[1]);
    BOARD board = parser.parseFile();
    Puzzle puzzle(board);
    if (av[2]) {
      std::string option(av[2]);
      if (option == "-h") {
        try {
          std::string heuristic(av[3]);
          puzzle.setHeuristic(heuristic);
        } catch (Puzzle::UnknownHeuristicException & e) {
          std::cout << e.what() << std::endl;
        }
      }
    }
    puzzle.solve();
  } catch (Parser::MapNotFoundException & e) {
    std::cout << e.what() << std::endl;
  }

  return (0);
}
