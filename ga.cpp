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
    for (int i = 0; i < generation->size; sum_length += generation->cycles[i++]->length);

    double cumulative[generation->size];

    cumulative[0] = sum_length / generation->cycles[0]->length;
    for (int i = 1; i < generation->size; i++) {
        cumulative[i] = cumulative[i - 1] + 1 / (sum_length / generation->cycles[i]->length);
    }

    double reversed_sum_length = cumulative[generation->size - 1];

    random_device random;
    mt19937 gen(random());

    gen.seed(time(0));

//    for (int i = 0; i < generation->size; i++) {
//        uniform_double_distribution<> dist(0, reversed_sum_length);
//        double index = dist(gen);
//
//        int l = 0;
//        int r = generation->size - 1;
//        int c = 0;
//        while (l < r) {
//            c = (l + r) >> 1;
//            if (index <= while[c]){
//                r = c;
//            }else{
//                l = c + 1;
//            }
//        }
//        this.genomListOffsprings[i] = this.genomListParents[l].clone();
//    }
//    break;
}

