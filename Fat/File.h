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
    public:
        File();
        ~File();
        File(const string &name, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_);
        File(const string &name, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_,const uint32_t &rank_);
    public:
        void show();
        void listFile();
        vector<Component*> getListFileWithExt(const std::string&);
        vector<Component*> getListDeletedFileWithExt(const std::string&);
        vector<Component*> getAllFiles();
        vector<Component*> getListDeletedFile();
};

#endif