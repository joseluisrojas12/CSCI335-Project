#ifndef OPERATIONFILE_H
#define OPERATIONFILE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <cstdlib>

typedef struct
{
    int operation;
    int key;
    int expectedResult;
}Operation;

class OperationFile
{    
    int feedback;
    int indexes;
    int deletions;
    int maxKey;
    int capacity;
    int maxLoad;
    int numOperations;
    std::vector <Operation> operations;
public:
    OperationFile(std::string filename);    
	Operation& operator[](int i);
	int size() 
	{
	    return numOperations;
	}
private:
    void setProperty(int property,int value);
    void parseHeader(std::ifstream &ifile);
};

#endif
