#include "MatrixOperationBatchTester.h"
#include <typeinfo>
using namespace std;

// sets the different options for the operation of the batch tester using the command
// line arguments 
bool MatrixOperationBatchTester::setOptions(int argc,char **argv)
{
    Options options(argc,argv);
    string arg;
    if((arg=options.get("matrix_input_fname"))!="")
    {
        if (arg=="empty")
        {
            cout << "ERROR: missing filename for option --matrix_input_fname" << endl;
            return false;
        }
        inputFilename=arg;   // get the input filename 
    }
    if((arg=options.get("results_output_fname"))!="")
    {
        if (arg=="empty")
        {
            cout << "ERROR: missing filename for option --results_output_fname" << endl;
            return false;
        }
        outputFilename=arg;   // get the output filename
    }
    if((arg=options.get("matrix_data_type"))!="")
    {
        if (arg=="empty")
        {
            cout << "ERROR: missing type for option --matrix_data_type" << endl;
            return false;
        }
        dataType=arg;   // get the type
    }
    return true;
}

// get the numerical value contained in the string sval
int MatrixOperationBatchTester::parseInteger(string sval)
{
    int val;
    stringstream ss(sval);   // parse the number
    ss >> val;
    return val;
}

// parses two consecutive lines on the file to get the number of rows and columns
// of the matrix saved in the file 
pair<int,int> MatrixOperationBatchTester::parseMatrixDimensions(ifstream &ifile)
{
    string line;
    pair<int,int> mn(-1,-1); // in case of an error, a negative value will be returned
    getline(ifile,line);
    if(line.substr(0,11)=="NUM_COLUMNS")
    {
        mn.second=parseInteger(line.substr(11));   // parse the number
        getline(ifile,line);
        if(line.substr(0,8)=="NUM_ROWS")
            mn.first=parseInteger(line.substr(8));   // parse the number
    }
    else if(line.substr(0,8)=="NUM_ROWS")    
    {
        mn.first=parseInteger(line.substr(8));   // parse the number
        getline(ifile,line);
        if(line.substr(0,11)=="NUM_COLUMNS")
            mn.second=parseInteger(line.substr(11));   // parse the number
    }
    return mn;
}

// parses the next line in the file to get the number of matrices saved in the file
int MatrixOperationBatchTester::parseNMatrices(ifstream &ifile)
{
    int nmatrices=-1;   // if an error is found, a negative value will be returned
    string line;
    getline(ifile,line);
    if(line.substr(0,12)=="NUM_MATRICES")
        nmatrices=parseInteger(line.substr(12));   // parse the number
    return nmatrices;
}


// Class constructor, initialize the options based on the command line arguments 
// and dispatches a templated test function based on the selected data type
MatrixOperationBatchTester::MatrixOperationBatchTester(int argc, char **argv)
{
    inputFilename="";
    outputFilename="";
    dataType="";
    if(setOptions(argc,argv)) // parse the command line options
    {
        if(inputFilename=="" || dataType=="")   // if no input file or no datatype was given, end tests
            return;
        if(outputFilename=="")
            outputFilename="output.txt";    // default output filename            
        if(dataType=="int")         // selects a templated function for the selected data type
            runTest<int>(argc,argv);
        else if(dataType=="int8_t") 
            runTest<int8_t>(argc,argv);
        else if(dataType=="uint8_t") 
            runTest<uint8_t>(argc,argv);
        else if(dataType=="int16_t") 
            runTest<int16_t>(argc,argv);
        else if(dataType=="uint16_t") 
            runTest<uint16_t>(argc,argv);
        else if(dataType=="int32_t") 
            runTest<int32_t>(argc,argv);
        else if(dataType=="uint32_t") 
            runTest<uint32_t>(argc,argv);
        else if(dataType=="int64_t") 
            runTest<int64_t>(argc,argv);
        else if(dataType=="uint64_t") 
            runTest<uint64_t>(argc,argv);
        else if(dataType=="float") 
            runTest<float>(argc,argv);
        else if(dataType=="double") 
            runTest<double>(argc,argv);
        else
        {
            cout << "ERROR: Unrecognized matrix data type" << endl;
            return;
        }
    }
}
