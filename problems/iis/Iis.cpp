#include "Iis.hh"

extern "C" Problem *create() {
    return new Iis();
}

void Iis::print(const Strand &strand) const {
    unsigned int i = 0;
    std::cout << std::setprecision(16) << getters::getValue<dataType>(strand, i) << " ";
    std::cout << std::setprecision(16) << getters::getValue<dataType>(strand, i) << " ";
    std::cout << std::setprecision(16) << getters::getValue<dataType>(strand, i) << " ";
    std::cout << std::setprecision(16) << getters::getValue<dataType>(strand, i) << " ";
    std::cout << std::setprecision(16) << getters::getValue<dataType>(strand, i) << " ";
    std::cout << std::setprecision(16) << getters::getValue<dataType>(strand, i) << " ";
    std::cout << "fitness: " << computeFitnessOf(strand) << std::endl;
}

bool Iis::loadData() {
    std::ifstream file("./problems/iis/datfile.dat");
    if (file.is_open() == false)
        return false;
    double x, y;
    while (file >> x >> y) {
        _values.push_back({
            x, y, std::pow(x, 2), std::pow(x, 3), std::pow(x, 4), std::pow(x, 5)
        });
    }
    std::cout << _values.size() << " values loaded" << std::endl;
    file.close();
    return true;
}

double Iis::computeFitnessOf(const Strand &strand) const {
    double y, fitness = 0, distance;
    std::vector<dataType> coefs = getCoefs(strand);
    for (const std::vector<double> &value : _values) {
        y = computeValue(coefs, value);
        distance = value[1] - y;
        fitness += distance < 0 ? -distance : distance;
    }
    return fitness == 0 ? 0 : 1.0 / fitness;
}

bool Iis::test(const Strand &strand) const {
    std::vector<dataType> coefs = getCoefs(strand);
    for (const std::vector<double> &value : _values)
        if (computeValue(coefs, value) != value[1])
            return false;
    return true;
}

void Iis::giveBestSolution(const Strand &strand) const {
    std::vector<dataType> coefs = getCoefs(strand);
    std::ofstream file("results.dat", std::ofstream::trunc | std::ofstream::out);
    for (const std::vector<double> &value : _values)
        file << value[0] << "\t" << computeValue(coefs, value) << std::endl;
    file.close();
}

double Iis::computeValue(const std::vector<dataType> &coefs, const std::vector<double> &value) const {
    return  coefs[0]            + coefs[1] * value[0] +
            coefs[2] * value[2] + coefs[3] * value[3] +
            coefs[4] * value[4] + coefs[5] * value[5]; 
}

std::vector<dataType> Iis::getCoefs(const Strand &strand) const {
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