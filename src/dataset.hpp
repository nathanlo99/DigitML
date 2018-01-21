
#ifndef DATASET_HPP
#define DATASET_HPP

#include <cstdio>
#include <cstdlib>

// This class is specifically tuned to load the MNIST database of handwritten
// digits (http://yann.lecun.com/exdb/mnist/)

// A single instance of a training / testing example, a 28 x 28 grayscale 
// image, and its corresponding (correct) label.
typedef struct {
    unsigned char data[28][28];
    unsigned int label;
} Example;

// Loads the training and test data from MNIST files, stream-like
// implementation to save memory
class Dataset {
    private:
        char *m_image_file_name, *m_label_file_name;
        FILE *m_image_file, *m_label_file;
        unsigned int m_num_sets, m_cur_set;

    public:
        Dataset(const char* image_file_name, const char* label_file_name);
        Dataset(const Dataset& rhs);
        virtual ~Dataset();
        
        Example get_next();
        bool done();
};

#include "dataset.cpp"

#endif
