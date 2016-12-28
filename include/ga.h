#ifndef GA_HAMILTONIAN_CYCLE_GA_H
#define GA_HAMILTONIAN_CYCLE_GA_H

#include "structures.h"

Generation* process(Generation* generation);

HamiltonianCycle* crossover(HamiltonianCycle* first, HamiltonianCycle* second);

HamiltonianCycle* crossover_split_one(HamiltonianCycle* first, 
                                      HamiltonianCycle* second);

HamiltonianCycle* mutation(HamiltonianCycle* cycle);

#endif //GA_HAMILTONIAN_CYCLE_GA_H
