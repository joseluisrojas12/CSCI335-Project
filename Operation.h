/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Operation.h
 * Author: benjamin
 *
 * Created on September 6, 2017, 11:01 PM
 */

#ifndef OPERATION_H
#define OPERATION_H

    #include<cstdint>
    #include<fstream>
    #include<iostream>
    #include<string.h>

    namespace GarrettCSCI335 {
        class Operation {
        public:
            Operation(int argc, char ** argv);
            int64_t doOperation(int64_t type, int64_t value);
        private:
            int64_t currentValue;
        };
    }

#endif /* OPERATION_H */

