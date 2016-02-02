#ifndef APROBLEM_HH
#define	APROBLEM_HH

#include "Problem.hh"

class AProblem : public Problem
{
public:
    AProblem() : Problem() {}
    
    virtual void print(const std::string &strand) const = 0;
    virtual void askParameters() = 0;
    virtual double computeFitnessOf(const std::string &strand) const = 0;
    virtual bool test(const std::string &strand) const = 0;
    void setConfig(Config &config);
    
    virtual ~AProblem() {}
protected:
    Config _config;
};

#endif	/* APROBLEM_HH */

