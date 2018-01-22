
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

//TODO move somewhere better?
unsigned int read_int(FILE* f) {
    static unsigned char buffer[4];
    fread(&buffer, 4, 1, f);
    return buffer[0] << 24 
         | buffer[1] << 16
         | buffer[2] << 8
         | buffer[3] << 0;
}

#define assert(something, msg, code) \
    do { \
    if (!(something)) { \
        fprintf(stderr, msg); \
        exit(code); \
    }} while (0)

Dataset::Dataset(const char* image_file_name, const char* label_file_name) {
    m_image_file = fopen(image_file_name, "rb");
    m_label_file = fopen(label_file_name, "rb");
    
    assert(m_image_file != NULL, "Image file could not be opened\n", 1);
    assert(m_label_file != NULL, "Label file could not be opened\n", 1);
    
    unsigned int image_magic_number = read_int(m_image_file),
                 label_magic_number = read_int(m_label_file);
    
    assert(image_magic_number == 0x00000803, 
            "Incorrect magic number in image file\n", 2);
    assert(label_magic_number == 0x00000801, 
            "Incorrect magic number in label file\n", 2);

    unsigned int num_images = read_int(m_image_file),
                 num_labels = read_int(m_label_file);
   
    assert(num_images == num_labels, "Number of examples do not match\n", 3);

    m_num_sets = num_images;
    m_cur_set = 0;
    
    unsigned int image_height = read_int(m_image_file),
                 image_width = read_int(m_image_file);

    assert(image_height == 28 && image_width == 28, "Images not 28x28!\n", 1);
}

Dataset::~Dataset() {
    fclose(m_image_file);
    fclose(m_label_file);
}

Example Dataset::get_next() {
    Example result;
    if (done()) return result;
    result.label = fgetc(m_label_file);
    assert(fread(&result.data, 28 * 28, 1, m_image_file) != 0,
            "Attempted to read past EOF\n", 2);
    m_cur_set++;
    return result;
}

bool Dataset::done() {
    return m_cur_set >= m_num_sets;
}
