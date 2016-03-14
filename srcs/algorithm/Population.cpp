#include "Population.hh"

RandomGenerator Population::_random;

Population::Population(Problem *problem) :
_population(config.populationSize),
_nextGeneration(config.populationSize),
_currentGeneration(1),
_problem(problem),
selections({
    {"fitness-proportional", &Population::fitnessProportionateSelection},
    {"tournament", &Population::tournamentSelection}
}) {
    double fitness;
    for (auto &candidate : _population) {
        candidate.generate();
        fitness = _problem->computeFitnessOf(candidate.getStrand());
        candidate.setFitness(fitness);
    }
}

void Population::solve() {
    //test if initial population already have a good solution
    bool solution = test();
    unsigned int p5 = config.simulationNumber / 100 * 5;
    for (; _currentGeneration < config.simulationNumber + 1 && solution == false; ++_currentGeneration) {
        reproduce();
        solution = test();
        // print information about the current population each 5% of generation
        if (config.verbose && _currentGeneration % p5 == 0)
            printResume();
    }
    if (solution == true)
        std::cout << "Solution found in " << _currentGeneration << " generations(s) " << std::endl;
    else
        std::cout << "Solution not found, best candidate is: " << std::endl;
    _problem->print(_population.front().getStrand());
    _problem->giveBestSolution(_population.front().getStrand());
}

void Population::printResume() const {
    std::cout << "generation " << _currentGeneration << std::endl;
    std::cout << "Best: ";
    _problem->print(_population.front().getStrand());
    std::cout << "Mid: ";
    _problem->print(_population[config.populationSize / 2].getStrand());
    std::cout << "Worst: ";
    _problem->print(_population.back().getStrand());
    std::cout << std::endl;
}

bool Population::test() {
    // compute fitness of all chromosome
    if (config.selectionType == "fitness-proportional")
        for (const auto &candidate : _population)
            _totalFitness += candidate.getFitness();
    // sort them by fitness
    sortByFitness();
    // test if the best candidate solution solves the problem
    return _problem->test(_population.front().getStrand());
}

void Population::print() const {
    for (const auto &candidate : _population)
        _problem->print(candidate.getStrand());
}

unsigned int Population::selectChromosome() const {
    return (this->*selections.at(config.selectionType))();
}

void Population::sortByFitness() {
    std::sort(_population.begin(), _population.end(), Chromosome());
}

void Population::reproduce() {
    double fitness;
    unsigned int c1, c2;
    int modified;
    Strand child;
    // Elitism if used
    for (unsigned int i = 0; i < config.eliteNumber; ++i) 
        _nextGeneration[i] = _population[i];
    #pragma omp parallel for private(c1, c2, child, fitness, modified)
    for (unsigned int i = config.eliteNumber; i < config.populationSize; ++i) {
        modified = 0;
        c1 = selectChromosome();
        if (_random.d0_1() <= config.crossoverRate) {
            c2 = selectChromosome();
            child = Chromosome::crossover(config.crossoverType, _population[c1].getStrand(), _population[c2].getStrand());
            ++modified;
        }
        else
            child = _population[c1].getStrand();
        _nextGeneration[i].setStrand(child);
        modified += _nextGeneration[i].mutate();
        if (modified > 0)
            fitness = _problem->computeFitnessOf(_nextGeneration[i].getStrand());
        else
            fitness = _population[c1].getFitness();
        _nextGeneration[i].setFitness(fitness);
    }
   _population = _nextGeneration;
}

/**
 ** Selections
 */

unsigned int Population::fitnessProportionateSelection() const {
    double randomNb = _random.d0_limit(_totalFitness);
    double curFitness = 0;
    unsigned int id = 0;
    while (curFitness < randomNb)
        curFitness += _population[id++].getFitness();
    return id;
}

unsigned int Population::tournamentSelection() const {
    // use set to ensure chromosome uniqueness
    std::set<int> subPop;
    int id, bestId = _population.size() - 1;
    // for each tournament
    do {
        // randomly select a chromosome
        id = _random.i0_limit(config.populationSize - 1);
        subPop.insert(id);
        // and check if it's better than the other
        if (_population[id].getFitness() > _population[bestId].getFitness())
            bestId = id;
    } while (subPop.size() != config.tournamentSize);
    return bestId;
}
