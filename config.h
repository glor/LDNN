#ifndef CONFIG_H
#define CONFIG_H
#define PRECISION float

typedef PRECISION *vector_t;

// hyper params
struct {
	int N;
	int M;
	int DIM;
	int CLUSTER_ITERATIONS;
	PRECISION ALPHA;
} ldnn_settings;
#endif
