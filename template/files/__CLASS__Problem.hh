#ifndef __CLASS__ProblemHH
#define __CLASS__ProblemHH

#include "AProblem.hh"
#include "Getters.hpp"

class __CLASS__Problem : public AProblem {
    public:

    __CLASS__Problem();
    void print(const Strand &strand) const;
    void askParameters();
    bool loadData();
    double computeFitnessOf(const Strand &strand) const;
    bool test(const Strand &strand) const;
    void giveBestSolution(const Strand &strand) const;
    virtual ~__CLASS__Problem();
};

#endif /* __CLASS___ProblemHH */

