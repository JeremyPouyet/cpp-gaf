#ifndef _POPULATION_HH_
#define _POPULATION_HH_

#include <vector>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <cfloat>

#include "./Gene.hh"
#include "./GenesDatabase.hh"
#include "./Chromosome.hh"

class Population
{
public:
  Population(double number) :
    _winner(NULL), _number(number)
    {}
  ~Population();
  void print();
  void generate();
  void test();
  void clean();
  bool hasResult() const;
  void reproduce();
  Chromosome *getWinner();

private:
  Chromosome * selectChromosome() const;
  static constexpr int SIZE = 100;
  // the double is the score of each chromosome
  std::vector<std::pair<Chromosome *, double> > _population;
  const GenesDatabase _db;
  Chromosome *_winner;
  double _number;
  double _totalFitness;
};

#endif
