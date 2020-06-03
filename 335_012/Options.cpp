#include "Options.h"
using namespace std;
#include<iostream>

// Constructor for the Options class, parses the command line argumments and fills a
// vector with the options found
Options::Options(int argc,char **argv)
{
    for(int opt=1; opt<argc; opt++) // go through all the arguments
    {
        vector<string> option=parseOption(string(argv[opt]));   // parse the current argument
        if(option.size()==2)    // if the option had a value (--option=value)
            options.insert(pair<string,string>(option[0],option[1]));   // save both parts in the hash map
        else if(option.size()==1)   // if the option has no value (--option)
            options.insert(pair<string,string>(option[0],"empty")); // save the option adding an empty value
    }
}

// return the value for the requested option if the option is in the option map,
// otherwise, it returns an empty string 
string Options::get(string option)
{
    if(options.size()==0)   // if the map is empty
        return "";
    map <string,string>::iterator it;
    it = options.find(option);  // search the option on the options map
    if (it!=options.end())  // if the option was found
        return options[option]; // return the value 
    else
        return "";
}

// parse a string that could represent an option --option=value, returns a vector
// that contains 0, 1 or 2 elements, 0 indicates no option was found in the string
// 1 = option without a value, 2=option and value
vector<string> Options::parseOption(string option)
{
    vector<string> parts;    
    if(option.substr(0,2) != "--")  // if no double dash is present, is not an option
        return parts; // return empty vector
    option=option.substr(2);
    size_t found = option.find("=");
    if(found!=string::npos)
    {
        string opt=option.substr(0,found);
        string rest=option.substr(found+1);
        found = rest.find("=");
        if (found!=string::npos)    // repeated  = sign
            return parts;   // return empty vector
        parts.push_back(opt);   // save found paris of option and value
        parts.push_back(rest);
    }
    else
        parts.push_back(option);    // single option
    return parts;
}
