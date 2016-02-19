#include "Population.hh"

Population::Population() : 
        _winner(NULL),
        _problem(NULL),
        selections({
            {"fitness-proportional", &Population::fitnessProportionateSelection},
            {"tournament", &Population::tournamentSelection}})
{ }

void Population::solve(Problem *problem) {
    _problem = problem;
    unsigned int generation;
    bool solutionFound = false;
    for (generation = 0; generation < config.simulationNumber; generation++)
    {
        if (test() == true) {
            solutionFound = true;
            break;
        }
        reproduce();
    }
    if (solutionFound == true)
        std::cout << "Solution found in " << generation + 1 << " generations(s) " << std::endl;
    else
        std::cout << "Solution not found, best candidate is: " << std::endl;
    sortByFitness();
    _problem->print(_population.front()->getStrand());
    _problem->giveBestSolution(_population.front()->getStrand());
    //print();
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
    _totalFitness = totalFitness;
    std::cout << "fitness total: " << _totalFitness << std::endl;
    // sort them by fitness
    sortByFitness();
    // test if the best candidate solution solves the problem
    return _problem->test(_population.front()->getStrand());
}

void Population::print() const
{
    for (auto &candidate : _population)
        _problem->print(candidate->getStrand());
}

Chromosome *Population::selectChromosome() const
{
    return (this->*selections.at(config.selectionType))();
}

void Population::sortByFitness() {
    std::sort(_population.begin(), _population.end(), Chromosome());
    //std::cout << "1st: " << _population.front()->getFitness() << std::endl
    //        << "last: " << _population.back()->getFitness() << std::endl;
}

void Population::reproduce()
{
  Generation nextGeneration;
  Chromosome *c1, *c2;
  if (config.useElitism == true) {
      for (unsigned int i = 0; i < config.eliteNumber && i < _population.size(); i++)
          nextGeneration.push_back(new Chromosome(_population.at(i)->getStrand()));
  }
  Strand s1, s2;
  do
  {
    s1 = selectChromosome()->getStrand();
    s2 = selectChromosome()->getStrand();
    if ((double)rand() / RAND_MAX <= config.crossoverRate)
        Chromosome::crossover(config.crossoverType, s1, s2);
    c1 = new Chromosome(s1);
    c2 = new Chromosome(s2);
    c1->mutate();
    c2->mutate();
    nextGeneration.push_back(c1);
    nextGeneration.push_back(c2);
  } while (nextGeneration.size() < config.populationSize);
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
    for (auto &candidate : _population)
    {
        curFitness += candidate->getFitness();
        if (curFitness >= randomNb)
            return candidate;
    }
    // never happens, just here for the compiler
    return NULL;
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
        if (tmpFitness < bestFitness) {
            // if so, set it as the winner
            bestFitness = tmpFitness;
            bestId = id;
        }
        subPop.push_back(id);
    } while (subPop.size() != config.tournamentSize);
    return _population[bestId];
}
