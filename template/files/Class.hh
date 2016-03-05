#ifndef __CLASS___HH
#define __CLASS___HH

#include "AProblem.hh"
#include "Getters.hpp"

class __CLASS__ : public AProblem {
    public:

    __CLASS__();
    void print(const Strand &strand) const;
    void askParameters();
    bool loadData();
    double computeFitnessOf(const Strand &strand) const;
    bool test(const Strand &strand) const;
    void giveBestSolution(const Strand &strand) const;
    virtual ~__CLASS__();
};

#endif /* __CLASS___HH */

