#include "RandomGenerator.hh"

RandomGenerator::RandomGenerator() {
    _mt = create();
    _i0_1udis = std::uniform_int_distribution<>(0, 1);
    _d0_1udis = std::uniform_real_distribution<>(0, std::nextafter(1, DBL_MAX));
}

int RandomGenerator::i0_1() {
    return _i0_1udis(_mt);
}

double RandomGenerator::d0_1() {
    return _d0_1udis(_mt);
}

int RandomGenerator::i0_limit(int limit) {
    std::uniform_int_distribution<> udis(0, limit);
    return udis(_mt);
}

double RandomGenerator::d0_limit(double limit) {
    std::uniform_real_distribution<double> udis(0, std::nextafter(limit, DBL_MAX));
    return udis(_mt);
}

std::mt19937 RandomGenerator::create() const {
    std::random_device rd;
    std::mt19937::result_type random_data[std::mt19937::state_size];
    std::generate(std::begin(random_data), std::end(random_data), std::ref(rd));
    std::seed_seq seeds(std::begin(random_data), std::end(random_data)); 
    std::mt19937 mt(seeds);
    return mt;
}