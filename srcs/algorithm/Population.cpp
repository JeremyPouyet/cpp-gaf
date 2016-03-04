#include "Population.hh"

RandomGenerator Population::_random;

Population::Population() :
_problem(NULL),
selections({
    {"fitness-proportional", &Population::fitnessProportionateSelection},
    {"tournament", &Population::tournamentSelection}
}) {
}

void Population::solve(Problem *problem) {
    _problem = problem;
    unsigned int generation;
    //test if initial population already have a good solution
    bool solution = test();
    unsigned int p5 = config.simulationNumber / 100 * 5;
    unsigned int t = p5;
    for (generation = 1; generation < config.simulationNumber + 1 && solution == false; generation++) {
        reproduce();
        solution = test();
        if (generation % 100 == 0/*t == generation*/) {
            //t += p5;
            std::cout << "generation " << generation << std::endl;
            printResume();
        }
    }
    if (solution == true)
        std::cout << "Solution found in " << generation << " generations(s) " << std::endl;
    else
        std::cout << "Solution not found, best candidate is: " << std::endl;
    _problem->print(_population.front()->getStrand());
    _problem->giveBestSolution(_population.front()->getStrand());
}

void Population::printResume() const {
    std::cout << "Best: ";
    _problem->print(_population.front()->getStrand());
    std::cout << "Mid: ";
    _problem->print(_population[config.populationSize / 2]->getStrand());
    std::cout << "Worst: ";
    _problem->print(_population.back()->getStrand());
    std::cout << std::endl;
}

void Population::generate() {
    for (unsigned int i = 0; i < config.populationSize; i++)
        _population.push_back(new Chromosome());
}

bool Population::test() {
    double fitness, totalFitness = 0;
    Chromosome *candidate;
    // compute fitness of all chromosome
#pragma omp parallel for private(fitness, candidate) reduction(+:totalFitness)
    for (unsigned int i = 0; i < config.populationSize; i++) {
        candidate = _population.at(i);
        fitness = _problem->computeFitnessOf(candidate->getStrand());
        if (isnan(fitness))
            fitness = -1;
        candidate->setFitness(fitness);
        totalFitness += fitness;
    }
    // sort them by fitness
    sortByFitness();
    _totalFitness = totalFitness;
    // test if the best candidate solution solves the problem
    return _problem->test(_population.front()->getStrand());
}

void Population::print() const {
    for (auto &candidate : _population)
        _problem->print(candidate->getStrand());
}

Chromosome *Population::selectChromosome() const {
    return (this->*selections.at(config.selectionType))();
}

void Population::sortByFitness() {
    std::sort(_population.begin(), _population.end(), Chromosome());
}

void Population::reproduce() {
    Generation nextGeneration;
    Generation gens[4];
    Chromosome *c1, *c2, *child;
    // Elitism if used
    for (unsigned int i = 0; i < config.eliteNumber && i < _population.size(); i++)
        nextGeneration.push_back(new Chromosome(_population.at(i)->getStrand()));
#pragma omp parallel for private(c1, c2, child) num_threads(4)
    for (unsigned int i = nextGeneration.size(); i < config.populationSize; i++) {
        c1 = selectChromosome();
        if (_random.d0_1() <= config.crossoverRate) {
            c2 = selectChromosome();
            child = Chromosome::crossover(config.crossoverType, c1, c2);
        } else
            child = new Chromosome(c1->getStrand());
        child->mutate();
        gens[omp_get_thread_num()].push_back(child);
    }
    std::merge(gens[0].begin(), gens[0].end(), gens[1].begin(), gens[1].end(), std::back_inserter(nextGeneration));
    std::merge(gens[2].begin(), gens[2].end(), gens[3].begin(), gens[3].end(), std::back_inserter(nextGeneration));
    clean();
    _population = nextGeneration;
}

void Population::clean() {
    for (Chromosome *p : _population)
        delete p;
}

Population::~Population() {
    clean();
}

/**
 ** Selections
 */

Chromosome *Population::fitnessProportionateSelection() const {
    double randomNb = _random.d0_limit(_totalFitness);
    double curFitness = 0;
    unsigned int id = 0;
    while (curFitness < randomNb)
        curFitness += _population[id++]->getFitness();
    return _population[id];
}

Chromosome *Population::tournamentSelection() const {
    // use set to ensure chromosome uniqueness
    std::set<int> subPop;
    int id, bestId = _population.size() - 1;
    double tmpFitness, bestFitness = _population.back()->getFitness();
    // for each tournament
    do {
        // randomly select a chromosome
        id = _random.i0_limit(config.populationSize - 1);
        subPop.insert(id);
        tmpFitness = _population.at(id)->getFitness();
        // and check if it's better than the other
        if (tmpFitness > bestFitness) {
            // if so, set it as the winner
            bestFitness = tmpFitness;
            bestId = id;
        }
        //subPop.push_back(id);
    } while (subPop.size() != config.tournamentSize);
    return _population[bestId];
}
