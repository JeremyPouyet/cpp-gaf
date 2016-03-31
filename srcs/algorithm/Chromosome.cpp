#include "./Chromosome.hh"

const std::map<const std::string, const Chromosome::fp> Chromosome::crossovers = {
    {"one-point", &Chromosome::onePointCrossover},
    {"two-point", &Chromosome::twoPointCrossover},
    {"uniform", &Chromosome::uniformCrossover},
    {"arithmetic", &Chromosome::arithmeticCrossover}
};

std::vector<std::string> Chromosome::getCrossovers() {
    std::vector<std::string> keys;
    for (const auto &crossover : Chromosome::crossovers)
        keys.push_back(crossover.first);
    return keys;
}

Chromosome::Chromosome(const Strand &strand) :
_strand(strand) {
}

void Chromosome::generate() {
    RandomGenerator &randomGenerator = RandomGenerator::getInstance();
    _strand.resize(config.chromosomeSize, false);
    for (unsigned int j = 0; j < config.chromosomeSize; ++j)
        _strand[j] = randomGenerator.i_between(0, 1);
}

Chromosome &Chromosome::operator=(const Chromosome &other) {
    _fitness = other.getFitness();
    _strand = other.getStrand();
    return *this;
}

Strand Chromosome::crossover(const Strand &s1, const Strand &s2, const Problem *problem) {
    return crossovers.at(config.crossoverType)(s1, s2, problem);
}

void Chromosome::mutate() {
    RandomGenerator &randomGenerator = RandomGenerator::getInstance();
    for (unsigned int i = 0; i < _strand.size(); ++i)
        if (randomGenerator.d_between(0, 1) <= config.mutationRate)
            _strand[i].flip();
}

Strand Chromosome::getStrand() const {
    return _strand;
}

double Chromosome::getFitness() const {
    return _fitness;
}

void Chromosome::setStrand(const Strand &strand) {
    _strand = strand;
}

void Chromosome::setFitness(double fitness) {
    if (isnan(fitness))
        fitness = -1;
    _fitness = fitness;
}

/**
 * crossovers type
 */

Strand Chromosome::onePointCrossover(const Strand &s1, const Strand &s2, const Problem *problem) {
    RandomGenerator& randomGenerator = RandomGenerator::getInstance();
    int limit = randomGenerator.i_between(0, config.chromosomeSize);
    Strand child1 = crossoverBetween(s1, s2, limit, config.chromosomeSize);
    Strand child2 = crossoverBetween(s1, s2, limit, config.chromosomeSize);
    return problem->computeFitnessOf(child1) > problem->computeFitnessOf(child2) ? child1 : child2;
}

Strand Chromosome::twoPointCrossover(const Strand &s1, const Strand &s2, const Problem *problem) {
    RandomGenerator& randomGenerator = RandomGenerator::getInstance();
    unsigned int limit1 = randomGenerator.i_between(0, config.chromosomeSize);
    unsigned int limit2 = randomGenerator.i_between(0, config.chromosomeSize);
    Strand child1, child2;
    if (limit1 > limit2) {
        child1 = crossoverBetween(s1, s2, limit1, limit2);
        child2 = crossoverBetween(s2, s1, limit1, limit2);
    } else {
        child1 = crossoverBetween(s1, s2, limit2, limit1);
        child2 = crossoverBetween(s2, s1, limit2, limit1);
    }
    return problem->computeFitnessOf(child1) > problem->computeFitnessOf(child2) ? child1 : child2;
}

Strand Chromosome::uniformCrossover(const Strand &s1, const Strand &s2, const Problem *problem) {
    (void) problem;
    Strand strand = s1;
    RandomGenerator& randomGenerator = RandomGenerator::getInstance();
    for (unsigned int i = 0; i < config.chromosomeSize; ++i)
        if (randomGenerator.i_between(0, 1) == 1)
            strand[i] = s2[i];
    return strand;
}

Strand Chromosome::arithmeticCrossover(const Strand &s1, const Strand &s2, const Problem *problem) {
    (void) problem;
    return s1 ^ s2;
}

Strand Chromosome::crossoverBetween(const Strand &s1, const Strand &s2, unsigned int l1, unsigned int l2) {
    Strand strand = s1;
    for (unsigned int i = l1; i < l2; i++)
        strand[i] = s2[i];
    return strand;
}
