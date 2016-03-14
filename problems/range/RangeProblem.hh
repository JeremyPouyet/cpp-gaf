#pragma once

#include <iostream>
#include <climits>

#include "AProblem.hh"
#include "Getters.hpp"

class RangeProblem : public AProblem {
    public:
        void print(const Strand &strand) const;
        void askParameters();
        double computeFitnessOf(const Strand &strand) const;
        bool test(const Strand &strand) const;
        
        virtual ~RangeProblem() {}
        
    private:
        typedef int16_t targetType;
        
        targetType _min;
        targetType _max;
};
