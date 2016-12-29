/*
 * Genetic Algorithm for a Travelling Salesman Problem.
 * Hamiltonian Cycle problem.
 */

#include <algorithm> // max
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

    Graph* graph = generate_random_graph(100, 1000);

    // Graph* graph = read_graph();
    // graph->repr();

    // cout << endl << endl;

    Generation *gen = generate_random_generation(graph);
    // gen->repr();

    cout << endl << endl;

    double first_answer = 0;
    double best_of_last_generation = gen->best()->length;
    long count = 0;

    while (!stop) {
        cout << "Generation #" << ++count << endl;

        gen = process(gen);

        if (count == 1) {
            first_answer = gen->best()->length;
        }

        cout << "The best length of Hamiltonian Cycle is " << gen->best()->length; 
        cout << endl << endl;

        if (count % (int) 1e3 * 5 == 0) {
            if (best_of_last_generation == gen->best()->length) {
                cout << "Mutation probability increased!!!";

                gen->set_mutation_probability(gen->get_mutation_probability() + 25);
                gen->set_mutation_swap_probability(gen->get_mutation_swap_probability() + 25);
            }
        }

        if (count % ((int) 1e3 * 5 + 5) == 0) {
            gen->set_mutation_probability(gen->get_mutation_probability() - 25);
            gen->set_mutation_swap_probability(gen->get_mutation_swap_probability() - 25);
        }
    }

    cout << endl;

    cout << "First answer: " << first_answer << endl;
    cout << "Last answer: " << gen->best()->length << endl;

    cout << "End";

    delete graph;
    delete gen;
    return 0;
}
