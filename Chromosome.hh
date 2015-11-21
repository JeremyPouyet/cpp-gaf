#ifndef CHROMOSOME_HH_
#define CHROMOSOME_HH_

#include <cstdint>
#include <bitset>
#include <utility>

#include "./Gene.hh"
#include "./GenesDatabase.hh"

class Chromosome
{
public:

  static constexpr int SIZE = 9;
  static constexpr double CROSSOVER_RATE = 0.7;
  static constexpr double MUTATION_RATE = 0.01;

  typedef std::bitset<SIZE * GENE_SIZE> chrome;
  typedef std::pair<Chromosome *, Chromosome *> Children;

  Chromosome() : _chromosome(0) {}
  // check if the chromosome is of the good shape
  double computeValue() const;
  // generate a new chromosome
  static Children reproduce(const Chromosome *c1, const Chromosome *c2);
  // mutate the chromosome
  void mutate();
  // print well formated equation
  void prettyPrint() const;
  // get the chromosome
  chrome get() const;
  // set the chromosome
  void set(chrome c);

private:
  Gene getGene(int index);
  chrome _chromosome;
  GenesDatabase _db;
};

#endif
