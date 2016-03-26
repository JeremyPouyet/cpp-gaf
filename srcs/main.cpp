#include <string>
#include <iostream>
#include <string>

#include "AProblem.hh"
#include "Config.hh"
#include "Population.hh"
#include "Display.hpp"

bool userInitialization(Problem *problem) {
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
        }
    }
    return !error;
}

static int configInitialization(const Display &display, int ac, char **av) {
    if (ac < 2) {
        display.usage();
        return -1;
    }
    std::string configurationPath = std::string(av[1]) + "problem.ini";
    config.parseOptions(ac, av);
    if (config.help == true) {
        display.help();
        return 0;
    }        
    if (config.load(configurationPath) == false)
        return -1;
    return 1;
}

int main(int ac, char **av) {
    Display &display = Display::getInstance();
    std::string problemPath = std::string(av[1]) + "problem.so";
    int ret = configInitialization(display, ac, av);
    if (ret != 1) return ret;
    display.conf();
    ProblemLoader problemLoader;
    Problem *problem = dynamic_cast<AProblem *>(problemLoader.load(problemPath));
    if (problem == NULL)
        return -1;
    if (userInitialization(problem) == false) {
        std::cerr << "Problem while loading data" << std::endl;
        return -1;
    }
    Population population(problem);
    population.solve();
    problemLoader.close();
    return 0;
}
