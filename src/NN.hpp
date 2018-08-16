
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

        std::vector<double> sigmoid(const std::vector<double>& x);
        std::vector<double> sigmoid_prime(const std::vector<double>& x);

		Matrix<double> weight_init(double max_weight, unsigned int width, unsigned int height);

        std::vector<double> feed_forward(
                const std::vector<double>& input,
                const Matrix<double>& weights);

    public:
        NeuralNetwork();
        NeuralNetwork(const NeuralNetwork& rhs) = default;
        virtual ~NeuralNetwork() = default;

        void train(
                const unsigned int iterations,
                const Matrix<unsigned char>& images,
                const Matrix<unsigned char>& labels);
        void compute_gradients_and_cost(
                const Matrix<unsigned char>& images,
                const Matrix<unsigned char>& labels,
                Matrix<double>& gradient_1,
                Matrix<double>& gradient_2,
                double& cost);
        unsigned int compute(const Example& e);
};

#include "NN.cpp"

#endif
