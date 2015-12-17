#include "EquationProblem.hh"

extern "C" Problem *create() {
    return new EquationProblem();
}

extern "C" void destroy(Problem *problem) {
    delete problem;
}

EquationProblem::EquationProblem() 
{ }

void EquationProblem::print(const Chromosome *chromosome) const {
    Chromosome::Strand strand = chromosome->getStrand();
    Type type = DIGIT;
    for (auto gene: strand)
    {
        if (type == OPERATOR)
            std::cout << " " << chromosome->getCharValue(gene) << " ";
        else
            std::cout << std::to_string(gene);
        type = type == DIGIT ? OPERATOR : DIGIT; 
    }
    std::cout << " = " << chromosome->getValue() << " && fitness = " << chromosome->getFitness() << std::endl;
}

void EquationProblem::askParameters() {
    std::cout << "Enter a value: " << std::flush;
    std::cin >> _number;
}

double EquationProblem::computeFitnessOf(const Chromosome *chromosome) const {
    return 1 / std::abs(_number - chromosome->getValue());
}

EquationProblem::~EquationProblem() 
{ }

double EquationProblem::getSolution() const {
    return _number;
}

