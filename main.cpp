#include <cstdlib>
#include <string>

#include <iostream>

#include "./Population.hh"
#include "./Chromosome.hh"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Wrong number of arguments: ./number problem" << std::endl;
        return 1;
    }
    std::srand(time(NULL));
    ProblemLoader pl;
    try {
        pl.load(av[1]);
    } catch(std::string &error) {
       std::cerr << error << std::endl;
       return false;
    }
    Problem * problem = pl.getProblem();
    Population p;
    return p.solve(problem);
}
