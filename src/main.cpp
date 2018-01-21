
#include "dataset.hpp"

int main() {
    Dataset test("../data/t10k-images-idx3-ubyte", "../data/t10k-labels-idx1-ubyte");
    Dataset train("../data/train-images-idx3-ubyte", "../data/train-labels-idx1-ubyte");

    int counter;
    while (!train.done()) {
        Example e = train.get_next();
        counter++;
    }
    printf("%d\n", counter);
    return 0;
}
