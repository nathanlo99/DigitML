
#include "dataset.hpp"
#include "NN.hpp"

void debug(Example e) {
    static char* shades = " .:-=+*#%@";

    printf("Label: %d", e.label);
    for (unsigned int i = 0; i < 28 * 28; i++) {
        if (i % 28 == 0) printf("\n");
        printf("%c", shades[e.data[i] / 30]);
    }
    printf("\n");
}

int main() {
    Dataset test("data/t10k-images-idx3-ubyte", "data/t10k-labels-idx1-ubyte");
    Dataset train("data/train-images-idx3-ubyte", "data/train-labels-idx1-ubyte");
    
    int counter;
    while (!train.done()) {
        Example e = train.get_next();
        debug(e);
        counter++;
    }
    printf("%d\n", counter);
    return 0;
}
