/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#include "ga.h"
#include "cycle.h"
#include "generation.h"
#include "twister.h"

using namespace std;


Cycle* tournament(Generation* generation) {
    uniform_int_distribution<> dist(0, generation->size - 1);

    int tournament_size = generation->size;
    Cycle** cycles = new Cycle*[tournament_size];

    for (int i = 0; i < tournament_size; i++) {
        cycles[i] = generation->cycles[dist(*get_wersenne_twister())];
    }

    Cycle* best = cycles[0];

    for (int i = 1; i < tournament_size; i++) {
        if (best->length > cycles[i]->length) {
            best = cycles[i];
        }
    }

    return best;
}

Generation* process(Generation* generation) {
    int generation_size = generation->size;
    Cycle** new_cycles = new Cycle*[generation_size];
    
    // generate a new generation (N)
    for (int i = 0; i < generation_size; i++) {
        Cycle* first = tournament(generation);
        Cycle* second = tournament(generation);

        new_cycles[i] = crossover(first, second);
    }

    // TODO: Delete all chromosomes
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
    current_cycle->mutate();
    return current_cycle;
}
