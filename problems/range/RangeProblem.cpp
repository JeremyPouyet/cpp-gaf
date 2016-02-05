#include "RangeProblem.hh"

extern "C" Problem *create() {
    return new RangeProblem();
}

extern "C" void destroy(Problem *problem) {
    delete problem;
}

void RangeProblem::print(const std::string &strand) const {
    std::cout << "numbers in this chromosome: " << std::endl;
    int p = 0;
    for (int i = 0; i < _config.genePerChromosome; i++)
        std::cout << getNextInt(strand, p) << " ";
    std::cout << " fitness: " << computeFitnessOf(strand) << std::endl;
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

double RangeProblem::computeFitnessOf(const std::string &strand) const {
    double fitness = 0;
    targetType value;
    int p = 0;
    for (int i = 0; i < _config.genePerChromosome; i++) {
        value = getNextInt(strand, p);
        if (value < _min)
            fitness += 1.0 / (1 + std::abs(_min - value));
        else if (value > _max)
            fitness += 1.0 / (1 + std::abs(value - _max));
        else
            fitness += 2;
    }
    return fitness;
}

bool RangeProblem::test(const std::string &strand) const
{
    targetType value;
    int p = 0;
    for (int i = 0; i < _config.genePerChromosome; i++)
    {
        value = getNextInt(strand, p);
        if (value < _min || value > _max)
            return false;
    }
    return true;
}

RangeProblem::targetType RangeProblem::getNextInt(const std::string &strand, int &p) const
{
    targetType a = 0;
    for (int j = 0; j < _config.chromosomeSize/_config.genePerChromosome; j++)
        if (strand[p + j] == '1')
            a |= 1 << j;   
    p += _config.chromosomeSize/_config.genePerChromosome;
    return a;
}