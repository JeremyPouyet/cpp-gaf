#include "Config.hh"

Config config;

// list of all possible crossover type
static const std::vector<std::string> _crossovers = {
    "one-point", "two-point"};

// list of all possible selection type
static const std::vector<std::string> _selections = {
    "fitness-proportional", "tournament"};

bool Config::load(const std::string &path) {
    INIReader reader(path);
    if (reader.ParseError() < 0)
      return false;
    
    crossoverRate = reader.GetReal("population", "crossover_rate", 0.7);
    populationSize = reader.GetInteger("population", "size", 100);
    simulationNumber = reader.GetInteger("population", "simulation_number", 1500);
    
    mutationRate = reader.GetReal("chromosome", "mutation_rate", 0.1);
    genePerChromosome = reader.GetInteger("chromosome", "gene_per_chromosome", 13);
    chromosomeSize = reader.GetInteger("chromosome", "chromosome_size", 8) * genePerChromosome;
    crossoverType = reader.Get("chromosome", "crossover_type", "one-point");
    if (checkCrossover() == false) {
        printCrossoverError();
        return false;
    }
    
    useElitism = reader.GetBoolean("elitism", "use_elitism", false);
    eliteNumber = reader.GetInteger("elitism", "elite_number", 0);
 
    selectionType = reader.Get("selection", "selection_type", "fitness-proportional");
    if (checkSelection() == false) {
        printSelectionError();
        return false;
    }
    tournamentSize = reader.GetInteger("selection", "tournament_size", 1);
    return true;
}

void Config::display() {
    std::cout << "Population configuration:\t " << std::endl << "-------------------------" << std::endl << std::endl;
    std::cout << "crossover rate:\t\t " << crossoverRate << std::endl;
    std::cout << "population size:\t " << populationSize << std::endl;
    std::cout << "simulation number:\t " << simulationNumber << std::endl << std::endl;
    
    std::cout << "Chromosome configuration:\t " << std::endl << "-------------------------" << std::endl << std::endl;
    std::cout << "mutation rate:\t\t " << mutationRate << std::endl;
    std::cout << "gene per chromosome:\t " << genePerChromosome << std::endl;
    std::cout << "chromosome size:\t " << chromosomeSize << std::endl;
    std::cout << "crossover_type:\t\t " << crossoverType << std::endl << std::endl; 
    
    std::cout << "Elitism configuration:\t " << std::endl << "----------------------" << std::endl << std::endl;
    std::cout << "Is elitism used:\t " << useElitism << std::endl;
    std::cout << "Number of elite:\t " << eliteNumber << std::endl << std::endl;
    
    std::cout << "Selection configuration:" << std::endl << "------------------------" << std::endl << std::endl;
    std::cout << "selection_type:\t\t " << selectionType << std::endl;
    std::cout << "Tournament size:\t" << tournamentSize << std::endl << std::endl;
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
        std::cerr << c;
    std::cerr << std::flush;
}

void Config::printSelectionError() const {
    std::cerr << "Error: selection " << selectionType << " does not exists or is not yet implemented" << std::endl;
    std::cerr << "Available selections: " << std::endl;
    for (auto s: _selections)
        std::cerr << s;
    std::cerr << std::flush;
}