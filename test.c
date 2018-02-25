#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"config.h"
#include"vector.h"
#include"LDNN.h"

vector_t *read_data(FILE *file, int *dim, int *len) {
	
	fscanf(file, "%d", dim);
	fscanf(file, "%d", len);
	vector_t *data = malloc((*len) * (*dim) * sizeof(PRECISION));
	for(int i=0; i<*len; i++)
		for(int j=0; j<*dim; j++)
			fscanf(file, "%f", &data[i][j]);
	return data;
}

void write_data(FILE *file, int dim, int len, vector_t *data) {
	fprintf(file, "%d ", dim);
	fprintf(file, "%d\n", len);
	for(int i=0; i<len; i++) {
		for(int j=0; j<dim; j++)
			fprintf(file, "%f ", data[i][j]);
		fprintf(file, "\n");
	}	
}
/*
network_t network *read_model(FILE *file) {
	int N, M;
	fscanf(file, "%d", N);
	fscanf(file, "%d", M);
	
	vector_t *data = malloc((*len) * (*dim) * sizeof(PRECISION));
	for(int i=0; i<*len; i++)
		for(int j=0; j<*dim; j++)
			fscanf(file, "%f", &data[i][j]);
	return data;
}*/

void write_model(FILE *file, network_t network) {
	printf("%d %d %d\n", network.N, network.M, settings.DIM);
	for(int i=0; i<network.N; i++) {
		for(int j=0; j<network.M; j++) {
			for(int k=0; k<settings.DIM; k++) {
				//printf("%f ", );
			}
		}
	}
}

vector_t *gen_train_data_circle(PRECISION min_dist, PRECISION max_dist, int amount) {
	vector_t *data = vectors_allocate(amount);
	vector_t center = vector_allocate();
	vector_fill(center, 0);
	for(int i=0; i<amount; i++) {
		data[i] = malloc(settings.DIM*sizeof(PRECISION));
		PRECISION dist = 0;
		do {
			for(int j=0; j<settings.DIM; j++)
				data[i][j] = (rand()%(int)(1000*2*max_dist))/(PRECISION)1000;
			dist = vector_metric(data[i], center);
		} while (dist < min_dist && dist > max_dist);
        vector_print(data[i]);
	}
	return data;
}

vector_t *gen_train_data(PRECISION range, PRECISION offset, int amount) {
	vector_t *data = malloc(amount*sizeof(vector_t));
	for(int i=0; i<amount; i++) {
		data[i] = malloc(settings.DIM*sizeof(PRECISION));
		for(int j=0; j<settings.DIM; j++)
			data[i][j] = (abs(rand())%(int)(1000*range))/(PRECISION)1000 + offset;
		vector_print(data[i]);
	}
	return data;
}
// only 2D
vector_t *gen_train_data_square(PRECISION min_x, PRECISION max_x, PRECISION min_y, PRECISION max_y, int amount) {
    vector_t *data = vectors_allocate(amount);
    for(int i=0; i<amount; i++) {
        PRECISION rx = (rand()%(int)(1000*(max_x-min_x)))/(PRECISION)1000 + min_x;
        PRECISION ry = (rand()%(int)(1000*(max_y-min_y)))/(PRECISION)1000 + min_y;
        data[i][0] = rx;
        data[i][1] = ry;
        vector_print(data[i]);
    }
    return data;
}

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	
	settings.N = 10;
	settings.M = 10;
	settings.DIM = 2;
	settings.alpha = 0.001;
	settings.CLUSTER_ITER = 100;
	network_t *network = make_network();
	
	int neg_len = 400;
	int pos_len = 400;
	//vector_t *neg = gen_train_data_square(0, 5, pos_len);
	vector_t *neg = gen_train_data_square(0, 10, 0, 10, neg_len);//(0, 5, 5, 10, 100);
	//vector_t *neg = vectors_merge(gen_train_data_square(0, 5, neg_len/2), neg_len/2, gen_train_data_square(10, 15, neg_len/2), neg_len/2);
	puts("");
	vector_t *pos = gen_train_data_square(3, 8, 3, 8, pos_len);;
	
	puts("");
	fflush(stdout);
	
	init_network(network, neg_len, neg, pos_len, pos);
	
	PRECISION testvec[settings.DIM];
	
	int dim = 15;
	
	for(int i=0; i<dim; i++) {
		for(int j=0; j<dim; j++) {
			//for(int k=-5; k<dim; k++) {
				testvec[0] = i;
				testvec[1] = j;
				//testvec[2] = k;
				printf("%1.0f ", classify(network, testvec));
			//}
			//puts("");
		}
		puts("");
	}
}
