#ifndef _POPULATION_HH_
#define _POPULATION_HH_

#include <vector>
#include <cstdlib>
#include <cfloat>

#include "./Problem.hh"
#include "./ProblemLoader.hh"
#include "./Gene.hh"
#include "./Chromosome.hh"

class Population
{
public:
  Population();
  ~Population();
  int solve(Problem *problem);

private:
  typedef std::vector<Chromosome *> Generation;
  static constexpr int SIZE = 100;
  static constexpr int SIMULATION_NUMBER = 1500;

  Chromosome * selectChromosome() const;
  void print() const;
  void generate();
   Chromosome *test();
  void clean();
  void reproduce();

  Generation _population;
  Chromosome *_winner;
  double _totalFitness;
  Problem *_problem;
};

#endif
