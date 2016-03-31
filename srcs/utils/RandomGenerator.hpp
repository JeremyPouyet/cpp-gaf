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
     * Randomly generates a T between [min; max]
     * using the random generator U
     * @param min, minimum possible T
     * @param max, maximum possible T
     * @return a random T between [min; max]
     */
    template <class T, template<typename P> class U>
    T min_max(T min, T max) {
        U<T> udis(min, max);
        return udis(_mt);
    }

    /**
     * randomly get an integer between [min ; max]
     * @param min, minimum possible integer
     * @param max, maximum possible integer
     * @return a random integer between [min ; max]
     */
    int i_between(int min, int max) {
        return min_max<int, std::uniform_int_distribution>(min, max);
    }
    
    /**
     * randomly get a double between [min ; max]
     * @param min, minimum possible double
     * @param max, maximum possible double
     * @return a random double between [min ; max]
     */
    double d_between(double min, double max) {
        return min_max<double, std::uniform_real_distribution>(min, std::nextafter(max, DBL_MAX));
    }

private:
    
    // random seeder
    std::mt19937 _mt;

    /**
     * Create and seed the RNG
     */
    RandomGenerator() {
        std::random_device rd;
        std::mt19937::result_type random_data[std::mt19937::state_size];
        std::generate(std::begin(random_data), std::end(random_data), std::ref(rd));
        std::seed_seq seeds(std::begin(random_data), std::end(random_data));
        _mt.seed(seeds);
    }
    
    RandomGenerator(const RandomGenerator &other) = delete;
    const RandomGenerator &operator=(const RandomGenerator &other) = delete;
    ~RandomGenerator() {}
};
