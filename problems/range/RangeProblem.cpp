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
    std::cout << " fitness: " << computeFitnessOf(chromosome) << std::endl;
}

void RangeProblem::askParameters() {
    std::cout << "Enter the minimum value: " << std::flush;
    std::cin >> _min;
    do {
        std::cout << "Enter the maximum value: " << std::flush;
        std::cin >> _max;
        if (_min > _max)
            std::cout << "maximum value is bellow minimum value" << std::endl;
    } while (_min > _max);
}

double RangeProblem::computeFitnessOf(const Chromosome *chromosome) const {
    Chromosome::Strand strand = chromosome->getStrand();
    double fitness = 0;
    double k = 4;
    for (auto gene: strand) {
        if (gene < _min)
            fitness += k * (1.0 / (1 + std::abs(_min - gene)));
        else if (gene > _max)
            fitness += k * (1.0 / (1 + std::abs(gene - _max)));
        else
            fitness += 1;
    }
    return fitness;
}

bool RangeProblem::test(Chromosome *chromosome) const
{
    Chromosome::Strand strand = chromosome->getStrand();
    for (auto gene: strand)
        if (gene < _min || gene > _max)
            return false;
    return true;
}