#ifndef VECTOR_H
#define VECTOR_H

#include<math.h>
#include<stdio.h>

#include"config.h"

void vector_print(vector_t v);
void vector_copy(vector_t src, vector_t dest);
void vector_scale(vector_t v, PRECISION s);
void vector_normalize(vector_t v);

PRECISION vector_length(vector_t v);
PRECISION vector_scalar_prod(vector_t x, vector_t y);
vector_t vector_add(vector_t x, vector_t y);
vector_t vector_sub(vector_t x, vector_t y);

vector_t vector_allocate();
vector_t *vectors_allocate(int len);

void vector_centroid2(vector_t dest, vector_t *vec, int len);

#endif
