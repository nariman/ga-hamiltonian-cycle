/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <algorithm> // sort
#include <random> // uniform_int_distribution

#include "ga.h"
#include "cycle.h"
#include "generation.h"
#include "twister.h"

#define TOURNAMENT_PROBABILITY 0 // %

using namespace std;


Cycle* tournament(Generation* generation) {
    uniform_int_distribution<> dist(0, generation->size - 1);

    Cycle* first = generation->cycles[dist(*get_mersenne_twister())];
    Cycle* second = generation->cycles[dist(*get_mersenne_twister())];

    uniform_int_distribution<> chance(0, 100);

    if (chance(*get_mersenne_twister()) > TOURNAMENT_PROBABILITY) {
        return first->length < second->length ? first : second;  
    } else {
        return first->length < second->length ? second : first;  
    }
}

Generation* process(Generation* generation) {
    int generation_size = generation->size;
    Cycle* best = generation->best();
    Cycle** new_cycles = new Cycle*[generation_size];

    new_cycles[0] = best;
    
    // generate a new generation (N)
    for (int i = 1; i < generation_size; i++) {
        Cycle* first = tournament(generation);
        Cycle* second = tournament(generation);

        new_cycles[i] = crossover(first, second);
        new_cycles[i]->mutate(generation->get_mutation_probability(),
                              generation->get_mutation_swap_probability());
    }

    for (int i = 0; i < generation->size; i++) {
        if (generation->cycles[i] == best) {
            continue;
        }

        delete generation->cycles[i];
    }

    delete generation;

    return new Generation(generation_size, new_cycles);
}

Cycle* crossover(Cycle* first, Cycle* second) {
    return crossover_split_one(first, second);
}

Cycle* crossover_split_one(Cycle* first, Cycle* second) {
    int split_index = -1;

    for (int j = 0; j < second->graph->size; j++) {
        for (int i = 0; i <= j; i++) {
            if (first->vertices[i] == second->vertices[j]) {
                split_index = j;
                break;
            }
        }

        if (split_index != -1) {
            break;
        }
    }

    Cycle* current_cycle = new Cycle(first->graph);

    for (int i = 0; i < first->graph->size; i++) {
        current_cycle->vertices[i] = first->vertices[i];
    }

    if (split_index != 0) {
        for (int i = 0; i < split_index; i++) {
            int temp_gen = second->vertices[i];
            for (int k = split_index; k < first->graph->size; k++) {
                if (first->vertices[k] == temp_gen) {
                    current_cycle->vertices[k] = first->vertices[i];
                    current_cycle->vertices[i] = temp_gen;
                    break;
                }
            }
        }
    }

    current_cycle->recalc();
    return current_cycle;
}
