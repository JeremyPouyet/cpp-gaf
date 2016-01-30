#ifndef CONFIG_HH
#define	CONFIG_HH

#include <iostream>

#include "INIReader.h"

struct Config {
    
    bool load(const std::string &path);
    
    // Population
    double crossoverRate;
    unsigned int populationSize;
    unsigned int simulationNumber;
    
    // Chromosome 
    double mutationRate;
    int genePerChromosome;
    int chromosomeSize;
};

#endif	/* CONFIG_HH */

