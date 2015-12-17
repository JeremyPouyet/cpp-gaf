#include "./Chromosome.hh"

Chromosome::Chromosome()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(MIN_GENE_VALUE, MAX_GENE_VALUE);
    for (int j = 0; j < GENE_PER_CHROMOSOME; j++)
        _strand.push_back(dis(gen));
}

void Chromosome::setFitness(double fitness) {
    _fitness = fitness;
}

Chromosome::Children 
Chromosome::reproduce(Problem *problem, const Chromosome * const c1, const Chromosome * const c2)
{
  Chromosome *n1 = new Chromosome();
  Chromosome *n2 = new Chromosome();
  Strand tmp1 = c1->getStrand();
  Strand tmp2 = c2->getStrand();
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
  n1->set(problem, tmp1);
  n2->set(problem, tmp2);
  return {n1, n2};
}

void Chromosome::mutate(Problem *problem)
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
      try {
          setValue(problem);
      } catch (int e) {
          _hasValue = false;
      }
    }
  }
}

Chromosome::Strand Chromosome::getStrand() const
{
  return _strand;
}

double Chromosome::getValue() const
{
  return _value;
}

void Chromosome::setValue(Problem *problem) 
{
  try {
    _value = problem->computeValue(this);
  } catch (int e) {
    _hasValue = false;
  }
}

bool Chromosome::isValid() const
{
  return _hasValue;
}

double Chromosome::getFitness() const
{
  return _fitness;
}

void Chromosome::set(Problem *problem, const Strand strand)
{
  _strand = strand;
  setValue(problem);
}
