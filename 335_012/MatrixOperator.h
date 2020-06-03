#ifndef MATRIXOPERATOR_H
#define MATRIXOPERATOR_H


//#pragma once
#include "Options.h"
#include "Matrix.h"

template <class T>
class MatrixOperator
{
    bool truncate_invalid;
public:
    MatrixOperator(int argc,char **argv);    
    Matrix<T> multiply(Matrix<T> a,Matrix<T> b);
};

// MatrixOperator class constructor
template <class T>
MatrixOperator<T>::MatrixOperator(int argc,char **argv)
{    
    Options options(argc,argv); // load the options from the command line arguments
    std::string arg;
    if((arg=options.get("truncate_invalid_matrix_pairs"))!="")  // set the flag depending on the option given
        truncate_invalid=true;
    else 
        truncate_invalid=false;

}

// multiplies two given matrices and returns a new matrix that holds the multiplication result
template <class T>
Matrix<T> MatrixOperator<T>::multiply(Matrix<T> a,Matrix<T> b)
{
    int m=a.getM();
    int n=a.getN();
    int p=b.getM();
    int r=b.getN();
    Matrix<T> c;    
    if(n!=p)    // if the inner dimensions are not equal, the multiplication cannot be done directly
    {
        if(!truncate_invalid)   // if no truncation is required, the multiplication can't be done
            return c; // return an empty matrix to indicate error
        else {  // else, the user wants to adjust the sizes to make the multiplication
            if(n<p) // set the dimensions accordingly
                p=n;
            else
                n=p;
        }
    }
    c.setDimensions(m,r);   // create the resulting matrix
    for (int i=0; i<m; i++) // perform the matrix multiplication
        for(int j=0; j<r; j++) 
        {
            T sum=0;
            for (int k=0; k<n; k++)
            {
                sum+=a[i][k]*b[k][j];
            }
            c[i][j]=sum; // save the result of rowA*colB in the current position in C
        }       
    return c;    
}

#endif
