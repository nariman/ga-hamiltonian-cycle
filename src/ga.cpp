/*
 * Algorithms
 */

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <random>
#include <vector>

#include "structures.h"
#include "ga.h"

using namespace std;

Generation *greedy(Graph *graph) {
    random_device random;
    mt19937 gen(random());

    gen.seed(time(0));

    HamiltonianCycle **cycles = new HamiltonianCycle *[(int) log((double) graph->size)];

    for (int i = 0; i < (int) log((double) graph->size); i++) {
        int *cycle = new int[graph->size];
        vector<int> vertices;

        for (int j = 1; j <= graph->size; vertices.push_back(j++));

        for (int j = graph->size; j-- > 0;) {
            uniform_int_distribution<> dist(0, j);
            int v = dist(gen);

            cycle[graph->size - j - 1] = vertices[v];
            vertices.erase(vertices.begin() + v);
        }

        cycles[i] = new HamiltonianCycle(graph, cycle);
    }

    return new Generation((int) log((double) graph->size), cycles);
}

Generation *process(Generation *generation) {

    long sum_length = 0;
    double probability[generation->size];
    double sum_probability = 0;
    double cumulative[generation->size];
    double sum_cumulative = 0;
    vector<*HamiltonianCycle> selected_chromosomes;

    HamiltonianCycle **new_cycles = new HamiltonianCycle *[generation->size];

    for (int i = 0; i < generation->size; i++) {
        sum_length += generation->cycles[i]->length;
    }

    for (int i = 0; i < generation->size; i++) {
        probability[i] = 1 - (generation->cycles[i]->length / sum_length);
        sum_probability += probability[i];
    }

    cumulative[0] = probability[0];
    for (int i = 1; i < generation->size; i++) {
        cumulative[i] = cumulative[i - 1] + probability[i];
    }

    sum_cumulative = cumulative[generation->size - 1];

    random_device random;
    mt19937 gen(random());

    gen.seed(time(0));

    //vector indices 2*N chromosomes for crossover or mutation
    for (int i = 0; i < 2 * generation->size; i++) {
        uniform_double_distribution<> dist(0, sum_cumulative);
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
        selected_chromosomes.push_back(&generation->cycles[l]);
    }

    //generate new generation (N)
    for (int i = 0; i < 2 * generation->size; i += 2) {
        new_cycles[i] = crossover(selected_chromosomes[i], selected_chromosomes[i + 1]);
    }

    return /*GENERATION OF NEW_CYCLES*/

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
}


HamiltonianCycle &crossover(HamiltonianCycle &first_chromosome, HamiltonianCycle &first_chromosome) {

    /*{

     HamiltonianCycle* temp;

     int change_method = rand(1..4)
      1 = 1-razrez
      2 = 2-razrez
      3 = 1-swap
      4 = k-swap
      }

      int is_mutation = rand(1..10)
      if (is_mutation < 3) {
           mutation(temp);
      }

     */

}

