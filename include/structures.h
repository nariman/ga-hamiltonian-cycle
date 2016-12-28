#ifndef GA_HAMILTONIAN_CYCLE_STRUCTURES_H
#define GA_HAMILTONIAN_CYCLE_STRUCTURES_H

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
    void print();
};

class HamiltonianCycle {
public:
    Graph* graph;
    long length;
    int* vertices; // In this list, the last repeated vertex is not 
                   // neccessary.

/**
     * Create a new hamiltonian cycle with provided graph object.
     *
     * @param graph Graph, on which was built the cycle
     */

    HamiltonianCycle(Graph* graph);
    /**
     * Create a new hamiltonian cycle with provided graph object and
     * list of vertices in the cycle.
     *
     * @param graph    Graph, on which was built the cycle
     * @param vertices List of vertices in the cycle
     */
    HamiltonianCycle(Graph* graph, int* vertices);

    /**
     * Delete a hamiltonian cycle and free memory, allocated to the list
     * of vertices.
     */
     ~HamiltonianCycle();

    // TODO:
    void recalc();
 
    // TODO: 
    void mutate();

    /**
     * Print to the standart I/O a human-readable hamiltonian cycle
     * representation.
     */
    void print();
};

class Generation {
public:
    int size;
    HamiltonianCycle** cycles;

    /**
     * Create a new generation of cycles with provided size and list of
     * cycles.
     *
     * @param size     Size of the generation (number of cycles)
     * @param cycles   List of cycles
     */
    Generation(int size, HamiltonianCycle** cycles);

    /**
     * Delete a generation and free memory, allocated to the list
     * of cycles (but not the each hamiltonian cycle!).
     */
     ~Generation();

    /**
     * Print to the standart I/O a human-readable generation
     * representation.
     */
    void print();
};

#endif //GA_HAMILTONIAN_CYCLE_STRUCTURES_H
