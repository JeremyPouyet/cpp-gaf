#ifndef _POPULATION_HH_
#define _POPULATION_HH_

#include <vector>
#include <cstdlib>
#include <string>
#include <cfloat>
#include <map>

#include "INIReader.h"
#include "./Problem.hh"
#include "./ProblemLoader.hh"
#include "./Chromosome.hh"

class Population
{
public:
    Population();
    ~Population();
  int solve(Problem *problem, const INIReader &reader);

private:
    static constexpr double	CROSSOVER_RATE		= 0.7;

    typedef std::vector<Chromosome *> Generation;
    static constexpr int SIZE = 100;
    static constexpr int SIMULATION_NUMBER = 1500;

    typedef Chromosome *(Population::*fp)() const;
    Chromosome *fitnessProportionateSelection() const;
    Chromosome *tournamentSelection() const;

    Chromosome *selectChromosome(const std::string &name) const;
    void print() const;
    void generate();
    Chromosome *test();
    void clean();
    void reproduce();

    Generation _population;
    Chromosome *_winner;
    double _totalFitness;
    Problem *_problem;
    const std::map<const std::string, fp> selections;
};

#endif
