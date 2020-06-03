
#include "OperationFile.h"
using namespace std;

const char *hid[]={"HAS_FEEDBACK","HAS_INDEXES","DELETIONS_ENABLED",
             "MAX_KEY","CAPACITY","MAX_LOAD","NUM_OPERATIONS"};
enum {HAS_FEEDBACK,HAS_INDEXES,DELETIONS_ENABLED,
      MAX_KEY,CAPACITY,MAX_LOAD,NUM_OPERATIONS};

Operation& OperationFile::operator[](int i) {
	return operations[i];
}

void OperationFile::setProperty(int property,int value)
{
    switch(property)
    {
        case HAS_FEEDBACK:
            feedback=value;
            break;
        case HAS_INDEXES:
            indexes=value;
            break;
        case DELETIONS_ENABLED:
            deletions=value;
            break;
        case MAX_KEY:
            maxKey=value;
            break;
        case CAPACITY:
            capacity=value;
            break;
        case MAX_LOAD:
            maxLoad=value;
            break;
        case NUM_OPERATIONS:
            numOperations=value;
            break;
    }
}

void OperationFile::parseHeader(ifstream &ifile)
{
    feedback = -1;
    indexes = -1; 
    deletions = -1;
    maxKey = -1;
    capacity = -1;
    maxLoad = -1;
    numOperations=-1;
    vector<string> ids(hid,hid+7);
    string line;
    bool done=false;
    while(!done)
    {
        size_t pos=ifile.tellg();
        getline(ifile,line);
        unsigned i;
        for(i=0; i<ids.size(); i++)        
            if(line.substr(0,ids[i].length())==ids[i] && isspace(line[ids[i].length()]))
            {
                stringstream ss(line.substr(ids[i].length()));   // parse the number
                int value;   // parse the number
                ss >> value;
                setProperty(i,value);
                break;
            }
        if(i==ids.size())
        {
            ifile.seekg(pos,std::ios::beg);
            done=true;
        }
    }
}


OperationFile::OperationFile(string filename)
{
    ifstream ifile;
    ifile.open(filename.c_str());
    if(!ifile.is_open())
    {
        cout << "ERROR: unable to open file " << filename << endl;
        exit(1);
    }
    parseHeader(ifile);   
    if(feedback == -1 || indexes == -1 ||  deletions == -1 || maxKey == -1 ||
        capacity == -1 || maxLoad == -1 || numOperations == -1)
    {
        cout << "ERROR: invalid file."<< endl;
        exit(1);
    }
    string line;
    for (int i=0; i<numOperations; i++)
    {
        if(getline(ifile,line)) {
            Operation op;
            stringstream ss(line);   // parse the number
            ss >> op.operation;
            ss >> op.key;
            ss >> op.expectedResult;
            operations.push_back(op); 
        }
        else
        {
            cout << "ERROR: invalid file."<< endl;
            exit(1);
        }
    }
    ifile.close();
}






