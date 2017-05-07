#ifndef VECTOR_H
#define VECTOR_H

#include<math.h>

#include"config.h"

void vector_copy(vector_t src, vector_t dest);
void vector_scale(vector_t v, PRECISION s);
void vector_normalize(vector_t v);
PRECISION vector_length(vector_t v);
PRECISION vector_scalar_prod(vector_t x, vector_t y);
PRECISION sigmoid(PRECISION p);
vector_t vector_add(vector_t x, vector_t y);
vector_t vector_sub(vector_t x, vector_t y);
void vector_centroid(vector_t centroid, vector_t *data, int start, int len);

#endif
