#include <cstdlib>
#include <string>

#include "./Population.hh"
#include "./Chromosome.hh"

#define SIMULATION_NUMBER 1500

bool solve(double number)
{
  Population population(number);
  int generation;
  Chromosome *solution;
  population.generate();
  for (generation = 0; generation < SIMULATION_NUMBER; ++generation)
  {
    if ((solution = population.test()) != NULL)
      break;
    population.reproduce();
  }
  if (solution)
  {
    std::cout << "Solution found in " << generation + 1 << " generation(s)" << std::endl;
    solution->prettyPrint();
    std::cout << " = " << number << std::endl;
    return true;
  }
  std::cout <<  "Solution not found" << std::endl;
  population.print();
  return false;
}

int main(int ac, char **av)
{
  if (ac != 2) {
    std::cout << "Wrong number of arguments: ./number number" << std::endl;
    return 1;
  }
  double number;
  try
  {
    number = std::stod(av[1]);
  }
  catch (std::exception &ia)
  {
    std::cout << "Wrong argument type, arg need to be a double" << std::endl;
    return 2;
  }
  std::srand(time(NULL));
  if (solve(number))
    return 0;
  return 3;
}
