#include <string>
#include <iostream>
#include <string>

#include "AProblem.hh"
#include "Config.hh"
#include "Population.hh"

bool initialise(Problem *problem, Population &population) {
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
    if (error == true)
        return false;
    return true;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Wrong number of arguments: ./open-gaf problemDirectory" << std::endl;
        return 1;
    }
    std::string configurationPath = std::string(av[1]) + "problem.ini";
    std::string problemPath = std::string(av[1]) + "problem.so";
    std::srand(time(NULL));
    ProblemLoader problemLoader;
    if (config.load(configurationPath) == false)
        return 2;
    config.display();
    Problem *problem = (AProblem *)problemLoader.load(problemPath);
    if (problem == NULL)
        return 3;
    Population population;
    if (initialise(problem, population) == false) {
        std::cerr << "Problem while loading data" << std::endl;
        return 4;
    }
    population.solve(problem);
    return 0;
}
