
#ifndef DATASET_HPP
#define DATASET_HPP

#include <cstdio>
#include <cstdlib>
#include "../lib/matrix.h"

// A single instance of a training / testing example, a 28 x 28 grayscale
// image, and its corresponding (correct) label.
typedef struct {
    unsigned char data[28 * 28];
    unsigned char label;
} Example;

// This function is specifically tuned to load the MNIST database of handwritten
// digits (http://yann.lecun.com/exdb/mnist/)
void load_dataset(
        Matrix<unsigned char>& images,
        Matrix<unsigned char>& labels,
        const char *image_file_name,
        const char *label_file_name);

#include "dataset.cpp"

#endif
