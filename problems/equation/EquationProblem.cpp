#include "EquationProblem.hh"

extern "C" Problem *create() {
    return new EquationProblem();
}

void EquationProblem::print(const Strand &strand) const {
    Type type = DIGIT;
    for (unsigned int i = 0; i < _config.chromosomeSize;) {
        if (type == OPERATOR)
            std::cout << " " << getCharValue(strand, i) << " ";
        else
            std::cout << (int)getters::getValue<int8_t>(strand, i);
        type = type == DIGIT ? OPERATOR : DIGIT; 
    }
    try {
        std::cout << " = " << computeValue(strand) << " && fitness = " << computeFitnessOf(strand) << std::endl;
    } catch (int e) {
        std::cout << " chromosome with a division by 0 " << std::endl;
    } 
}

void EquationProblem::askParameters() {
    std::cout << "Enter a value: " << std::flush;
    std::cin >> _number;
}

double EquationProblem::computeFitnessOf(const Strand &strand) const {
    try {
        return 1.0 / std::abs(_number - computeValue(strand));
    } catch (int e) {
        return 1.0 / (_config.populationSize * _config.simulationNumber); // minimise division by zero 
    }
}

double	EquationProblem::computeValue(const Strand &strand) const
{
    char op;
    bool hasLeft = false;
    Type type = DIGIT;
    double value = 0;
    int16_t v;
    for (unsigned int i = 0; i < _config.chromosomeSize; )
    {
        if (type == OPERATOR)
        {
            op = getCharValue(strand, i);
            hasLeft = true;
        }
        else if (hasLeft == false)
            value = getters::getValue<int8_t>(strand, i);
        else
        {
            v = getters::getValue<int8_t>(strand, i);
            if (op == '+')
                value += v;
            else if (op == '-')
                value -= v;
            else if (op == '*')
                value *= v;
            else if (v == 0)
                throw 0;
            else
                value /= v;
        }
        type = (type == DIGIT) ? OPERATOR : DIGIT;
    }
    return value;
}

const std::map<bool, std::map<bool, char> > toSymb = {
    {true, {
        {true, '+'},
        {false, '-'}
    }},
    {false, {
        {true, '*'},
        {false, '/'}
    }}
};

char EquationProblem::getCharValue(const Strand &strand, unsigned int &off) const 
{
    bool g1 = getters::getValue<bool>(strand, off), 
            g2 = getters::getValue<bool>(strand, off);
    return toSymb.at(g1).at(g2);
}

bool EquationProblem::test(const Strand &strand) const
{
    try {
        return computeValue(strand) == _number;
    } catch (int e) {
        return false;
    }
}