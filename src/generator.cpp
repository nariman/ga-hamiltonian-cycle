/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <ctime> // time
#include <random> // uniform_int_distribution

#include "cycle.h"
#include "generation.h"
#include "graph.h"
#include "twister.h"

using namespace std;


Graph* generate_random_graph(int size, long max_weight) {
    Graph* graph = new Graph(size);

    uniform_int_distribution<> dist(1, max_weight);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            graph->matrix[i][j] = graph->matrix[j][i] = dist(*get_wersenne_twister());
        }

        graph->matrix[i][i] = 0;
    }

    return graph;
}

Generation* generate_random_generation(Graph* graph) {
    int log_size = (int) log((double) graph->size);

    Cycle** cycles = new Cycle*[log_size];

    for (int i = 0; i < log_size; i++) {
        int* cycle = new int[graph->size];
        vector<int> vertices;

        for (int j = 0; j < graph->size; vertices.push_back(j++));

        for (int j = graph->size; j --> 0;) {
            uniform_int_distribution<> dist(0, j);
            int v = dist(*get_wersenne_twister());

            cycle[graph->size - j - 1] = vertices[v];
            vertices.erase(vertices.begin() + v);
        }

        cycles[i] = new Cycle(graph, cycle);
    }

    return new Generation(log_size, cycles);
}
