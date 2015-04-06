#include <npuzzle.hpp>

int main (int ac, char **av) {

int main (int ac, char **av)
{
  static_cast<void>(av);
  if (ac != 2) {
    std::cerr << "Usage: ./npuzzle <map>" << std::endl;
    return (1);
  }
  return (0);
}
