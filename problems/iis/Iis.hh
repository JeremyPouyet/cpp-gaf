#ifndef IIG_HH
#define	IIG_HH

#include <cstdint>
#include <climits>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>
#include "AProblem.hh"

typedef float dataType;

union u_t {
    float f;
    uint32_t i;
};

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
            double computeValue(const std::vector<dataType> &coefs, double x) const;
            std::vector<dataType> getCoefs(const std::string &strand) const;
            dataType getIntValue(const std::string &strand, int &p) const;
            
            std::vector<std::pair<double, double> > _values;
};
#endif	/* IIG_HH */
