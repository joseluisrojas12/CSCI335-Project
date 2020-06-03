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
    #include<string.h>
    #include<fstream>
    #include<iostream>
    #include "Operation.h"

    namespace GarrettCSCI335 {
        class OperationBatchTester{
        public:
            OperationBatchTester(int argc, char **argv);
        private:
            int64_t * type;
            int64_t * value;
            int64_t num_operations;
            char operation_input_fname[200];
            bool readOperationSequence();
        };
    }

#endif /* OPERATIONBATCHTESTER_H */

