/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <algorithm> // sort
#include <cmath> // log
#include <ctime> // time
#include <iostream> // cin, cout
#include <random> // uniform_int_distribution
#include <vector> // vector

#include "cycle.h"
#include "graph.h"
#include "twister.h"

#define MUTATION_PROBABILITY 65 // %

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
    uniform_int_distribution<> dist(0, 100);

    if (dist(*get_wersenne_twister()) > MUTATION_PROBABILITY) {
        return;
    }

    // We choose log(this->graph->size) vertices from the cycle
    int log_size = (int) log((double) this->graph->size);

    int selected_gens[log_size];
    vector<int> vertices;

    for (int i = 0; i < this->graph->size; vertices.push_back(i++));

    for (int i = log_size; i --> 0;) {
        uniform_int_distribution<> dist(0, vertices.size() - 1);
        int v = dist(*get_wersenne_twister()); 

        selected_gens[log_size - i - 1] = vertices[v];
        vertices.erase(vertices.begin() + v);
    }

    sort(selected_gens, selected_gens + log_size);

    for (int i = 0; i < log_size; i++) {
        cout << selected_gens[i] << " ";
    }

    cout << endl;

    for (int i = 0; i < this->graph->size; i++) {
        cout << this->vertices[i] << " ";
    }

    cout << endl;

    int v = this->vertices[selected_gens[0]];

    for (int i = 1; i < log_size; i++) {
        int t = this->vertices[selected_gens[i]];
        this->vertices[selected_gens[i]] = v;
        v = t;
    }

    this->vertices[selected_gens[0]] = v;

    for (int i = 0; i < this->graph->size; i++) {
        cout << this->vertices[i] << " ";
    }

    cout << endl;

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