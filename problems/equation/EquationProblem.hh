#pragma once

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
        
        void print(const Strand &strand) const;
        void askParameters();
        double computeFitnessOf(const Strand &strand) const;
        double computeValue(const Strand &strand) const;
        bool test(const Strand &strand) const;
        
        virtual ~EquationProblem() {}
        
    private:
        char getCharValue(const Strand &strand, unsigned int &off) const;
        double _number;
};
