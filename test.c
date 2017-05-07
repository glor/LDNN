#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"config.h"
#include"vector.h"
#include"LDNN.h"

vector_t *gen_train_data(PRECISION range, PRECISION offset, int amount) {
	vector_t *data = malloc(amount*sizeof(vector_t));
	for(int i=0; i<amount; i++) {
		data[i] = malloc(settings.DIM*sizeof(PRECISION));
		for(int j=0; j<settings.DIM; j++)
			data[i][j] = (abs(rand())%(int)(1000*range))/(PRECISION)1000 + offset;
	}
	return data;
}

int main(int argc, char *argv[]) {
	settings.N = 5;
	settings.M = 5;
	settings.DIM = 2;
	network_t *network = make_network();
	
	vector_t *test2 = gen_train_data(10, 5, 10);
	int neg_len = 1000;
	int pos_len = 1000;
	vector_t *neg = gen_train_data(10, 0, neg_len);
	vector_t *pos = gen_train_data(10, 5, pos_len);
	
	init_network(network, neg_len, neg, pos_len, pos);
	
	vector_t *test = gen_train_data(10, 5, 10);
	PRECISION x, y;
	float array[2];
	while(scanf("%f %f", &array[0], &array[1])==2) {
		printf("%lf\n", classify(network, array));
	}
	//for(int i=0; i<10; i++)
	//	printf("%lf ", classify(network, test[i]));
	
	for(int i=0; i<20; i++) {
		for(int j=0; j<20; j++) {
			array[0] = i;
			array[1] = j;
			printf("%1.0f ", classify(network, array));
		}
		puts("");
	}
}
