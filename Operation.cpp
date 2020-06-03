/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Operation.h"
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3

using std::cout;

namespace GarrettCSCI335 {
    
    int64_t currentValue;
    
    Operation::Operation(int argc, char ** argv){

        currentValue = 0;
    }
    int64_t Operation::doOperation(int64_t type, int64_t value){

        int64_t g;

        switch(type){
            case ADD:
                currentValue += value;
                break;
            case SUB:
                currentValue -= value;
                break;
            case MUL:
                currentValue *= value;
                break;
            case DIV:
                currentValue /= value;
                break;
            default:
                cout << "Invalid operation type.\n";
                exit(1);
        }
        return currentValue;
    }
}