/*
 * Methods for generating new graphs with weights
 */

#include <ctime>
#include <random>
#include "structures.h"

using namespace std;

Graph *generate(int length, long max_weight) {
    long **matrix = new long *[length + 1];
    for (int i = 0; i <= length; matrix[i++] = new long[length + 1]);

    random_device random;
    mt19937 gen(random());
    uniform_int_distribution<> dist(1, max_weight);

    gen.seed(time(0));

    for (int i = 1; i <= length; i++) {
        for (int j = 1; j <= i; j++) {
            matrix[i][j] = matrix[j][i] = dist(gen);
        }

        matrix[i][i] = 0;
    }

    return new Graph(length, matrix);
}
