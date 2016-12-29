/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#ifndef GA_HAMILTONIAN_CYCLE_TWISTER_H
#define GA_HAMILTONIAN_CYCLE_TWISTER_H

#include <random> // mt19937

using namespace std;


/**
 * Return a Mersenne Twister number generator.
 *
 * @return Mersenne Twister number generator
 */
mt19937* get_mersenne_twister();

#endif //GA_HAMILTONIAN_CYCLE_TWISTER_H
