#include "Simulation.hh"

int main(int ac, char **av) {
    Simulation simulation;
    int ret = simulation.initialise(ac, av);
    if (ret != 1)
        return ret;
    simulation.run();
    return 0;
}
