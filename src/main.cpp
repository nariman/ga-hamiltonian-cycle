/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <random>

#include "cycle.h"
#include "ga.h"
#include "generation.h"
#include "generator.h"
#include "graph.h"

using namespace std;


volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}

int main() {
    signal(SIGINT, inthand); //CTRL + C = STOP

    Graph* graph = generate_random_graph(100, 1000);
    graph->repr();

    cout << endl << endl;

    Generation *gen = generate_random_generation(graph);
    gen->repr();

    cout << endl << endl;

    int count = 0;
     while (!stop) {
        //  cout << "Generation #" << ++count << endl;
         gen = process(gen);
         cout << "- best len is " << gen->best()->length << endl << endl;
     }

    cout << "We're here";

    delete graph;
    delete gen;
    return 0;
}
