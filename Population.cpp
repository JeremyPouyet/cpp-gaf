#include "./Population.hh"

void Population::generate()
{
  Gene gene;
  int j, k;
  for (int i = 0; i < SIZE; i++)
  {
    Chromosome *chromosome = new Chromosome();
    for (j = 0; j < Chromosome::SIZE; j++)
    {
      for (k = 0; k < GENE_SIZE; k++)
	gene[k] = rand() % 2;
      chromosome->addGene(gene, k);
    }
    _population.push_back({chromosome});
  }
}

Chromosome *Population::test()
{
  double value;
  _totalFitness = 0;
  for (Solution &candidate : _population)
  {
    try
    {
      value = candidate._candidate->computeValue();
      // solution is found!!
      if (_number == value)
	return candidate._candidate;
      candidate._fitness = 1 / std::abs((double)(_number - value));
      _totalFitness += candidate._fitness;
    }
    catch (int e)
    {
      (void)e;
      // if (e == 0)
      // 	std::cerr << "Division by zero" << std::endl;
      // else
      // 	std::cerr << "No value in chromosome" << std::endl;
    }
  }
  return NULL;
}

void Population::print()
{
  for (Solution &candidate : _population)
  {
    candidate._candidate->prettyPrint();
    try {
      std::cout << " Value = " << candidate._candidate->computeValue()
		<< " & fitness: " << candidate._fitness << std::endl;
    }
    catch (int e) {
      (void)e;
    }
  }
}

Chromosome *Population::selectChromosome() const
{
  double randomNb = std::fmod(std::rand(), _totalFitness);
  double curFitness = 0;
  for (auto candidate : _population)
  {
    curFitness += candidate._fitness;
    if (curFitness >= randomNb)
      return candidate._candidate;
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
    nextGeneration.push_back({children.first});
    nextGeneration.push_back({children.second});
  } while (nextGeneration.size() != SIZE);
  clean();
  _population = nextGeneration;
}

void Population::clean()
{
  for (auto p : _population)
    delete p._candidate;
}

Population::~Population()
{
  clean();
}
