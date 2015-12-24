#ifndef EQUATIONPROBLEM_HH
#define	EQUATIONPROBLEM_HH

#include <iostream>

#include "Problem.hh"
#include "Chromosome.hh"

enum Type
{
  DIGIT,
  OPERATOR,
  UNKNOWN
};

class EquationProblem : public Problem
{
    public: 
        EquationProblem() {}
        
        virtual void print(const Chromosome *chromosome) const;
        virtual void askParameters();
        virtual double computeFitnessOf(const Chromosome *chromosome) const;
        virtual double computeValue(const Chromosome *chromosome) const;
        virtual bool test(Chromosome *chromosome) const;
        
        virtual ~EquationProblem() {}
        
    private:
        std::string getCharValue(Chromosome::Strand strand, int &p) const;
        int8_t getIntValue(Chromosome::Strand strand, int &p) const;
        double _number;
};

#endif	/* EQUATIONPROBLEM_HH */

