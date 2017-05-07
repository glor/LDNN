#include"LDNN.h"

#define wijk network->weight[i][j][k]
#define wij network->weight[i][j]
#define bij network->bias[i][j]

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

void init_network(network_t *network, int neg_size, vector_t *neg, int pos_size, vector_t *pos) {
	int N = network->N;
	int M = network->M;
	vector_t pos_centroid = malloc(settings.DIM*sizeof(PRECISION));
	vector_t neg_centroid = malloc(settings.DIM*sizeof(PRECISION));
	for(int i=0; i<settings.N; i++) {
		for(int j=0; j<settings.M; j++) {
			vector_centroid(pos_centroid, pos, i*(pos_size/N), pos_size/N);
			int pos_centroid_len = vector_length(pos_centroid);
			
			vector_centroid(neg_centroid, neg, j*(neg_size/M), neg_size/M);
			int neg_centroid_len = vector_length(neg_centroid);
			
			//puts("pos");
			//vector_print(pos_centroid);
			
			//puts("neg");
			//vector_print(neg_centroid);
			
			vector_copy(pos_centroid, wij);
			vector_sub(wij, neg_centroid);
			vector_normalize(wij);
			
			
			vector_add(pos_centroid, neg_centroid);
			vector_scale(pos_centroid, 0.5);
			bij = vector_scalar_prod(wij, pos_centroid);
		}
	}
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
			bij = bij - diff_bias;
		}
	}
	//PRECISION diff_weight
}
