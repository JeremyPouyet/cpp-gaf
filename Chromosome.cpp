#include "./Chromosome.hh"

RandomGenerator Chromosome::_random;

const std::map<const std::string, const Chromosome::fp> Chromosome::crossovers = {
        {"one-point", &Chromosome::onePointCrossover},
        {"two-point", &Chromosome::twoPointCrossover},
        {"uniform", &Chromosome::uniformCrossover}
    };

Chromosome::Chromosome() : _strand(config.chromosomeSize)
{
    for (unsigned int j = 0; j < config.chromosomeSize; j++)
        _strand[j] = _random.i0_1();
}

Chromosome::Chromosome(const Strand &strand) : _strand(strand)
{}

void Chromosome::setFitness(double fitness)
{
    _fitness = fitness;
}

bool Chromosome::operator() (const Chromosome *c1, const Chromosome *c2)
{
    return c1->getFitness() > c2->getFitness();
}

Chromosome *Chromosome::crossover(const std::string &name, const Chromosome *c1, const Chromosome *c2)
{
    Strand strand = crossovers.at(name)(c1->getStrand(), c2->getStrand());
    return new Chromosome(strand);
}

void Chromosome::mutate()
{
  for (unsigned int i = 0; i < _strand.size(); i++)
      if (_random.d0_1() <= config.mutationRate)
          _strand[i].flip();
}

Strand Chromosome::getStrand() const
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

Strand Chromosome::onePointCrossover(Strand s1, Strand s2)
{
    return crossoverBetween(s1, s2, _random.i0_limit(config.chromosomeSize), config.chromosomeSize);
}

Strand Chromosome::twoPointCrossover(Strand s1, Strand s2)
{
    unsigned int r1 = _random.i0_limit(config.chromosomeSize);
    unsigned int r2 = _random.i0_limit(config.chromosomeSize);
    if (r1 > r2)
        return crossoverBetween(s1, s2, r1, r2);    
    return crossoverBetween(s1, s2, r2, r1);
}

Strand Chromosome::uniformCrossover(Strand s1, Strand s2) {
    Strand strand = s1;
    for (unsigned int i = 0; i < config.chromosomeSize; i++)
        if (Chromosome::_random.i0_1() == 1)
            strand[i] = s2[i];
    return strand;
}

Strand Chromosome::crossoverBetween(Strand s1, Strand s2, unsigned int l1, unsigned  int l2)
{
    Strand strand = s1;
    for (unsigned int i = l1; i < l2; i++)
        strand[i] = s2[i];
    return strand;
}