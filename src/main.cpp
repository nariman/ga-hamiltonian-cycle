/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <iostream> // cout
#include <signal.h> // SIGINT
#include <unistd.h> // sig_atomic_t

#include "cycle.h"
#include "ga.h"
#include "generation.h"
#include "generator.h"
#include "graph.h"
#include "reader.h"

using namespace std;


volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}

int main() {
    signal(SIGINT, inthand); // CTRL + C = STOP

    Graph* graph = generate_random_graph(1000, 1000);
    // Graph* graph = read_graph();
    // graph->repr();

    // cout << endl << endl;

    Generation *gen = generate_random_generation(graph);
    // gen->repr();

    cout << endl << endl;

    int count = 0;
    while (!stop) {
    //  cout << "Generation #" << ++count << endl;
        gen = process(gen);
        cout << "- best len is " << gen->best()->length << endl << endl;

        // if (count++ % 10000 == 0) {
        //     gen->repr();
        // }
    }

    cout << "We're here";

    delete graph;
    delete gen;
    return 0;
}
