#ifndef PROBLEM_H
#define	PROBLEM_H

#include "Config.hh"

class Problem {
public:
    Problem() {}
    
    virtual void print(const std::string &strand) const = 0;
    virtual void askParameters() = 0;
    virtual double computeFitnessOf(const std::string &strand) const = 0;
    virtual bool test(const std::string &strand) const = 0;
    
    virtual ~Problem() {}
};

typedef Problem * create_t();
typedef void destroy_t(Problem *);

#endif	/* PROBLEM_H */

