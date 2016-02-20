#ifndef EQUATIONPROBLEM_HH
#define	EQUATIONPROBLEM_HH

#include <iostream>
#include <cmath>
#include <cstdint>
#include <climits>

#include "AProblem.hh"
#include "Getters.hpp" 

enum Type
{
  DIGIT,
  OPERATOR,
  UNKNOWN
};

class EquationProblem : public AProblem
{
    public:
        
        void print(const std::string &strand) const;
        void askParameters();
        double computeFitnessOf(const std::string &strand) const;
        double computeValue(const std::string &strand) const;
        bool test(const std::string &strand) const;
        
        virtual ~EquationProblem() {}
        
    private:
        char getCharValue(const std::string &strand, unsigned int &off) const;
        double _number;
};

#endif	/* EQUATIONPROBLEM_HH */

