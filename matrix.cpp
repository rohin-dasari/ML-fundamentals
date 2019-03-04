#include <iostream>
#include <cstdlib>
#include <random>
#include <stdexcept>
#include <tuple>

using namespace std;

class Matrix
{

  public:
    // all public data
    size_t r, c;
    double **data;

    // default constructor
    Matrix()
    {

        r = 0;
        c = 0;
        data = new double *[r];
        for (int i = 0; i < r; ++i)
        {
            data[i] = new double[c];
            for (int j = 0; j < c; ++j)
            {
                data[i][j] = 0;
            }
        }
    }

    // alternative constructor
    // first arg --> # of rows
    // second arg --> # of columns
    // third arg --> initial value
    // initialize matrix of dimensions ixj with initial set of values
    Matrix(size_t rows, size_t cols, double val = 0.0)
    {

        r = rows;
        c = cols;
        data = new double *[rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] = val;
            }
        }
    }

    Matrix(size_t rows, size_t cols, double mean, double std_dev)
    {
        r = rows;
        c = cols;
        data = new double *[rows];
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(mean, std_dev);
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] = distribution(generator);
            }
        }
    }

    // destructor
    ~Matrix()
    {
        for (int i = 0; i < r; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    Matrix T()
    {
        Matrix temp(this->c, this->r);
        for (int i = 0; i < this->c; ++i)
        {
            for (int j = 0; j < this->r; ++j)
            {
                temp.data[i][j] = this->data[j][i];
            }
        }

        return temp;
    }

    // assignment operator
    // first arg --> matrix
    // sets input matrix equal to "this" matrix
    Matrix &
    operator=(const Matrix &that)
    {
        if (this == &that)
        {
            return *this;
        }
        this->r = that.r;
        this->c = that.c;

        this->data = new double *[r];
        for (int i = 0; i < r; ++i)
        {
            data[i] = new double[c];
            for (int j = 0; j < c; ++j)
            {
                this->data[i][j] = that.data[i][j];
            }
        }
        return *this;
    }

    // overload "*" operator to allow for element wise addition of matrices
    friend Matrix operator+(const Matrix &a, const Matrix &b)
    {

        if (a.r == b.r && a.c == b.c)
        {
            Matrix product(a.r, a.c);
            for (int i = 0; i < a.r; ++i)
            {
                for (int j = 0; j < a.c; ++j)
                {
                    product.data[i][j] = a.data[i][j] + b.data[i][j];
                }
            }
            return product;
        }
        // else if
        else
        {
            Matrix error(0, 0);
            cout << endl
                 << "Warning: operands can not be added together" << endl;
            return error;
        }
    }

    // overload "*" operator to allow for element wise addition of matrices
    friend Matrix operator+(const Matrix &a, double b)
    {

        Matrix product(a.r, a.c);
        for (int i = 0; i < a.r; ++i)
        {
            for (int j = 0; j < a.c; ++j)
            {
                product.data[i][j] = a.data[i][j] + b;
            }
        }
        return product;
    }

    // overload "*" operator to allow for element wise subtraction of matrices
    friend Matrix operator-(const Matrix &a, const Matrix &b)
    {

        if (a.r == b.r && a.c == b.c)
        {
            Matrix product(a.r, a.c);
            for (int i = 0; i < a.r; ++i)
            {
                for (int j = 0; j < a.c; ++j)
                {
                    product.data[i][j] = a.data[i][j] - b.data[i][j];
                }
            }
            return product;
        }
        // else if
        else
        {
            Matrix error(0, 0);
            cout << endl
                 << "Warning: operands can not be subtracted together" << endl;
            return error;
        }
    }

    // overload "*" operator to allow for element wise multiplication of matrices
    friend Matrix operator*(const Matrix &a, const Matrix &b)
    {

        if (a.r == b.r && a.c == b.c)
        {
            Matrix product(a.r, a.c);
            for (int i = 0; i < a.r; ++i)
            {
                for (int j = 0; j < a.c; ++j)
                {
                    product.data[i][j] = a.data[i][j] * b.data[i][j];
                }
            }
            return product;
        }
        // else if
        else
        {
            Matrix error(0, 0);
            cout << endl
                 << "Warning: operands can not be multiplied together" << endl;
            return error;
        }
    }

    // overload "*" operator to allow scalar multiplication
    friend Matrix operator*(const Matrix &a, double b)
    {

        Matrix product(a.r, a.c);
        for (int i = 0; i < a.r; ++i)
        {
            for (int j = 0; j < a.c; ++j)
            {
                product.data[i][j] = a.data[i][j] * b;
            }
        }
        return product;
    }
    // overload "*" operator to allow scalar multiplication
    friend Matrix operator*(double b, const Matrix &a)
    {

        Matrix product(a.r, a.c);
        for (int i = 0; i < a.r; ++i)
        {
            for (int j = 0; j < a.c; ++j)
            {
                product.data[i][j] = a.data[i][j] * b;
            }
        }
        return product;
    }

    // overload "<<" operator
    friend ostream &operator<<(ostream &cout, Matrix &a)
    {
        // cout << "dimensions: " << a.r << " x " << a.c << endl;
        for (int i = 0; i < a.r; ++i)
        {
            cout << "[";
            for (int j = 0; j < a.c; ++j)
            {
                cout << " " << a.data[i][j];
            }
            cout << " ]";
            cout << endl;
        }
        return cout;
    }
};

void add_row(Matrix &a)
{

    Matrix temp(a.r + 1, a.c);
    for (int i = 0; i < temp.r; ++i)
    {
        for (int j = 0; j < temp.c; ++j)
        {
            if (i < a.r)
            {
                temp.data[i][j] = a.data[i][j];
            }
            else
            {
                // temp.data[i][j] = a.data[a.r - 1][j];
                temp.data[i][j] = 2;
            }
        }
    }
    a = temp;
}

Matrix getCol(Matrix &a, int num)
{
    Matrix column(a.r, 1);
    for (int i = 0; i < a.r; ++i)
    {
        column.data[i][0] = a.data[i][num];
    }
    return column;
}

void add_col(Matrix &a)
{
    Matrix temp(a.r, a.c + 1);
    for (int i = 0; i < temp.r; ++i)
    {
        for (int j = 0; j < temp.c; ++j)
        {
            if (j < a.c)
            {
                temp.data[i][j] = a.data[i][j];
            }
            else
            {
                // temp.data[i][j] = a.data[i][a.c - 1];
                temp.data[i][j] = 1;
            }
        }
    }
    a = temp;
}

Matrix dot(Matrix &a, Matrix &b)
{
    if (a.c != b.r)
    {
        cout << endl;
        throw std::invalid_argument("Matrix dimensions don't match up");
    }
    Matrix sol(a.r, b.c);
    double sum;
    for (int i = 0; i < a.r; ++i)
    {
        for (int j = 0; j < b.c; ++j)
        {
            sol.data[i][j] = 0;
            for (int k = 0; k < a.c; ++k)
            {
                // cout << a.data[i][k] * b.data[k][j] << endl;
                sol.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return sol;
}

Matrix batch_regression(Matrix &in, Matrix &out, int epochs, double alpha)
{
    // if in and out are not the same size: throw error
    if (in.c != out.c || in.r != out.r)
    {
        cout << endl;
        throw std::invalid_argument("Matrix dimensions don't match up");
    }

    //else continue
    Matrix theta(in.r, in.c);
    Matrix theta1(in.r, in.c);
    Matrix y_hat(in.r, in.c);
    double sample_size = in.r;
    Matrix in_transpose;
    Matrix temp1;
    Matrix temp2;
    Matrix temp3;
    Matrix temp4;
    Matrix ones(1, sample_size, 1);
    Matrix slopes(1, in.c);
    Matrix intercepts(1, in.c);
    for (int i = 0; i < epochs; ++i)
    {
        for (int j = 0; j < in.r; ++j)
        {
            for (int k = 0; k < in.c; ++k)
            {
                // calculate y_hat by multiplying theta and input element-wise;
                y_hat.data[j][k] = in.data[j][k] * theta.data[j][k] + theta1.data[j][k];
            }
        }
        for (int u = 0; u < in.c; ++u)
        {
            temp1 = getCol(in, u);
            in_transpose = temp1.T();
            temp2 = getCol(out, u);
            temp3 = getCol(y_hat, u);
            temp4 = temp3 - temp2;
            slopes.data[0][u] = slopes.data[0][u] - alpha * (1 / sample_size) * dot(in_transpose, temp4).data[0][0];
            intercepts.data[0][u] = intercepts.data[0][u] - alpha * (1 / sample_size) * dot(ones, temp4).data[0][0];
        }
        // update theta matrix with new values from slope matrix
        for (int y = 0; y < in.r; ++y)
        {
            for (int q = 0; q < in.c; ++q)
            {
                theta.data[y][q] = slopes.data[0][q];
                theta1.data[y][q] = intercepts.data[0][q];
            }
        }
    }
    return slopes;
}

int main()
{
    Matrix x(15, 2, 5.0, 2.0);
    Matrix y;
    y = x * 5;
    y = y + 7;

    cout << "x: " << x << endl;
    cout << endl;
    cout << "o: " << y << endl;
    Matrix m;
    m = batch_regression(x, y, 10000, 0.01);
    cout << m;
    return 0;
}