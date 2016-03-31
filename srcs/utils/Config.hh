#pragma once

#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../inih/INIReader.h"

struct Config {
public:
    
    // whether the help have to be displayed
    bool help = false;
    // whether diverse informations have to be displayed
    bool verbose = false;
    
    /**
     * Parse command line options stored in av
     * @param ac, number of command line parameters
     * @param av, command line parameters
     */
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
    
    void setCrossovers(const std::vector<std::string> &crossovers);
    void setSelections(const std::vector<std::string> &selections);
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
    
    // path of the configuration file
    std::string _configurationPath;
    // path of the shared library representing the current problem
    std::string _problemPath;
    // list of all possible crossovers
    std::vector<std::string> _crossovers;
    // list of all possible selections
    std::vector<std::string> _selections;
};

// configuration variable
extern Config config;
