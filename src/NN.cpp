
#include <cstdlib>
#include <random>

// TODO valarray?
std::vector<double> operator-(
        const std::vector<double>& lhs, 
        const std::vector<double>& rhs) {
    std::vector<double> result(lhs.size());
    for (unsigned int i = 0; i < lhs.size(); i++)
        result[i] = lhs[i] - rhs[i];
    return result;
}

NeuralNetwork::NeuralNetwork() {
    weights1 = weightInit(2.0, HIDDEN_SIZE, INPUT_SIZE);
    weights2 = weightInit(2.0, OUTPUT_SIZE, HIDDEN_SIZE);
}

inline std::vector<double> NeuralNetwork::feed_forward(
        const std::vector<double>& input, 
        const Matrix<double>& weights, 
        const std::vector<double>& bias) {
    return sigmoid(weights * input - bias);
}

Matrix<double> NeuralNetwork::weight_init(double maxWeight, unsigned int rows, unsigned int cols){
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> dist(-maxWeight, maxWeight);

    Matrix<double> weights(rows, cols);
    for (int i = 0; i < weights.rows(); i++)
	for (int j = 0; j < weights.cols(); j++)
	    weights[i][j] = dist(e2); 
    
    return weights;
}

unsigned int NeuralNetwork::compute(const Example& e) {
    std::vector<unsigned int> first_layer_bytes(e.data, e.data + INPUT_SIZE);
    std::vector<double> first_layer(INPUT_SIZE);
    for (unsigned int i = 0; i < INPUT_SIZE; i++)
        first_layer[i] = first_layer_bytes[i] / 255.0;

    std::vector<double> hidden_layer(HIDDEN_SIZE), last_layer(OUTPUT_SIZE);

    hidden_layer = feed_forward(first_layer, weights1, bias1);
    last_layer = feed_forward(hidden_layer, weights2, bias2);

    unsigned int max_val_index = 0;
    for (int i = 1; i < 10; i++) {
	if (last_layer[i] > last_layer[max_val_index])
	    max_val_index = i;
    }
    return max_val_index;
} 

// TODO parallelize (now its really easy to valarray)
std::vector<double> NeuralNetwork::sigmoid(const std::vector<double>& x) {
    std::vector<double> result(x.size());
    for (unsigned int i = 0; i < x.size(); i++)
        result[i] = 1 / (1 + exp(-x[i]));
    return result;
}

std::vector<double> NeuralNetwork::sigmoid_prime(const std::vector<double>& x) {
    std::vector<double> result(x.size());
    for (unsigned int i = 0; i < result.size(); i++) {
        const double t = exp(x[i]);
        result[i] = t / ((1 + t) * (1 + t));
    }
    return result;
}

