/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#ifndef GA_HAMILTONIAN_CYCLE_CYCLE_H
#define GA_HAMILTONIAN_CYCLE_CYCLE_H

#include "graph.h"


class Cycle {
private:
    int mutations;
public:
    Graph* graph;
    double length;
    int* vertices; // In this list, the last repeated vertex is not 
                   // neccessary.

    /**
     * Create a new hamiltonian cycle with provided graph object.
     *
     * @param graph Graph, on which was built the cycle
     */

    Cycle(Graph* graph);
    /**
     * Create a new hamiltonian cycle with provided graph object and
     * list of vertices in the cycle.
     *
     * @param graph    Graph, on which was built the cycle
     * @param vertices List of vertices in the cycle
     */
    Cycle(Graph* graph, int* vertices);

    /**
     * Delete a hamiltonian cycle and free memory, allocated to the list
     * of vertices.
     */
     ~Cycle();

    /**
     * Recalculate the length of the path.
     */
    void recalc();
 
    /**
     * Mutate the cycle (chromosome) with some probability.
     */
    void mutate(int mutation_probability, int mutation_swap_probability);

    /**
     * Print to the standart I/O a human-readable hamiltonian cycle
     * representation.
     */
    void repr();
};

#endif //GA_HAMILTONIAN_CYCLE_CYCLE_H
