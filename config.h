#ifndef CONFIG_H
#define CONFIG_H
#define PRECISION float

typedef PRECISION *vector_t;

struct {
	int N;
	int M;
	int DIM;
	PRECISION alpha;
} settings;
#endif
