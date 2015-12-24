#ifndef RANGEPROBLEM_HH
#define	RANGEPROBLEM_HH

#include <iostream>

#include "Problem.hh"
#include "Chromosome.hh"

class RangeProblem : public Problem {
    public:
        RangeProblem() {}
        
        virtual void print(const Chromosome *chromosome) const;
        virtual void askParameters();
        virtual double computeFitnessOf(const Chromosome *chromosome) const;
        virtual bool test(Chromosome *chromosome) const;
        
        virtual ~RangeProblem() {}
        
    private:
        int8_t getNextInt(Chromosome::Strand strand) const;
        
        int _min;
        int _max;
};

#endif	/* RANGEPROBLEM_HH */

