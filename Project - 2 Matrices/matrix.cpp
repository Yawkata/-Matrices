#include "matrix.h"

// allocate space for the actual matrix
void Matrix::allocSpace()
{
    p = new double *[rows];
    for (int i = 0; i < rows; ++i)
    {
        p[i] = new double[cols];
    }
}

// default constructor
Matrix::Matrix() : rows(1), cols(1)
{
    allocSpace();
    p[0][0] = 0;
}

// constructor from rows and columns
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    allocSpace();
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            p[i][j] = 0;
        }
    }
}

// constructor from а given matrix
Matrix::Matrix(const Matrix &m) : rows(m.rows), cols(m.cols)
{
    allocSpace();
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            p[i][j] = m.p[i][j];
        }
    }
}

// destructor
Matrix::~Matrix()
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] p[i];
    }
    delete[] p;
}

// return a flipped version of the given matrix
Matrix Matrix::transpose()
{
    Matrix ret(cols, rows);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            ret.p[j][i] = p[i][j];
        }
    }
    return ret;
}

// operator = for matrixs
Matrix& Matrix::operator=(const Matrix &m)
{
    if (this == &m)
    {
        return *this;
    }

    // deleting the matrix if number of rows and columns does not match 
    if (rows != m.rows || cols != m.cols)
    {
        for (int i = 0; i < rows; ++i)
        {
            delete[] p[i];
        }
        delete[] p;

        // making new matrix;
        rows = m.rows;
        cols = m.cols;
        allocSpace();
    }
    
    // filling the matrix
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}

// subtract the gicen matrix
Matrix& Matrix::operator-=(const Matrix &m)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}

// multiply every row by given matrix with one row and columns coresponding the original one's
void Matrix::dotProductOfRowns(const Matrix &m)
{

    if (m.cols != cols || m.rows != 1)
        return;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            p[i][j] *= m.p[0][j];
        }
    }
}

// divide every row by given matrix
void Matrix::divisionOfRowns(const Matrix &m)
{

    if (m.cols != cols || m.rows != 1)
        return;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            p[i][j] /= m.p[0][j];
        }
    }
}

// add a column to the given matrix (it should work with more than one column too)
Matrix Matrix::addColumn(Matrix &clmn)
{
    // checking if the number of rows of the two matrices match
    if (clmn.rows != rows)
        throw invalid_argument("Can not add column with different number of rows");

    // allocating the new matrix
    Matrix newM = Matrix(rows, cols + clmn.cols);

    // filling the old values
    int i = 0;
    int j = 0;
    for (; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            newM.p[i][j] = p[i][j];
        }
    }

    // adding the new columns
    int newClmnIndex = 0;
    for (i = 0; i < newM.rows; ++i)
    {

        for (int k = j, newClmnIndex = 0; k < newM.cols; ++k, ++newClmnIndex)
        {
            newM.p[i][k] = clmn.p[i][newClmnIndex];
        }
    }

    return newM;
}

// get a matrix representing the sum of every row in a matrix
Matrix Matrix::sumOfRows()
{
    Matrix m = Matrix(1, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            m.p[0][i] += p[i][j];
        }
    }

    return m;
}

// add (rowToBeAdded multiplyed by multiplier) to rowToAddTo; 
// the function is adding a row to another one and the first row is multiplied by given number
void Matrix::addRowToRow(int rowToBeAdded, int rowToAddTo, double multiplier)
{
    for (int j = 0; j < cols; ++j)
        p[rowToAddTo][j] += (p[rowToBeAdded][j] * multiplier);

    p[rowToAddTo][rowToBeAdded] = 0;
}

// solve an equation with one unknown
double Matrix::solveRow(int row, int solveFor)
{
    int lastCol = cols - 1;

    // getting the number the equation should be equal to
    double sum = p[row][lastCol];

    // checking if there is only one addend
    if (solveFor == cols - 2)
        p[row][lastCol] / p[row][solveFor];

    // starting from the number after the one we solve for and taking out all the others from the sum
    for (int j = solveFor + 1; j < lastCol; j++)
    {
        sum -= p[row][j];
    }

    // returning the sum divided by the last one
    return sum / p[row][solveFor];
}

// implements the Gaussian method
Matrix Matrix::GaussianMethod()
{
    int i = 0;
    for (int j = 0; j < cols - 2; ++j)
    {
        i = j;
        // getting the next number from the diagonal
        double diagonal_num = p[j][i];
        for (i += 1; i < rows; i++)
        {
            // taking the number by which we have to multiply to get the same nuber we are adding to
            double multiplyer = p[i][j] / diagonal_num;

            // adjusting the sign so that after the addition it results to zero
            if ((multiplyer * diagonal_num > 0 && p[i][j] > 0) || (multiplyer * diagonal_num < 0 && p[i][j] < 0))
                multiplyer *= -1;
            
            // adding the row[i] to row[j]
            addRowToRow(j, i, multiplyer);
        }
    }
    // making a matrix for the X's
    Matrix solutions = Matrix(1, cols - 1);

    // finding x1, x2, x3 and x4  (it works only for 4x4 matrix) !!!

    // finding x1 (solvig for x1)
    solutions.p[0][solutions.cols - 1] = solveRow(rows - 1, cols - 2);

    // substituting x1 into an equation 3 (third row)
    p[rows - 2][cols - 2] *= solutions.p[0][solutions.cols - 1];

    // finding x2 (solvig for x2)
    solutions.p[0][solutions.cols - 2] = solveRow(rows - 2, cols - 3);

    // substituting x1 and x2 into an equation 2 (second row)
    p[rows - 3][cols - 2] *= solutions.p[0][solutions.cols - 1];
    p[rows - 3][cols - 3] *= solutions.p[0][solutions.cols - 2];

    // finding x3 (solvig for x3)
    solutions.p[0][solutions.cols - 3] = solveRow(rows - 3, cols - 4);

    // substituting x1, x2 and x3 into an equation 1 (first row)
    p[rows - 4][cols - 2] *= solutions.p[0][solutions.cols - 1];
    p[rows - 4][cols - 3] *= solutions.p[0][solutions.cols - 2];
    p[rows - 4][cols - 4] *= solutions.p[0][solutions.cols - 3];

    // finding x4 (solvig for x4)
    solutions.p[0][solutions.cols - 4] = solveRow(rows - 4, cols - 5);

    /*
    for (int i = 0; i < solutions.rows; ++i)
    {
        cout << solutions.p[i][0];
        for (int j = 1; j < solutions.cols; ++j)
        {
            cout << " " << solutions.p[i][j];
        }
        cout << endl;
    }
    */

    return solutions;
}

Matrix operator-(const Matrix &m1, const Matrix &m2)
{
    Matrix temp(m1);
    return (temp -= m2);
}
