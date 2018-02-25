#include"vector.h"
#include<stdlib.h>
#include<math.h>

/*
 * Allocates new vector of size ldnn_settings.DIM
 */
vector_t vector_allocate() {
	return malloc(ldnn_settings.DIM*sizeof(PRECISION));
}

/*
 * Allocates len new vectors of size ldnn_settings.DIM
 */
vector_t *vectors_allocate(int len) {
	vector_t *vec = malloc(len*sizeof(vector_t));
	for(int i=0; i<len; i++) {
		vec[i] = vector_allocate();
	}
	return vec;
}
/*
 * Print vector
 */
void vector_print(vector_t vec) {
	printf("(");
	for(int i=0; i<ldnn_settings.DIM-1; i++)
		printf("%lg ", vec[i]);
	printf("%lg", vec[ldnn_settings.DIM-1]);
	puts(")");
}

/*
 * Print vectors
 */
void vectors_print(int len, vector_t *vecs) {
	for(int i=0; i<len; i++)
		vector_print(vecs[i]);
}

/*
 * Copy vector content from src to dest
 */
void vector_copy(vector_t src, vector_t dest) {
	for(int i=0; i<ldnn_settings.DIM; i++)
		dest[i] = src[i];
}

/*
 * Scale vector vec by s
 */
void vector_scale(vector_t vec, PRECISION s) {
	for(int i=0; i<ldnn_settings.DIM; i++)
		vec[i] *= s;
}

/*
 * Scale vector to length 1
 */
void vector_normalize(vector_t vec) {
	vector_scale(vec, vector_norm(vec));
}

/*
 * Calculate norm
 */
PRECISION vector_norm(vector_t vec) {
	PRECISION sum = 0;
	for(int i=0; i<ldnn_settings.DIM; i++) {
		sum += vec[i] * vec[i];
	}
	return sqrt(sum);
}

/*
 * Calculate dot product from two vectors
 */
PRECISION vector_dot_prod(vector_t x, vector_t y) {
	PRECISION sum = 0;
	for(int i=0; i<ldnn_settings.DIM; i++) {
		sum += x[i]*y[i];
	}
	return sum;
}
/*
 * Add vector src onto vector dest
 */
vector_t vector_add(vector_t dest, vector_t src) {
	for(int i=0; i<ldnn_settings.DIM; i++) {
		dest[i] += src[i];
	}
	return dest;
}
/*
 * Substract vector src from vector dest
 */
vector_t vector_sub(vector_t dest, vector_t src) {
	for(int i=0; i<ldnn_settings.DIM; i++) {
		dest[i] -= src[i];
	}
	return dest;
}
/*
 * Calculate distance between x and y
 */
PRECISION vector_metric(vector_t x, vector_t y) {
    PRECISION norm = 0;
	for(int i=0; i<ldnn_settings.DIM; i++) {
	    norm += (x[i]-y[i])*(x[i]-y[i]);
	}
	return sqrt(norm);
}

/*
 * Calculate centroid from list of vectors
 * don't use if you are working with clusterings
 */
void vector_centroid(vector_t dest, vector_t *vec, int len) {
	for(int i=0; i<ldnn_settings.DIM; i++)
		dest[i] = 0;
	for(int i=0; i<len; i++)
		vector_add(dest, vec[i]);
	vector_scale(dest, 1/(PRECISION)len);
}

/*
 * Fill all vector components with value
 */
void vector_fill(vector_t vec, PRECISION value) {
	for(int i=0; i<ldnn_settings.DIM; i++) {
		vec[i] = value;
	}
}

/*
 * Fill list of vectors with value
 */
void vectors_fill(int len, vector_t *vecs, PRECISION value) {
	for(int i=0; i<len; i++) {
	    for(int j=0; j<ldnn_settings.DIM; j++) {
		    vecs[i][j] = value;
	    }
	}
}
/*
 * Concatenate vectors
 */
vector_t *vectors_concat(vector_t *x, int x_len, vector_t *y, int y_len) {
    vector_t *new = malloc((x_len+y_len)*sizeof(vector_t));
    for(int i=0; i<x_len; i++) {
        new[i] = x[i];
    }
    for(int i=0; i<y_len; i++) {
        new[x_len+i] = y[i];
    }
    return new;
}
/*
 * Permutate vectors in a list of vectors
 * needs rand() initialized
 */
vector_t *vectors_permutate(int len, vector_t *vec) {
	vector_t tmp;
	for(int i=0; i<len; i++) {
		int r = rand()%len;
		tmp = vec[i];
		vec[i] = vec[r];
		vec[r] = tmp;
	}
	return vec;
}
