#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "ga.h"
#include "generator.h"
#include "structures.h"

using namespace std;


volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}

int main() {

    signal(SIGINT, inthand); //CTRL + C = STOP

    Graph* graph = generate_random_graph(10, 1000);
    graph->print();

    cout << endl << endl;

    Generation *gen = generate_random_generation_by_greedy_strategy(graph);
    gen->print();

    cout << endl << endl;

    // while (!stop) {
    //     // gen = process(gen);
    // }

    cout << "We're here";

    delete graph;
    delete gen;
    return 0;
}
