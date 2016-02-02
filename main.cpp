#include <cstdlib>
#include <string>

#include <iostream>

#include "AProblem.hh"
#include "Config.hh"
#include "Population.hh"
#include "Chromosome.hh"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cout << "Wrong number of arguments: ./number problem config" << std::endl;
        return 1;
    }
    std::srand(time(NULL));
    ProblemLoader problemLoader;
    if (config.load(av[2]) == false) {
        std::cerr << "Can't load config file " << std::endl;
        return 3;
    }
    try {
        problemLoader.load(av[1]);
    } catch(std::string &error) {
       std::cerr << error << std::endl;
       return 2;
    }
    Problem *problem = problemLoader.getProblem();
    ((AProblem *)problem)->setConfig(config);
    Population p(problem);
    return p.solve();
}
