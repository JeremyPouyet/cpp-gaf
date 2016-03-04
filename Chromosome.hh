#ifndef CHROMOSOME_HH_
#define CHROMOSOME_HH_

#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#include "RandomGenerator.hh"
#include "Config.hh"

class Chromosome
{
public:
  /**
   * Creates a new random chromosome according to the configuration file
   */
  Chromosome();
  
  /**
   * Creates a new chromosome according to a Strand
   * @param strand, the chromosome strand
   */
  Chromosome(const Strand &strand);

  /**
   * Apply a crossover on two Chromosome to generate a pair of new chromosome
   * @param name, crossover to apply
   * @param c1, chromosome 1
   * @param c2, chromosome 2
   * @return a pair of new chromosome
   */
  static Chromosome *crossover(const std::string &name, const Chromosome * c1, const Chromosome *c2);

  /**
   * Set the current fitness of a chromosome previously computed into a problem
   * @param fitness, fitness of the chromosome.
   */
  void          setFitness(double fitness);
  
  /**
   * generates a random mutation
   */
  void		mutate();
  
  /**
   * Set a chromosome strand
   * @param strand, new chromosome strand
   */
  void		set(const Strand strand);
  
  /**
   * get the chromosome strand
   * @return the chromosome strand
   */
  Strand        getStrand()                     const;
  
  /**
   * get the chromosome fitness
   * @return the chromosome fitness
   */
  double	getFitness()			const;
  
  /**
   * Overload of the parenthesis operator, used to compare chromosome fitness
   * in order to sort them in case of elitism
   * @param c1, first chromosome
   * @param c2, second chromosome
   * @return whether the first chromosome has a better fitness than the second
   */
  bool operator() (const Chromosome *c1, const Chromosome *c2);

private:

    typedef Strand (*fp)(Strand s1, Strand s2);

    /**
     * Crossover function, apply the one point crossover on two strand
     * @param s1, strand 1
     * @param s2, strand 2
     * @return new strand generated from s1 and s2
     */
    static Strand onePointCrossover(Strand s1, Strand s2);
    
    /**
     * Crossover function, apply the two point crossover on two strand
     * @param s1, strand 1
     * @param s2, strand 2
     * @return new strand generated from s1 and s2
     */
    static Strand twoPointCrossover(Strand s1, Strand s2);

    /**
     * Function used by one point and two point crossover to avoid code duplication
     * @param s1, strand 1
     * @param s2, strand 2
     * @param l1, limit at which to start crossover
     * @param l2, limit at which to end crossover
     * @return new strand generated from s1 and s2
     */
    static Strand crossoverBetween(Strand s1, Strand s2, unsigned int l1, unsigned int l2);

    /**
     * Crossover function, apply the uniform crossover on two strand
     * @param s1, strand 1
     * @param s2, strand 2
     * @return new strand generated from s1 and s2
     */
    static Strand uniformCrossover(Strand s1, Strand s2);
    
    
    // Computation representation of a possible solution
    Strand      _strand;
    // rating, explains how a potential solution is good
    double	_fitness;
    //  map of possible crossover
    static const std::map<const std::string, const fp> crossovers;
    // random generator
    static RandomGenerator _random;
};

#endif
