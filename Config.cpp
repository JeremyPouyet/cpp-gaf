#include "Config.hh"

Config config;

// list of all possible crossover type
static const std::vector<std::string> _crossovers = {
    "one-point", "two-point", "uniform"};

// list of all possible selection type
static const std::vector<std::string> _selections = {
    "fitness-proportional", "tournament"};

static struct option const long_opts[] = {
    {"help", no_argument, NULL, 'h'},
    {"verbose", no_argument, NULL, 'v'}
};

void Config::parseOptions(int ac, char **av) {
    help = false;
    verbose = false;
    int c;
    
    while ((c = getopt_long(ac, av, "hv", long_opts, NULL)) != -1) {
        switch (c) {
            case 'h': this->help = true; break;
            case 'v': this->verbose = true; break;
        }
    }
}
 
bool Config::load(const std::string &path) {
    INIReader reader(path);
    int error = reader.ParseError();
    if (error > 0) {
        std::cerr << "Error on configuration file line " << error << std::endl;
        return false;
    }
    if (error < 0) {
        std::cerr << "Error while opening configuration file" << std::endl;
        return false;
    }
    this->crossoverRate = reader.GetReal("population", "crossover_rate", 0.7);
    this->populationSize = reader.GetInteger("population", "size", 100);
    this->simulationNumber = reader.GetInteger("population", "simulation_number", 1500);
    
    this->mutationRate = reader.GetReal("chromosome", "mutation_rate", 0.1);
    this->genePerChromosome = reader.GetInteger("chromosome", "gene_per_chromosome", 1);
    this->chromosomeSize = reader.GetInteger("chromosome", "chromosome_size", 8);
    this->crossoverType = reader.Get("chromosome", "crossover_type", "one-point");
    if (checkCrossover() == false) {
        printCrossoverError();
        return false;
    }
    this->eliteNumber = reader.GetInteger("elitism", "elite_number", 0);
    this->selectionType = reader.Get("selection", "selection_type", "fitness-proportional");
    if (checkSelection() == false) {
        printSelectionError();
        return false;
    }
    if (this->selectionType == "tournament" && populationSize < tournamentSize) {
        std::cerr << "Tournament size is bigger than the population" << std::endl;
        return false;
    }
    this->tournamentSize = reader.GetInteger("selection", "tournament_size", 1);
    return true;
}

bool Config::checkCrossover() const {
    return std::find(_crossovers.begin(), _crossovers.end(), crossoverType) != _crossovers.end();
}

bool Config::checkSelection() const {
    return std::find(_selections.begin(), _selections.end(), selectionType) != _selections.end();
}

void Config::printCrossoverError() const {
    std::cerr << "Error: crossover " << crossoverType << " does not exists or is not yet implemented" << std::endl;
    std::cerr << "Available crossovers: " << std::endl;
    for (auto c: _crossovers)
        std::cerr << c << " ";
    std::cerr << std::flush;
}

void Config::printSelectionError() const {
    std::cerr << "Error: selection " << selectionType << " does not exists or is not yet implemented" << std::endl;
    std::cerr << "Available selections: " << std::endl;
    for (auto s: _selections)
        std::cerr << s << " ";
    std::cerr << std::flush;
}