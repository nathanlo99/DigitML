
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
        Matrix<double> weights1 = Matrix<double>(HIDDEN_SIZE, INPUT_SIZE),
                       weights2 = Matrix<double>(OUTPUT_SIZE, HIDDEN_SIZE);
        Matrix<double> bias1 = Matrix<double>(HIDDEN_SIZE, 1), 
                       bias2 = Matrix<double>(OUTPUT_SIZE, 1);
        
        Matrix<double> sigmoid(Matrix<double> x);
        Matrix<double> sigmoid_prime(Matrix<double> x);
	
        unsigned int compute(Matrix<double> firstLayer);

	Matrix<double> feedForward(Matrix<double> input, 
                Matrix<double> weights, 
                Matrix<double> bias);

    public:
        NeuralNetwork();
        NeuralNetwork(const NeuralNetwork& rhs) = default;
        virtual ~NeuralNetwork() = default;
        
        unsigned int compute(Example e);
        // void train(Example e);
        
};

#include "NN.cpp"

#endif
