/*
 * Structures
 */

#include <iostream>
#include "structures.h"

using namespace std;

Graph::Graph(int size, long **matrix) :
        size(size),
        matrix(matrix) {}

void Graph::print() {
    cout << "Length: " << this->size << endl;

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            cout << this->matrix[i][j] << " ";
        }

        cout << endl;
    }
}

HamiltonianCycle::HamiltonianCycle(Graph *graph, int *vertices) {
    this->graph = graph;
    this->vertices = vertices;

    this->length = this->graph->matrix[this->vertices[0]][this->vertices[this->graph->size - 1]];

    for (int i = 0; i < this->graph->size - 1; i++) {
        this->length += this->graph->matrix[this->vertices[i]][this->vertices[i + 1]];
    }
}

Generation::Generation(int size, HamiltonianCycle **cycles) :
        size(size),
        cycles(cycles) {}

void Generation::print() {
    for (int i = 0; i < this->size; i++) {
        cout << cycles[i]->length << endl;

        for (int j = 0; j < cycles[i]->graph->size; j++) {
            cout << cycles[i]->vertices[j] << " ";
        }

        cout << endl;
    }
}
