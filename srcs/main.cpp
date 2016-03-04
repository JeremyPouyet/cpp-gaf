#include <string>
#include <iostream>
#include <string>

#include "AProblem.hh"
#include "Config.hh"
#include "Population.hh"
#include "Display.hpp"

bool userInitialization(Problem *problem, Population &population) {
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
            (dynamic_cast<AProblem *>(problem))->setConfig(config);
            if (problem->loadData() == false)
                error = true;
            else {
                population.generate();
            }
        }
    }
    return !error;
}

static int configInitialization(const Display &display, int ac, char **av) {
    if (ac != 2) {
        display.usage();
        return -1;
    }
    config.parseOptions(ac, av);
    if (config.help == true) {
        display.help();
        return 0;
    }        
    std::string configurationPath = std::string(av[1]) + "problem.ini";
    if (config.load(configurationPath) == false)
        return -1;
    return 1;
}

int main(int ac, char **av)
{
    Display &display = Display::getInstance();
    int ret = configInitialization(display, ac, av);
    if (ret != 1) return ret;
    display.conf();
    ProblemLoader problemLoader;
    std::string problemPath = std::string(av[1]) + "problem.so";
    Problem *problem = dynamic_cast<AProblem *>(problemLoader.load(problemPath));
    if (problem == NULL) {
        return -1;
    }
    Population population;
    if (userInitialization(problem, population) == false) {
        std::cerr << "Problem while loading data" << std::endl;
        return -1;
    }
    population.solve(problem);
    problemLoader.close();
    return 0;
}
