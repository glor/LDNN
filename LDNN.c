#include"LDNN.h"

#define wijk network->weight[i][j][k]
#define wij network->weight[i][j]
#define bij network->bias[i][j]

PRECISION halfspace(network_t *network, int i, int j, vector_t v) {
	PRECISION sum = 0;
	for(int k=0; k<settings.DIM; k++) {
		sum += wijk * v[k] + bij;
	}
	return 1/(1+exp(-sum));
}

PRECISION polytope(network_t *network, int i, vector_t testvec) {
	PRECISION prod = 1;
	for(int j=0; j<network->M; j++) {
		prod *= halfspace(network, i, j, testvec);
	}
	return 1-prod;
}

PRECISION classify(network_t *network, vector_t testvec) {
	PRECISION prod = 1;
	for(int i=0; i<network->N; i++) {
		prod *= polytope(network, i, testvec);
	}
	return 1-prod;
}

void init_network(network_t *network, int neg_size, vector_t *neg, int pos_size, vector_t *pos) {
	int N = network->N;
	int M = network->M;
	vector_t pos_centroid = malloc(settings.DIM*sizeof(PRECISION));
	vector_t neg_centroid = malloc(settings.DIM*sizeof(PRECISION));
	for(int i=0; i<settings.N; i++) {
		for(int j=0; i<settings.M; j++) {
			vector_centroid(pos_centroid, pos, i*(neg_size/N), neg_size/N);
			int neg_centroid_len = vector_length(neg_centroid);
			vector_centroid(neg_centroid, neg, j*(pos_size/M), pos_size/M);
			int pos_centroid_len = vector_length(pos_centroid);
			vector_copy(pos_centroid, wij);
			vector_sub(wij, neg_centroid);
			vector_normalize(wij);
			
			vector_add(pos_centroid, neg_centroid);
			vector_scale(pos_centroid, 0.5);
			bij = vector_scalar_prod(wij, pos_centroid);
			
		}
	}
	
}

