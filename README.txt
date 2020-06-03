# CSCI335-Project
/***************************************************************************
Title:		README.txt
Author:		Jose Luis Rojas-Salazar
Date Created:	9/18/2017
Class:		Fall 2017, CSCI 335, Tu & Thu 7:00pm-8:15pm
Professor:	Benjamin Garrett
Purpose:	Assigment #1
Description:	Detail about
		-Built instructions for your makefile.
		-Parts complete and parts incomplete.
		-Description of known bugs.
		-Report on how your project works, and explanations of your
		 algorithms and class structure. 
****************************************************************************/

CSCI335-Software Analysis & Design III
Assigment #1

-Built instructions for your makefile.

The files that are part of the assignment are:
main.cpp
Options.h
Options.cpp
MatrixOperationBatchTester.h
MatrixOperationBatchTester.cpp
MatrixOperator.h
Matrix.h
Matrix.cpp

The files using for testing containing data are:
input2.txt
input_double.txt
input_float.txt

The file containing the makefile to compile and generate the executable is:
Makefile

1. Compile with make
$ make

2. Run
To run it, use the executable named test followed of the parameters file name and data type.
$ ./test --matrix_input_fname=[name of file with data] --matrix_data_type=[data type]

NOTE: For the gprof I modified the Makefile adding the option -pg in each line of the elements to be compiled, then type the following commands (for example to use double data type):

$ ./test --matrix_input_fname=input_double.txt --matrix_data_type=double
$ gprof test gmon.out>analysis.txt

To see the results of the gprofilying type the following:

$ gedit analysis.txt

-Parts complete and parts incomplete.

The program was made but modifying the project framework.
It was tested using a txt file with data type double using as arguments the txt file named input_double.txt and the data type = double.
After the execution and verification that in the output.txt file can perform the matrix multiplication it was profilying getting the following info in the analysis.txt file:

NOTE: Today 9/22/2017 I modify the Makefile following recommendations from teacher Garrett for profiling.

Flat profile:

Each sample counts as 0.01 seconds.
 no time accumulated

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00    39900     0.00     0.00  Matrix<double>::operator[](int)
  0.00      0.00     0.00     3454     0.00     0.00  Matrix<double>::getN()
  0.00      0.00     0.00      600     0.00     0.00  std::abs(double)
  0.00      0.00     0.00      162     0.00     0.00  Matrix<double>::getM()
  0.00      0.00     0.00       44     0.00     0.00  std::vector<std::string, std::allocator<std::string> >::size() const
  0.00      0.00     0.00       44     0.00     0.00  bool std::operator==<char, std::char_traits<char>, std::allocator<char> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*)
  0.00      0.00     0.00       32     0.00     0.00  std::string const&
...

The results show that Matrix class using double data type accumulate the most number of calls when use member overloaded function operator[] to access the elements on the matrix and when interact with members getN() and getM() to set dimensions of the matrix.

- Description of known bugs

The first issue was using templates. Separate the interface from the implementations using templates always gave me a lot of errors during compilation and I was consuming a lot of time trying to fixed. After review some web sites as www.stackoverflow.com many people recommend to not separate them if will be used with templates, in other words, you must sacrifice separation for the advantage of use templates, it is the price to pay for use templates in a project. Thats the reason why is important to work with data type well defined in future projects.

The second one was during construction of the Matrix class member function equals(). When work with integer values work OK but when start testing with double values warning and error messages appear again, the file Matrix.cpp was added containing the template specialization for the float type and the double type, they compare the values up to given tolerance since float/double number equality is not possible. 

The third issue was trying to get the profile gprof file. Due is the first time I use gprof to profile a project I was trying to figure out how to use or enable the option -pg in the command line when compile but after check in some web sites like www.thegeekstuff.com and linuxgazette.net I found that -pg option must be added in each line of the compiler files in the makefile and after compile and get the executable file use the gmon.out>[name of file that will hold the gprof results] to load the results in a txt file so I can review how the program works and what elements consume more time.

The fourth issue is during the use with namespace Jose_RojasCSCI335, trying to correct why show a lot of error messages when compile
I just run the program using namespace std and works fine, try to correct this one but if not I left the files that compile and run.

- Report on how the project works

_____________________
|Matrix             |         ____________________________
| __________________|         |                          |
| | MatrixOperator ||<--------|MatrixOperationBatchTester|      /
| |________________||         |__________________________|     /  Once compiled generate the executable: test
|___________________|                      |                  /   and to run it must indicate in the command line the arguments
                              _____________|______________   /    that test will be use.
                              |                          |  /
                              |         Options          |  \        ____________
                              |__________________________|   \       |          |<------[input file name with data]
                                           |                  \      |  ./test  |
                                           |                   \     |__________|<------[data type]
                                    _______|_______             \
                                    |             |
                                    |    Main     |
                                    |_____________|      



In the main.cpp file argv and argc are how command line arguments are passed to main(). 
argc will be the number of strings pointed to by argv or the argument vector. 

Options class parses the command line arguments and fills a vector named option with the options found (in this case will be the name of the file with the input data and name of the data type). To identify the strings or start of each option use the characters "--" and"=".

