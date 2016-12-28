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

using namespace std;


Generation* process(Generation* generation) {
    long sum_length = 0;

    double sum_reversed = 0;
    double reversed[generation->size];

    double cumulative[generation->size];

    vector<Cycle*> selected_chromosomes;
    Cycle** new_cycles = new Cycle*[generation->size];

    for (int i = 0; i < generation->size; i++) {
        sum_length += generation->cycles[i]->length;
    }

    for (int i = 0; i < generation->size; i++) {
        reversed[i] = sum_length / generation->cycles[i]->length;
        sum_reversed += reversed[i];
    }

    cumulative[0] = reversed[0] / sum_reversed;

    for (int i = 1; i < generation->size; i++) {
        cumulative[i] = reversed[i - 1] + reversed[i] / sum_reversed;
    }

    random_device random;
    mt19937 gen(random());

    gen.seed(time(0));

    // vector indices 2*N chromosomes for crossover or mutation
    for (int i = 0; i < 2 * generation->size; i++) {
        uniform_real_distribution<> dist(0, cumulative[generation->size - 1]);
        double index = dist(gen);

        int l = 0;
        int r = generation->size - 1;
        int c = 0;

        while (l < r) {
            c = (l + r) >> 1;
            if (index <= cumulative[c]) {
                r = c;
            } else {
                l = c + 1;
            }
        }

        selected_chromosomes.push_back(generation->cycles[l]);
    }

    cout << endl << "SELECTED: " << endl;

    for (size_t i = 0; i < selected_chromosomes.size(); i++) {
        selected_chromosomes[i]->repr();
        cout << endl;
    }

    cout << endl;
    cout <<  "CROSSOVERED: " << endl;

    // generate a new generation (N)
    for (int i = 0; i < generation->size; i++) {
        new_cycles[i] = crossover(selected_chromosomes[2 * i], selected_chromosomes[2 * i + 1]);
        new_cycles[i]->repr();
        cout << endl;
    }

    cout << endl;

    int new_size = generation->size;
    // TODO: Delete all chromosomes
    delete generation;

    return new Generation(new_size, new_cycles);
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

    if (split_index == 0) {
        current_cycle->mutate();
    } else {
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
