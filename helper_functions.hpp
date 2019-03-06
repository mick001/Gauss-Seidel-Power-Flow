#include<iostream>
#include<vector>
#include<complex>

using std::vector;
using std::cout;
using std::complex;
using std::endl;
using std::string;

/*
*********************************************************************************************************
                                Functions working on vectors
*********************************************************************************************************
*/

namespace vector_functions
{

    // This function prints a column (or a row) vector
    void print_vector(const vector< complex<double> > &column_vector, string name)
    {
        cout << endl;
        cout << "Vector " << name << ":" << endl;
        for(int i=0; i < column_vector.size(); i++)
        {
            cout << column_vector[i] << endl;
        }
    }

    // This function computes matrix-column vector multiplication and returns the k-th element of the resulting column vector
    complex<double> row_column_product(const vector<vector< complex<double> > > &matrix,
                                       const vector< complex<double> > &column_vector,
                                       const int element_index)
    {
        complex<double> result {0, 0};
        int vector_size = column_vector.size();

        for(int i = 0; i < vector_size; i++)
        {
            result = result + matrix[element_index][i] * column_vector[i];
        }

        return result;
    }

    // This function computes the euclidean norm of a vector
    double vector_norm_euclidean(const vector< complex<double> > &x,
                                 const vector< complex<double> > &x_0)
    {
        double norm = 0;
        int vector_size = x.size();

        for(int i = 0; i < vector_size; i++)
        {
            norm = norm + pow(fabs(x[i]) - fabs(x_0[i]), 2);
        }

        return sqrt(norm);
    }

}
