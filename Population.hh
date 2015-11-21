#ifndef _POPULATION_HH_
#define _POPULATION_HH_

#include <vector>
#include <cstdlib>
#include <cmath>
#include <cfloat>

#include "./Gene.hh"
#include "./GenesDatabase.hh"
#include "./Chromosome.hh"

struct Solution
{
public:
  Solution(Chromosome *candidate) :
    _candidate(candidate), _fitness(0)
    {}

  Chromosome	*_candidate;
  double	_fitness;
};

class Population
{
public:
  Population(double number) :
    _winner(NULL), _number(number)
    {}
  ~Population();
  void print();
  void generate();
  Chromosome *test();
  void clean();
  void reproduce();

private:
  typedef std::vector<Solution> Generation;
  static constexpr int SIZE = 100;

  Chromosome * selectChromosome() const;

  Generation _population;
  const GenesDatabase _db;
  Chromosome *_winner;
  double _number;
  double _totalFitness;
};

#endif
