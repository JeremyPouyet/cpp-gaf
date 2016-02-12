#ifndef PROBLEM_H
#define	PROBLEM_H

#include "Config.hh"

/**
 * Problem Interface. It is the computational representation of a Problem
 * Just implement it to be able to load a new problem into the framework.
 */
class Problem {
public:
    /**
     * print a chromosome strand
     * @param strand, strand to print
     */
    virtual void print(const std::string &strand) const = 0;
    
    /**
     * user interaction function. Used to ask parameter to the user. 
     * Can be graphic, not mendatory;
     */
    virtual void askParameters() = 0;
    
    /**
     * give the possibility to load some data into the framework
     * not mendatory
     */
    virtual bool loadData() = 0;
    
    /**
     * Compute the fitness of a chromosome through its strand.
     * @param strand, strand used to compute a chromosome fitness
     * @return 
     */
    virtual double computeFitnessOf(const std::string &strand) const = 0;
    
    /**
     * test whether a solution resolves the problem
     * @param strand, strand to test
     * @return whether a solution resolves the problem
     */
    virtual bool test(const std::string &strand) const = 0;
    
    /**
     * Transmit the best candidate solution to the problem
     * @param strand, the best candidate solution
     */
    virtual void giveBestSolution(const std::string &strand) const = 0;
    
    virtual ~Problem() {}
};

typedef Problem * create_t();
typedef void destroy_t(Problem *);

#endif	/* PROBLEM_H */

