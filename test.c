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

vector_t *gen_train_data2(PRECISION range, PRECISION min_dist, PRECISION max_dist, int amount) {
	vector_t *data = malloc(amount*sizeof(vector_t));
	for(int i=0; i<amount; i++) {
		data[i] = malloc(settings.DIM*sizeof(PRECISION));
		PRECISION dist = 0;
		do {
			for(int j=0; j<settings.DIM; j++)
				data[i][j] = (abs(rand())%(int)(1000*max_dist))/(PRECISION)1000;
			dist = sqrt(vector_scalar_prod(data[i], data[i]));
		} while (dist >= min_dist && dist <= max_dist);
	}
	return data;
}

vector_t *gen_train_data(PRECISION range, PRECISION offset, int amount) {
	vector_t *data = malloc(amount*sizeof(vector_t));
	for(int i=0; i<amount; i++) {
		data[i] = malloc(settings.DIM*sizeof(PRECISION));
		for(int j=0; j<settings.DIM; j++)
			data[i][j] = (abs(rand())%(int)(1000*range))/(PRECISION)1000 + offset;
	}
	return data;
}

vector_t *gen_train_data3(PRECISION maxval, PRECISION minval, int amount) {
	vector_t *data = malloc(amount*sizeof(vector_t));
	for(int i=0; i<amount; i++) {
		data[i] = malloc(settings.DIM*sizeof(PRECISION));
		for(int j=0; j<settings.DIM; j++) {
			do {
				data[i][j] = (rand()%(int)(1000*maxval))/(PRECISION)1000;
			} while(fabs(data[i][j]) < minval);
		}
	}
	return data;
}

void test0() {
	settings.N = 5;
		settings.M = 5;
		settings.DIM = 3;
		settings.alpha = 0.001;
		network_t *network = make_network();
	
		int neg_len = 100;
		int pos_len = 100;
		vector_t *neg = gen_train_data(6, 0, neg_len);
		vector_t *pos = gen_train_data(6, 3, pos_len);
	
		init_network(network, neg_len, neg, pos_len, pos);
	
		PRECISION array[10];
	
		for(int i=0; i<10; i++) {
			for(int j=0; j<10; j++) {
				for(int k=0; k<10; k++) {
					array[0] = i;
					array[1] = j;
					array[2] = k;
					printf("%1.0f ", classify(network, array));
				}
				puts("");
			}
			puts("");
		}
}

void test1() {
	settings.N = 3;
	settings.M = 3;
	settings.DIM = 2;
	settings.alpha = 0.001;
	network_t *network = make_network();

	int neg_len = 5;
	int pos_len = 5;
	vector_t *neg = gen_train_data3(2, 0, neg_len);
	vector_t *pos = gen_train_data3(4, 2, pos_len);
	
	init_network(network, neg_len, neg, pos_len, pos);

	PRECISION array[10];

	for(int i=-5; i<5; i++) {
		for(int j=-5; j<5; j++) {
			array[0] = i;
			array[1] = j;
			printf("%1.0f ", classify(network, array));
		}
		puts("");
	}
}

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
	if(argc==1) {
		test0();
	} else {
		test1();
	}
}
