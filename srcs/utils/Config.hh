#pragma once

#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/dynamic_bitset.hpp>

#include "../inih/INIReader.h"

typedef boost::dynamic_bitset<> Strand;

struct Config {
public:
    
    // whether the help have to be displayed
    bool help = false;
    // whether diverse informations have to be displayed
    bool verbose = false;
    
    void parseOptions(int ac, char **av);
    
    /**
     * load a configuration file into the program
     * @return whether the configuration file is loaded or not
     */
    bool load();
    
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
    // Number of chromosome in a gene, not mandatory, only used by the user
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
    // number of elite to pick in a generation
    unsigned int eliteNumber;
    
    std::string getProblemPath() const;
private:
    /**
     * Display an error when the chosen crossover does not exists
     */
    inline void printCrossoverError() const;
    
    /**
     * Display an error when the chosen selection does not exists
     */
    inline void printSelectionError() const;
    
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
    
    /**
     * check if the loaded configuration is valid
     * @return whether the configuration is valid
     */
    bool isValid() const;
    
    std::string _configurationPath;
    std::string _problemPath;
};

// configuration variable
extern Config config;
