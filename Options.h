#ifndef OPTIONS_H
#define OPTIONS_H


//#pragma once
#include <string>
#include <vector>
#include <map>

class Options 
{
    std::map <std::string,std::string> options;
public:
    Options(int argc,char **argv);
    std::string get(std::string option);
private:
    std::vector<std::string> parseOption(std::string option);
};

#endif
