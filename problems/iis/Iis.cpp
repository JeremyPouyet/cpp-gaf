#include "Iis.hh"

extern "C" Problem *create() {
    return new Iis();
}

extern "C" void destroy(Problem *problem) {
    delete problem;
}

void Iis::print(const std::string &strand) const {
    for (unsigned int i = 0; i < _config.chromosomeSize;)
      std::cout << std::setprecision(8) << getters::getValue<dataType>(strand, i) << " ";
    std::cout << "fitness: " << computeFitnessOf(strand) << std::endl;
}

bool Iis::loadData() {
    std::ifstream file("./problems/iis/datfile.dat");
    double a, b;
    while (file >> a >> b)
        _values.push_back(std::make_pair(a, b));
    std::cout << _values.size() << " values loaded" << std::endl;
    file.close();
    return true;
}

double Iis::computeFitnessOf(const std::string &strand) const {
    double y, fitness = 0;
    std::vector<dataType> coefs = getCoefs(strand);
    for (unsigned int i = 0; i < _values.size(); i++) {
        y = computeValue(coefs, _values[i].first);
        fitness += std::abs(_values[i].second - y);
    }
    return fitness;
}

bool Iis::test(const std::string &strand) const {
    double y;
    std::vector<dataType> coefs = getCoefs(strand);
    for (auto q : _values) {
        y = computeValue(coefs, q.first);
        if (y != q.second)
            return false;
    }
    return true;
}

void Iis::giveBestSolution(const std::string &strand) const {
    std::vector<dataType> coefs = getCoefs(strand);
    std::ofstream file("results.dat", std::ofstream::trunc | std::ofstream::out);
    double y;
    for (auto q : _values) {
        y = computeValue(coefs, q.first);
        file << q.first << "\t" << std::setprecision(12) << y << std::endl;
    }
    file.close();
}

double Iis::computeValue(const std::vector<dataType> &coefs, double x) const {
    return coefs[0] + 
            coefs[1] * x +
            coefs[2] * std::pow(x, 2) +
            coefs[3] * std::pow(x, 3) +
            coefs[4] * std::pow(x, 4) +
            coefs[5] * std::pow(x, 5);
}

std::vector<dataType> Iis::getCoefs(const std::string &strand) const {
    unsigned int i = 0;
    return {
        getters::getValue<dataType>(strand, i),
        getters::getValue<dataType>(strand, i),
        getters::getValue<dataType>(strand, i),
        getters::getValue<dataType>(strand, i),
        getters::getValue<dataType>(strand, i),
        getters::getValue<dataType>(strand, i)
    };
}