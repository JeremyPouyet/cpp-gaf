#ifndef APROBLEM_HH
#define	APROBLEM_HH

#include "Problem.hh"

class AProblem : public Problem
{
public:
    virtual void print(const std::string &strand) const = 0;
    virtual void askParameters() {}
    virtual bool loadData() { return true; }
    virtual double computeFitnessOf(const std::string &strand) const = 0;
    virtual bool test(const std::string &strand) const = 0;
    void setConfig(Config &config) { _config = config; }
    virtual void giveBestSolution(const std::string &strand) const { (void)strand;}
    
    virtual ~AProblem() {}
protected:
    Config _config;
};

#endif	/* APROBLEM_HH */

