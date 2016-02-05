#ifndef RANGEPROBLEM_HH
#define	RANGEPROBLEM_HH

#include <iostream>

#include "AProblem.hh"

class RangeProblem : public AProblem {
    public:
        RangeProblem() : AProblem() {}
        
        virtual void print(const std::string &strand) const;
        virtual void askParameters();
        virtual double computeFitnessOf(const std::string &strand) const;
        virtual bool test(const std::string &strand) const;
        
        virtual ~RangeProblem() {}
        
    private:
        typedef int32_t targetType;
        targetType getNextInt(const std::string &strand, int &p) const;
        
        targetType _min;
        targetType _max;
};

#endif	/* RANGEPROBLEM_HH */

