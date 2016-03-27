#pragma once

#include <string>
#include <iostream>

#include "AProblem.hh"
#include "Config.hh"
#include "Population.hh"
#include "Display.hpp"
#include "Chrono.hpp"
#include "DynamicLoader.hpp"

class Simulation {
public:
    /**
     * Initialise the simulation
     * @param ac, command line parameters number
     * @param av, command line parameters
     * @return an error or success code that says if the initialisation succeeded
     */ 
    int initialise(int ac, char **av);
    
    /**
     * run the simulation
     */
    void run();
    
    /**
     * properly destroy the simulation
     */
    ~Simulation();

private:
    /**
     * Try to Solve the current Problem
     * @param population, chromosome population
     * @return whether the problem is solve or not
     */
    bool solve(Population &population);
    
    /**
     * print informations about the population
     * @param population, population to get data from
     */
    inline void printResume(const Population &population) const;
    
    /**
     * Initialise user data
     * @return whether the initialisation succeed
     */
    bool userInitialisation();
    /**
     * Initialise configuration file
     * @param ac, command line parameters number
     * @param av, command line parameters
     * @return an error or success code that says if the initialisation succeeded 
     */
    int configInitialisation(int ac, char **av);
    
    // problem to solve
    Problem *_problem = NULL;
    // display object
    Display &_display = Display::getInstance();
    // Timer to time the simulation time
    Chrono _timer;
    // object that loads a shared library into the framework
    DynamicLoader<Problem> _problemLoader;
    // index of the current generation
    unsigned int _currentGeneration = 1;
};