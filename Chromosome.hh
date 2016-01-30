#ifndef CHROMOSOME_HH_
#define CHROMOSOME_HH_

#include <cstdint>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#include "Config.hh"

class Chromosome
{
public:
  typedef char Gene;
  typedef std::string Strand;
  typedef std::pair<Chromosome *, Chromosome *> Children;

  Chromosome();
  Chromosome(const Strand &strand);

  static Children
  crossover(const std::string &name, const Chromosome * const c1, const Chromosome * const c2);

  void          setFitness(double fitness);
  void		mutate();
  void		set(const Strand strand);
  Strand        getStrand()                     const;
  double	getFitness()			const;

private:

    typedef void (*fp)(Strand &s1, Strand &s2);

    static void onePointCrossover(Strand &s1, Strand &s2);
    static void twoPointCrossover(Strand &s1, Strand &s2);

    static void crossoverBetween(Strand &s1, Strand &s2, int l1, int l2);

    Strand      _strand;
    double	_fitness;

    static const std::map<const std::string, fp> crossovers;
};

#endif
