/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#ifndef GA_HAMILTONIAN_CYCLE_GENERATOR_H
#define GA_HAMILTONIAN_CYCLE_GENERATOR_H

#include "generation.h"
#include "graph.h"


/**
 * Generates a new graph with random weights.
 * 
 * @param size       Size of the graph
 * @param max_weight Max weight of the edge in the graph
 *
 * @return Generated graph
 */
Graph* generate_random_graph(int size, long max_weight);

/**
 * Generates a new generation by the random strategy.
 * 
 * @param graph Graph, on which generation will be generated
 *
 * @return Generated generation
 */
Generation* generate_random_generation(Graph* graph);

#endif //GA_HAMILTONIAN_CYCLE_GENERATOR_H
