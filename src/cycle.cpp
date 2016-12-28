/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <algorithm> // sort
#include <cmath> // log
#include <ctime> // time
#include <iostream> // cin, cout
#include <random> // random_device, mt19937, uniform_int_distribution
#include <vector> // vector

#include "cycle.h"
#include "graph.h"

#define MUTATION_PROBABILITY 15 // %

using namespace std;


Cycle::Cycle(Graph* graph) {
    this->graph = graph;
    this->vertices = new int[graph->size];
    this->length = 0;
}

Cycle::Cycle(Graph* graph, int* vertices) {
    this->graph = graph;
    this->vertices = vertices;
    this->length = 0;

    recalc();
}

Cycle::~Cycle() {
    delete this->vertices;
}

void Cycle::recalc() {
    // Weight from the last vertex to the first vertex in the cycle
    this->length = this->graph->matrix[this->vertices[0]][this->vertices[this->graph->size - 1]];

    for (int i = 0; i < this->graph->size - 1; i++) {
        this->length += this->graph->matrix[this->vertices[i]][this->vertices[i + 1]];
    }

    cout << this->length << endl;
}

void Cycle::mutate() {
    random_device random;
    mt19937 gen(random());

    gen.seed(time(0));

    uniform_int_distribution<> dist(0, 100);

    if (dist(gen) > MUTATION_PROBABILITY) {
        return;
    }

    // We choose log(this->graph->size) vertices from the cycle
    int log_size = (int) log((double) this->graph->size);

    int selected_gens[log_size];
    vector<int> vertices;

    for (int i = 0; i < this->graph->size; vertices.push_back(i++));

    for (int i = log_size; i --> 0;) {
        uniform_int_distribution<> dist(0, vertices.size() - 1);
        int v = dist(gen); 

        selected_gens[log_size - i - 1] = vertices[v];
        vertices.erase(vertices.begin() + v);
    }

    sort(selected_gens, selected_gens + log_size);

    int v = this->vertices[selected_gens[0]];

    for (int i = 1; i < log_size; i++) {
        int t = this->vertices[selected_gens[i]];
        this->vertices[selected_gens[i]] = v;
        v = t;
    }

    this->vertices[selected_gens[0]] = v;
    this->recalc();
}

void Cycle::repr() {
    cout << "<Cycle" << " ";
    cout << "length=" << this->length << " ";
    cout << "vertices=(";

    for (int i = 0; i < this->graph->size; i++) {
        cout << (i == 0 ? "" : ", ") << this->vertices[i];
    }

    cout << ")>";
}
