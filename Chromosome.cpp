#include "./Chromosome.hh"

Chromosome::Chromosome()
{
  for (int j = 0; j < CHROMOSOME_SIZE; j++)
    _chromosome[j] = rand() % 2;
}

void	Chromosome::computeValue()
{
  Gene g;
  char op;
  double right;
  bool hasLeft = false;
  Type type = DIGIT;
  int j;
  _value = 0;
  _hasValue = false;
  for (int i = 0; i < GENE_PER_CHROMOSOME; i++)
  {
    for (j = 0; j < GENE_SIZE; j++)
      g[j] = _chromosome[i * GENE_SIZE + j];
    if (_db.exists(g) == false || _db.getTypeOf(g) != type)
      continue;
    if (type == OPERATOR)
    {
      op = _db.getCharValueOf(g);
      hasLeft = true;
    }
    else if (hasLeft == false)
      _value = _db.getIntValueOf(g);
    else
    {
      right = _db.getIntValueOf(g);
      if (op == '+')
	_value += right;
      else if (op == '-')
	_value -= right;
      else if (op == '*')
	_value *= right;
      else
      {
	if (right == 0)
	{
	  _hasValue = false;
	  return;
	}
	_value /= right;
      }
      _hasValue = true;
    }
    type = (type == DIGIT) ? OPERATOR : DIGIT;
    g.reset();
  }
}

void Chromosome::computeFitness(double number)
{
  _fitness = 1 / std::abs(number - _value);
}

void Chromosome::prettyPrint() const
{
  Gene gene;
  int j;
  Type type = DIGIT;
  std::string s = "";
  for (int i = 0 ; i < GENE_PER_CHROMOSOME; i++)
  {
    gene.reset();
    for (j = 0; j < GENE_SIZE; j++)
      gene[j] = _chromosome[i * GENE_SIZE + j];
    if (_db.getTypeOf(gene) == type)
    {
      s += _db.getCharValueOf(gene);
      type = type == DIGIT ? OPERATOR : DIGIT;
    }
  }
  if (s.size() < 3)
    std::cout << "Chromosome " << _chromosome << " has no pretty format: " << s << std::flush;
  else
  {
    if (s.size() % 2 == 0)
      s.pop_back();
    std::cout << s << std::flush;
  }
}

Chromosome::Children Chromosome::reproduce(const Chromosome * const c1, const Chromosome * const c2)
{
  Chromosome *n1 = new Chromosome();
  Chromosome *n2 = new Chromosome();
  chrome tmp1 = c1->get();
  chrome tmp2 = c2->get();
  chrome tmp;
  int i, randomPos;
  if ((double)rand() / RAND_MAX <= CROSSOVER_RATE)
  {
    randomPos = rand() % CHROMOSOME_SIZE;
    for (i = randomPos; i < CHROMOSOME_SIZE; i++)
    {
      tmp[i] = tmp1[i];
      tmp1[i] = tmp2[i];
      tmp2[i] = tmp[i];
    }
  }
  n1->set(tmp1);
  n2->set(tmp2);
  return {n1, n2};
}

void Chromosome::mutate()
{
  double randomNb;
  for (int i = 0; i < CHROMOSOME_SIZE; i++)
  {
    randomNb = (double)rand() / RAND_MAX;
    if (randomNb <= MUTATION_RATE)
    {
      _chromosome.flip(i);
      computeValue();
    }
  }
}

Chromosome::chrome Chromosome::get() const
{
  return _chromosome;
}

double Chromosome::getValue() const
{
  return _value;
}

bool Chromosome::isValid() const
{
  return _hasValue;
}

double Chromosome::getFitness() const
{
  return _fitness;
}

void Chromosome::set(const chrome c)
{
  _chromosome = c;
  computeValue();
}