MatrixOperationBatchTester class use the Options class in the member setOptions to get the strings that will be the names of the input data file and the data type and get the output file name using the names specified in the assignment:

--matrix_input_fname
--results_output_fname
--matrix_data_type

MatrixOperationBatchTester sets the different options for the operation of the batch tester using the command lines arguments.
It's constructor initialize the options based on the command line arguments and dispatches a templated test function based on the
selected data type: int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, float, double.

The member function loadInputMatrices() will load the matrices from the input file detecting first the string of 12 characters
"NUM_MATRICES" to skip initial comments.

The strings with the values like number of matrices, number of rows and number of columns start with characters NUM_ so each time 
these four characters are detected in the file first parse the number of matrices to create the array of matrices, then load the matrix
dimensions from the following two lines.

If there is only one o none matrix will display an error message:ERROR: not enought input matrices to make the operation.

When parameter --truncate_invalid_matrix_pairs is present the MatrixOperator class modifies a pair of matrices before multiplying
them when their sizes are incompatible. 

Matrix A with dimensions mxn
Matrix B with dimensions pxr

If the inner dimensions are not equal (n!=p) the multiplication can not be done directly, using the member function
Matrix<T> MatrixOperator<T>::multiply(Matrix<T> a,Matrix<T> b) the sizes to make the multiplication will be adjust.

if (n<p) //set the dimensions accordingly to create the new matric named c and perform the matrix multiplication
 p=n;
else
 n=p;
...

c.setDimensions(m,r);
 for(int i=0;i<m;i++)
   for(int j=0;j<r;j++)
     {
      T sum=0;
      for (int k=0;k<n;K++)
      {
       sum+=a[i][k]*b[k][j];
      }
      c[i][j]=sum;
     }
return c;
...

Matrix class provides methods of initializing, modigying, and accesing a matrix and also provides a method called equals()
which returns true if the matrix given as input is identical element-wise.

In this class use #define TOL 1e6 as a default tolerance range for float and double type equality comparison (to try to make uniform the
number of decimals between floats or doubles).

It have two constructors, te first one to empty matrix (m=0, n=0 and pointer mat=NULL) and the second one initializes the matrix using
the given dimensions readed from the input file.

setDimensions(int m, int n) member function changes the dimensions of the matrix reallocating space for the new matrix.

To access the elements in the matrix use operator[](int rowi)

To test the equality between two matrices use equals(Matrix<T> mat) for this one first must to check if their dimensions are equal,
then go through all the matrix elements checking one by one, if any element is different the matrices are not equal and return false.

When use equals() with matrices that have double or float elements I used a tolerance given by #define TOL 1e6 since float or double
equality present problems without that tolerance.

In the interfaces of the classes first I used #pragma once, because is very well supported across compilers and speed up preprocessor.
Professor Garrett suggest to use guards in .h files, in this case we will use one specific compiler and programs will be compared so is
important that the code be standard and #pragma once is not guarantee that be part of the standard. The .h files are now with guards.
There is an interesting discussion about the use of #pragma once in the following link:
https://stackoverflow.com/questions/1143936/pragma-once-vs-include-guards






For assignment 2 phase 3 gprof analysis.txt

Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 66.70      0.08     0.08   400360     0.00     0.00  BinarySearchTree::read(BinarySearchTree::Node*, long)
 33.35      0.12     0.04   199640     0.00     0.00  BinarySearchTree::remove(BinarySearchTree::Node*&, long)
  0.00      0.12     0.00   400360     0.00     0.00  BinarySearchTree::read(long)
  0.00      0.12     0.00   200465     0.00     0.00  BinarySearchTree::write(long)
  0.00      0.12     0.00   199640     0.00     0.00  BinarySearchTree::remove(long)
  0.00      0.12     0.00   116376     0.00     0.00  BinarySearchTree::write(BinarySearchTree::Node*&, long)
  0.00      0.12     0.00    28805     0.00     0.00  BinarySearchTree::findMin(BinarySearchTree::Node*)
  0.00      0.12     0.00        1     0.00     0.00  _GLOBAL__sub_I__ZN14GarrettCSCI33527DemoOperationSequenceReaderC2EiPPc
  0.00      0.12     0.00        1     0.00     0.00  _GLOBAL__sub_I_main
  0.00      0.12     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      0.12     0.00        1     0.00     0.00  __static_initialization_and_destruction_0(int, int)
  0.00      0.12     0.00        1     0.00   120.06  GarrettCSCI335::DemoOperationSequenceReader::DemoOperationSequenceReader(int, char**)
  0.00      0.12     0.00        1     0.00     0.00  BinarySearchTree::BinarySearchTree()
  0.00      0.12     0.00        1     0.00     0.00  read_operation_sequence

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.

 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.

Copyright (C) 2012-2015 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.

		     Call graph (explanation follows)


granularity: each sample hit covers 2 byte(s) for 8.33% of 0.12 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.00    0.12                 main [1]
                0.00    0.12       1/1           GarrettCSCI335::DemoOperationSequenceReader::DemoOperationSequenceReader(int, char**) [2]
