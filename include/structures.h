/*
 * Structures
 */

#ifndef GA_HAMILTONIAN_CYCLE_STRUCTURES_H
#define GA_HAMILTONIAN_CYCLE_STRUCTURES_H

class Graph {
public:
    int size;
    long **matrix;

    Graph(int size, long **matrix);

    void print();
};

class HamiltonianCycle {
public:
    Graph *graph;
    long length;
    int *vertices;

    HamiltonianCycle(Graph *graph, int *vertices);
};

class Generation {
public:
    int size;
    HamiltonianCycle **cycles;

    Generation(int size, HamiltonianCycle **cycles);

    void print();
};

#endif //GA_HAMILTONIAN_CYCLE_STRUCTURES_H
