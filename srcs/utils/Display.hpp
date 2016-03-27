#pragma once

#include <string>
#include <iostream>

/*
 * Singleton Display
 */
class Display {
public:
    
    /**
     * initialise and/or return the Display instance
     * @return the display instance
     */
    static Display &getInstance() {
        static Display display;
        return display;
    }
    
    /**
     * print help message
     */
    void help() const {
        usage();
        newLine();
        basicLine("Option list:");
        optionLine('h', "help\t", "display this help and exit");
        optionLine('v', "verbose", "explain what is being done");
    }
    
    /**
     * print usage message
     */
    void usage() const {
        basicLine("Usage: open-gaf path_to_problem_directory");
    }

    /**
     * print the current configuration
     */
    void showConf() const {
        titleLine("Population configuration:");
        configLine("crossover rate:\t", config.crossoverRate);
        configLine("population size:", config.populationSize);
        configLine("simulation number:", config.simulationNumber);
        newLine();
        titleLine("Chromosome configuration:");
        configLine("mutation rate:\t", config.mutationRate);
        configLine("gene per chromosome:", config.genePerChromosome);
        configLine("chromosome size:", config.chromosomeSize);
        configLine("crossover_type:\t", config.crossoverType);
        newLine();
        titleLine("Elitism configuration:");
        configLine("Number of elite:", config.eliteNumber);
        newLine();
        titleLine("Selection configuration:");
        configLine("selection_type:\t", config.selectionType);
        configLine("Tournament size:", config.tournamentSize);
        newLine();
    }
    
    /**
     * Print an error on a standard way
     * @param error, error to print
     */
    void error(const std::string& err) const {
        std::cerr << "Error: " << err << std::endl;
    }
    
    /**
     * Print a message on a standard way
     * @param msg, msg to print
     */
    void basicLine(const std::string &msg) const {
        std::cout << msg << std::endl;
    }
    
    /**
     * print a new line
     */
    void newLine() const {
        std::cout << std::endl;
    }
private:
    
    /**
     * print an option line
     * @param c, option character
     * @param name, option long name
     * @param msg, option description
     */
    void optionLine(char c, const std::string &name, const std::string &msg) const {
        std::cout << "  -" << c << "\t--" << name << "\t" << msg << std::endl;
    }
    
    /**
     * print a title
     * @param msg, title to print
     */
    void titleLine(const std::string &msg) const {
        std::cout << msg << std::endl << underline(msg) 
                << std::endl << std::endl;
    }
    
    /**
     * print a configuration line
     * @param msg, message to print
     * @param var, option value
     */
    template<class T>
    void configLine(const std::string &msg, T var) const {
        std::cout << msg << "\t" << var << std::endl; 
    }
 
    /**
     * Underline a message
     * @param msg, message to underline
     * @return, a string of '-' of the size of msg 
     */
    std::string underline(const std::string &msg) const {
        return std::string(msg.length(), '-');
    }
    
    Display() = default;
    Display(const Display &other) = delete;
    const Display &operator=(const Display &other) = delete;
    ~Display() {}
};
