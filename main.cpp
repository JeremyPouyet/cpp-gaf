#include <cstdlib>
#include <string>

#include "./Population.hh"
#include "./Chromosome.hh"

#define SIMULATION_NUMBER 1500

bool solve(double number)
{
  Population population(number);
  int simulation_number = 0;
  population.generate();
  do
  {
    population.test();
    if (population.hasResult()) {
      std::cout << "WINNNNNEEEER" << std::endl;
      break;
    }
    if (simulation_number != SIMULATION_NUMBER - 1)
      population.reproduce();
  } while (++simulation_number < SIMULATION_NUMBER);
  if (population.hasResult())
  {
    std::cout << "Solution found in " << simulation_number + 1 << " simulations:" << std::endl;
    std::cout << number << " =" << std::flush;
    population.getWinner()->print();
    std::cout << std::endl << std::endl;
  }
  else
  {
    std::cout <<  "Solution not found" << std::endl;
    population.print();
  }
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
