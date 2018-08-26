
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cstdint>

// TODO optimize possibly with valarrays instead?
// TODO make everything const correct?

template <typename T> class Matrix {
    private:
        std::vector<std::vector<T> > m_data;
        unsigned int m_cols, m_rows;
    public:
        // Standard constructor
        Matrix(unsigned int rows, unsigned int cols);
        // Standard constructor with initialization value
        Matrix(const unsigned int rows, const unsigned int cols, const double init_val);
        // Copy constructor
        Matrix(const Matrix<T>& rhs);
        // Column vector copy constructor
        Matrix(const std::vector<T>& rhs);
        // Destructor
        virtual ~Matrix();

        // Standard mathematical operations
        Matrix<T>& operator=(const Matrix<T>& rhs);

        Matrix<T> operator+(const Matrix<T>& rhs) const;
        Matrix<T>& operator+=(const Matrix<T>& rhs);
        Matrix<T> operator-(const Matrix<T>& rhs) const;
        Matrix<T>& operator-=(const Matrix<T>& rhs);
        Matrix<T> operator*(const Matrix<T>& rhs) const;
        Matrix<T>& operator*=(const Matrix<T>& rhs);
        Matrix<T> transpose() const;

        Matrix<T> operator+(const T& rhs) const;
        Matrix<T> operator-(const T& rhs) const;
        Matrix<T> operator*(const T& rhs) const;
        Matrix<T> operator/(const T& rhs) const;

        Matrix<T> hadamard(const Matrix<T>& rhs) const;
        Matrix<T> kronecker(const Matrix<T>& rhs) const;
        Matrix<T> concat(const Matrix<T>& rhs) const;

        std::vector<T> operator*(const std::vector<T>& rhs) const;
        std::vector<T> diag_vec();

        // Included this so users can do m[0][0] rather than m(0, 0)
        std::vector<T>& operator[] (const unsigned int x);
        const std::vector<T>& operator[] (const unsigned int x) const;

        unsigned int rows() const;
        unsigned int cols() const;

        // DEBUG
        void debug() const;
};

#include "matrix.cpp"
#endif
