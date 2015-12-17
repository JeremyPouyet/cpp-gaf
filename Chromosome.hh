#ifndef CHROMOSOME_HH_
#define CHROMOSOME_HH_

#include <cstdint>
#include <bitset>
#include <utility>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Gene.hh"

class Chromosome
{
public:

  static constexpr double	CROSSOVER_RATE		= 0.7;
  static constexpr double	MUTATION_RATE		= 0.1;
  static constexpr int		GENE_PER_CHROMOSOME	= 9;
  static constexpr int          CHROMOSOME_SIZE		= GENE_SIZE * GENE_PER_CHROMOSOME;

  typedef std::vector<Gene> Strand;
  typedef std::pair<Chromosome *, Chromosome *> Children;

  Chromosome();

  static Children
  reproduce(const Chromosome * const c1, const Chromosome * const c2);

  void          setFitness(double fitness);
  void		mutate();
  void		set(const Strand strand);
  Strand        getStrand()                     const;
  double	getFitness()			const;
private:
  
  Strand        _strand;
  double	_fitness;
};

#endif
