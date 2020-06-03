/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "OperationBatchTester.h"
#include "Operation.h"
#include "HashTable.h"

#include <cstring>
#include <fstream>
#include <iostream>

namespace GarrettCSCI335 {
    
    OperationBatchTester::OperationBatchTester(int argc, char **argv){

        int64_t g, result;
        std::string operation_input_fname;

		// read filename argument

        for(g=0; g<argc; g++){
            if(strcmp(argv[g], "--operation_input_fname")==0){
                if(g+1 < argc){
                    operation_input_fname = argv[++g];
                }
            }
        }
        
        
        //read content of the file
        if(readOperationSequence(operation_input_fname)){
            
            std::cout << "Results:\n";
			{	// run sequence of the operatons with linear probing for Murmurhash64
				Operation<LinearProber, MurmurHasher64> linearMur64;
				for (auto t : _ops) {
					int64_t op, key, value;
					std::tie(op, key, value) = t;
					std::cout << linearMur64(op, key, value) << "\n";
				}
			}
			{	// run sequence of the operatons with linear probing for Murmurhash32
				Operation<LinearProber, MurmurHasher32> linearMur32;
				for (auto t : _ops) {
					int64_t op, key, value;
					std::tie(op, key, value) = t;
					std::cout << linearMur32(op, key, value) << "\n";
				}
			}
		}
		else 
		{
            std::cout << "Unable to read input operation sequence.\n";
            exit(1);
        }
    }

    //reading content of the operation file     
            
    bool OperationBatchTester::readOperationSequence(const std::string& filename){

        size_t num_op = 0;
        std::ifstream fin(filename);
        std::string buf;
       
        if(fin.fail()){
            std::cerr << "Input file opening failed.\n";
            return false;
        }
        while( fin >> buf ){
            if(buf== "NUM_OPERATIONS"){
                fin >> num_op;
                
                for(size_t g = 0; g < num_op; ++g)
				{
					int64_t op, key, value;
                    fin >> op >> key >> value;
					_ops.push_back(std::make_tuple(op, key, value));
                }
            }
        }
		return true;
    }
}

                
               
