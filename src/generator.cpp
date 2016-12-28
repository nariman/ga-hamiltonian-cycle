#include <ctime>
#include <random>
#include "structures.h"

using namespace std;


Graph* generate_random_graph(int size, long max_weight) {
    Graph* graph = new Graph(size);

    random_device random;
    mt19937 gen(random());
    uniform_int_distribution<> dist(1, max_weight);

    gen.seed(time(0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            graph->matrix[i][j] = graph->matrix[j][i] = dist(gen);
        }

        graph->matrix[i][i] = 0;
    }

    return graph;
}

Generation* generate_random_generation_by_greedy_strategy(Graph* graph) {
    int log_size = (int) log((double) graph->size);

    random_device random;
    mt19937 gen(random());

    gen.seed(time(0));

    HamiltonianCycle** cycles = new HamiltonianCycle*[log_size];

    for (int i = 0; i < log_size; i++) {
        int* cycle = new int[graph->size];
        vector<int> vertices;

        for (int j = 0; j < graph->size; vertices.push_back(j++));

        for (int j = graph->size; j --> 0;) {
            uniform_int_distribution<> dist(0, j);
            int v = dist(gen);

            cycle[graph->size - j - 1] = vertices[v];
            vertices.erase(vertices.begin() + v);
        }

        cycles[i] = new HamiltonianCycle(graph, cycle);
    }

    return new Generation(log_size, cycles);
}
