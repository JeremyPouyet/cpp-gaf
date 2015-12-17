#ifndef EQUATIONPROBLEM_HH
#define	EQUATIONPROBLEM_HH

#include <iostream>

#include "Problem.hh"
#include "Chromosome.hh"

class EquationProblem : public Problem
{
    public: 
        EquationProblem();
        
        virtual void print(const Chromosome *chromosome) const;
        virtual void askParameters();
        virtual double computeFitnessOf(const Chromosome *chromosome) const;
        virtual double getSolution() const;
       
        ~EquationProblem();
        
    private:
        double _number;
};

#endif	/* EQUATIONPROBLEM_HH */

