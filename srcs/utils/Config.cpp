#include "Config.hh"

Config config;

// list of all possible crossover type
static const std::vector<std::string> _crossovers = {
    "one-point", "two-point", "uniform", "arithmetic"};

// list of all possible selection type
static const std::vector<std::string> _selections = {
    "fitness-proportional", "tournament"};

static struct option const long_opts[] = {
    {"help", no_argument, NULL, 'h'},
    {"verbose", no_argument, NULL, 'v'}
};

/*
 * This class is the only one on which the keyword this is used
 * we use it here because attributes aren't starting with '_' because they are public
*/

void Config::parseOptions(int ac, char **av) {
    std::string path(av[1]);
    _configurationPath  = path + "problem.ini";
    _problemPath        = path + "problem.so";
    int c;
    
    while ((c = getopt_long(ac, av, "hv", long_opts, NULL)) != -1) {
        switch (c) {
            case 'h': this->help    = true; break;
            case 'v': this->verbose = true; break;
        }
    }
}
 
bool Config::load() {
    INIReader reader(_configurationPath);
    int error = reader.ParseError();
    if (error > 0) {
        std::cerr << "Error on configuration file line " << error << std::endl;
        return false;
    }
    if (error < 0) {
        std::cerr << "Error while opening problem.ini file" << std::endl;
        return false;
    }
    this->crossoverRate     = reader.GetReal("population", "crossover_rate", 0.7);
    this->populationSize    = reader.GetInteger("population", "size", 100);
    this->simulationNumber  = reader.GetInteger("population", "simulation_number", 1500);
    this->mutationRate      = reader.GetReal("chromosome", "mutation_rate", 0.1);
    this->genePerChromosome = reader.GetInteger("chromosome", "gene_per_chromosome", 1);
    this->chromosomeSize    = reader.GetInteger("chromosome", "chromosome_size", 8);
    this->crossoverType     = reader.Get("chromosome", "crossover_type", "one-point");
    this->eliteNumber       = reader.GetInteger("elitism", "elite_number", 0);
    this->selectionType     = reader.Get("selection", "selection_type", "fitness-proportional");
    this->tournamentSize    = reader.GetInteger("selection", "tournament_size", 1);    
    return isValid();
}

bool Config::isValid() const {
    if (checkCrossover() == false) {
        printCrossoverError();
        return false;
    }
    if (this->eliteNumber > this->populationSize) {
        std::cerr << "Elite number is bigger than population size." << std::endl;
        return false;
    }
    if (checkSelection() == false) {
        printSelectionError();
        return false;
    }
    if (this->selectionType == "tournament" && this->populationSize < this->tournamentSize) {
        std::cerr << "Tournament size is bigger than population size" << std::endl;
        return false;
    }
    return true;
}

bool Config::checkCrossover() const {
    return std::find(_crossovers.begin(), _crossovers.end(), this->crossoverType) != _crossovers.end();
}

bool Config::checkSelection() const {
    return std::find(_selections.begin(), _selections.end(), this->selectionType) != _selections.end();
}

void Config::printCrossoverError() const {
    std::cerr << "Error: crossover " << this->crossoverType << " does not exists or is not yet implemented" << std::endl;
    std::cerr << "Available crossovers: " << std::endl;
    for (auto c: _crossovers)
        std::cerr << c << " ";
    std::cerr << std::flush;
}

void Config::printSelectionError() const {
    std::cerr << "Error: selection " << this->selectionType << " does not exists or is not yet implemented" << std::endl;
    std::cerr << "Available selections: " << std::endl;
    for (auto s: _selections)
        std::cerr << s << " ";
    std::cerr << std::flush;
}

std::string Config::getProblemPath() const {
    return _problemPath; 
}