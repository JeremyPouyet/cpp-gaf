#include <cstdlib>
#include <string>

#include <iostream>
#include <dlfcn.h>

#include "./Population.hh"
#include "./Chromosome.hh"
#include "./Problem.hh"

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
    solution->print();
    return true;
  }
  std::cout <<  "Solution not found" << std::endl;
  population.print();
  return false;
}

int main(int ac, char **av)
{
    void *pb = dlopen("./EquationProblem.so", RTLD_LAZY);
    if (!pb) {
        std::cerr << "Cannot open lib" << std::endl;
        return 1;
    }
    
    dlerror();
    create_t *create_problem = (create_t *)dlsym(pb, "create");
    const char * dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load create symbol" << dlsym_error << std::endl;
        return 1;
    }
    
    destroy_t *destroy_problem = (destroy_t *)dlsym(pb, "destroy");
    dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load destroy symbol " << dlsym_error << std::endl;
        return 1;
    }
    
    Problem *problem = create_problem();
    problem->print();
    
    destroy_problem(problem);
    dlclose(pb);
    return 0;
    
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
