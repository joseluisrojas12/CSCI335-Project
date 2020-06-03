#include "Matrix.h"

// template specialization for the float type, it compares the values up to a given tolerance
// since float equality is not possible
template<>
bool Matrix<float>::equals(Matrix<float> mat)
{
    if (m!=mat.getM() || n!=mat.getN()) // if the dimensions are not equal
        return false;           // the matrices are not equal
    for (int row=0; row<mat.getM(); row++)  // go through all the matrix elements
        for(int col=0; col<mat.getN(); col++)
            if(std::abs(this->mat[row][col]-mat[row][col])>TOL) // if any element is different,
                return false;
    return true;    // if we reach this point the matrices are equal
}

// template specialization for the double type, it compares the values up to a given tolerance
// since double number equality is not possible
template<>
bool Matrix<double>::equals(Matrix<double> mat)
{
    if (m!=mat.getM() || n!=mat.getN()) // if the dimensions are not equal
        return false;       // the matrices are not equal
    for (int row=0; row<mat.getM(); row++)  // go through all the matrix elements
        for(int col=0; col<mat.getN(); col++)
            if(std::abs(this->mat[row][col]-mat[row][col])>TOL) // if any element is different,
                return false;   // the matrices are not equal
    return true;    // if we reach this point the matrices are equal
}
