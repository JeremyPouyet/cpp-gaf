#ifndef EQUATIONPROBLEM_HH
#define	EQUATIONPROBLEM_HH

#include <iostream>

#include "Problem.hh"

class EquationProblem : public Problem
{
    public: 
        EquationProblem();
        virtual void print() const;
        ~EquationProblem();
};

#endif	/* EQUATIONPROBLEM_HH */

