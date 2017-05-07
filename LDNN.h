#ifndef LDNN_H
#define LDNN_H

#include<math.h>

#include"config.h"
#include"vector.h"
#include"datamodel.h"

PRECISION halfspace(network_t *network, int i, int j, vector_t v);
PRECISION polytope(network_t *network, int i, vector_t testvec);
PRECISION classify(network_t *network, vector_t testvec);
void init_network(network_t *network, int neg_size, vector_t *neg, int pos_size, vector_t *pos);

#endif

