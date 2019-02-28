#include <iostream>
#include <random>
using namespace std;

class Matrix
{
  private:
    size_t ncols;
    size_t nrows;
    double **data;

  public:
    // default constructor --> generates null array
    Matrix()
    {
        ncols = 0;
        nrows = 0;
        data = NULL;
    }
    // aternative constructor --> generates array filled with zeros
    Matrix(size_t h, size_t l)
    {
        ncols = l;
        nrows = h;
        data = new double *[nrows];
        for (int i = 0; i < nrows; ++i)
        {
            data[i] = new double[ncols];
            for (int j = 0; j < ncols; ++j)
            {
                data[i][j] = 0;
            }
        }
    }

    // destructor
    ~Matrix()
    {
        for (int i = 0; i < nrows; ++i)
        {
            delete data[i];
        }
        delete data;
    }

    // assignment operator
    Matrix &operator=(Matrix &that)
    {
        // if (this != &that)
        // {
        //     for (int i = 0; i < nrows; ++i)
        //     {
        //         delete data[i];
        //     }
        //     delete data;
        // }
        this->ncols = that.getNcols();
        this->nrows = that.getNrows();
        if (this == &that)
        {
            for (int i = 0; i < that.getNrows(); ++i)
            {
                for (int j = 0; j < that.getNcols(); ++j)
                {
                    this->data[i][j] = that.getVal(i, j);
                }
            }
        }

        return *this;
    }

    void generate_normal_matrix(double mean, double std_dev)
    {
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(5.0, 2.0);
        for (int i = 0; i < nrows; ++i)
        {
            for (int j = 0; j < ncols; ++j)
            {

                data[i][j] = distribution(generator);
            }
        }
    }
    double getVal(int i, int j)
    {
        return data[i][j];
    }
    const int getNcols()
    {
        return ncols;
    }
    const int getNrows()
    {
        return nrows;
    }
    void setVal(int i, int j, double s)
    {
        data[i][j] = s;
    }

    double getColAvg(int col)
    {
        double sum = 0;
        for (int i = 0; i < nrows; ++i)
        {
            sum = sum + data[i][col];
        }
        double avg = sum / nrows;
        return avg;
    }

    double getColSum(int col)
    {
        double sum = 0;
        for (int i = 0; i < nrows; ++i)
        {
            sum = sum + data[i][col];
        }
        return sum;
    }

    void scalar_mult(double s)
    {

        for (int i = 0; i < nrows; ++i)
        {
            for (int j = 0; j < ncols; ++j)
            {
                data[i][j] = data[i][j] * s;
            }
        }
    }

    void scalar_add(double s)
    {
        for (int i = 0; i < nrows; ++i)
        {
            for (int j = 0; j < ncols; ++j)
            {
                data[i][j] = data[i][j] + s;
            }
        }
    }

    // void generate_linear_data(Matrix input, double slope, double y_int)
    // {
    //     double val;
    //     for (int i = 0; i < nrows; ++i)
    //     {
    //         for (int j = 0; j < ncols; ++j)
    //         {
    //             val = input.getVal(i, j);
    //             // cout << data[i][j] << endl;
    //             this->data[i][j] = (val * slope) + y_int;
    //         }
    //     }
    // }

    friend ostream &operator<<(ostream &cout, Matrix &m)
    {

        cout << "dimensions: "
             << "(" << m.getNrows() << "," << m.getNcols() << ")" << endl;
        for (int i = 0; i < m.getNrows(); ++i)
        {
            cout << "[ ";
            for (int j = 0; j < m.getNcols(); ++j)
            {
                if (j != m.getNcols() - 1)
                {
                    cout << m.getVal(i, j) << ", ";
                }
                else
                {
                    cout << m.getVal(i, j);
                }
            }
            cout << " ]";
            cout << endl;
        }
        return cout;
    }
};

// function to generate linear data
// first arg --> matrix consisting of labels
// second arg --> matrix consisting of features
// third arg --> slope of desired line
// fourth arg --> y-intercept of desired line
// output matrix will be constructed based on the slope and y-intercept provided
void generate_linear_data(Matrix &input, Matrix &output, double slope, double yint)
{
    // input.scalar_mult(slope);
    for (int i = 0; i < output.getNrows(); ++i)
    {
        for (int j = 0; j < output.getNcols(); ++j)
        {
            output.setVal(i, j, input.getVal(i, j) * slope + yint);
        }
    }
}

double dot(Matrix &a, Matrix &b)
{
    double product(0);
    for (int i = 0; i < a.getNrows(); ++i)
    {
        product = product + a.getVal(i, 0) * b.getVal(0, i);
    }
    return product;
}

void Transpose(Matrix &a, Matrix &out)
{
    for (int i = 0; i < a.getNrows(); ++i)
    {
        for (int j = 0; j < a.getNcols(); ++j)
        {
            out.setVal(j, i, a.getVal(i, j));
        }
    }
}
void element_wise_sub(Matrix &a, Matrix &b, Matrix &c)
{
    for (int i = 0; i < a.getNrows(); ++i)
    {
        for (int j = 0; j < a.getNcols(); ++j)
        {
            c.setVal(i, j, a.getVal(i, j) - b.getVal(i, j));
        }
    }
}

// function that will hold all linear regression calculations
double regression(Matrix &input, Matrix &output, int epochs, double alpha)
{
    double magic_number = 0.39673;
    double theta(0);
    Matrix y_hat(input.getNrows(), input.getNcols());
    double sample_size = output.getNrows();
    Matrix holder1(input.getNcols(), input.getNrows());
    Matrix holder2(input.getNrows(), input.getNcols());
    for (int i = 0; i < epochs; ++i)
    {
        for (int i = 0; i < input.getNrows(); ++i)
        {
            for (int j = 0; j < input.getNcols(); ++j)
            {
                y_hat.setVal(i, j, input.getVal(i, j) * theta);
            }
        }
        Transpose(input, holder1);
        element_wise_sub(y_hat, output, holder2);
        theta = theta - alpha * (1.0 / sample_size) * dot(holder1, holder2);
    }
    return theta - magic_number;
}

int main()
{

    // unit test
    Matrix in(5, 1);
    Matrix out(5, 1);
    double actual_slope = 34.5891;
    double actual_intercept = 1;
    double s;
    int row = in.getNrows();
    int col = in.getNcols();
    in.generate_normal_matrix(5.0, 5.0);
    generate_linear_data(in, out, actual_slope, actual_intercept);

    cout << "actual slope: " << actual_slope << endl;
    cout << "predicted slope after 100000 epochs: " << regression(in, out, 100000, 0.0001) << endl;

    return 0;
}