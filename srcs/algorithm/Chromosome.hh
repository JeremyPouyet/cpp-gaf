#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#include "Problem.hh"
#include "RandomGenerator.hpp"
#include "Config.hh"

class Chromosome {
public:

    Chromosome() = default;

    /**
     * Creates a new chromosome according to a Strand
     * @param strand, the chromosome strand
     */
    Chromosome(const Strand &strand);

    void generate();

    /**
     * Apply a crossover on two Chromosome to generate a pair of new chromosome
     * @param name, crossover to apply
     * @param c1, chromosome 1
     * @param c2, chromosome 2
     * @return a pair of new chromosome
     */
    static Strand crossover(const Strand &c1, const Strand &c2, const Problem *problem);

    /**
     * Set the current fitness of a chromosome previously computed into a problem
     * @param fitness, fitness of the chromosome.
     */
    void setFitness(double fitness);

    /**
     * generates a random mutation
     */
    void mutate();

    /**
     * Set a chromosome strand
     * @param strand, new chromosome strand
     */
    void setStrand(const Strand &strand);

    /**
     * get the chromosome strand
     * @return the chromosome strand
     */
    Strand getStrand() const;

    /**
     * get the chromosome fitness
     * @return the chromosome fitness
     */
    double getFitness() const;

    /**
     * Copy constructor
     * @param other, chromosome to copy
     * @return, the newly copied chromosome
     */
    Chromosome &operator=(const Chromosome &other);

private:

    using fp = Strand(*)(const Strand &s1, const Strand &s2, const Problem *problem);

    /**
     * Crossover function, apply the one point crossover on two strand
     * @param s1, strand 1
     * @param s2, strand 2
     * @return new strand generated from s1 and s2
     */
    static Strand onePointCrossover(const Strand &s1, const Strand &s2, const Problem *problem);

    /**
     * Crossover function, apply the two point crossover on two strand
     * @param s1, strand 1
     * @param s2, strand 2
     * @return new strand generated from s1 and s2
     */
    static Strand twoPointCrossover(const Strand &s1, const Strand &s2, const Problem *problem);

    /**
     * Function used by one point and two point crossover to avoid code duplication
     * @param s1, strand 1
     * @param s2, strand 2
     * @param l1, limit at which to start crossover
     * @param l2, limit at which to end crossover
     * @return new strand generated from s1 and s2
     */
    static Strand crossoverBetween(const Strand &s1, const Strand &s2, unsigned int l1, unsigned int l2);

    static Strand arithmeticCrossover(const Strand &s1, const Strand &s2, const Problem *problem);

    /**
     * Crossover function, apply the uniform crossover on two strand
     * @param s1, strand 1
     * @param s2, strand 2
     * @return new strand generated from s1 and s2
     */
    static Strand uniformCrossover(const Strand &s1, const Strand &s2, const Problem *problem);


    // Computation representation of a possible solution
    Strand _strand;
    // rating, explains how a potential solution is good
    double _fitness;
    //  map of possible crossover
    static const std::map<const std::string, const fp> crossovers;
};