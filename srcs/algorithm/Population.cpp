#include "Population.hh"

RandomGenerator Population::_random;

Population::Population() :
_population(config.populationSize),
_problem(NULL),
selections({
    {"fitness-proportional", &Population::fitnessProportionateSelection},
    {"tournament", &Population::tournamentSelection}
}) {
    for (auto &candidate: _population)
        candidate.generate();
}

void Population::solve(Problem *problem) {
    _problem = problem;
    unsigned int generation;
    //test if initial population already have a good solution
    bool solution = test();
    unsigned int p5 = config.simulationNumber / 100 * 5;
    for (generation = 1; generation < config.simulationNumber + 1 && solution == false; generation++) {
        reproduce();
        solution = test();
        if (generation % p5 == 0)
            printResume(generation);
    }
    if (solution == true)
        std::cout << "Solution found in " << generation << " generations(s) " << std::endl;
    else
        std::cout << "Solution not found, best candidate is: " << std::endl;
    _problem->print(_population.front().getStrand());
    _problem->giveBestSolution(_population.front().getStrand());
}

void Population::printResume(unsigned int generation) const {
    std::cout << "generation " << generation << std::endl;
    std::cout << "Best: ";
    _problem->print(_population.front().getStrand());
    std::cout << "Mid: ";
    _problem->print(_population[config.populationSize / 2].getStrand());
    std::cout << "Worst: ";
    _problem->print(_population.back().getStrand());
    std::cout << std::endl;
}

bool Population::test() {
    double fitness, totalFitness = 0;
    // compute fitness of all chromosome
    #pragma omp parallel for private(fitness) reduction(+:totalFitness)
    for (unsigned int i = 0; i < config.populationSize; i++) {
        fitness = _problem->computeFitnessOf(_population.at(i).getStrand());
        if (isnan(fitness))
            fitness = -1;
        _population.at(i).setFitness(fitness);
        totalFitness += fitness;
    }
    // sort them by fitness
    sortByFitness();
    _totalFitness = totalFitness;
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
    Generation nextGeneration(config.populationSize);
    unsigned int c1, c2;
    Strand child;
    // Elitism if used
    for (unsigned int i = 0; i < config.eliteNumber; i++)
        nextGeneration[i].set(_population.at(i).getStrand());
    #pragma omp parallel for private(c1, c2, child)
    for (unsigned int i = config.eliteNumber; i < config.populationSize; i++) {
        c1 = selectChromosome();
        if (_random.d0_1() <= config.crossoverRate) {
            c2 = selectChromosome();
            child = Chromosome::crossover(config.crossoverType, _population.at(c1), _population.at(c2));
        } else
            child = _population.at(c1).getStrand();
        nextGeneration[i].set(child);
        nextGeneration[i].mutate();
    }
    _population = nextGeneration;
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
    double tmpFitness, bestFitness = _population.back().getFitness();
    // for each tournament
    do {
        // randomly select a chromosome
        id = _random.i0_limit(config.populationSize - 1);
        subPop.insert(id);
        tmpFitness = _population.at(id).getFitness();
        // and check if it's better than the other
        if (tmpFitness > bestFitness) {
            // if so, set it as the winner
            bestFitness = tmpFitness;
            bestId = id;
        }
        //subPop.push_back(id);
    } while (subPop.size() != config.tournamentSize);
    return bestId;
}
