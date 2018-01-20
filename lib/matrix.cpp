
#ifdef DEBUG
void warn(const char* func, const char* message) {
    printf("[WARNING]: (%s): %s (you've been warned)\n", func, message);
}
#else
void warn(const char* func, const char* message) {}
#endif

// Standard constructor
template<typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols): 
    m_rows(rows), m_cols(cols) {
    m_data.resize(rows);
    for (unsigned int i = 0; i < rows; i++) 
        m_data[i].resize(cols);
}

// Copy constructor
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs):
    m_data(rhs.m_data), m_rows(rhs.m_rows), m_cols(rhs.m_cols)
{ /* initialization list suffices */ }

// Destructor
template<typename T>
Matrix<T>::~Matrix() { /* virtual */ }


// Assignment operator
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
    if (&rhs == this) 
        return *this;
    
    unsigned int new_rows = rhs.rows(), new_cols = rhs.cols();
    
    m_data.resize(new_rows);
    for (unsigned int i = 0; i < new_rows; i++) {
        m_data.resize(new_cols);
    }   

    for (unsigned int i = 0; i < new_rows; i++) {
        for (unsigned int j = 0; j < new_cols; j++) {
            m_data[i][j] = rhs[i][j];
        }
    }

    m_rows = new_rows, m_cols = new_cols;
    return *this;
}

// Start mathematical operations
// TODO: Most of these operations are embarassingly parallel
//       BUT most of these can be parallelized using valarrays

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) {
    if (m_rows != rhs.m_rows)
        warn("Matrix::operator+", "Inconsistent number of rows");
    if (m_cols != rhs.m_cols)
        warn("Matrix::operator+", "Inconsistent number of cols");
    
    Matrix result(m_rows, m_cols);
    
    for (unsigned int i = 0; i < m_rows; i++)
        for (unsigned int j = 0; j < m_cols; j++)
            result[i][j] = m_data[i][j] + rhs[i][j];
        
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
    if (m_rows != rhs.m_rows)
        warn("Matrix::operator+", "Inconsistent number of rows");
    if (m_cols != rhs.m_cols)
        warn("Matrix::operator+", "Inconsistent number of cols");

    for (unsigned int i = 0; i < m_rows; i++)
        for (unsigned int j = 0; j < m_cols; j++)
            m_data[i][j] += rhs[i][j];
        
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) {
    if (m_rows != rhs.m_rows)
        warn("Matrix::operator-", "Inconsistent number of rows");
    if (m_cols != rhs.m_cols)
        warn("Matrix::operator-", "Inconsistent number of cols");
    
    Matrix<T> result(m_rows, m_cols);
    
    for (unsigned int i = 0; i < m_rows; i++)
        for (unsigned int j = 0; j < m_cols; j++)
            result[i][j] = m_data[i][j] - rhs[i][j];
        
    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
    if (m_rows != rhs.m_rows)
        warn("Matrix::operator-", "Inconsistent number of rows");
    if (m_cols != rhs.m_cols)
        warn("Matrix::operator-", "Inconsistent number of cols");

    for (unsigned int i = 0; i < m_rows; i++)
        for (unsigned int j = 0; j < m_cols; j++)
            m_data[i][j] -= rhs[i][j];
        
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) {
    if (m_cols != rhs.m_rows)
        warn("Matrix::operator*", "Multiplying these won't work");

    Matrix<T> result(m_rows, rhs.m_cols);

    for (unsigned int i = 0; i < m_rows; i++) {
        for (unsigned int j = 0;  j < rhs.m_cols; j++) {
            T sum = 0.0;
            for (unsigned int k = 0; k < m_cols; k++) {
                sum += m_data[i][k] * rhs.m_data[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
    Matrix<T> result = *this * rhs;
    *this = result;
    return *this;
}

// TODO check loop order for cache locality??
template<typename T>
Matrix<T> Matrix<T>::transpose() {
    Matrix<T> result(m_cols, m_rows);
    for (int i = 0; i < m_cols; i++) {
        for (int j = 0; j < m_rows; j++) {
            result[i][j] = m_data[j][i];
        }
    }
}

// Scalar operations
#define do_op(op) \
template<typename T> \
Matrix<T> Matrix<T>::operator op (const T& rhs) { \
    Matrix<T> result(m_rows, m_cols); \
    for (int i = 0; i < m_rows; i++) \
        for (int j = 0; j < m_cols; j++) \
            result[i][j] = m_data[i][j] op rhs; \
    return result; \
}
do_op(+);
do_op(-);
do_op(*);
do_op(/);
#undef do_op

template<typename T>
Matrix<T> Matrix<T>::hadamard(const Matrix<T>& rhs) {
    if (m_rows != rhs.m_rows)
        warn("Matrix::hadamard", "Number of rows don't match up");
    if (m_cols != rhs.m_cols)
        warn("Matrix::hadamard", "Number of cols don't match up");

    Matrix<T> result(m_rows, m_cols);
    for (unsigned int i = 0; i < m_rows; i++) 
        for (unsigned int j = 0; j < m_cols; j++)
            result[i][j] = m_data[i][j] * rhs[i][j];

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::kronecker(const Matrix<T>& rhs) {
    if (m_rows != 1 || rhs.m_cols != 1)
        warn("Matrix::kronecker", "Arbitrary matrix kronecker not yet implemented");
    
    Matrix<T> result(m_cols, rhs.m_rows);
    for (unsigned int i = 0; i < m_cols; i++)
        for (unsigned int j = 0; j < rhs.m_rows; j++)
            result[i][j] = m_data[0][i] * rhs[j][0];

    return result;
}

template<typename T>
Matrix<T> Matrix<T>::concat(const Matrix<T>& rhs) {
    if (m_rows != rhs.m_rows)
        warn("Matrix::concat", "Number of rows doesn't match up");

    Matrix<T> result(m_rows, m_cols + rhs.m_cols);
    for (unsigned int i = 0; i < m_rows; i++) {
        for (unsigned int j = 0, n = m_cols + rhs.m_cols; j < n; j++) {
            if (j < m_cols)
                result[i][j] = m_data[i][j];
            else
                result[i][j] = rhs[i][j - m_cols];
        }
    }
    return result;
}

// Accessors
template<typename T>
std::vector<T>& Matrix<T>::operator[] (const unsigned int x) {
    return m_data[x];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[] (const unsigned int x) const
{
    return m_data[x];
}

template<typename T>
void Matrix<T>::debug() const {
    for (unsigned int i = 0; i < m_rows; i++) {
        for (unsigned int j = 0; j < m_cols; j++) {
            printf("%3.3lf ", m_data[i][j]);
        }
        printf("\n");
    }
}

template<typename T>
unsigned int Matrix<T>::rows() const { return m_rows; }

template<typename T>
unsigned int Matrix<T>::cols() const { return m_cols; }
