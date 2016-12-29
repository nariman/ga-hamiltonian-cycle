/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <fstream> // ifstream

#include "graph.h"

using namespace std;


ifstream in("tests/matrix.txt");

Graph* read_graph() {
    int size;
    in >> size;

    Graph* graph = new Graph(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            in >> graph->matrix[i][j];
        }
    }

    return graph;
}
