#include <cstdlib>
#include <string>

#include <iostream>

#include "Config.hh"
#include "Population.hh"
#include "Chromosome.hh"
#include "INIReader.h"

extern Config config;

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cout << "Wrong number of arguments: ./number problem config" << std::endl;
        return 1;
    }
    std::srand(time(NULL));
    ProblemLoader problemLoader;
    try {
        problemLoader.load(av[1]);
    } catch(std::string &error) {
       std::cerr << error << std::endl;
       return 2;
    }
    if (config.load(av[2]) == false) {
        std::cerr << "Can't load config file " << std::endl;
        return 3;
    }
    Population p(problemLoader.getProblem());
    return p.solve();
}
