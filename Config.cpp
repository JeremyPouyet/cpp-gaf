#include "Config.hh"

Config config;

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
    
    std::cout << "Population config: " << std::endl << "------------------" << std::endl << std::endl;
    std::cout << "crossover rate: " << crossoverRate << std::endl;
    std::cout << "population size: " << populationSize << std::endl;
    std::cout << "simulation number: " << simulationNumber << std::endl << std::endl;
    
    std::cout << "Chromosome config: " << std::endl << "------------------" << std::endl << std::endl;
    std::cout << "mutation rate: " << mutationRate << std::endl;
    std::cout << "gene per chromosome: " << genePerChromosome << std::endl;
    std::cout << "chromosome size: " << chromosomeSize << std::endl << std::endl;
    return true;
}