#include"config.h"
#include"vector.h"
#include<stdlib.h>

typedef struct {
    vector_t mean;
    PRECISION varsum;
    int size;
} cluster_t;

int randRange(int from, int to) {
    int x = rand();
    x = x<0 ? -x : x;
    return (x)%(to-from)+from;
}

void cluster_centroid(vector_t centroid, int data_size, vector_t *data, int filter, int *filters) {
	for(int i=0; i<settings.DIM; i++)
		centroid[i] = 0;
	int cnt++;
	for(int i=0; i<data_size; i++) {
	    if(filters[i] == filter) {
    		vector_add(centroid, data[i]);
    		cnt++;
    	}
	}
	PRECISION len = vector_length(centroid);
	vector_scale(centroid, 1/(PRECISION)cnt);
}

vector_t fill(vector_t vec, PRECISION value) {
    for(int i=0; i<settings.DIM; i++) {
        vec[i] = value;
    }
    return vec;
}

PRECISION vector_variance(vector_t a, vector_t b) {
    PRECISION diff[settings.DIM];
    vector_copy(a,diff);
    vector_sub(diff, b);
    PRECISION tmp = vector_length(diff);
    return tmp*tmp;
}

void update_cluster_variance(cluster_t cluster, int data_size, vector_t *data, int filter, int *filters) {
    cluster.varsum = 0;
    cluster.size = 0;
    for(int i=0; i<data_size; i++) {
        if(filters[i] == filter) {
            cluster.size++;
            cluster.varsum += vector_varsum(mean, data[i]);
        }
    }
}

int find_cluster(vector_t vec, int k, cluster_t *clusters) {
    int argmin = 0;
    PRECISION min = (clusters[0].variance + vector_variance(vec, clusters[0].mean))/(PRECISION)(clusters[0].size+1);
    for(int i=1; i<k; i++) {
        int tmp = (clusters[i].variance + vector_variance(vec, clusters[i].mean))/(PRECISION)(clusters[i].size+1);
        if(tmp < min) {
            argmin = i;
            min = tmp;
        }
    }
    return argmin;
}

int *lloyd_cluster(int data_size, vector_t *data, int k) {// -> {0,...,k-1}[data_size]
    // vector_t data -> int cluster
    int *clustering = malloc(sizeof(int)*data_size);
    int *newclustering = malloc(sizeof(int)*data_size);
    for(int i=0; i<data_size; i++)
        // -1 <=> no cluster
        clustering[i] = -1;
    
    // int cluster -> cluster_t details
    cluster_t *clusters = malloc(sizeof(int)*k);
    for(int i=0; i<k; i++) {
        clusters[i].mean = malloc(sizeof(PRECISION)*settings.DIM);
        clusters[i].varsum = 0;
        clusters[i].size = 1;
        vector_copy(data[randRange(0, data_size)], clusters[i].mean);
    }
    
    int iterations = 0;
    int changes = 1;
    //while änderungen
    while(changes && iterations<CLUSTER_MAX_ITERATIONS) {
        changes = 0;
        for(int i=0; i<data_size; i++) {
            int newclustering[i] = find_cluster(data[i], k, clusters);
            if(newclustering[i] != clustering[i]) {
                changes = 1;
            }
        }
        void *tmp = clustering;
        clustering = newclustering;
        newclustering = tmp;
        
        for(int i=0; i<k; i++) {
            update_cluster_variance(clusters[i], data_size, data, i, clustering);
        }
        iterations++;
    }
    free(means[0]);
    free(means);
    return clustering;
}
