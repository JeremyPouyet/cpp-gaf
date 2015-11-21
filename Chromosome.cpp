#include "./Chromosome.hh"

bool Chromosome::addGene(Gene gene, int index)
{
  if (index < 0 || index > SIZE - 1)
    return false;
  for (int i = 0; i < GENE_SIZE; i++)
    _chromosome.set(index * GENE_SIZE + i, gene[i]);
  return true;
}

double Chromosome::computeValue() const
{
  Gene g;
  char op = '$';
  double right, value = 0;
  bool hasLeft = false, hasValue = false;
  Type type = DIGIT;
  for (int i = 0; i < SIZE; i++)
  {
    g.reset();
    for (int j = 0; j < GENE_SIZE; j++)
      g.set(j, _chromosome[i * GENE_SIZE + j]);
    if (_db.exists(g) == false || _db.getTypeOf(g) != type)
      continue;
    if (type == OPERATOR)
    {
      op = _db.getCharValueOf(g);
      hasLeft = true;
    }
    else if (hasLeft == false)
      value += _db.getIntValueOf(g);
    else
    {
      right = _db.getIntValueOf(g);
      if (op == '+')
	value += right;
      else if (op == '-')
	value -= right;
      else if (op == '*')
	value *= right;
      else
      {
	if (right == 0)
	  throw 0;
	value /= right;
      }
      op = '$';
      hasValue = true;
    }
    type = (type == DIGIT) ? OPERATOR : DIGIT;
  }
  if (hasValue == false)
    throw 1;
  return value;
}

void Chromosome::print() const
{
  Gene gene;
  int j;
  for (int i = 0; i < SIZE; i++)
  {
    gene.reset();
    for (j = 0; j < GENE_SIZE; j++)
      gene[j] = _chromosome[i * GENE_SIZE + j];
    if (_db.exists(gene))
      std::cout << " " << _db.getCharValueOf(gene) << std::flush;
    else
      std::cout << " UNKNOWN" << std::flush;
  }
  std::cout << std::endl;
}

void Chromosome::prettyPrint() const
{
  Gene gene;
  int j;
  Type type = DIGIT;
  std::string s = "";
  for (int i = 0 ; i < SIZE; i++)
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

std::pair<Chromosome *, Chromosome *>
Chromosome::reproduce(const Chromosome *c1, const Chromosome *c2)
{
  Chromosome *n1 = new Chromosome();
  Chromosome *n2 = new Chromosome();
  chrome tmp1 = c1->get();
  chrome tmp2 = c2->get();
  chrome tmp;
  int i, randomPos;
  if ((double)rand() / RAND_MAX <= CROSSOVER_RATE)
  {
    randomPos = rand() % (GENE_SIZE * SIZE);
    for (i = randomPos; i < GENE_SIZE * SIZE; i++)
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
  for (int i = 0; i < GENE_SIZE * SIZE; i++)
  {
    randomNb = (double)rand() / RAND_MAX;
    if (randomNb <= MUTATION_RATE)
      _chromosome[i] = !_chromosome[i];
  }
}

Chromosome::chrome Chromosome::get() const
{
  return _chromosome;
}

void Chromosome::set(chrome c)
{
  for (int i = 0; i < SIZE * GENE_SIZE; i++)
    _chromosome[i] = c[i];
}
