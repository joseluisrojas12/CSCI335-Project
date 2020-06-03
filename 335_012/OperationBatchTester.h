/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OperationBatchTester.h
 * Author: benjamin
 *
 * Created on September 6, 2017, 11:02 PM
 */

#ifndef OPERATIONBATCHTESTER_H
#define OPERATIONBATCHTESTER_H

#include<cstdint>
#include<cstdlib>
#include <vector>
#include <bits/stdc++.h>
#include <string>


    #include<string.h>
    #include<fstream>
    #include<iostream>
    #include "Operation.h"

    namespace GarrettCSCI335 {
        class OperationBatchTester{
        public:
            OperationBatchTester(int argc, char **argv);
        private:
            //Each operation with the hash table has his own code, key and value
            
            typedef std::tuple<int64_t, int64_t, int64_t> operation_bundle_type;

		    // sequence of the operations
		    std::vector<operation_bundle_type> _ops;
                        
            bool readOperationSequence(const std::string& );
        };
    }

#endif /* OPERATIONBATCHTESTER_H */

