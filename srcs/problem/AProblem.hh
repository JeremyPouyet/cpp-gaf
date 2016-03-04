#ifndef APROBLEM_HH
#define	APROBLEM_HH

#include "Problem.hh"

class AProblem : public Problem
{
public:
    virtual void print(const Strand &strand) { (void)strand; }
    virtual void askParameters() {}
    virtual bool loadData() { return true; }
    virtual double computeFitnessOf(const Strand &strand) const = 0;
    virtual bool test(const Strand &strand) const = 0;
    void setConfig(Config &config) { _config = config; }
    virtual void giveBestSolution(const Strand &strand) const { (void)strand; }
    
    virtual ~AProblem() {}
protected:
    Config _config;
};

#endif	/* APROBLEM_HH */

