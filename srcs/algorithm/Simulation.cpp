#include "Simulation.hh"

void Simulation::run() {
    _timer.start();
    Population population(_problem);
    if (solve(population) == true)
        _display.basicLine("Solution found in " + std::to_string(_currentGeneration) + " generations(s) ");
    else
        _display.basicLine("Solution not found, best candidate is: ");
    _problem->print(population.best());
    _timer.stop();
    _problem->giveBestSolution(population.best());
    if (config.verbose)
        _display.basicLine("Simulation took " + std::to_string(_timer.getTime()) + "s");
}

bool Simulation::solve(Population &population) {
    bool solution = population.checkForWinner();
    unsigned int p5 = config.simulationNumber / 100 * 5;
    for (; _currentGeneration < config.simulationNumber + 1 && solution == false; ++_currentGeneration) {
        population.reproduce();
        solution = population.checkForWinner();
        // print information about the current population each 5% of generation
        if (config.verbose && _currentGeneration % p5 == 0)
            printResume(population);
    }
    return solution;
}

void Simulation::printResume(const Population &population) const {
    _display.basicLine("generation " + std::to_string(_currentGeneration) + "/" + std::to_string(config.simulationNumber));
    _display.basicLine("Best: ");
    _problem->print(population.best());
    _display.basicLine("Mid: ");
    _problem->print(population.at(config.populationSize / 2));
    _display.basicLine("Worst: ");
    _problem->print(population.worst());
    _display.newLine();
}

int Simulation::initialise(int ac, char **av) {
    int ret = configInitialisation(ac, av);
    if (ret != 1) return ret;
    _problem = dynamic_cast<AProblem *>(_problemLoader.load(config.getProblemPath()));
    if (_problem == NULL)
        return -1;
    Chromosome::_problem = _problem;
    if (userInitialisation() == false) {
        _display.error("Problem while loading data");
        return -1;
    }
    if (config.verbose)
        _display.showConf();
    return 1; 
}

bool Simulation::userInitialisation() {
    bool error = false;
    // Don't waste time, load and generate data while the user enter parameters
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            _problem->askParameters();
        }
        #pragma omp section
        {
            (dynamic_cast<AProblem *>(_problem))->setConfig(config);
            if (_problem->loadData() == false)
                error = true;
        }
    }
    return !error;
}

int Simulation::configInitialisation(int ac, char **av) {
    if (ac < 2) {
        _display.usage();
        return -1;
    }
    config.parseOptions(ac, av);
    if (config.help == true) {
        _display.help();
        return 0;
    }
    return (config.load() == false) ? -1 : 1;
}

Simulation::~Simulation() {
    _problemLoader.close();
}