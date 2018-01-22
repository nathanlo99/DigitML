

double NeuralNetwork::sigmoid(double x) {
    return 1 / (exp(-x) + 1);
}

double NeuralNetwork::sigmoid_prime(double x) {
    const double t = exp(x);
    return t / ((1 + t) * (1 + t));
}

Matrix<unsigned char> NeuralNetwork::feedForward(Matrix<double> input, Matrix<double> weights, Matrix<double> bias){
	Matrix<double> result = weights * input;
	for (int i = 0; i < result.rows(); i++) {
		result[i][0] = sigmoid(result[i][0] - bias[i]);
	}
	return result;
}

unsigned int NeuralNetwork::compute(Matrix<double> firstLayer) {
	Matrix<double> hiddenLayer(HIDDEN_SIZE, 1), lastLayer(OUTPUT_SIZE, 1);
	hiddenLayer = feedForward(firstLayer, firstWeights, firstBias);
	lastLayer = feedForward(hiddenLayer, secondWeights, secondBias);

	int maxValIndex = 0;
	for (int i = 1; i < 10; i++) {
		if (lastLayer[i][0] > lastLayer[maxValIndex][0])
			maxValIndex = i;
	}
	return maxValIndex;
} 
