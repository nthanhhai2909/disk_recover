#ifndef __FOLDER__
#define __FOLDER__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include"FIle.h"
#include"Component.h"

using namespace std;


class Folder: public Component {
    private:
        string folerName;
        char type;
        uint32_t indexClusterBegin;
        uint32_t size;
        vector<File*> files;
        vector<Folder*> folders;
    public:
        Folder();
        ~Folder();
        Folder(const string &name, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_);
    public:
        void show();
        void addFolder(Folder* folder);
        void addFile(File* file)
}

#endif