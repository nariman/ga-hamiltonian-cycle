/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <ctime>
#include <random>

#include "twister.h"

using namespace std;


random_device randdev;
mt19937 wersenne_twister(randdev());
bool initialized;

mt19937* get_wersenne_twister() {
    if (!initialized) {
        initialized = true;
        wersenne_twister.seed(time(0));
    }

    return &wersenne_twister;
}
