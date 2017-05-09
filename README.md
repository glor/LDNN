# Logistic Disjunctive Normal Network (LDNN)
This is an implementation of Logistic Disjunctive Neural Networks as proposed in the paper listed under References.

## Implementation State
### Basic Functionality
- [x] data structures
- [ ] read and write files
- [x] initialize
- [x] evaluate/classify
- [x] gradient decendent learning
- [ ] (optional) convolutional network
### Optimization
- [ ] optimize memory
- [ ] parallelize initialization
- [ ] parallelize gradient decent learning
- [ ] parallelize classification (only preferable on very big networks)

## How to use
run `make` to build.  
run `make test` to run a simple test.  
`test.c` shows how to create, initialize, train und evaluate a LDNN.

## References
M. Sajjadi, M. Seyedhosseini, T. Tasdizen "Disjunctive Normal Networks" arXiv:1412.8534 [cs.LG] (2014) http://arxiv.org/abs/1412.8534

