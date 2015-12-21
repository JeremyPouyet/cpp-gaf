#ifndef CHROMOSOME_HH_
#define CHROMOSOME_HH_

#include <cstdint>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

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
  reproduce(const std::string &name, const Chromosome * const c1, const Chromosome * const c2);

  void          setFitness(double fitness);
  void		mutate();
  void		set(const Strand strand);
  Strand        getStrand()                     const;
  double	getFitness()			const;
  
private:  
    
    Chromosome(const Strand &strand);
    
    typedef void (*fp)(Strand &s1, Strand &s2);
      
    static void onePointCrossover(Strand &s1, Strand &s2);
    static void twoPointCrossover(Strand &s1, Strand &s2);
    
    static void crossoverBetween(Strand &s1, Strand &s2, int l1, int l2);
    
    Strand      _strand;
    double	_fitness;
    
    static const std::map<const std::string, fp> crossovers;
    
};

#endif
