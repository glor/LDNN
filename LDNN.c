#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;

#define PRECISION float
#define HIGH_PRECISION double

/*
typedef struct hyper_param_s {
	int SAMPLE_SIZE;
	int 
} hyper_param_t;
*/

typedef struct param_s {
	int N;
	int M;
	int dim;
	
} param_t;

// used to store 
typedef struct network_s {
	int N, M; // N polytopes; M linear functions
	PRECISION **weight;	// MxN weights
	PRECISION *bias;	// N biases
} network_t;

typedef struct vector_s {
	int dim;
	PRECISION *data;	// len x dim
} data_t;

PRECISION scalar_prod(vector_t x, vector_t y) {
	PRECISION sum = 0;
	for(int i=0; i<x.dim; i++) {
		sum += x.content[i]*y.content[i];
	}
	return sqrt(sum);
}

PRECISION sigmoid() {
	printf("sigmoid unimpl");
	exit(1);
}

network_t *make_network(param_t *settings) {
	int N = settings->N;
	int M = settings->M;
	int dim = settings->dim;
	
	// network + weights + bias
	// sizeof(network) + N*M*dim*sizeof(PRECISION) + N*M*sizeof(PRECISION)
	network_t* network = (network_t*) malloc(sizeof(network_t));
	network->N = N;
	network->M = M;
	network->weight = malloc(N*sizeof(PRECISION **));
	for(int i=0; i<N; i++) {
		network->weight[i] = malloc(M*dim*sizeof(PRECISION));
	}
	network->bias = malloc(M*sizeof(PRECISION))
	return network;
}

PRECISION vector_length(vector_t v) {
	PRECISION sum = 0;
	for(int i=0; i<v->dim; i++) {
		sum += v->data[i] * v->data[i];
	}
	return sqrt(sum);
}

void centroid(vector_t *centroid, vector_t *data, int from, int to) {
	for(int i=0; i<centroid->dim; i++) {
		centroid->data[i] = 0;
	}
	for(int i=from; i<to; i++) {
		for(int j=0; j<centroid->dim; j++) {
			centroid->data[i] += data[i]->data[j];
		}
	}
}

void init_network(network_t network, data_t pos_train, data_t neg_train) {
	int NposBlockSize = pos_train->
	for(int i=0; i<network.N; i++) {
		PRECISION len = pos_train;
		network_t pos_centroid;
		centroid(pos_centroid, pos_train);
		for(int j=0; j<network.M; j++) {
			network->weight[i]->data[j] = 
		}
		
	}
}

int main(int argc, char *argv[]) {
	
}
