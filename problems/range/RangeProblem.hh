#ifndef RANGEPROBLEM_HH
#define	RANGEPROBLEM_HH

#include <iostream>

#include "Problem.hh"

class RangeProblem : public Problem {
    public:
        RangeProblem() {}
        
        virtual void print(const std::string &strand) const;
        virtual void askParameters();
        virtual double computeFitnessOf(const std::string &strand) const;
        virtual bool test(const std::string &strand) const;
        
        virtual ~RangeProblem() {}
        
    private:
        int8_t getNextInt(const std::string &strand) const;
        
        int _min;
        int _max;
};

#endif	/* RANGEPROBLEM_HH */

