
NeuralNetwork::NeuralNetwork():
    weights1: Matrix<double>(784, 15),
    weights2: Matrix<double>(15, 10) {

}

double NeuralNetwork::sigmoid(double x) {
    return 1 / (exp(-x) + 1);
}

double NeuralNetwork::sigmoid_prime(double x) {
    const double t = exp(x);
    return t / ((1 + t) * (1 + t));
}

unsigned int NeuralNetwork::compute(Example e) {
    // TODO
}
