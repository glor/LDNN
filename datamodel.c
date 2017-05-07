#include"datamodel.h"

network_t *make_network() {
	int N = settings.N;
	int M = settings.M;
	int DIM = settings.DIM;
	// network + weights + bias
	// sizeof(network) + N*M*dim*sizeof(PRECISION) + N*M*sizeof(PRECISION)
	network_t* network = (network_t*) malloc(sizeof(network_t));
	network->N = N;
	network->M = M;
	
	vector_t tmp = malloc(N*M*DIM*sizeof(PRECISION));
	network->weight = malloc(N*sizeof(vector_t *));
	network->bias   = malloc(N*sizeof(vector_t ));
	for(int i=0; i<N; i++) {
		network->weight[i] = malloc(M*sizeof(vector_t));
		network->bias[i] = malloc(M*sizeof(PRECISION));
		for(int j=0; j<M; j++) {
			network->weight[i][j] = tmp;
			tmp += DIM*sizeof(PRECISION);
		}
	}
	return network;
}

void destroy_network(network_t *network) {
	// not impl
}

