
#include "dataset.hpp"

void debug(Example e) {
    static char* shades = " .:-=+*#%@";

    printf("Label: %d\n", e.label);
    for (unsigned int i = 0; i < 28; i++) {
        for (unsigned int j = 0; j < 28; j++) {
            printf("%c", shades[e.data[i][j] / 30]);
        }
        printf("\n");
    }
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
