#ifndef CONFIG_HH
#define	CONFIG_HH

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "INIReader.h"

struct Config {
public:
    /**
     * load a configuration file into the program
     * @param path, configuration file path
     * @return whether the configuration file is loaded or not
     */
    bool load(const std::string &path);
    
    /*
    ** Population configuration variable
    */
    // rate at which a chromosome can be crossover
    double crossoverRate;
    // number of possible solution
    unsigned int populationSize;
    // Number of generation
    unsigned int simulationNumber;
    
    /*
    ** Chromosome configuration variable
    */
    // Rate at which a chromosome mutate
    double mutationRate;
    // Number of chromosome in a gene => equal to a possible solution
    int genePerChromosome;
    // Number of bit in a chromosome, each bit represents a part of a solution
    int chromosomeSize;
    // Type of crossover used during chromosome reproduction
    std::string crossoverType;
    // Type of selection used during population selection
    std::string selectionType;
private:
    /**
     * Display an error when the chosen crossover does not exists
     */
    void printCrossoverError() const;
    
    /**
     * Display an error when the chosen selection does not exists
     */
    void printSelectionError() const;
    
    /**
     * Check if chosen crossover is valid
     * @return whether the crossover is valid or not
     */
    bool checkCrossover() const;
    
    /**
     * check if chosen selection is valid
     * @return whether the selection is valid or not
     */
    bool checkSelection() const;
};

// configuration variable
extern Config config;

#endif	/* CONFIG_HH */