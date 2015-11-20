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
    _population.push_back({chromosome, 0});
  }
}

void Population::test()
{
  Chromosome *current;
  double value;
  double fitness;
  _totalFitness = 0;
  for (unsigned int i = 0; i < SIZE; i++)
  {
    current = _population[i].first;
    try
    {
      value = current->computeValue();
      // solution is found!!
      if (_number == value)
      {
	_winner = _population[i].first;
	return;
      }
      fitness = 1 / std::abs((double)(_number - value));
      _population[i].second = fitness;
      _totalFitness += fitness;
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
}

void Population::print()
{
  for (unsigned int i = 0; i < _population.size(); i++)
  {
    _population[i].first->print();
    try {
      std::cout << "Value = " << _population[i].first->computeValue() << " & Score: " << _population[i].second << std::endl;
    }
    catch (int e) {
      (void)e;
    }
  }
}

bool Population::hasResult() const
{
  return _winner != NULL;
}

Chromosome *Population::selectChromosome() const
{
  double randomNb = std::fmod(std::rand(), _totalFitness);
  double curFitness = 0;
  for (unsigned int i = 0; i < _population.size(); i++)
  {
    curFitness += _population[i].second;
    if (curFitness >= randomNb)
      return _population[i].first;
  }
  // never hapen, just here for the compiler
  return NULL;
}

void Population::reproduce()
{
  std::vector<std::pair<Chromosome *, double> > nextGeneration;
  Chromosome *c1, *c2;
  do
  {
     c1 = selectChromosome();
    c2 = selectChromosome();
    std::pair<Chromosome *, Chromosome *>p = Chromosome::reproduce(c1, c2);
    p.first->mutate();
    p.second->mutate();
    nextGeneration.push_back({p.first, 0});
    nextGeneration.push_back({p.second, 0});
  } while (nextGeneration.size() != SIZE);
  _population.clear();
  _population = nextGeneration;
}

Chromosome *Population::getWinner()
{
  return _winner;
}
