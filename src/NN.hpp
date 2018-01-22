
#ifndef NN_HPP
#define NN_HPP

#define INPUT_SIZE (28 * 28)
#define HIDDEN_SIZE 15
#define OUTPUT_SIZE 10

#include "../lib/matrix.h"
#include "dataset.hpp"
#include <cmath>

class NeuralNetwork {
    private:
        Matrix<double> weight1, weight2;
        Matrix<double> bias1, bias2;
        
        double sigmoid(double x);
        double sigmoid_prime(double x);

    public:
        NeuralNetwork();
        NeuralNetwork(const NeuralNetwork& rhs);
        virtual ~NeuralNetwork();

        unsigned int compute(Example e);
        // void train(Example e);
        
};

#include "NN.cpp"

#endif
