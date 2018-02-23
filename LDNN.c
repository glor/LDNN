#include"LDNN.h"

#define wijk network->weight[i][j][k]
#define wij network->weight[i][j]
#define bij network->bias[i][j]

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
			tmp += DIM;
		}
	}
	return network;
}

void destroy_network(network_t *network) {
	// not impl
}

void init_network(network_t *network, int neg_size, vector_t *neg, int pos_size, vector_t *pos) {
	int N = network->N;
	int M = network->M;
	vector_t pos_centroid = malloc(settings.DIM*sizeof(PRECISION));
	vector_t neg_centroid = malloc(settings.DIM*sizeof(PRECISION));
	for(int i=0; i<settings.N; i++) {
		for(int j=0; j<settings.M; j++) {
			vector_centroid2(pos_centroid, pos+i*(pos_size/N), pos_size/N);
			vector_centroid2(neg_centroid, neg+j*(neg_size/M), neg_size/M);
			
			vector_copy(pos_centroid, wij);
			vector_sub(wij, neg_centroid);
			vector_normalize(wij);
			
			
			vector_add(pos_centroid, neg_centroid);
			vector_scale(pos_centroid, 0.5);
			bij = vector_scalar_prod(wij, pos_centroid);
		}
	}
}

PRECISION halfspace(network_t *network, int i, int j, vector_t v) {
	PRECISION sum = 0;
	for(int k=0; k<settings.DIM; k++) {
		sum += wijk * v[k];
	}
	return 1/(1+exp(-sum+bij));
}

PRECISION polytope(network_t *network, int i, vector_t testvec) {
	PRECISION prod = 1;
	for(int j=0; j<network->M; j++) {
		prod *= halfspace(network, i, j, testvec);
	}
	return prod;
}

PRECISION classify(network_t *network, vector_t testvec) {
	PRECISION prod = 1;
	for(int i=0; i<network->N; i++) {
		prod *= 1-polytope(network, i, testvec);
	}
	return 1-prod;
}

void gradient_train(network_t *network, int class, vector_t x) {
	for(int i=0; i<settings.N; i++) {
		for(int j=0; j<settings.M; j++) {
			PRECISION diff_bias = 2*(classify(network, x) - class);
			for(int r=0; r<settings.N; r++) {
				if(i==r)
					continue;
				diff_bias *= (1-polytope(network, r, x));
			}
			diff_bias *= (1-polytope(network, i, x)) * (1-halfspace(network, i, j, x));
			diff_bias *= settings.alpha;
			vector_scale(x, diff_bias);
			
			//apply diff
			vector_sub(wij, x);
			bij -= diff_bias;
		}
	}
	//PRECISION diff_weight
}
