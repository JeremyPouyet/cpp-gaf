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
        virtual double computeValue(Chromosome *chromosome) const;
        
        ~EquationProblem();
        
    private:
        std::string getCharValue(int n) const;
        double _number;
};

#endif	/* EQUATIONPROBLEM_HH */

