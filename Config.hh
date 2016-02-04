#ifndef CONFIG_HH
#define	CONFIG_HH

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "INIReader.h"

struct Config {
public:
    bool load(const std::string &path);
    
    /*
    ** Population
    */
    // rate at which a chromosome can be crossovered
    double crossoverRate;
    // number of possible solution
    unsigned int populationSize;
    // Number of generation
    unsigned int simulationNumber;
    
    /*
    ** Chromosome 
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
    // display an error when the chosen crossover does not exists
    void printCrossoverError() const;
    // display an error when the chosen selection does not exists
    void printSelectionError() const;
    
    // check if chosen crossover is valid
    bool checkCrossover() const;
    // check if chosen selection is valid
    bool checkSelection() const;
};

extern Config config;

#endif	/* CONFIG_HH */