-----------------------------------------------
                0.00    0.12       1/1           main [1]
[2]    100.0    0.00    0.12       1         GarrettCSCI335::DemoOperationSequenceReader::DemoOperationSequenceReader(int, char**) [2]
                0.00    0.04  200465/200465      BinarySearchTree::write(long) [5]
                0.00    0.04  199640/199640      BinarySearchTree::remove(long) [7]
                0.00    0.04  199895/400360      BinarySearchTree::read(long) [4]
                0.00    0.00       1/1           BinarySearchTree::BinarySearchTree() [21]
                0.00    0.00       1/1           read_operation_sequence [8]
-----------------------------------------------
                             7063296             BinarySearchTree::read(BinarySearchTree::Node*, long) [3]
                0.08    0.00  400360/400360      BinarySearchTree::read(long) [4]
[3]     66.7    0.08    0.00  400360+7063296 BinarySearchTree::read(BinarySearchTree::Node*, long) [3]
                             7063296             BinarySearchTree::read(BinarySearchTree::Node*, long) [3]
-----------------------------------------------
                0.00    0.04  199895/400360      GarrettCSCI335::DemoOperationSequenceReader::DemoOperationSequenceReader(int, char**) [2]
                0.00    0.04  200465/400360      BinarySearchTree::write(long) [5]
[4]     66.7    0.00    0.08  400360         BinarySearchTree::read(long) [4]
                0.08    0.00  400360/400360      BinarySearchTree::read(BinarySearchTree::Node*, long) [3]
-----------------------------------------------
                0.00    0.04  200465/200465      GarrettCSCI335::DemoOperationSequenceReader::DemoOperationSequenceReader(int, char**) [2]
[5]     33.4    0.00    0.04  200465         BinarySearchTree::write(long) [5]
                0.00    0.04  200465/400360      BinarySearchTree::read(long) [4]
                0.00    0.00  116376/116376      BinarySearchTree::write(BinarySearchTree::Node*&, long) [15]
-----------------------------------------------
                             3585303             BinarySearchTree::remove(BinarySearchTree::Node*&, long) [6]
                0.04    0.00  199640/199640      BinarySearchTree::remove(long) [7]
[6]     33.3    0.04    0.00  199640+3585303 BinarySearchTree::remove(BinarySearchTree::Node*&, long) [6]
                0.00    0.00   28805/28805       BinarySearchTree::findMin(BinarySearchTree::Node*) [16]
                             3585303             BinarySearchTree::remove(BinarySearchTree::Node*&, long) [6]
-----------------------------------------------
                0.00    0.04  199640/199640      GarrettCSCI335::DemoOperationSequenceReader::DemoOperationSequenceReader(int, char**) [2]
[7]     33.3    0.00    0.04  199640         BinarySearchTree::remove(long) [7]
                0.04    0.00  199640/199640      BinarySearchTree::remove(BinarySearchTree::Node*&, long) [6]
-----------------------------------------------
                0.00    0.00       1/1           GarrettCSCI335::DemoOperationSequenceReader::DemoOperationSequenceReader(int, char**) [2]
[8]      0.0    0.00    0.00       1         read_operation_sequence [8]
-----------------------------------------------
                             2119956             BinarySearchTree::write(BinarySearchTree::Node*&, long) [15]
                0.00    0.00  116376/116376      BinarySearchTree::write(long) [5]
[15]     0.0    0.00    0.00  116376+2119956 BinarySearchTree::write(BinarySearchTree::Node*&, long) [15]
                             2119956             BinarySearchTree::write(BinarySearchTree::Node*&, long) [15]
-----------------------------------------------
                               35900             BinarySearchTree::findMin(BinarySearchTree::Node*) [16]
                0.00    0.00   28805/28805       BinarySearchTree::remove(BinarySearchTree::Node*&, long) [6]
[16]     0.0    0.00    0.00   28805+35900   BinarySearchTree::findMin(BinarySearchTree::Node*) [16]
                               35900             BinarySearchTree::findMin(BinarySearchTree::Node*) [16]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [161]
[17]     0.0    0.00    0.00       1         _GLOBAL__sub_I__ZN14GarrettCSCI33527DemoOperationSequenceReaderC2EiPPc [17]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [20]
-----------------------------------------------
                0.00    0.00       1/1           __libc_csu_init [161]
[18]     0.0    0.00    0.00       1         _GLOBAL__sub_I_main [18]
                0.00    0.00       1/1           __static_initialization_and_destruction_0(int, int) [19]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I_main [18]
[19]     0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [19]
-----------------------------------------------
                0.00    0.00       1/1           _GLOBAL__sub_I__ZN14GarrettCSCI33527DemoOperationSequenceReaderC2EiPPc [17]
[20]     0.0    0.00    0.00       1         __static_initialization_and_destruction_0(int, int) [20]
-----------------------------------------------
                0.00    0.00       1/1           GarrettCSCI335::DemoOperationSequenceReader::DemoOperationSequenceReader(int, char**) [2]
[21]     0.0    0.00    0.00       1         BinarySearchTree::BinarySearchTree() [21]
-----------------------------------------------
