
#include "dataset.hpp"
#include "NN.hpp"
#include "../lib/matrix.h"
#include <vector>
#include <iostream>

void debug(Example e) {
    static std::string shades = " .:-=+*#%@";

    printf("Label: %d", e.label);
    for (unsigned int i = 0; i < 28 * 28; i++) {
        if (i % 28 == 0) printf("\n");
        printf("%c", shades[e.data[i] / 30]);
    }
    printf("\n");
}

std::vector<double> load_matrix(Example& e) {
    std::vector<double> result(e.data, e.data + 28 * 28);
    return result;
}

int main() {
    Dataset test("data/t10k-images-idx3-ubyte", "data/t10k-labels-idx1-ubyte");
    Dataset train("data/train-images-idx3-ubyte", "data/train-labels-idx1-ubyte");
	
	std::vector<std::vector<double> > nodes;
    int counter = 0;
    while (!train.done()) {
        Example e = train.get_next();
		nodes.push_back(load_matrix(e));
        // debug(e);
        counter++;
        // if (counter == 10) break;
    }
    printf("%d\n", counter);
    return 0;
}
