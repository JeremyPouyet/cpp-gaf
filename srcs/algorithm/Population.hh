#pragma once

#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "Config.hh"
#include "Problem.hh"
#include "Chromosome.hh"
#include "RandomGenerator.hpp"

class Population {
public:
    /**
     * Population constructor
     * @param problem, the problem to solve
     */
    Population(Problem *problem);

    /**
     * test if the population has a winner
     * @return if a candidate solution solves the problem
     */
    bool checkForWinner();

    /**
     * reproduce the current population, creation of the next generation
     */
    void reproduce();

    /**
     * Get the best candidate solution
     * @return the best candidate solution
     */
    Strand best() const;
    
    /**
     * Get the nth candidate solution
     * @param id, id of the candidate solution
     * @return the nth candidate solution
     */
    Strand at(unsigned int id) const;
    
    /**
     * Get the worst candidate solution
     * @return the worst candidate solution
     */
    Strand worst() const;
    
private:
    typedef std::vector<Chromosome> Generation;
    using fp = unsigned int (Population::*)() const;

    /**
     * Selection function, Select a chromosome in the current population by using
     * fitness proportional selection
     * @return the selected chromosome
     */
    unsigned int fitnessProportionateSelection() const;

    /**
     * Selection function, Select a chromosome in the current population by using
     * tournament selection
     * @return the selected chromosome
     */
    unsigned int tournamentSelection() const;

    /**
     * Selection function, redirect to the good selection according to the configuration's selection type
     * @return the selected chromosome
     */
    inline unsigned int selectChromosome() const;

    /**
     * print the current population
     */
    void print() const;

    /**
     * sort the current population by chromosome fitness
     */
    inline void sortByFitness();

    // current population
    Generation _population;
    // next population
    Generation _nextGeneration;
    // total fitness of the current generation
    double _totalFitness;
    // current problem
    Problem *_problem;
    // list of possible selections
    const std::map<const std::string, fp> selections;
};
