
/* TRAINING SET LABEL FILE (train-labels-idx1-ubyte):

[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000801(2049) magic number (MSB first)
0004     32 bit integer  60000            number of items
0008     unsigned byte   ??               label
0009     unsigned byte   ??               label
........
xxxx     unsigned byte   ??               label
The labels values are 0 to 9.

TRAINING SET IMAGE FILE (train-images-idx3-ubyte):

[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000803(2051) magic number
0004     32 bit integer  60000            number of images
0008     32 bit integer  28               number of rows
0012     32 bit integer  28               number of columns
0016     unsigned byte   ??               pixel
0017     unsigned byte   ??               pixel
........
xxxx     unsigned byte   ??               pixel
Pixels are organized row-wise. Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black).

source: http://yann.lecun.com/exdb/mnist/
*/

#define assert(something, msg, code) \
    do { \
    if (!(something)) { \
        fprintf(stderr, msg); \
        exit(code); \
    }} while (0)

// Load all of the data from the image and label files into data and labels
void load_data(
        Matrix<unsigned char>& images,
        Matrix<unsigned char>& labels,
        FILE *image_file,
        FILE *label_file,
        unsigned int num_images) {
    for (unsigned int i = 0; i < num_images; ++i) {
        unsigned char image_data[28 * 28];
        unsigned char label;

        label = fgetc(label_file);
        assert(fread(&image_data, 1, 28 * 28, image_file) == 28 * 28,
                "Attempted to read past EOF\n", 2);

        labels[i][0] = label;
        for (unsigned int j = 0; j < 28*28; ++j) {
            images[i][j] = image_data[j];
        }
    }
}

//TODO move somewhere better?
unsigned int read_int(FILE* f) {
	static unsigned char buffer[4];
    fread(&buffer, 1, 4, f);
	//bitshift in direction of most significant bit to convert little endian to big endian
    return buffer[3] << 0
         | buffer[2] << 8
         | buffer[1] << 16
         | buffer[0] << 24;
}

void load_dataset(
        Matrix<unsigned char>& images,
        Matrix<unsigned char>& labels,
        const char *image_file_name,
        const char *label_file_name) {
    // Prepare the files and variables
    FILE *image_file = fopen(image_file_name, "rb"),
         *label_file = fopen(label_file_name, "rb");

    assert(image_file != NULL, "Image file could not be opened\n", 1);
    assert(label_file != NULL, "Label file could not be opened\n", 1);

    unsigned int image_magic_number = read_int(image_file),
                 label_magic_number = read_int(label_file);

    assert(image_magic_number == 0x00000803,
            "Incorrect magic number in image file\n", 2);
    assert(label_magic_number == 0x00000801,
            "Incorrect magic number in label file\n", 2);

    unsigned int num_images = read_int(image_file),
                 num_labels = read_int(label_file);

    assert(num_images == num_labels, "Number of examples do not match\n", 3);

    unsigned int image_height = read_int(image_file),
                 image_width = read_int(image_file);

    assert(image_height == 28 && image_width == 28, "Images not 28x28!\n", 1);

    images = Matrix<unsigned char>(num_images, 28*28);
    labels = Matrix<unsigned char>(num_images, 1);

    // Read in the actual data
    load_data(images, labels, image_file, label_file, num_images);

    fclose(image_file);
    fclose(label_file);
}
