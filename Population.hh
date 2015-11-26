#ifndef _POPULATION_HH_
#define _POPULATION_HH_

#include <vector>
#include <cstdlib>
#include <cfloat>

#include "./Gene.hh"
#include "./GenesDatabase.hh"
#include "./Chromosome.hh"

class Population
{
public:
  Population(double number) : _winner(NULL), _number(number) {}
  ~Population();
  void print() const;
  void generate();
  Chromosome *test();
  void clean();
  void reproduce();

private:
  typedef std::vector<Chromosome *> Generation;
  static constexpr int SIZE = 100;

  Chromosome * selectChromosome() const;

  Generation _population;
  Chromosome *_winner;
  double _number;
  double _totalFitness;
};

#endif
