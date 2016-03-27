#pragma once

#include <random>
#include <cfloat>
#include <algorithm>

class RandomGenerator {
public:
    
    static RandomGenerator &getInstance() {
        static RandomGenerator randomGenerator;
        return randomGenerator;
    }
    
    /**
     * randomly get 0 or 1
     * @return 0 or 1
     */
    int     i0_1();
    
    /**
     * randomly get a double between [0;1]
     * @return a random double between [0;1]
     */
    double  d0_1();
    
    /**
     * randomly get an integer between [0;limit]
     * @param limit, maximum possible integer
     * @return a random integer between [0;limit]
     */
    int     i0_limit(int limit);
    
    /**
     * randomly get a double between [0;limit]
     * @param limit, maximum possible value
     * @return a random double between [0;limit]
     */
    double  d0_limit(double limit);
    
    
private:
    /**
     * Create and seed the RNG
     * @return 
     */
    std::mt19937 create() const;
    
    // random seeder
    std::mt19937 _mt;
    // random integer between 0 an 1
    std::uniform_int_distribution<> _i0_1udis;
    // random double between 0 and 1
    std::uniform_real_distribution<double> _d0_1udis;
    
    RandomGenerator();
    RandomGenerator(const RandomGenerator &other) = delete;
    const RandomGenerator &operator=(const RandomGenerator &other) = delete;
    ~RandomGenerator() {}
};
