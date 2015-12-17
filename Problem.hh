#ifndef PROBLEM_H
#define	PROBLEM_H

#include "Chromosome.hh"

class Problem {
public:
    Problem() {}
    
    virtual void print(const Chromosome *chromosome) const = 0;
    virtual void askParameters() = 0;
    virtual double computeFitnessOf(const Chromosome *chromosome) const = 0;
    virtual bool test(Chromosome *chromosome) const = 0;
    
    virtual ~Problem() {}
};

typedef Problem * create_t();
typedef void destroy_t(Problem *);

#endif	/* PROBLEM_H */

