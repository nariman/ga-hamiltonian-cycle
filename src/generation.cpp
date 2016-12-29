/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <iostream> // cout

#include "generation.h"
#include "cycle.h"

#define MUTATION_PROBABILITY 25 // %
#define MUTATION_SWAP_PROBABILITY 25 // %

using namespace std;


Generation::Generation(int size, Cycle** cycles) :
        size(size),
        cycles(cycles),
        mutation_probability(MUTATION_PROBABILITY),
        mutation_swap_probability(MUTATION_SWAP_PROBABILITY) {}

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


int Generation::get_mutation_probability() {
    return this->mutation_probability;
}

int Generation::get_mutation_swap_probability() {
    return this->mutation_swap_probability;
}

void Generation::set_mutation_probability(int mutation_probability) {
    if (mutation_probability > 100) {
        mutation_probability = 100;
    }

    if (mutation_probability < MUTATION_PROBABILITY) {
        mutation_probability = MUTATION_PROBABILITY;
    }

    this->mutation_probability = mutation_probability;
}

void Generation::set_mutation_swap_probability(int mutation_swap_probability) {
    if (mutation_swap_probability > 100) {
        mutation_swap_probability = 100;
    }

    if (mutation_swap_probability < MUTATION_SWAP_PROBABILITY) {
        mutation_swap_probability = MUTATION_SWAP_PROBABILITY;
    }

    this->mutation_swap_probability = mutation_swap_probability;
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
