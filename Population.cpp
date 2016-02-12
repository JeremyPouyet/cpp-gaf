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
    _problem->giveBestSolution(_population.back()->getStrand());
    //print();
}

void Population::generate()
{
    for (unsigned int i = 0; i < config.populationSize; i++)
        _population.push_back(new Chromosome());
}

bool Population::test()
{
    double fitness;
    Chromosome *candidate;
    _totalFitness = 0;
    // compute fitness of all chromosome
    for (unsigned int i = 0; i < config.populationSize; i++) {
        candidate = _population.at(i);
        fitness = _problem->computeFitnessOf(candidate->getStrand());
        candidate->setFitness(fitness);
        _totalFitness += fitness;
    }
    // sort them by fitness
    sortByFitness();
    // test if the best candidate solution solves the problem
    if (_problem->test(_population.front()->getStrand()))
        return true;
    return false;
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
}

void Population::reproduce()
{
  Generation nextGeneration;
  Chromosome *c1, *c2;
  Chromosome::Children children;
  if (config.useElitism == true) {
      for (unsigned int i = 0; i < config.eliteNumber && i < _population.size(); i++)
          nextGeneration.push_back(new Chromosome(_population.at(i)->getStrand()));
  }
  do
  {
    c1 = selectChromosome();
    c2 = selectChromosome();
    if ((double)rand() / RAND_MAX <= config.crossoverRate)
        children = Chromosome::crossover(config.crossoverType, c1, c2);
    else {
	children.first = new Chromosome(c1->getStrand());
	children.second = new Chromosome(c2->getStrand());
    }
    children.first->mutate();
    children.second->mutate();
    nextGeneration.push_back(children.first);
    nextGeneration.push_back(children.second);
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
    const int ts = 5;
    std::vector<int> subPop;
    int id;
    double tmpFitness;
    do {
        do {
            id = rand() % _population.size();
        } while (std::find(subPop.begin(), subPop.end(), id) != subPop.end());
        subPop.push_back(id);
    } while (subPop.size() != ts);
    double f = 0;
    for (auto i : subPop)
    {
        tmpFitness = _population.at(i)->getFitness(); 
        if (tmpFitness > f)
        {
            f = tmpFitness;
            id = i;
        }
    }
    return _population[id];
}
