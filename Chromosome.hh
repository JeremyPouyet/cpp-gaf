#ifndef CHROMOSOME_HH_
#define CHROMOSOME_HH_

#include <cstdint>
#include <bitset>
#include <utility>
#include <cmath>

#include "./Gene.hh"
#include "./GenesDatabase.hh"

class Chromosome
{
public:

  static constexpr double	CROSSOVER_RATE		= 0.7;
  static constexpr double	MUTATION_RATE		= 0.1;
  static constexpr int		GENE_PER_CHROMOSOME	= 9;
  static constexpr int		CHROMOSOME_SIZE		= GENE_SIZE * GENE_PER_CHROMOSOME;

  typedef std::bitset<CHROMOSOME_SIZE> chrome;
  typedef std::pair<Chromosome *, Chromosome *> Children;

  Chromosome();

  static Children
  reproduce(const Chromosome * const c1, const Chromosome * const c2);

  void		mutate();
  void		prettyPrint()			const;
  chrome	get()				const;
  void		set(const chrome c);
  void		computeFitness(double number);
  double	getValue()			const;
  double	getFitness()			const;
  bool		isValid()			const;

private:
  void		computeValue();

  chrome		_chromosome;
  const GenesDatabase	_db;
  double		_fitness;
  double		_value;
  bool			_hasValue;
};

#endif
