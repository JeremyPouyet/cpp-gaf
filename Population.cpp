#include "Population.hh"

Population::Population(Problem *problem) : 
        _winner(NULL),
        _problem(problem),
        selections({
            {"fitness-proportional", &Population::fitnessProportionateSelection},
            {"tournament", &Population::tournamentSelection}})
{
    generate();
}

bool Population::solve() {
    unsigned int generation;
    Chromosome *solution;
    for (generation = 0; generation < config.simulationNumber; ++generation)
    {
        if ((solution = test()) != NULL)
            break;
        reproduce();
    }
    if (solution)
    {
        std::cout << "Solution found in " << generation + 1 << " generation(s)" << std::endl;
        _problem->print(solution->getStrand());
        return true;
    }
    std::cout <<  "Solution not found" << std::endl;
    print();
    return false;
}

void Population::generate()
{
    _problem->askParameters();
    for (unsigned int i = 0; i < config.populationSize; i++)
        _population.push_back(new Chromosome());
}

Chromosome *Population::test()
{
    double fitness;
    _totalFitness = 0;
    for (auto &candidate : _population)
    {
        if (_problem->test(candidate->getStrand()))
            return candidate;
        fitness = _problem->computeFitnessOf(candidate->getStrand());
        candidate->setFitness(fitness);
        //compute total fitness in case of fitness proportional selection
        _totalFitness += fitness;
    }
    return NULL;
}

void Population::print() const
{
    for (auto &candidate : _population)
        _problem->print(candidate->getStrand());
}

Chromosome *Population::selectChromosome(const std::string &name) const
{
    return (this->*selections.at(name))();
}

void Population::reproduce()
{
  Generation nextGeneration;
  Chromosome *c1, *c2;
  Chromosome::Children children;
  do
  {
    c1 = selectChromosome(config.selectionType);
    c2 = selectChromosome(config.selectionType);
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
  } while (nextGeneration.size() != config.populationSize);
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
    do {
        do {
            id = rand() % _population.size();
        } while (std::find(subPop.begin(), subPop.end(), id) != subPop.end());
        subPop.push_back(id);
    } while(subPop.size() != ts);
    int f = 0;
    for (auto i : subPop)
    {
        if (_population.at(i)->getFitness() > f)
        {
            f = _population.at(i)->getFitness();
            id = i;
        }
    }
    return _population[id];
}
