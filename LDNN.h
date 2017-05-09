#ifndef LDNN_H
#define LDNN_H

#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#include"config.h"
#include"vector.h"

// used to store the network values
typedef struct network_s {
	int N, M; // N polytopes; M halfspaces
	vector_t **weight;	// MxN weight vectors
	PRECISION **bias;	// MxN biases
} network_t;

network_t *make_network();
void destroy_network(network_t *network);

PRECISION classify(network_t *network, vector_t testvec);

void init_network(network_t *network, int neg_size, vector_t *neg, int pos_size, vector_t *pos);
void gradient_train(network_t *network, int class, vector_t x);

#endif

