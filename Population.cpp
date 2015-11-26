#include "./Population.hh"

void Population::generate()
{
  for (int i = 0; i < SIZE; i++)
    _population.push_back(new Chromosome());
}

Chromosome *Population::test()
{
  double value;
  _totalFitness = 0;
  for (auto &candidate : _population)
  {
    if (candidate->isValid())
    {
      value = candidate->getValue();
      // solution is found!!
      if (_number == value)
	return candidate;
      candidate->computeFitness(_number);
      _totalFitness += candidate->getFitness();
    }
  }
  return NULL;
}

void Population::print() const
{
  for (auto &candidate : _population)
  {
    candidate->prettyPrint();
    if (candidate->isValid())
    {
      std::cout << " Value = " << candidate->getValue()
		<< " & fitness: " << candidate->getFitness() << std::endl;
    }
    else
      std::cout << " Chromosome not printable" << std::endl;
  }
}

Chromosome *Population::selectChromosome() const
{
  double randomNb = std::fmod(std::rand(), _totalFitness);
  double curFitness = 0;
  for (auto &candidate : _population)
  {
    curFitness += candidate->getFitness();
    if (curFitness >= randomNb)
      return candidate;
  }
  // never hapen, just here for the compiler
  return NULL;
}

void Population::reproduce()
{
  Generation nextGeneration;
  Chromosome *c1, *c2;
  Chromosome::Children children;
  do
  {
    c1 = selectChromosome();
    c2 = selectChromosome();
    children = Chromosome::reproduce(c1, c2);
    children.first->mutate();
    children.second->mutate();
    nextGeneration.push_back(children.first);
    nextGeneration.push_back(children.second);
  } while (nextGeneration.size() != SIZE);
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
