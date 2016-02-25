#ifndef IIG_HH
#define	IIG_HH

#include <cstdint>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>

#include "AProblem.hh"
#include "Getters.hpp"

typedef int16_t dataType;

class Iis : public AProblem
{
    public:

        void print(const std::string &strand) const;
        bool loadData();
        double computeFitnessOf(const std::string &strand) const;
        bool test(const std::string &strand) const;
        void giveBestSolution(const std::string &strand) const;

        virtual ~Iis() {}

        private:
            inline double computeValue(const std::vector<dataType> &coefs, double x) const;
            inline std::vector<dataType> getCoefs(const std::string &strand) const;
            
            std::vector<std::pair<double, double> > _values;
};
#endif	/* IIG_HH */
