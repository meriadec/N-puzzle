#include <npuzzle.hpp>
#include <sstream>
#include <Parser.class.hpp>
#include <Puzzle.class.hpp>
#include <Utils.class.hpp>

int main (int ac, char **av)
{
  if (ac < 2) {
    std::cerr << "Usage: ./npuzzle [-f file] [-s size] [-i iterations] [-h <manhattan|hamming|third>]" << std::endl;
    return -1;
  }
  try {

    Puzzle puzzle;

    bool generate = true;
    size_t sizeToGenerate = 5;
    size_t iterations = 100;

    for (int i = 1; i < ac; i++) {

      std::string option(av[i]);

      // -> file option
      if (option == "-f") {
        if (ac <= i + 1) { throw MissingArgException(); }
        Parser parser(av[++i]);
        puzzle.setBoard(parser.parseFile());
        generate = false;
      }

      // -> heuristic option
      if (option == "-h") {
        if (ac <= i + 1) { throw MissingArgException(); }
        std::string heuristic(av[++i]);
        try { puzzle.setHeuristic(heuristic); }
        catch (Puzzle::UnknownHeuristicException & e) {
          std::cerr << e.what() << std::endl;
          return 1;
        }
      }

      // -> size option
      if (option == "-s") {
        if (ac <= i + 1) { throw MissingArgException(); }
        std::stringstream ss;
        ss << av[++i];
        ss >> sizeToGenerate;
        if (sizeToGenerate < 3) { throw MapTooSmallException(); }
      }

      // -> iterations option
      if (option == "-i") {
        if (ac <= i + 1) { throw MissingArgException(); }
        std::stringstream ss;
        ss << av[++i];
        ss >> iterations;
        if (iterations < 1) { throw IterationsTooSmallException(); }
      }

    }

    if (generate) {
      puzzle.setBoard(Utils::generateBoard(sizeToGenerate, iterations));
    }

    puzzle.solve();

  } catch (std::exception & e) {
    std::cout << "Error: " << e.what() << std::endl;
    return (1);
  }

  return (0);
}
