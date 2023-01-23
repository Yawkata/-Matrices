#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

class Matrix
{
public:
    int rows, cols;
    double **p;

    // allocate space for the actual matrix
    void allocSpace();

    // default constructor
    Matrix();

    // construct matrix from given number of rows and columns
    Matrix(int rows, int cols);

    // contruct a matrix from a given matrix
    Matrix(const Matrix &m);

    // destructor
    ~Matrix();

    // return a flipped version of the given matrix
    Matrix transpose();

    // operator = for matrixs
    Matrix &operator=(const Matrix &m);

    // subtract the gicen matrix
    Matrix &operator-=(const Matrix &m);

    // multiply every row by given matrix
    void dotProductOfRowns(const Matrix &m);

    // divide every row by given matrix
    void divisionOfRowns(const Matrix &m);

    // add a column to the given matrix
    Matrix addColumn(Matrix &clmn);

    // get a matrix representing the sum of every row in a matrix
    Matrix sumOfRows();

    // add rowToBeAdded multiplyed by multiplier to rowToAddTo
    void addRowToRow(int rowToBeAdded, int rowToAddTo, double multiplier);

    // solve an equation with one unknown the equation is defined by the given row of the matrix
    // and it is solved for the number corresponding to the given row and column
    double solveRow(int row, int solveFor);

    //simplifies the matrix using the Gaussian method
    Matrix GaussianMethod();
};

// operator for printing the matrix
inline ostream &operator<<(std::ostream &out, Matrix &m)
{
    for (int i = 0; i < m.rows; ++i)
    {
        out << m.p[i][0];
        for (int j = 1; j < m.cols; ++j)
        {
            out << " " << m.p[i][j];
        }
        out << endl;
    }
    return out;
}

// operator for subtracting two matrices
Matrix operator-(const Matrix &m1, const Matrix &m2);

#endif