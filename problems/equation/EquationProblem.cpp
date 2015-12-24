#include "EquationProblem.hh"

extern "C" Problem *create() {
    return new EquationProblem();
}

extern "C" void destroy(Problem *problem) {
    delete problem;
}

void EquationProblem::print(const Chromosome *chromosome) const {
    Chromosome::Strand strand = chromosome->getStrand();
    Type type = DIGIT;
    int p = 0;
    for (int i = 0; i < 13; i++)
    {
        if (type == OPERATOR)
            std::cout << " " << getCharValue(strand, p) << " ";
        else
            std::cout << (int)getIntValue(strand, p);
        type = type == DIGIT ? OPERATOR : DIGIT; 
    }
    try {
        std::cout << " = " << computeValue(chromosome) << " && fitness = " << chromosome->getFitness() << std::endl;
    } catch (int e) {
        std::cout << " chromosome with a division by 0 " << std::endl;
    } 
}

void EquationProblem::askParameters() {
    std::cout << "Enter a value: " << std::flush;
    std::cin >> _number;
}

double EquationProblem::computeFitnessOf(const Chromosome *chromosome) const {
    try  {
        return 1 / std::abs(_number - computeValue(chromosome));
    } catch (int e) {
        return 0.001; // minimise division by zero  
    }
}

double	EquationProblem::computeValue(const Chromosome *chromosome) const
{
    Chromosome::Strand strand = chromosome->getStrand();
    std::string op;
    bool hasLeft = false;
    Type type = DIGIT;
    double value = 0;
    int p = 0, v;
    for (int i = 0; i < 13; i++)
    {
        if (type == OPERATOR)
        {
            op = getCharValue(strand, p);
            hasLeft = true;
        }
        else if (hasLeft == false)
            value = getIntValue(strand, p);
        else
        {
            v = getIntValue(strand, p);
            if (op == "+")
                value += v;
            else if (op == "-")
                value -= v;
            else if (op == "*")
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

std::string EquationProblem::getCharValue(Chromosome::Strand strand, int &p) const 
{
    char g1 = strand[p], g2 = strand[p + 1];
    p += 2;
    if (g1 == '1' && g2 == '1')
        return "+";
    if (g1 == '1' && g2 == '0')
        return "-";
    if (g1 == '0' && g2 == '1')
        return "*";
    return "/";
}

int8_t EquationProblem::getIntValue(Chromosome::Strand strand, int &p) const
{
    int8_t a = 0;
    for (int j = 0; j < 8; j++)
        if (strand[p + j] == '1')
            a |= 1 << j;   
    p += 8;
    return a;
}

bool EquationProblem::test(Chromosome *chromosome) const
{
    try {
        return computeValue(chromosome) == _number;
    } catch (int e) {
        return false;
    }
}