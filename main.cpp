#include <cstdlib>
#include <string>

#include <iostream>
#include <string>

#include "AProblem.hh"
#include "Config.hh"
#include "Population.hh"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Wrong number of arguments: ./number problemDirectory" << std::endl;
        return 1;
    }
    std::string configurationPath = std::string(av[1]) + "problem.ini";
    std::string problemPath = std::string(av[1]) + "problem.so";
    std::srand(time(NULL));
    ProblemLoader problemLoader;
    if (config.load(configurationPath) == false) {
        std::cerr << "Can't load configuration file " << std::endl;
        return 3;
    }
    config.display();
    try {
        problemLoader.load(problemPath);
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
