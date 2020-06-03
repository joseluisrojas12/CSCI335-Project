
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <chrono>


#include "OperationFile.h"
#include "BinaryTree.h"
using namespace std;

#define RD      0
#define WR      1
#define RM      2
#define LDBT    3
#define WRBT    4

void makeOperations(OperationFile operations,BinaryTree<int> & BT)
{
    BTNode<int> *node;
    bool result;
    cout << "Performing " << operations.size() << " operations..." << endl;
    for(int i=0; i<operations.size(); i++)
    {
        switch(operations[i].operation)
        {
        case RD:
            cout << "Reading " << operations[i].key << ": ";
            node=BT.search(operations[i].key);
            if((node==NULL && operations[i].expectedResult==0) ||
               (node!=NULL && operations[i].expectedResult==1) )
               cout << "success" << endl;
            else
               cout << "failure" << endl;
            break;
        case WR:
            cout << "Writing " << operations[i].key << ": ";
            result=BT.insert(operations[i].key);
            if((!result && operations[i].expectedResult==0) ||
               (result && operations[i].expectedResult==1) )
               cout << "success" << endl;
            else
               cout << "failure" << endl;
            break;
        case RM:
            cout << "Deleting " << operations[i].key << ": ";
            result=BT.remove(operations[i].key);
            if((!result && operations[i].expectedResult==0) ||
               (result && operations[i].expectedResult==1) )
               cout << "success" << endl;
            else
               cout << "failure" << endl;
            break;
        case LDBT:
            cout << "Loading matrix " << endl;
            break;
        case WRBT:
            cout << "Writing matrix " << endl;
            break;                
        }
    }
    cout << "Operations completed." << endl;
}
/*
int main()
{
    string filename;
    cout << "Operation file?: ";
    getline(cin,filename);
    OperationFile operations(filename);

    BinaryTree<int> BT;
    
    chrono::time_point<chrono::system_clock> start, end;
    start=chrono::system_clock::now();
      
    makeOperations(operations,BT);        
    end=chrono::system_clock::now();
    chrono::nanoseconds elapsed_nanoseconds=end-start;
    cout<<"Total execution time: "<<(elapsed_nanoseconds.count()/1e9)<<endl;
    cout<<"Amortized cost per operation: "<<(elapsed_nanoseconds.count()/1e9/operations.size())<<endl;
    
    int h=BT.height();
    cout<<"Tree height (h): "<<h<<endl;
    int n=BT.size();
    cout<<"Tree nodes (n): "<<n<<endl;
    double exh=sqrt(n);
    cout<<"Expected height: "<<exh<<endl;
    cout<<"Height difference: "<<(exh-h)<<endl;
           
    return 0;
}
/*


