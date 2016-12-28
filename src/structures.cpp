#include <iostream>
#include "structures.h"

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

HamiltonianCycle::HamiltonianCycle(Graph* graph, int* vertices) {
    this->graph = graph;
    this->vertices = vertices;

    // Weight from the last vertex to the first vertex in the cycle
    this->length = graph->matrix[vertices[0]][vertices[graph->size - 1]];

    for (int i = 0; i < graph->size - 1; i++) {
        this->length += graph->matrix[vertices[i]][vertices[i + 1]];
    }
}

HamiltonianCycle::~HamiltonianCycle() {
    delete this->vertices;
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
