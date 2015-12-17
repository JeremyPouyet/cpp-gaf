#include "EquationProblem.hh"

extern "C" Problem *create() {
    return new EquationProblem();
}

extern "C" void destroy(Problem *problem) {
    delete problem;
}

EquationProblem::EquationProblem() {
    std::cout << "EquationProblem constructor" << std::endl;
}

void EquationProblem::print() const {
    std::cout << "lib has been loaded" << std::endl;
}

EquationProblem::~EquationProblem() {
    std::cout << "EquationProblem destructor" << std::endl;
}

