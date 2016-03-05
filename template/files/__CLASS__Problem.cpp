#include "__CLASS__Problem.hh"

extern "C" Problem *create() {
    return new __CLASS__Problem();
}

__CLASS__Problem::__CLASS__Problem() {
    
}

void __CLASS__Problem::print(const Strand &strand) const {

}

void __CLASS__Problem::askParameters() {

}

bool __CLASS__Problem::loadData() {

}

double __CLASS__Problem::computeFitnessOf(const Strand &strand) const {
    double fitness;
    
    return fitness;
}

bool __CLASS__Problem::test(const Strand &strand) const {

}

void __CLASS__Problem::giveBestSolution(const Strand &strand) const {

}

__CLASS__Problem::~__CLASS__Problem() {
    
}
