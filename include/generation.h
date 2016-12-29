/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#ifndef GA_HAMILTONIAN_CYCLE_GENERATION_H
#define GA_HAMILTONIAN_CYCLE_GENERATION_H

#include "cycle.h"


class Generation {
public:
    int size;
    Cycle** cycles;

    /**
     * Create a new generation of cycles with provided size and list of
     * cycles.
     *
     * @param size     Size of the generation (number of cycles)
     * @param cycles   List of cycles
     */
    Generation(int size, Cycle** cycles);

    /**
     * Delete a generation and free memory, allocated to the list
     * of cycles (but not the each hamiltonian cycle!).
     */
     ~Generation();

    // TODO:
    Cycle* best();

    /**
     * Print to the standart I/O a human-readable generation
     * representation.
     */
    void repr();
};

#endif //GA_HAMILTONIAN_CYCLE_GENERATION_H
