#pragma once
#include <iostream>
#include <cmath>

#define TOL 1e6 // default tolerance used for float and double type equality comparison

template <class T>
class Matrix
{
    T **mat;
    int m;
    int n;
public:
    Matrix();
    Matrix(int m,int n);    
    int getM() 
    {
        return m;
    }
    int getN()
    {
        return n;
    }
    void setDimensions(int m,int n);
    void setElements(T *elems);
	T*& operator[](int rowi);
	template <class U> friend std::ostream& operator<<(std::ostream& ostr, Matrix<U> & m);
	template <class U> friend std::istream& operator>>(std::istream& istr, Matrix<U> & m);
	T* getColumn(int i);
	void setColumn(int i,T* v);   
	bool equals(Matrix<T> m);
};

// empty constructor
template <class T>
Matrix<T>::Matrix()
{
    m=0;
    n=0;
    mat=NULL;
}

// Matrix class constructor, initializes the matrix using the given dimensions
template <class T>
Matrix<T>::Matrix(int m,int n)
{
    this->m=m;
    this->n=n;
    mat=new T*[m];
    for(int i=0; i<m; i++)
        mat[i]=new T[n];
}

// operator []  to access the elements on the matrix 
template <class T>
T*& Matrix<T>::operator[](int rowi) {
	return mat[rowi];
}

// set all the elements of the matrix using the values from a given array
// the array must be at least of length m*n
template <class T>
void Matrix<T>::setElements(T *elems)
{
    int k=0;
    for (int row=0; row<m; row++)
        for(int col=0; col<n; col++)
            mat[row][col]=elems[k++];
}

// operator used to load the contents of the matrix from a stream
template <class T>
std::istream& operator>>(std::istream& istr, Matrix<T> & m) {
    for (int row=0; row<m.getM(); row++)
        for(int col=0; col<m.getN(); col++)
	        istr >> m[row][col];
    return istr;    
}

// operator used to print the matrix to a stream
template <class T>
std::ostream& operator<<(std::ostream& ostr, Matrix<T> & m) {
    for (int row=0; row<m.getM(); row++)
	{
        for(int col=0; col<m.getN(); col++)
	        ostr << m[row][col] << " ";
		ostr << std::endl;
	}
    return ostr;
}

// returns the contents of a given column as an array of T type
template <class T>
T* Matrix<T>::getColumn(int i) {

	T* col = new T[m];
    for (int row=0; row<m; row++)
        col[row]=mat[row][i];
	return col;
}

// sets a column on the matrix using hte given array of values
template <class T>
void Matrix<T>::setColumn(int i, T* v) {
    for (int row=0; row<m; row++)
        mat[row][i]=v[row];
}

// templated function to test the equality between two matrices
template<class T>
bool Matrix<T>::equals(Matrix<T> mat)
{
    if (m!=mat.getM() || n!=mat.getN()) // if the dimensions are not equal
        return false;   // the matrices are not equal
    for (int row=0; row<mat.getM(); row++)  // go through all the matrix elements
        for(int col=0; col<mat.getN(); col++)
            if(this->mat[row][col]!=mat[row][col])  // if any element is different, 
                return false;   //the matrices are not equal
    return true;    // if we reach this point the matrices are equal
}

// changes the dimensions of the matrix, reallocating space for the new matrix
// the old contents are lost
template<class T>
void Matrix<T>::setDimensions(int m,int n)
{
    this->m=m;
    this->n=n;
    mat=new T*[m];
    for(int i=0; i<m; i++)
        mat[i]=new T[n];   
}


