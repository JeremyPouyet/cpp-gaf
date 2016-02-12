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
    
    /**
     * Display the current configuration
     */
    void display();
    
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
    unsigned int genePerChromosome;
    // Number of bit in a chromosome, each bit represents a part of a solution
    unsigned int chromosomeSize;
    // Type of crossover used during chromosome reproduction
    std::string crossoverType;
    
    /*
    ** Selection configuration variable
    */
    // Type of selection used during population selection
    std::string selectionType;
    // number of candidate solution selected in tournament selection
    unsigned int tournamentSize;
    
    /*
     * Elitism configuration variable
     */
    // whether or not elitism has to be used
    bool useElitism;
    // number of elite to pick in a generation
    unsigned int eliteNumber;
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