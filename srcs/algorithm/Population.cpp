#include "Population.hh"

const std::map<const std::string, const Population::fp> Population::selections = {
    {"fitness-proportional", &Population::fitnessProportionateSelection},
    {"tournament", &Population::tournamentSelection}
};

Population::Population(Problem *problem) :
_population(config.populationSize),
_nextGeneration(config.populationSize),
_problem(problem) {
    double fitness;
    for (auto &candidate : _population) {
        candidate.generate();
        fitness = _problem->computeFitnessOf(candidate.getStrand());
        candidate.setFitness(fitness);
    }
}

std::vector<std::string> Population::getSelections() {
    std::vector<std::string> keys;
    for (const auto &selection : selections)
        keys.push_back(selection.first);
    return keys;
}

bool Population::checkForWinner() {
    // compute fitness of all chromosome
    if (config.selectionType == "fitness-proportional") {
        _totalFitness = 0;
        for (const auto &candidate : _population)
            _totalFitness += candidate.getFitness();
    }
    // sort them by fitness
    sortByFitness();
    // test if the best candidate solution solves the problem
    return _problem->test(_population.front().getStrand());
}

void Population::print() const {
    for (const auto &candidate : _population)
        _problem->print(candidate.getStrand());
}

unsigned int Population::selectChromosome() const {
    return selections.at(config.selectionType)(*this);
}

void Population::sortByFitness() {
    std::sort(_population.begin(), _population.end(), [](const Chromosome& c1, const Chromosome & c2) {
        return c1.getFitness() > c2.getFitness();
    });
}

void Population::reproduce() {
    unsigned int c1, c2;
    Strand child;
    // Elitism if used
    for (unsigned int i = 0; i < config.eliteNumber; ++i)
        _nextGeneration[i] = _population[i];
#pragma omp parallel for private(c1, c2, child)
    for (unsigned int i = config.eliteNumber; i < config.populationSize; ++i) {
        c1 = selectChromosome();
        if (RandomGenerator::getInstance().d_between(0, 1) <= config.crossoverRate) {
            c2 = selectChromosome();
            child = Chromosome::crossover(_population[c1].getStrand(), _population[c2].getStrand(), _problem);
        } else
            child = _population[c1].getStrand();
        _nextGeneration[i].setStrand(child);
        _nextGeneration[i].mutate();
        _nextGeneration[i].setFitness(_problem->computeFitnessOf(_nextGeneration[i].getStrand()));
    }
    _population = _nextGeneration;
}

/**
 ** Selections
 */

unsigned int Population::fitnessProportionateSelection(const Population &population) {
    double randomNb = RandomGenerator::getInstance().d_between(0, population.getTotalFitness());
    double curFitness = 0;
    unsigned int id = 0;
    while (curFitness < randomNb)
        curFitness += population[id++].getFitness();
    return id;
}

unsigned int Population::tournamentSelection(const Population &population) {
    // use set to ensure chromosome uniqueness
    std::map<int, bool> subPop;
    int id, bestId = config.populationSize - 1;
    // for each tournament
    while (subPop.size() != config.tournamentSize) {
        // randomly select a chromosome
        id = RandomGenerator::getInstance().i_between(0, config.populationSize - 1);
        if (subPop.count(id) == 0) {
            subPop.insert({id, true});
            // and check if it's better than the other
            if (population[id].getFitness() > population[bestId].getFitness())
                bestId = id;
        }
    }
    return bestId;
}

/**
 * getters
 */

double Population::getTotalFitness() const {
    return _totalFitness;
}

Strand Population::at(unsigned int id) const {
    return _population[id].getStrand();
}

Strand Population::best() const {
    return at(0);
}

Strand Population::worst() const {
    return at(_population.size() - 1);
}

const Chromosome & Population::operator[](unsigned int id) const {
    return _population[id];
}