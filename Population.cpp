#include "Population.hh"

Population::Population() : 
        _problem(NULL),
        selections({
            {"fitness-proportional", &Population::fitnessProportionateSelection},
            {"tournament", &Population::tournamentSelection}})
{ }

void Population::solve(Problem *problem) {
    _problem = problem;
    unsigned int generation;
    //test if initial population already have a good solution
    bool solution = test();
    for (generation = 0; generation < config.simulationNumber && solution == false; generation++)
    {
        reproduce();
        if (test() == true)
            solution = true;
    }
    if (solution == true)
        std::cout << "Solution found in " << generation + 1 << " generations(s) " << std::endl;
    else
        std::cout << "Solution not found, best candidate is: " << std::endl;
    print();
    _problem->print(_population.front()->getStrand());
    _problem->giveBestSolution(_population.front()->getStrand());
}

void Population::generate()
{
    for (unsigned int i = 0; i < config.populationSize; i++)
        _population.push_back(new Chromosome());
}

bool Population::test()
{
    double fitness, totalFitness = 0;
    Chromosome *candidate;
    // compute fitness of all chromosome
    #pragma omp parallel for private(fitness, candidate) reduction(+:totalFitness)
    for (unsigned int i = 0; i < config.populationSize; i++) {
        candidate = _population.at(i);
        fitness = _problem->computeFitnessOf(candidate->getStrand());
        candidate->setFitness(fitness);
        totalFitness += fitness;
    }
    // sort them by fitness
    sortByFitness();
    _totalFitness = totalFitness;
    /*std::cout << "Best: ";
    _problem->print(_population.front()->getStrand());
    std::cout << "Mid: ";
    _problem->print(_population[config.populationSize/2]->getStrand());
    std::cout << "Worst: ";
    _problem->print(_population.back()->getStrand());
    std::cout << std::endl;*/
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

void Population::reproduce()
{
    Generation nextGeneration;
    Generation gens[4];
    Chromosome *c1, *c2, *child;
    // Elitism if used
    for (unsigned int i = 0; i < config.eliteNumber && i < _population.size(); i++)
         nextGeneration.push_back(new Chromosome(_population.at(i)->getStrand()));
    #pragma omp parallel for private(c1, c2, child) num_threads(4)
    for (unsigned int i = nextGeneration.size(); i < config.populationSize; i++)
    {
        c1 = selectChromosome();
        if (((double)rand() / RAND_MAX) <= config.crossoverRate) {
            c2 = selectChromosome();
            child = Chromosome::crossover(config.crossoverType, c1, c2);
        }
        else {
            child = new Chromosome(c1->getStrand());
        }
        child->mutate();
        gens[omp_get_thread_num()].push_back(child);
    }
    std::merge(gens[0].begin(), gens[0].end(), gens[1].begin(), gens[1].end(), std::back_inserter(nextGeneration));
    std::merge(gens[2].begin(), gens[2].end(), gens[3].begin(), gens[3].end(), std::back_inserter(nextGeneration));
    clean();
    _population = nextGeneration;
}

void Population::clean()
{
    for (Chromosome *p : _population)
        delete p;
}

Population::~Population()
{
  clean();
}

/**
 ** Selections
 */

Chromosome *Population::fitnessProportionateSelection() const
{
    double randomNb = std::fmod(std::rand(), _totalFitness);
    double curFitness = 0;
    unsigned int id = 0;
    for (;curFitness < randomNb; id++)
        curFitness += _population[id]->getFitness();
    return _population[id];
}

Chromosome *Population::tournamentSelection() const
{
    std::vector<int> subPop;
    int id, bestId = _population.size() - 1;
    double tmpFitness, bestFitness = _population.back()->getFitness();
    // for each tournament
    do {
        // select a chromosome
        do {
            id = rand() % _population.size();
        } while (std::find(subPop.begin(), subPop.end(), id) != subPop.end());
        tmpFitness = _population.at(id)->getFitness();
        // and check if it's better than the other
        if (tmpFitness > bestFitness) {
            // if so, set it as the winner
            bestFitness = tmpFitness;
            bestId = id;
        }
        subPop.push_back(id);
    } while (subPop.size() != config.tournamentSize);
    return _population[bestId];
}
