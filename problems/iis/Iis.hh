#pragma once

#include <cstdint>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>

#include "AProblem.hh"
#include "Getters.hpp"

typedef float dataType;

class Iis : public AProblem {
public:

    void print(const Strand &strand) const;
    bool loadData();
    double computeFitnessOf(const Strand &strand) const;
    bool test(const Strand &strand) const;
    void giveBestSolution(const Strand &strand) const;

    virtual ~Iis() {}

private:
    inline double computeValue(const std::vector<dataType> &coefs, const std::vector<double> &value) const;
    inline std::vector<dataType> getCoefs(const Strand &strand) const;

    std::vector<std::vector<double> > _values;
};
