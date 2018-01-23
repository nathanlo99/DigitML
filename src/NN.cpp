
NeuralNetwork::NeuralNetwork() {
    // TODO
}

Matrix<double> NeuralNetwork::feedForward(Matrix<double> input, Matrix<double> weights, Matrix<double> bias){
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

unsigned int NeuralNetwork::compute(Matrix<double> firstLayer) {
    Matrix<double> hiddenLayer(HIDDEN_SIZE, 1), lastLayer(OUTPUT_SIZE, 1);
    hiddenLayer = feedForward(firstLayer, weights1, bias1);
    lastLayer = feedForward(hiddenLayer, weights2, bias2);

    int maxValIndex = 0;
    for (int i = 1; i < 10; i++) {
	if (lastLayer[0][i] > lastLayer[0][maxValIndex])
	    maxValIndex = i;
    }
    return maxValIndex;
} 

// TODO parallelize
Matrix<double> NeuralNetwork::sigmoid(Matrix<double> x) {
    Matrix<double> result(x.rows(), x.cols());
    for (unsigned int i = 0; i < result.rows(); i++)
        for (unsigned int j = 0; j < result.cols(); j++)
            result[i][j] = 1 / (exp(-x[i][j]) + 1);
    return result;
}

Matrix<double> NeuralNetwork::sigmoid_prime(Matrix<double> x) {
    Matrix<double> result(x.rows(), x.cols());
    for (unsigned int i = 0; i < result.rows(); i++)
        for (unsigned int j = 0; j < result.cols(); j++) {
            const double t = exp(x[i][j]);
            result[i][j] = t / ((1 + t) * (1 + t));
        }
    return result;
}

