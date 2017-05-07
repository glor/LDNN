#ifndef DATAMODEL_H
#define DATAMODEL_H

#include<stdlib.h>

#include"config.h"

// used to store the network values
typedef struct network_s {
	int N, M; // N polytopes; M linear functions
	vector_t **weight;	// MxN weight vectors
	vector_t *bias;	// N biases
} network_t;

network_t *make_network();
void destroy_network(network_t *network);

#endif
