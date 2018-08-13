
#include "dataset.hpp"
#include "NN.hpp"
#include "../lib/matrix.h"
#include <vector>
#include <iostream>

void debug(Example e) {
    static std::string shades = " .:-=+*#%@";
    for (unsigned int i = 0; i < 28 * 28; i++) {
        if (i % 28 == 0) printf("\n");
        printf("%c", shades[e.data[i] / 30]);
    }
    printf("\nLabel: %d\n", e.label);
}

std::vector<double> load_matrix(Example& e) {
    std::vector<double> result(e.data, e.data + 28 * 28);
    return result;
}

int main() {
    Matrix<unsigned char> images_train = Matrix<unsigned char>(0, 0);
    Matrix<unsigned char> lables_train = Matrix<unsigned char>(0, 0);
    load_dataset(images_train, lables_train, "data/train-images-idx3-ubyte", "data/train-labels-idx1-ubyte");

    Matrix<unsigned char> images_test = Matrix<unsigned char>(0, 0);
    Matrix<unsigned char> lables_test = Matrix<unsigned char>(0, 0);
    load_dataset(images_test, lables_test, "data/t10k-images-idx3-ubyte", "data/t10k-labels-idx1-ubyte");

    NeuralNetwork n;

    // Tests to see that data was read in properly
    for (int i = 0; i < 10; ++i) {
        Example e;
        for (int j = 0; j < 28*28; ++j) {
            e.data[j] = images_train[i][j];
        }
        e.label = lables_train[i][0];
        debug(e);
        printf("Guess: %d\n", n.compute(e));
    }
    for (int i = 0; i < 10; ++i) {
        Example e;
        for (int j = 0; j < 28*28; ++j) {
            e.data[j] = images_test[i][j];
        }
        e.label = lables_test[i][0];
        debug(e);
        printf("Guess: %d\n", n.compute(e));
    }
    return 0;
}
