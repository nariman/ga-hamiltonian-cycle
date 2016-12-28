/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <iostream> // cin, cout

#include "graph.h"

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

void Graph::repr() {
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
