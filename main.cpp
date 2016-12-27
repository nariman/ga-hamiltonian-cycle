/*
 * Main logic
 */

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>


#include "structures.h"
#include "generator.h"
#include "ga.h"

using namespace std;

volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}


int main() {

    signal(SIGINT, inthand); //CTRL + C = STOP

    Graph *graph = generate(10, 1000);
    graph->print();

    cout << endl;

    Generation *gen = greedy(graph);
    gen->print();

    while (!stop) {
        gen = process(gen);
    }

    cout << "We're here";

    delete graph;
    delete gen;
    return 0;
}
