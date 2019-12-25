#ifndef __FILE_H__
#define __FILE_H__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include"Component.h"

using namespace std;

class File: public Component {
    private:
        string filename;
        char type;
        uint32_t indexClusterBegin;
        uint32_t size;
    public:
        File();
        ~File();
        File(const string &name, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_);
    public:
        void show();
};

#endif