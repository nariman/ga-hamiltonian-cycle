/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#ifndef GA_HAMILTONIAN_CYCLE_GA_H
#define GA_HAMILTONIAN_CYCLE_GA_H

#include "cycle.h"
#include "generation.h"


/**
 * Select a cycle from given generation by tournament strategy.
 *
 * @param generation Generation, where to search a cycle
 *
 * @return Selected cycle
 */
Cycle* tournament(Generation* generation);

/**
 * Process a new generation from the given by genetic algorithm.
 *
 * @param generation Previous generation
 *
 * @return A new generation
 */
Generation* process(Generation* generation);

/**
 * Crossover the two cycles (chromosomes).
 *
 * @param first  First cycle
 * @param second Second cycle
 *
 * @return Crossovered cycle
 */
Cycle* crossover(Cycle* first, Cycle* second);

/**
 * Crossover the two cycles by the "split one" strategy.
 *
 * @param first  First cycle
 * @param second Second cycle
 *
 * @return Crossovered cycle
 */
Cycle* crossover_split_one(Cycle* first, Cycle* second);

#endif //GA_HAMILTONIAN_CYCLE_GA_H
