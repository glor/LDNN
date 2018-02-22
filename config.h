#ifndef CONFIG_H
#define CONFIG_H
#define PRECISION float

#define CLUSTER_MAX_ITERATIONS 1000

typedef PRECISION *vector_t;

// hyper params
struct {
	int N;
	int M;
	int DIM;
	PRECISION alpha;
} settings;
#endif
