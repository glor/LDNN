#include "config.h"
#include "vector.h"
#include "clustering.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

//#define ASSERT(X) (X) ? ;

#define DEBUG(X) //puts(X); fflush(stdout);


vector_t *permutate(int len, vector_t *vec) {
	vector_t tmp;
	for(int i=0; i<len; i++) {
		int r = rand()%len;
		tmp = vec[i];
		vec[i] = vec[r];
		vec[r] = tmp;
	}
	return vec;
}

/*
 * class enthält eine zuordnung von {0,...,classes-1} für jedes element von vec
 */
void vector_centroids_from_class(vector_t *centroids, vector_t *vec, int *class, int classes, int len) {
	vectors_fill(classes, centroids, 0);
	
	int *class_size = malloc(classes*sizeof(int));
	for(int i=0; i<classes; i++) {
		class_size[i] = 0;
	}
    
	for(int i=0; i<len; i++) {
		vector_add(centroids[class[i]], vec[i]);
		class_size[class[i]]++;
	}
	for(int i=0; i<classes; i++) {
		vector_scale(centroids[i], 1/(PRECISION)class_size[i]);
	}
	free(class_size);
}

clustering_t make_clustering(int data_size, vector_t *data, int classes, int iterations) {
	// ASSERT(classes < data_size)
	clustering_t clusters;
	clusters.data_size = data_size;
	clusters.data = data;
	clusters.classes = classes;
	int *class = malloc(data_size*sizeof(int));
	clusters.class = class;
	for(int i=0; i<classes; i++) {
		class[i] = i;
	}
	// use the first classes points as initial values for centroids
	vector_t *centroids = vectors_allocate(classes);
	vector_centroids_from_class(centroids, data, class, classes, classes);
	clusters.centroids = centroids;
	
	for(int i=0; i<iterations; i++) {
		//1. assign classes according to centroids (nearest neighbor)
		for(int j=0; j<data_size; j++) {
			int argmin = 0;
			for(int k=0; k<classes; k++) {
				if(vector_metric(data[j], centroids[k]) <= vector_metric(data[j], centroids[argmin])) {
					argmin = k;
				}
			}
			class[j] = argmin;
		}
		//2. update centroids according to class assingment
		vector_centroids_from_class(centroids, data, class, classes, data_size);
	}
	return clusters;
}


#define set(vec, i, v1, v2) vec[i][0] = (v1), vec[i][1] = (v2)

void test_vector_centroids_from_class() {
	
	int n = 9;
	
	vector_t *pos = vectors_allocate(n);
	set(pos, 0, 0, 10);
	set(pos, 1, 10, 0);
	set(pos, 2, 10, 10);
	set(pos, 3, 0, 0);
	
	set(pos, 4, 0, 1);
	set(pos, 5, 10, 1);
	set(pos, 6, 11, -1);
	set(pos, 7, 11, 12);
	set(pos, 8, 0, 8);
	
	//permutate(n, pos);
	for(int i=0; i<n; i++)
		vector_print(pos[i]);
	puts("");
	
	int classes = 4;
	clustering_t c = make_clustering(n, pos, classes, 20); // n, vec, classes, iterations
	for(int i=0; i<n; i++) {
		printf("%d ", c.class[i]);
		vector_print(pos[i]);
	}
	for(int i=0; i<classes; i++)
		vector_print(c.centroids[i]);
}

void main2(void) {
	settings.N = 5;
	settings.M = 5;
	settings.DIM = 2;
	srand(time(NULL));
	
	test_vector_centroids_from_class();
	
}
