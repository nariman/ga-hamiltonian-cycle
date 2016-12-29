/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <iostream> // cin, cout

#include "generation.h"
#include "cycle.h"

using namespace std;


Generation::Generation(int size, Cycle** cycles) :
        size(size),
        cycles(cycles) {}

Generation::~Generation() {
    delete this->cycles;
}

Cycle* Generation::best() {
    Cycle* best = cycles[0];

    for (int i = 0; i < this->size; i++) {
        if (best->length > this->cycles[i]->length) {
            best = cycles[i];
        }
    }

    return best;
}

void Generation::repr() {
    cout << "<Generation" << " ";
    cout << "size=" << this->size << " ";
    cout << "cycles=" << "(" << endl;

    for (int i = 0; i < this->size; i++) {
        cout << "  ";
        cycles[i]->repr();
        cout << "," << endl;
    }

    cout << ")>";
}
