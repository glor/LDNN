#ifndef VECTOR_H
#define VECTOR_H

#include<math.h>
#include<stdio.h>

#include"config.h"

vector_t vector_allocate();
vector_t *vectors_allocate(int len);

void vector_fill(vector_t vec, PRECISION value);
void vectors_fill(int len, vector_t *vecs, PRECISION value);

void vector_print(vector_t vec);
void vector_copy(vector_t src, vector_t dest);
void vector_scale(vector_t vec, PRECISION s);
void vector_normalize(vector_t vec);

PRECISION vector_metric(vector_t x, vector_t y);
PRECISION vector_norm(vector_t vec);
PRECISION vector_dot_prod(vector_t x, vector_t y);

vector_t vector_add(vector_t dest, vector_t src);
vector_t vector_sub(vector_t dest, vector_t src);

// willst du vermutlich nicht verwenden
void vector_centroid(vector_t dest, vector_t *vec, int len);
vector_t *vectors_concat(vector_t *x, int x_len, vector_t *y, int y_len);
vector_t *vectors_permutate(int len, vector_t *vec);

#endif
