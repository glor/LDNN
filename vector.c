#include"vector.h"


void vector_copy(vector_t src, vector_t dest) {
	for(int i=0; i<settings.DIM; i++)
		dest[i] = src[i];
}

void vector_scale(vector_t v, PRECISION s) {
	for(int i=0; i<settings.DIM; i++)
		v[i] *= s;
}

void vector_print(vector_t v) {
	printf("(");
	for(int i=0; i<settings.DIM; i++)
		printf("%lf ", v[i]);
	puts(")");
}

void vector_normalize(vector_t v) {
	vector_scale(v, vector_length(v));
}
int c = 0;
PRECISION vector_length(vector_t v) {
	PRECISION sum = 0;
	for(int i=0; i<settings.DIM; i++) {
		sum += v[i] * v[i];
	}
	return sqrt(sum);
}

PRECISION vector_scalar_prod(vector_t x, vector_t y) {
	PRECISION sum = 0;
	for(int i=0; i<settings.DIM; i++) {
		sum += x[i]*y[i];
	}
	return sum;
}

PRECISION sigmoid(PRECISION p) {
	return (PRECISION)(1/(1+exp(-p)));
}

vector_t vector_add(vector_t x, vector_t y) {
	for(int i=0; i<settings.DIM; i++) {
		x[i] += y[i];
	}
	return x;
}
vector_t vector_sub(vector_t x, vector_t y) {
	for(int i=0; i<settings.DIM; i++) {
		x[i] -= y[i];
	}
	return x;
}

void vector_centroid(vector_t centroid, vector_t *data, int start, int amount) {
	for(int i=0; i<settings.DIM; i++)
		centroid[i] = 0;
	for(int i=start; i<start+amount; i++)
		vector_add(centroid, data[i]);
	PRECISION len = vector_length(centroid);
	for(int i=0; i<settings.DIM; i++) {
		centroid[i] /= amount;
	}
}
