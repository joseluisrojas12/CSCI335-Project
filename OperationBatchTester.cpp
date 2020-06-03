/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "OperationBatchTester.h"

using std::ifstream;
using std::ofstream;
using std::cout;

namespace GarrettCSCI335 {
    
    OperationBatchTester::OperationBatchTester(int argc, char **argv){

        int64_t g, result;

        for(g=0; g<argc; g++){
            if(strcmp(argv[g], "--operation_input_fname")==0){
                if(g+1 < argc){
                    strcpy(operation_input_fname, &argv[++g][0]);
                }
            }
        }
        if(readOperationSequence()){
            GarrettCSCI335::Operation operation(argc, argv);
            cout << "Results:\n";
            for(g=0; g<num_operations; g++){
                result = operation.doOperation(type[g],value[g]);
                cout << result << "\n";
            }
        } else {
            cout << "Unable to read input operation sequence.\n";
            exit(1);
        }
    }

    bool OperationBatchTester::readOperationSequence(){

        int64_t g;
        ifstream fin;
        char buf[200];

        fin.open(operation_input_fname);
        if(fin.fail()){
            cout << "Input file opening failed.\n";
            exit(1);
        }
        while( fin >> buf ){
            if(strcmp(buf, "NUM_OPERATIONS")==0){
                fin >> num_operations;
                type = new int64_t[num_operations];
                value = new int64_t[num_operations];
                for(g=0; g<num_operations; g++){
                    fin >> type[g] >> value[g];
                }
            }
        }
    }
}