#ifndef _POPULATION_HH_
#define _POPULATION_HH_

#include <vector>
#include <cstdlib>
#include <string>
#include <cfloat>
#include <map>

#include "Config.hh"
#include "Problem.hh"
#include "ProblemLoader.hh"
#include "Chromosome.hh"

class Population
{
public:
    Population(Problem *problem);
    ~Population();
    int solve();

private:
    typedef std::vector<Chromosome *> Generation;
    typedef Chromosome *(Population::*fp)() const;
    
    Chromosome  *fitnessProportionateSelection()            const;
    Chromosome  *tournamentSelection()                      const;
    Chromosome  *selectChromosome(const std::string &name)  const;
    Chromosome  *test();
    
    void        print()                                     const;
    void        generate();
    void        clean();
    void        reproduce();

    Generation  _population;
    Chromosome  *_winner;
    double      _totalFitness;
    Problem     *_problem;
    
    const std::map<const std::string, fp> selections;
};

#endif
