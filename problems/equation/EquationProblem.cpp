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
    for (auto gene: strand)
    {
        if (type == OPERATOR)
            std::cout << " " << getCharValue(gene) << " ";
        else
            std::cout << std::to_string(gene);
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
    for (auto gene: strand)
    {
        if (type == OPERATOR)
        {
            op = getCharValue(gene);
            hasLeft = true;
        }
        else if (hasLeft == false)
            value = gene;
        else
        {
            if (op == "+")
                value += gene;
            else if (op == "-")
                value -= gene;
            else if (op == "*")
                value *= gene;
            else if (gene == 0)
                throw 0;
            else
                value /= gene;
        }
        type = (type == DIGIT) ? OPERATOR : DIGIT;
    }
    return value;
}

std::string EquationProblem::getCharValue(int n) const 
{
    int b1 = (n >> 0) & 1, b2 = (n >> 1) & 1;
    if (b1 && b2)
        return "+";
    if (b1 && !b2)
        return "-";
    if (!b1 && !b2)
        return "*";
    return "/";
}

bool EquationProblem::test(Chromosome *chromosome) const
{
    double value;
    try {
        value = computeValue(chromosome);
    } catch (int e) {
        return false;
    }
    return value == _number;
}