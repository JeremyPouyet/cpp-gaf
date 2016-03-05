#include "RangeProblem.hh"

extern "C" Problem *create() {
    return new RangeProblem();
}

void RangeProblem::print(const Strand &strand) const {
    std::cout << "numbers in this chromosome: " << std::endl;
    for (unsigned int i = 0; i < _config.chromosomeSize;)
        std::cout << getters::getValue<int16_t>(strand, i) << " ";
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

double RangeProblem::computeFitnessOf(const Strand &strand) const {
    double fitness = 0;
    targetType value;
    for (unsigned int i = 0; i < _config.chromosomeSize;) {
        value = getters::getValue<int16_t>(strand, i);
        if (value < _min)
            fitness += 1.0 / (1 + std::abs(_min - value));
        else if (value > _max)
            fitness += 1.0 / (1 + std::abs(value - _max));
        else
            fitness += 2;
    }
    return fitness;
}

bool RangeProblem::test(const Strand &strand) const
{
    targetType value;
    for (unsigned int i = 0; i < _config.chromosomeSize;)
    {
        value = getters::getValue<int16_t>(strand, i);
        if (value < _min || value > _max)
            return false;
    }
    return true;
}