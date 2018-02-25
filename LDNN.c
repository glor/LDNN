#include"LDNN.h"
#include"clustering.h"

#define wijk network->weight[i][j][k]
#define wij network->weight[i][j]
#define bij network->bias[i][j]

/*
 * Allocate a new network
 * uses current settings parameters to determine size
 * @returns new empty network
 */
network_t *make_network() {
	int N = ldnn_settings.N;
	int M = ldnn_settings.M;
	int DIM = ldnn_settings.DIM;

	network_t* network = (network_t*) malloc(sizeof(network_t));
	network->N = N;
	network->M = M;

	vector_t tmp = (vector_t)vectors_allocate(N*M);
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
/*
 * initialize network from positive and negative training examples
 */
void init_network(network_t *network, int neg_size, vector_t *neg, int pos_size, vector_t *pos) {
	int N = network->N;
	int M = network->M;
	vector_t pos_centroid = vector_allocate();
	vector_t neg_centroid = vector_allocate();

	clustering_t pos_cluster = make_clustering(pos_size, pos, N, ldnn_settings.CLUSTER_ITERATIONS);
	clustering_t neg_cluster = make_clustering(neg_size, neg, M, ldnn_settings.CLUSTER_ITERATIONS);

	for(int i=0; i<ldnn_settings.N; i++) {
		for(int j=0; j<ldnn_settings.M; j++) {
			vector_copy(pos_cluster.centroids[i], pos_centroid);
			vector_copy(neg_cluster.centroids[j], neg_centroid);

			vector_copy(pos_centroid, wij);
			vector_sub(wij, neg_centroid);
			vector_normalize(wij);


			vector_add(pos_centroid, neg_centroid);
			vector_scale(pos_centroid, 0.5);
			bij = vector_dot_prod(wij, pos_centroid);
		}
	}
}

PRECISION halfspace(network_t *network, int i, int j, vector_t v) {
	PRECISION sum = 0;
	for(int k=0; k<ldnn_settings.DIM; k++) {
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
/*
 * Test if a vector classifies as positiv of negative
 */
PRECISION classify(network_t *network, vector_t testvec) {
	PRECISION prod = 1;
	for(int i=0; i<network->N; i++) {
		prod *= 1-polytope(network, i, testvec);
	}
	return 1-prod;
}

/*
 * Gradient training can be used to increase the accuracy of the model
 * only viable with much data_size
 */
void gradient_train(network_t *network, int class, vector_t x) {
	for(int i=0; i<ldnn_settings.N; i++) {
		for(int j=0; j<ldnn_settings.M; j++) {
			PRECISION diff_bias = 2*(classify(network, x) - class);
			for(int r=0; r<ldnn_settings.N; r++) {
				if(i==r)
					continue;
				diff_bias *= (1-polytope(network, r, x));
			}
			diff_bias *= (1-polytope(network, i, x)) * (1-halfspace(network, i, j, x));
			diff_bias *= ldnn_settings.ALPHA;
			vector_scale(x, diff_bias);

			//apply diff
			vector_sub(wij, x);
			bij -= diff_bias;
		}
	}
	//PRECISION diff_weight
}
