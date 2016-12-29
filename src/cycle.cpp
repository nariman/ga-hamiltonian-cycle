/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <iostream> // cout
#include <random> // uniform_int_distribution

#include "cycle.h"
#include "graph.h"
#include "twister.h"

#define MUTATION_PROBABILITY 25 // %
#define MUTATION_SWAP_PROBABILITY 25 // %

using namespace std;


Cycle::Cycle(Graph* graph) {
    this->graph = graph;
    this->vertices = new int[graph->size];
    this->length = 0;
    this->mutations = 0;
}

Cycle::Cycle(Graph* graph, int* vertices) {
    this->graph = graph;
    this->vertices = vertices;
    this->length = 0;
    this->mutations = 0;

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
}

void Cycle::mutate() {
    uniform_int_distribution<> chance(0, 100);

    if (chance(*get_mersenne_twister()) > MUTATION_PROBABILITY) {
        return;
    }

    for (int i = 0; i < this->graph->size; i++) {
        if (chance(*get_mersenne_twister()) > MUTATION_SWAP_PROBABILITY) {
            continue;
        }

        uniform_int_distribution<> dist(0, this->graph->size - 1);
        int u = dist(*get_mersenne_twister());
        int v = dist(*get_mersenne_twister());

        int s = this->vertices[u];
        this->vertices[u] = this->vertices[v];
        this->vertices[v] = s;
    }

    this->mutations++;
    this->recalc();
}

void Cycle::repr() {
    cout << "<Cycle" << " ";
    cout << "length=" << this->length << " ";
    cout << "mutations=" << this->mutations << " ";
    cout << "vertices=(";

    for (int i = 0; i < this->graph->size; i++) {
        cout << (i == 0 ? "" : ", ") << this->vertices[i];
    }

    cout << ")>";
}
