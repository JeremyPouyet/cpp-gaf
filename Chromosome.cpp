#include "./Chromosome.hh"

Chromosome::Chromosome()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(MIN_GENE_VALUE, MAX_GENE_VALUE);
    for (int j = 0; j < GENE_PER_CHROMOSOME; j++)
        _strand.push_back(dis(gen));
}

char getCharValue(int n) {
    int b1 = (n >> 0) & 1, b2 = (n >> 1) & 1;
    if (b1 && b2)
        return '+';
    if (b1 && !b2)
        return '-';
    if (!b1 && !b2)
        return '*';
    return '/';
}

void	Chromosome::computeValue()
{
  char op;
  bool hasLeft = false;
  Type type = DIGIT;
  _value = 0;
  _hasValue = false;
  for (auto gene: _strand)
  {
    if (type == OPERATOR)
    {
      op = getCharValue(gene);
      hasLeft = true;
    }
    else if (hasLeft == false)
      _value = gene;
    else
    {
      if (op == '+')
	_value += gene;
      else if (op == '-')
	_value -= gene;
      else if (op == '*')
	_value *= gene;
      else if (gene == 0)
      {
	_hasValue = false;
	return;
      }
      else
	_value /= gene;
      _hasValue = true;
    }
    type = (type == DIGIT) ? OPERATOR : DIGIT;
  } 
}

void Chromosome::computeFitness(double number)
{
  _fitness = 1 / std::abs(number - _value);
}

void Chromosome::prettyPrint() const
{
  Type type = DIGIT;
  std::string s;
  for (auto gene: _strand)
  {
      if (type == OPERATOR)
        s += getCharValue(gene);
      else
        s += std::to_string(gene);
     type = type == DIGIT ? OPERATOR : DIGIT; 
  }
  if (s.size() < 3)
    std::cout << "Chromosome has no pretty format: " << s << std::flush;
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
  Strand tmp1 = c1->get();
  Strand tmp2 = c2->get();
  Gene g1, g2;
  int i, randomPos, currentGeneId, currentBitId;
  if ((double)rand() / RAND_MAX <= CROSSOVER_RATE)
  {
    randomPos = rand() % CHROMOSOME_SIZE;
    for (i = randomPos; i < CHROMOSOME_SIZE; i++)
    {
        currentGeneId = i / GENE_SIZE;
        currentBitId = i - (currentGeneId * GENE_SIZE);
        g1 = (tmp1[currentGeneId] >> currentBitId) & 1;
        g2 = (tmp2[currentGeneId] >> currentBitId) & 1;
        tmp1[currentGeneId] |= 1 << g2;
        tmp2[currentGeneId] |= 1 << g1;
    }
  }
  n1->set(tmp1);
  n2->set(tmp2);
  return {n1, n2};
}

void Chromosome::mutate()
{
  double randomNb;
  int currentGeneId, currentBitId;
  for (int i = 0; i < CHROMOSOME_SIZE; i++)
  {
    randomNb = (double)rand() / RAND_MAX;
    currentGeneId = i / GENE_SIZE;
    currentBitId = i - (currentGeneId * GENE_SIZE);
    if (randomNb <= MUTATION_RATE)
    {
      _strand[currentGeneId] ^= 1 << currentBitId;  
      computeValue();
    }
  }
}

Chromosome::Strand Chromosome::get() const
{
  return _strand;
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

void Chromosome::set(const Strand strand)
{
  _strand = strand;
  computeValue();
}
