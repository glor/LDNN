#include"vector.h"
#include<stdlib.h>
#include<math.h>

void vector_print(vector_t vec) {
	printf("(");
	for(int i=0; i<settings.DIM-1; i++)
		printf("%lg ", vec[i]);
	printf("%lg", vec[settings.DIM-1]);
	puts(")");
}

void vector_copy(vector_t src, vector_t dest) {
	for(int i=0; i<settings.DIM; i++)
		dest[i] = src[i];
}

void vector_scale(vector_t vec, PRECISION s) {
	for(int i=0; i<settings.DIM; i++)
		vec[i] *= s;
}

void vector_normalize(vector_t vec) {
	vector_scale(vec, vector_length(vec));
}


PRECISION vector_length(vector_t vec) {
	PRECISION sum = 0;
	for(int i=0; i<settings.DIM; i++) {
		sum += vec[i] * vec[i];
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

vector_t vector_add(vector_t dest, vector_t src) {
	for(int i=0; i<settings.DIM; i++) {
		dest[i] += src[i];
	}
	return dest;
}
vector_t vector_sub(vector_t dest, vector_t src) {
	for(int i=0; i<settings.DIM; i++) {
		dest[i] -= src[i];
	}
	return dest;
}

PRECISION vector_metric(vector_t x, vector_t y) {
    PRECISION norm = 0;
	for(int i=0; i<settings.DIM; i++) {
	    norm += (x[i]-y[i])*(x[i]-y[i]);
	}
	return sqrt(norm);
	/*vector_t diff = vector_allocate();
	vector_copy(x, diff);
	vector_sub(diff, y);
	PRECISION norm = vector_length(diff);
	free(diff);
	return norm;*/
}

vector_t vector_allocate() {
	return malloc(settings.DIM*sizeof(PRECISION));
}

vector_t *vectors_allocate(int len) {
	vector_t *vec = malloc(len*sizeof(vector_t));
	for(int i=0; i<len; i++) {
		vec[i] = vector_allocate();
	}
	return vec;
}

void vector_centroid(vector_t dest, vector_t *vec, int len) {
	for(int i=0; i<settings.DIM; i++)
		dest[i] = 0;
	for(int i=0; i<len; i++)
		vector_add(dest, vec[i]);
	vector_scale(dest, 1/(PRECISION)len);
}

void vector_fill(vector_t vec, PRECISION value) {
	for(int i=0; i<settings.DIM; i++) {
		vec[i] = value;
	}
}
#define DEBUG(X) puts(X); fflush(stdout);

void vectors_fill(int len, vector_t *vecs, PRECISION value) {
	for(int i=0; i<len; i++) {
	    for(int j=0; j<settings.DIM; j++) {
		    vecs[i][j] = value;
	    }
	}
}

vector_t *vectors_merge(vector_t *x, int x_len, vector_t *y, int y_len) {
    vector_t *new = malloc((x_len+y_len)*sizeof(vector_t));
    for(int i=0; i<x_len; i++) {
        new[i] = x[i];
    }
    for(int i=0; i<y_len; i++) {
        new[x_len+i] = y[i];
    }
    return new;
}


