/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <ctime> // time
#include <random> // random_device, mt19937

#include "twister.h"

using namespace std;


random_device randdev;
mt19937 mersenne_twister(randdev());
bool initialized;

mt19937* get_mersenne_twister() {
    if (!initialized) {
        initialized = true;
        mersenne_twister.seed(time(0));
    }

    return &mersenne_twister;
}
