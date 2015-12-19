#include "RangeProblem.hh"

extern "C" Problem *create() {
    return new RangeProblem();
}

extern "C" void destroy(Problem *problem) {
    delete problem;
}

void RangeProblem::print(const Chromosome *chromosome) const {
    Chromosome::Strand strand = chromosome->getStrand();
    std::cout << "numbers in this chromosome: " << std::endl;
    for (auto gene: strand)
        std::cout << (int)gene << " ";
    std::cout << std::endl;
}

void RangeProblem::askParameters() {
    std::cout << "Enter the minimum value: " << std::flush;
    std::cin >> _min;
    std::cout << "Enter the maximum value: " << std::flush;
    std::cin >> _max;
}

double RangeProblem::computeFitnessOf(const Chromosome *chromosome) const {
    Chromosome::Strand strand = chromosome->getStrand();
    double fitness = 0.0002;
    for (auto gene: strand) {
        if (gene > _min && gene < _max)
            fitness += 0.5;
    }
    return fitness;
}

bool RangeProblem::test(Chromosome *chromosome) const
{
    Chromosome::Strand strand = chromosome->getStrand();
    for (auto gene: strand)
        if (gene <= _min || gene >= _max)
            return false;
    return true;
}