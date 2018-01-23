
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
        std::vector<double> bias1 = std::vector<double>(HIDDEN_SIZE), 
                       bias2 = std::vector<double>(OUTPUT_SIZE);
        

        std::vector<double> sigmoid(const std::vector<double>& x);
        std::vector<double> sigmoid_prime(const std::vector<double>& x);
		
	Matrix<double> weightInit(double maxWeight, unsigned int width, unsigned int height);	

        std::vector<double> feedForward(
                const std::vector<double>& input, 
                const Matrix<double>& weights, 
                const std::vector<double>& bias);

    public:
        NeuralNetwork();
        NeuralNetwork(const NeuralNetwork& rhs) = default;
        virtual ~NeuralNetwork() = default;
        
        unsigned int compute(const Example& e);
        // void train(Example e);
        
};

#include "NN.cpp"

#endif
