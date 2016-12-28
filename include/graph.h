/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#ifndef GA_HAMILTONIAN_CYCLE_GRAPH_H
#define GA_HAMILTONIAN_CYCLE_GRAPH_H


class Graph {
public:
    int size;
    long** matrix;

    /**
     * Create a new graph with provided size and set a default 
     * connectivity matrix with zero values.
     *
     * @param size Size of the graph (nubmer of vertices)
     */
    Graph(int size);

    /**
     * Create a new graph with provided size and connectivity matrix.
     *
     * @param size   Size of the graph (nubmer of vertices)
     * @param matrix Connectivity matrix 
     */
    Graph(int size, long** matrix);

    /**
     * Delete a graph and free memory, allocated to the matrix
     */
    ~Graph();

    /**
     * Print to the standart I/O a human-readable graph representation.
     */
    void repr();
};

#endif //GA_HAMILTONIAN_CYCLE_GRAPH_H
