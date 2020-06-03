#include "DemoOperationSequenceReader.h"
#include "Matrix.h"

#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;

namespace GarrettCSCI335 {

    DemoOperationSequenceReader::DemoOperationSequenceReader(int argc, char ** argv){
        BinarySearchTree *bst = new BinarySearchTree();

        int64_t g;
        uint64_t num_errors;
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
        num_errors = 0;
        for(g=0; g<os->num_operations; g++){
            bool result;

            switch(os->operation[g]){
                case 0:
                    result = bst->read(os->key[g]);
                    cout << "READ " << os->key[g] << "\nEXPECTED " << os->expected_result[g]
                            << " ACTUAL " << result << endl;
                    if(result != os->expected_result[g]){
                      num_errors++;
                    }
                    break;
                case 1:
                    result = bst->write(os->key[g]);
                    cout << "WRITE " << os->key[g] << "\nEXPECTED " << os->expected_result[g]
                            << " ACTUAL " << result << endl;
                    if(result != os->expected_result[g]){
                      num_errors++;
                    }
                    break;
                case 2:
                    result = bst->remove(os->key[g]);
                    cout << "DELETE " << os->key[g] << "\nEXPECTED " << os->expected_result[g]
                            << " ACTUAL " << result << endl;
                    if(result != os->expected_result[g]){
                      num_errors++;
                    }
                    break;
                case 3:
				{
					Matrix<int64_t> m(os->max_key, os->max_key);
					std::ifstream ifile(os->input_fname);
					if(!ifile.is_open())
						std::cout << "ERROR: unable to open input file!" << std::endl;
					else 
					{
						ifile >> m;
						ifile.close();
					}
					int result  = bst->ancestorTree(m);
                    cout << "SERIALIZE from "<< os->input_fname <<"\nEXPECTED " << os->expected_result[g]
                            << " ACTUAL " << result << endl;
                    break;
				}
                case 4:
				{
					Matrix<int64_t> m(os->max_key, os->max_key);
					int result  = bst->ancestorMatrix(m);
                    cout << "SERIALIZE to "<< os->output_fname <<"\nEXPECTED " << os->expected_result[g]
                            << " ACTUAL " << result << endl;
					ofstream ofile(os->output_fname);
					if(!ofile.is_open())
						std::cout << "ERROR: unable to open output file!" << std::endl;
					else 
					{
						ofile << m ;
						ofile.close();
					}
                    break;
				}
                default:
                    cout << "Invalid operation: " << os->operation[g] << endl;
            }
        }
        cout << "Num errors = " << num_errors << endl;
    }
}
