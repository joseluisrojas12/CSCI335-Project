#include "DemoOperationSequenceReader.h"

using std::cout;
using std::endl;

namespace GarrettCSCI335 {

    DemoOperationSequenceReader::DemoOperationSequenceReader(int argc, char ** argv){

        int64_t g;
        operation_sequence * os;
        char operation_input_fname[200];

        for(g=0; g<argc; g++){
            if(strcmp(argv[g], "--operation_input_fname")==0){
                if(g+1 < argc){
                    strcpy(operation_input_fname, &argv[++g][0]);
                }
            }
        }
        os = read_operation_sequence(operation_input_fname);
        for(g=0; g<os->num_operations; g++){
            switch(os->operation[g]){
                case 0:
                    cout << "READ " << os->key[g] << " " << os->expected_result[g] << endl;
                    // put the call to read from your ADT here
                    break;
                case 1:
                    cout << "WRITE " << os->key[g] << " " << os->expected_result[g] << endl;
                    // put the call to write to your ADT here
                    break;
                case 2:
                    cout << "DELETE " << os->key[g] << " " << os->expected_result[g] << endl;
                    // put the call to delete from your ADT here
                    break;
                default:
                    cout << "Invalid operation: " << os->operation[g] << endl;
            }
        }
    }
}
