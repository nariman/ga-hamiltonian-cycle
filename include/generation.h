/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#ifndef GA_HAMILTONIAN_CYCLE_GENERATION_H
#define GA_HAMILTONIAN_CYCLE_GENERATION_H

#include "cycle.h"


class Generation {
private:
    int mutation_probability;
    int mutation_swap_probability;
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

    /**
     * Return the best cycle (crhomosome) in the generation.
     *
     * @return The best cycle
     */
    Cycle* best();

    int get_mutation_probability();

    int get_mutation_swap_probability();

    void set_mutation_probability(int mutation_probability);

    void set_mutation_swap_probability(int mutation_swap_probability);

    /**
     * Print to the standart I/O a human-readable generation
     * representation.
     */
    void repr();
};

#endif //GA_HAMILTONIAN_CYCLE_GENERATION_H
