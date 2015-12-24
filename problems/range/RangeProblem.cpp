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
    for (int i = 0; i < 13; i++)
        std::cout << (int)getNextInt(strand) << " ";
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
    int value;
    for (int i = 0; i < 13; i++) {
        value = getNextInt(strand);
        if (value < _min)
            fitness += k * (1.0 / (1 + std::abs(_min - value)));
        else if (value > _max)
            fitness += k * (1.0 / (1 + std::abs(value - _max)));
        else
            fitness += 1;
    }
    return fitness;
}

bool RangeProblem::test(Chromosome *chromosome) const
{
    Chromosome::Strand strand = chromosome->getStrand();
    int value;
    for (int i = 0; i < 13; i++)
    {
        value = getNextInt(strand);
        if (value < _min || value > _max)
            return false;
    }
    return true;
}

int8_t RangeProblem::getNextInt(Chromosome::Strand strand) const
{
    static int p = 0;
    int a = 0;
    for (int j = 0; j < 8; j++)
        if (strand[p + j] == '1')
            a |= 1 << j;   
    p += 8;
    return a;
}