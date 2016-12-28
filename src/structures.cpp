#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#include "structures.h"

#define MUTATION_PROBABILITY 15

using namespace std;


Graph::Graph(int size) {
    this->size = size;
    this->matrix = new long*[size];

    for (int i = 0; i < size; this->matrix[i++] = new long[size]);
}

Graph::Graph(int size, long** matrix) :
        size(size),
        matrix(matrix) {}

Graph::~Graph() {
    for (int i = 0; i < size; delete this->matrix[i++]);
    delete this->matrix;
}

void Graph::print() {
    cout << "<Graph" << " ";
    cout << "size=" << this->size << " ";
    cout << "matrix=" << "(" << endl;

    for (int i = 0; i < this->size; i++) {
        cout << "  " << "(";

        for (int j = 0; j < this->size; j++) {
            cout << (j == 0 ? "" : ", ") << this->matrix[i][j];
        }

        cout << ")," << endl;
    }

    cout << ")>";
}

HamiltonianCycle::HamiltonianCycle(Graph* graph) {
    this->graph = graph;
    this->vertices = new int[graph->size];
    this->length = 0;
}

HamiltonianCycle::HamiltonianCycle(Graph* graph, int* vertices) {
    this->graph = graph;
    this->vertices = vertices;
    this->length = 0;

    recalc();
}

HamiltonianCycle::~HamiltonianCycle() {
    delete this->vertices;
}

void HamiltonianCycle::recalc() {
    // Weight from the last vertex to the first vertex in the cycle
    this->length = this->graph->matrix[this->vertices[0]][this->vertices[this->graph->size - 1]];

    for (int i = 0; i < this->graph->size - 1; i++) {
        this->length += this->graph->matrix[this->vertices[i]][this->vertices[i + 1]];
    }

    cout << this->length << endl;
}

void HamiltonianCycle::mutate() {
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

void HamiltonianCycle::print() {
    cout << "<HamiltonianCycle" << " ";
    cout << "length=" << this->length << " ";
    cout << "vertices=(";

    for (int i = 0; i < this->graph->size; i++) {
        cout << (i == 0 ? "" : ", ") << this->vertices[i];
    }

    cout << ")>";
}

Generation::Generation(int size, HamiltonianCycle** cycles) :
        size(size),
        cycles(cycles) {}

Generation::~Generation() {
    delete this->cycles;
}

void Generation::print() {
    cout << "<HamiltonianCycle" << " ";
    cout << "size=" << this->size << " ";
    cout << "cycles=" << "(" << endl;

    for (int i = 0; i < this->size; i++) {
        cout << "  ";
        cycles[i]->print();
        cout << "," << endl;
    }

    cout << ")>";
}
