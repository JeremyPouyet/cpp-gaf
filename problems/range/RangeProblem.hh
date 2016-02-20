#ifndef RANGEPROBLEM_HH
#define	RANGEPROBLEM_HH

#include <iostream>
#include <climits>

#include "AProblem.hh"
#include "Getters.hpp"

class RangeProblem : public AProblem {
    public:
        void print(const std::string &strand) const;
        void askParameters();
        double computeFitnessOf(const std::string &strand) const;
        bool test(const std::string &strand) const;
        
        virtual ~RangeProblem() {}
        
    private:
        typedef int16_t targetType;
        
        targetType _min;
        targetType _max;
};

#endif	/* RANGEPROBLEM_HH */

