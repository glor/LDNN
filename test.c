#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"config.h"
#include"vector.h"
#include"LDNN.h"

vector_t *gen_train_data(PRECISION range, PRECISION offset, int amount) {
	vector_t *data = malloc(amount*sizeof(vector_t *));
	vector_t tmp = malloc(amount*settings.DIM*sizeof(PRECISION));
	for(int i=0; i<amount; i++) {
		data[i] = tmp;
		tmp += settings.DIM*sizeof(PRECISION);
		for(int j=0; j<settings.DIM; j++) {
			data[i][j] = (abs(rand())%(int)(range*1000))/(PRECISION)1000 + offset;
		}
	}
	return data;
}

int main(int argc, char *argv[]) {
	settings.N = 5;
	settings.M = 5;
	settings.DIM = 2;
	network_t *network = make_network();
	
	vector_t *neg = gen_train_data(10, 0, 1000);
	vector_t *pos = gen_train_data(10, 9, 1000);
	
	init_network(network, 1000, neg, 1000, pos);
	
	vector_t *test = gen_train_data(10, 5, 10);
	for(int i=0; i<10; i++)
		printf("%lf ", classify(network, test[i]));
}
