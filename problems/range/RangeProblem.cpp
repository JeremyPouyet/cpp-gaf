#include "RangeProblem.hh"

extern "C" Problem *create() {
    return new RangeProblem();
}

extern "C" void destroy(Problem *problem) {
    delete problem;
}

void RangeProblem::print(const std::string &strand) const {
    std::cout << "numbers in this chromosome: " << std::endl;
    for (int i = 0; i < _config.genePerChromosome; i++)
        std::cout << (int)getNextInt(strand) << " ";
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
    std::cout << "compf" <<std::endl;
    double fitness = 0;
    double k = 4;
    int value;
    for (int i = 0; i < _config.genePerChromosome; i++) {
        value = getNextInt(strand);
        if (value < _min)
            fitness += k * (1.0 / (1 + std::abs(_min - value)));
        else if (value > _max)
            fitness += k * (1.0 / (1 + std::abs(value - _max)));
        else
            fitness += 1;
    }
    std::cout << "compf" <<std::endl;
    return fitness;
}

bool RangeProblem::test(const std::string &strand) const
{
    std::cout << "test"<< std::endl;
    int value;
    for (int i = 0; i < _config.genePerChromosome; i++)
    {
        value = getNextInt(strand);
        if (value < _min || value > _max)
            return false;
    }
    return true;
}

int8_t RangeProblem::getNextInt(const std::string &strand) const
{
    std::cout << "gni" <<std::endl;
    static int p = 0;
    int a = 0;
    for (int j = 0; j < _config.chromosomeSize; j++)
        if (strand[p + j] == '1')
            a |= 1 << j;   
    p += _config.chromosomeSize;
    std::cout << "gni" <<std::endl;
    return a;
}