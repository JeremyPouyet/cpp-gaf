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
        std::cerr << "Wrong number of arguments: ./number problem configuration_file" << std::endl;
        return 1;
    }
    std::srand(time(NULL));
    ProblemLoader problemLoader;
    if (config.load(av[2]) == false) {
        std::cerr << "Can't load configuration file " << std::endl;
        return 3;
    }
    config.display();
    try {
        problemLoader.load(av[1]);
    } catch(std::string &error) {
       std::cerr << error << std::endl;
       return 2;
    }
    Problem *problem = (AProblem *)problemLoader.getProblem();
    Population population;
    bool error = false;
    // Don't waste of time, load and generate data while the user enter parameters
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            problem->askParameters();
        }
        #pragma omp section
        {
            ((AProblem *)problem)->setConfig(config);
            if (problem->loadData() == false)
                error = true;
            population.generate();
        }
    }
    if (error == true) {
        std::cerr << "Problem while loading data" << std::endl;
        return 4;
    }
    population.solve(problem);
    return 0;
}
