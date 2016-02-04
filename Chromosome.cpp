#include "./Chromosome.hh"

const std::map<const std::string, Chromosome::fp> Chromosome::crossovers = {
        {"one-point", &Chromosome::onePointCrossover},
        {"two-point", &Chromosome::twoPointCrossover}
    };

Chromosome::Chromosome()
{
    _strand = "";
    for (int j = 0; j < config.chromosomeSize; j++)
        _strand += (rand() % 2) ? "1" : "0";
}

Chromosome::Chromosome(const Strand &strand) : 
            _strand(strand)
{}

void Chromosome::setFitness(double fitness)
{
    _fitness = fitness;
}

Chromosome::Children
Chromosome::crossover(const std::string &name, const Chromosome * const c1, const Chromosome * const c2)
{
  Strand s1 = c1->getStrand();
  Strand s2 = c2->getStrand();
  crossovers.at(name)(s1, s2);
  return {new Chromosome(s1), new Chromosome(s2)};
}

void Chromosome::mutate()
{
  double randomNb;
  for (unsigned int i = 0; i < _strand.size(); i++)
  {
    randomNb = (double)rand() / RAND_MAX;
    if (randomNb <= config.mutationRate)
        _strand[i] = (_strand[i] == '0') ? '1' : '0';
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
    crossoverBetween(s1, s2, rand() % config.chromosomeSize, config.chromosomeSize);
}

void Chromosome::twoPointCrossover(Strand &s1, Strand &s2)
{
    int r1, r2;
    r1 = rand() % config.chromosomeSize;
    r2 = (rand() % config.chromosomeSize) + r1;
    if (r2 > config.chromosomeSize)
        r2 = config.chromosomeSize;
    crossoverBetween(s1, s2, r1, r2);
}

void Chromosome::crossoverBetween(Strand &s1, Strand &s2, int l1, int l2)
{
    Gene g;
    for (int i = l1; i < l2; i++)
    {
        g = s1[i];
        s1[i] = s2[i];
        s2[i] = g;
    }
}
