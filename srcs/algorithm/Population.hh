#pragma once

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
     * @param problem, the problem to solve
     */
    Population(Problem *problem);
    
    /**
     * Try to Solve the current Problem
     */
    void solve();

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
    inline void printResume() const;
    
    // current population
    Generation  _population;
    // next population
    Generation  _nextGeneration;
    // index of the current generation
    unsigned int _currentGeneration;
    // total fitness of the current generation
    double      _totalFitness;
    // current problem
    Problem     *_problem;
    // list of possible selections
    const std::map<const std::string, fp> selections;
    // random generator
    static RandomGenerator _random;
};
