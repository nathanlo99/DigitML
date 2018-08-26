
#include <cstdlib>
#include <random>

// TODO valarray?
std::vector<double> operator-(
        const std::vector<double>& lhs,
        const std::vector<double>& rhs) {
    assert(lhs.size() == rhs.size(),
        "std::vector::operator-: Inconsistent size", 2);
    std::vector<double> result(lhs.size());
    for (unsigned int i = 0; i < lhs.size(); i++)
        result[i] = lhs[i] - rhs[i];
    return result;
}

NeuralNetwork::NeuralNetwork() {
    weights1 = weight_init(2.0, HIDDEN_SIZE, INPUT_SIZE + 1);
    weights2 = weight_init(2.0, OUTPUT_SIZE, HIDDEN_SIZE + 1);
}

// Performs one training iteration using the data in images and labels
void NeuralNetwork::train(
        const unsigned int iterations,
        const Matrix<unsigned char>& images,
        const Matrix<unsigned char>& labels) {
    // The learning rate
    const double alpha = 1.5;

    for (unsigned int i = 0; i < iterations; ++i) {
      // Initialize the gradient matrices to 0
      Matrix<double> gradient_1(weights1.rows(), weights1.cols(), 0.0);
      Matrix<double> gradient_2(weights2.rows(), weights2.cols(), 0.0);
      double cost = 0.0;


      // Perform one step of gradient descent
      compute_gradients_and_cost(images, labels, gradient_1, gradient_2, cost);

      printf("Cost after %d iteration(s): %f\n", i+1, cost);

      weights1 = weights1 - gradient_1 * alpha;
      weights2 = weights2 - gradient_2 * alpha;
    }
}

std::vector<double> vectorize_label(unsigned char label) {
    std::vector<double> result(10, 0.0);
    result[(unsigned int)label] = 1.0;
    return result;
}

std::vector<double> log(const std::vector<double>& vec) {
    std::vector<double> result(vec.size());
    for (unsigned int i = 0; i < result.size(); ++i) {
        // Currently not checking for log(0) errors, but it seems fine
        result[i] = log(vec[i]);
    }
    return result;
}
// Calculates the current cost and uses backpropagation to compute the gradients
void NeuralNetwork::compute_gradients_and_cost(
        const Matrix<unsigned char>& images,
        const Matrix<unsigned char>& labels,
        Matrix<double>& gradient_1,
        Matrix<double>& gradient_2,
        double& cost) {
    // The number of examples
    unsigned int m = images.rows();
    // The regularization parameter
    const double lambda = 1.0;

    for (unsigned int i = 0; i < m; ++i) {
        std::vector<double> first_layer(images[i].begin(), images[i].end());
        // The bias value
        first_layer.insert(first_layer.begin(), 1.0);

        std::vector<double> hidden_layer(HIDDEN_SIZE), last_layer(OUTPUT_SIZE);

        hidden_layer = feed_forward(first_layer, weights1);
        // The bias value
        hidden_layer.insert(hidden_layer.begin(), 1.0);

        last_layer = feed_forward(hidden_layer, weights2);

        const std::vector<double> vector_outcome = vectorize_label(labels[i][0]);

        const std::vector<double> ones(10, 1.0);
        const double first_part = ((Matrix<double>(vector_outcome) * (double)(-1)).transpose() * log(last_layer))[0];
        const double second_part = ((Matrix<double>(ones - vector_outcome)).transpose() * log(ones - last_layer))[0];
        // Octave code: cost += 1/m * (-vector_outcome' * log(last_layer) - (1 - vector_outcome)' * log(1 - last_layer));
        // unregularized part of the error for this training example
        cost += 1.0/m * (first_part - second_part);

        // Backpropagation
        const Matrix<double> d3(last_layer - vector_outcome);
        const std::vector<double> ones2(HIDDEN_SIZE + 1, 1);
        Matrix<double> d2((weights2.transpose() * d3).hadamard(Matrix<double>(hidden_layer)).hadamard(Matrix<double>(ones2 - hidden_layer)));

        gradient_2 += d3 * Matrix<double>(hidden_layer).transpose();

        // Remove the term in d2 corresponding to the bias node in the hidden layer
        std::vector<double> d2_vec(HIDDEN_SIZE);
        for (unsigned int i = 0; i < HIDDEN_SIZE; ++i) d2_vec[i] = d2[i+1][0];

        gradient_1 += Matrix<double>(d2_vec) * Matrix<double>(first_layer).transpose();
    }

    // Make copies of the weights matrices with the bias weights set to 0 so they're not regularized
    Matrix<double> temp_weights1(weights1);
    for (unsigned int i = 0; i < temp_weights1.rows(); ++i) {
      temp_weights1[i][0] = 0.0;
    }
    Matrix<double> temp_weights2(weights2);
    for (unsigned int i = 0; i < temp_weights2.rows(); ++i) {
      temp_weights2[i][0] = 0.0;
    }

    // Adjust the gradients
    gradient_1 = gradient_1 /((double)m) + temp_weights1*(lambda/m);
    gradient_2 = gradient_2 /((double)m) + temp_weights2*(lambda/m);

    // Regularize the cost
    double regularizationCost = 0.0;
    for (unsigned int i = 0; i < weights1.rows(); ++i) {
      // Don't regularize the bias terms
      for (unsigned int j = 1; j < weights1.cols(); ++j) {
        regularizationCost += weights1[i][j] * weights1[i][j];
      }
    }
    for (unsigned int i = 0; i < weights2.rows(); ++i) {
      // Don't regularize the bias terms
      for (unsigned int j = 1; j < weights2.cols(); ++j) {
        regularizationCost += weights2[i][j] * weights2[i][j];
      }
    }

    cost += lambda/(2*m) * regularizationCost;
}

inline std::vector<double> NeuralNetwork::feed_forward(
        const std::vector<double>& input,
        const Matrix<double>& weights) {
    return sigmoid(weights * input);
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
    std::vector<double> first_layer(e.data, e.data + INPUT_SIZE);
    // The bias value
    first_layer.insert(first_layer.begin(), 1.0);
    std::vector<double> hidden_layer(HIDDEN_SIZE), last_layer(OUTPUT_SIZE);

    hidden_layer = feed_forward(first_layer, weights1);
    // The bias value
    hidden_layer.insert(hidden_layer.begin(), 1.0);
    last_layer = feed_forward(hidden_layer, weights2);

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
