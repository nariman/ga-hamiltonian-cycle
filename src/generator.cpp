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


Graph* generate_random_graph(int size, double max_weight) {
    Graph* graph = new Graph(size);

    uniform_real_distribution<> dist(1, max_weight);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            graph->matrix[i][j] = graph->matrix[j][i] = dist(*get_mersenne_twister());
        }

        graph->matrix[i][i] = 0;
    }

    return graph;
}

Generation* generate_random_generation(Graph* graph) {
    int population_size = graph->population_size();

    Cycle** cycles = new Cycle*[population_size];

    for (int i = 0; i < population_size; i++) {
        int* cycle = new int[graph->size];
        vector<int> vertices;

        for (int j = 0; j < graph->size; vertices.push_back(j++));

        for (int j = graph->size; j --> 0;) {
            uniform_int_distribution<> dist(0, j);
            int v = dist(*get_mersenne_twister());

            cycle[graph->size - j - 1] = vertices[v];
            vertices.erase(vertices.begin() + v);
        }

        cycles[i] = new Cycle(graph, cycle);
    }

    return new Generation(population_size, cycles);
}
