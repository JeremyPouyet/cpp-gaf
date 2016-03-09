#ifndef _POPULATION_HH_
#define _POPULATION_HH_

#include <vector>
#include <cstdlib>
#include <string>
#include <cfloat>
#include <map>
#include <algorithm>
#include <omp.h>
#include <set>

#include "Config.hh"
#include "Problem.hh"
#include "ProblemLoader.hh"
#include "Chromosome.hh"
#include "RandomGenerator.hh"

class Population
{
public:
    /**
     * Population constructor
     * @param problem, Problem to solve
     */
    Population();
    
    /**
     * Try to Solve the current Problem
     * @param problem, the problem to solve
     */
    void solve(Problem *problem);

private:
    typedef std::vector<Chromosome > Generation;
    typedef unsigned int (Population::*fp)() const;
    
    /**
     * Selection function, Select a chromosome in the current population by using
     * fitness proportional selection
     * @return the selected chromosome
     */
    unsigned int    fitnessProportionateSelection()            const;
    
    /**
     * Selection function, Select a chromosome in the current population by using
     * tournament selection
     * @return the selected chromosome
     */
    unsigned int    tournamentSelection()                      const;
    
    /**
     * Selection function, redirect to the good selection according to the configuration's selection type
     * @return the selected chromosome
     */
    inline unsigned int  selectChromosome()                  const;
    
    /**
     * test if the population has a winner
     * @return if a candidate solution solves the problem
     */
    bool  test();
    
    /**
     * print the current population
     */
    void        print()                                     const;

    /**
     * reproduce the current population, creation of the next generation
     */
    void        reproduce();
    
    /**
     * sort the current population by chromosome fitness
     */
    inline void        sortByFitness();

    /**
     * print informations about the population
     */
    inline void printResume(unsigned int generation) const;
    
    // current population
    Generation  _population;
    // total fitness of the current generation
    double      _totalFitness;
    // current problem
    Problem     *_problem;
    // list of possible selections
    const std::map<const std::string, fp> selections;
    // random generator
    static RandomGenerator _random;
};

#endif
