#ifndef EQUATIONPROBLEM_HH
#define	EQUATIONPROBLEM_HH

#include <iostream>
#include <cmath>

#include "Problem.hh"

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
        
        virtual void print(const std::string &strand) const;
        virtual void askParameters();
        virtual double computeFitnessOf(const std::string &strand) const;
        virtual double computeValue(const std::string &strand) const;
        virtual bool test(const std::string &strand) const;
        
        virtual ~EquationProblem() {}
        
    private:
        std::string getCharValue(const std::string &strand, int &p) const;
        int8_t getIntValue(const std::string &strand, int &p) const;
        double _number;
};

#endif	/* EQUATIONPROBLEM_HH */

