#include "./Chromosome.hh"

const std::map<const std::string, Chromosome::fp> Chromosome::crossovers = {
        {"one-point", &Chromosome::onePointCrossover},
        {"two-point", &Chromosome::twoPointCrossover}
    };

Chromosome::Chromosome()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(MIN_GENE_VALUE, MAX_GENE_VALUE);
    for (int j = 0; j < GENE_PER_CHROMOSOME; j++)
        _strand.push_back(dis(gen));
}

Chromosome::Chromosome(const Strand &strand) : _strand(strand)
{}

void Chromosome::setFitness(double fitness) 
{
    _fitness = fitness;
}

Chromosome::Children 
Chromosome::reproduce(const std::string &name, const Chromosome * const c1, const Chromosome * const c2)
{
    if (crossovers.find(name) == crossovers.end())
        throw std::string(name);
    Strand s1 = c1->getStrand();
    Strand s2 = c2->getStrand();
    if ((double)rand() / RAND_MAX <= CROSSOVER_RATE)
        crossovers.at(name)(s1, s2);
    Chromosome *n1 = new Chromosome(s1);
    Chromosome *n2 = new Chromosome(s2);
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
        _strand[currentGeneId] ^= 1 << currentBitId;
  }
}

Chromosome::Strand Chromosome::getStrand() const
{
  return _strand;
}

double Chromosome::getFitness() const
{
  return _fitness;
}

void Chromosome::set(const Strand strand)
{
  _strand = strand;
}

/**
 * crossovers type
 */

void Chromosome::onePointCrossover(Strand &s1, Strand &s2)
{
    crossoverBetween(s1, s2, rand() % CHROMOSOME_SIZE, CHROMOSOME_SIZE);
}

void Chromosome::twoPointCrossover(Strand &s1, Strand &s2) 
{
    int r1, r2;
    r1 = rand() % CHROMOSOME_SIZE;
    r2 = (rand() % CHROMOSOME_SIZE) + r1;
    if (r2 > CHROMOSOME_SIZE)
        r2 = CHROMOSOME_SIZE;
    crossoverBetween(s1, s2, r1, r2);
}

void Chromosome::crossoverBetween(Strand &s1, Strand &s2, int l1, int l2) 
{
    int currentGeneId, currentBitId;
    Gene g1, g2;
    for (int i = l1; i < l2; i++)
    {
        currentGeneId = i / GENE_SIZE;
        currentBitId = i - (currentGeneId * GENE_SIZE);
        g1 = (s1[currentGeneId] >> currentBitId) & 1;
        g2 = (s2[currentGeneId] >> currentBitId) & 1;
        s1[currentGeneId] |= 1 << g2;
        s2[currentGeneId] |= 1 << g1;
    } 
}