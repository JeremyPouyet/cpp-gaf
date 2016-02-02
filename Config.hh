#ifndef CONFIG_HH
#define	CONFIG_HH

#include <iostream>
#include "INIReader.h"

struct Config {
    
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
};

extern Config config;

#endif	/* CONFIG_HH */