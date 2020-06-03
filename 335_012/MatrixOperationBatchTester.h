#ifndef MATRIXOPERATIONBATCHTESTER_H
#define MATRIXOPERATIONBATCHTESTER_H


//#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include "Options.h"
#include "Matrix.h"
#include "MatrixOperator.h"

class MatrixOperationBatchTester 
{
    std::string inputFilename;
    std::string outputFilename;
    std::string dataType;
public:
    MatrixOperationBatchTester(int argc, char **argv);
private:
    bool setOptions(int argc,char **argv);
    int parseInteger(std::string sval);
    std::pair<int,int> parseMatrixDimensions(std::ifstream &ifile);
    int parseNMatrices(std::ifstream &ifile);
    template <class T> Matrix<T>* loadInputMatrices();
    template <class T> void runTest(int argc,char **argv);
    template <class T> void saveOutputMatrix(Matrix<T> c);
};

// function that loads the matrices from the inputFilename, it returns an array with
// the matrices read from the file or NULL if an error is found
template <class T>
Matrix<T>* MatrixOperationBatchTester::loadInputMatrices()
{   
    Matrix<T>* matrices=NULL;
    std::ifstream ifile;
    ifile.open(inputFilename.c_str());
    if(!ifile.is_open())
        std::cout << "ERROR: unable to open input file!" << std::endl;
    else 
    {
        std::string line;
        int len; // current file position

        while((len = ifile.tellg())+1 && std::getline(ifile,line) && line.substr(0,12)!="NUM_MATRICES"); // skip initial comments
        if(line.substr(0,4)=="NUM_")    // if the NUM line was found
            ifile.seekg(len ,std::ios_base::beg);   // reset the file pointer to start before "NUM_..."
        int nmatrices;
        if((nmatrices=parseNMatrices(ifile))!=-1)   // parse the number of matrices
        {
            matrices = new Matrix<T>[nmatrices+1];  // cresate the array of matrices
            for(int i=0; i<nmatrices; i++)
            {
                std::pair<int,int> mn=parseMatrixDimensions(ifile); // load the matrix dimension from the following two lines 
                if(mn.first!=-1 && mn.second!=-1)   // if we found the row and col dimensions
                {
                    matrices[i].setDimensions(mn.first,mn.second);  // resize the matrix to the dimensions found
                    ifile >> matrices[i];
                    while((len = ifile.tellg()) && std::getline(ifile,line) && line.substr(0,4)!="NUM_"); // skip inner comments
                    if(line.substr(0,4)=="NUM_")    // if the NUM line was found
                        ifile.seekg(len ,std::ios_base::beg); // reset the file pointer to start before "NUM_..."
                }
                else    // if we didn't find the col and row dimension we can't read the matrix
                {
                    std::cout << "ERROR: unable to read matrix dimensions" << std::endl;
                    delete [] matrices;
                    matrices=NULL;
                    break;
                }
            }        
        }        
        else
            std::cout << "ERROR: no matrices were found in the file" << std::endl;
        ifile.close();
    }
    return matrices;
}

// save the output matrix using the standard format
template <class T>
void MatrixOperationBatchTester::saveOutputMatrix(Matrix<T> c)
{   
    std::ofstream ofile;
    ofile.open(outputFilename.c_str());
    if(!ofile.is_open())
        std::cout << "ERROR: unable to open output file!" << std::endl;
    else 
    {
        ofile << "NUM_MATRICES 1" << std::endl;
        ofile << "NUM_ROWS " << c.getM() << std::endl;
        ofile << "NUM_COLUMNS " << c.getN() << std::endl;
        if(c.getM()!=0) // if the multiplication was successful
            ofile << c ;
        else
            ofile << "NaN" << std::endl;
        ofile.close();
    }
}

// function tamplate for running the test on the selected input file using the 
// selected matrix data type
template <class T>
void MatrixOperationBatchTester::runTest(int argc,char **argv)
{
    std::cout << "Starting tests...\n"<<std::endl;
    Matrix<T> *mat = loadInputMatrices<T>();    // load the matrices from the inputFilename
    if (mat)
    {
        if(mat[1].getM()==0)
        {
            std::cout << "ERROR: not enough input matrices to make the operation" << std::endl;
            return;
        }
        MatrixOperator<T> mop(argc,argv);   // defines a new matrix operator object
        Matrix<T> c=mop.multiply(mat[0],mat[1]); // perform the operation (multiplication)
        saveOutputMatrix<T>(c); // save the matrix on the output file
        std::cout << "Operation result: "<<std::endl;
        //std::cout << c << std::endl;                               
        if(mat[2].getM()!=0)
        {
            if(mat[2].equals(c))
                std::cout << "Result is valid" << std::endl;
            else
                std::cout << "Result is not valid" << std::endl;
        }
        else 
            std::cout << "Unable to validate result. No result matrix was given." << std::endl;
    }   
    std::cout <<std::endl<< "End of tests."<<std::endl;
}

#endif
