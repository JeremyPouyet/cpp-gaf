#include <cstdlib>
#include <string>

#include <iostream>

#include "./Population.hh"
#include "./Chromosome.hh"
#include "INIReader.h"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cout << "Wrong number of arguments: ./number problem config" << std::endl;
        return 1;
    }
    std::srand(time(NULL));
    ProblemLoader pl;
    try {
        pl.load(av[1]);
    } catch(std::string &error) {
       std::cerr << error << std::endl;
       return 2;
    }
    INIReader reader(av[2]);
    if (reader.ParseError() < 0) {
      std::cerr << "Can't load config file " << av[2] << std::endl;
      return 3;
    }
    Problem * problem = pl.getProblem();
    Population p;
    return p.solve(problem, reader);
}
