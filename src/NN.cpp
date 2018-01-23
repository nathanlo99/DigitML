
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
    // TODO
}

inline std::vector<double> NeuralNetwork::feedForward(
        const std::vector<double>& input, 
        const Matrix<double>& weights, 
        const std::vector<double>& bias){
    return sigmoid(weights * input - bias);
}

Matrix<double> NeuralNetwork::weightInit(double maxWeight, unsigned int width, unsigned int height){
	Matrix<double> weights(width, height);
	for (int i = 0; i < weights.rows(); i++) {
		for (int j = 0; j < weights.cols(); j++) {
			//weights[i][j] = rand()
		}
	}
}

unsigned int NeuralNetwork::compute(const Example& e) {
    std::vector<unsigned int> firstLayerBytes(e.data, e.data + INPUT_SIZE);
    std::vector<double> firstLayer(INPUT_SIZE);
    for (unsigned int i = 0; i < INPUT_SIZE; i++)
        firstLayer[i] = firstLayerBytes[i] / 255.0;

    std::vector<double> hiddenLayer(HIDDEN_SIZE), lastLayer(OUTPUT_SIZE);

    hiddenLayer = feedForward(firstLayer, weights1, bias1);
    lastLayer = feedForward(hiddenLayer, weights2, bias2);

    unsigned int maxValIndex = 0;
    for (int i = 1; i < 10; i++) {
	if (lastLayer[i] > lastLayer[maxValIndex])
	    maxValIndex = i;
    }
    return maxValIndex;
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

