#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

#include "structures.h"
#include "ga.h"

#define MUTATION_PROBABILITY 15

using namespace std;


Generation* process(Generation* generation) {
    long sum_length = 0;

    double sum_reversed = 0;
    double reversed[generation->size];

    double cumulative[generation->size];

    vector<HamiltonianCycle*> selected_chromosomes;
    HamiltonianCycle** new_cycles = new HamiltonianCycle*[generation->size];

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

    // generate a new generation (N)
    for (int i = 0; i < 2 * generation->size; i += 2) {
        new_cycles[i] = crossover(selected_chromosomes[i], selected_chromosomes[i + 1]);
    }

    return new Generation(generation->size, new_cycles);
}

/*
* plan:
*
* 1) proportional line for current generation +
* 2) new generation = 2N chromosomes +
* 3) new_cycles = crossover (N with each other)
* 4) reutrn Generation
*
* 5*) myabe selection again? Or no..
*
*
*
*
*/

/*{

    HamiltonianCycle* temp;

    int change_method = rand(1..4)
    1 = 1-razrez
    2 = 2-razrez
    3 = 1-swap
    4 = k-swap
    }
    */

HamiltonianCycle* crossover(HamiltonianCycle* first, HamiltonianCycle* second) {
    return crossover_split_one(first, second);
}

HamiltonianCycle* crossover_split_one(HamiltonianCycle* first, 
                                      HamiltonianCycle* second) {
    
}

HamiltonianCycle* mutation(HamiltonianCycle* cycle) {
    random_device random;
    mt19937 gen(random());

    gen.seed(time(0));

    uniform_int_distribution<> dist(0, 100);

    if (dist(gen) <= MUTATION_PROBABILITY) {
        // We choose log(cycle->graph->size) vertices from cycle
        int log_size = (int) log((double) cycle->graph->size);

        int selected_gens[log_size];
        vector<int> vertices;

        for (int i = 0; i < cycle->graph->size; vertices.push_back(i++));

        for (int i = log_size; i --> 0;) {
            uniform_int_distribution<> dist(0, vertices.size());
            int v = dist(gen);

            selected_gens[cycle->graph->size - i - 1] = vertices[v];
            vertices.erase(vertices.begin() + v);
        }

        sort(selected_gens, selected_gens + log_size);

        int v = selected_gens[0];

        for (int i = 1; i < log_size; i++) {
            int t = cycle->vertices[selected_gens[i]];
            cycle->vertices[selected_gens[i]] = v;
            v = t;
        }

        selected_gens[0] = v;
    }

    return cycle;
}
