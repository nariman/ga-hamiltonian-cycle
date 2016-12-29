/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#ifndef GA_HAMILTONIAN_CYCLE_GA_H
#define GA_HAMILTONIAN_CYCLE_GA_H

#include "cycle.h"
#include "generation.h"

Cycle* tournament(Generation* generation);

Generation* process(Generation* generation);

Cycle* crossover(Cycle* first, Cycle* second);

Cycle* crossover_split_one(Cycle* first, Cycle* second);

#endif //GA_HAMILTONIAN_CYCLE_GA_H
