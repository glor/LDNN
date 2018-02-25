#ifndef CLUSTERING_H
#define CLUSTERING_H

#include "config.h"
#include "vector.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

typedef struct {
	int data_size;
	vector_t *data;
	int classes;
	int *class;
	vector_t *centroids;
} clustering_t;

void vector_centroids_from_class(vector_t *centroids, vector_t *vec, int *class, int classes, int len);
clustering_t make_clustering(int data_size, vector_t *data, int classes, int iterations);

#endif
