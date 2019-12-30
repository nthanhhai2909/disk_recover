#ifndef __COMPONENT__
#define __COMPONENT__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdint.h>

using namespace std;

class Component {
    protected:
        char state;
        std::string name;
        char type;
        uint32_t indexClusterBegin;
        uint32_t size;
        uint32_t rank;
        std::string ext;
    public:
        Component();
        ~Component();
        Component(const string &name_, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_);
        Component(const string &name_, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_, const uint32_t &rank_);
    public:
        virtual void show() = 0;
        virtual void listFile() = 0;
        virtual vector<Component*> getListFileWithExt(const std::string&) = 0;
        virtual vector<Component*> getListDeletedFileWithExt(const std::string&) = 0;
        virtual vector<Component*> getAllFiles() = 0;
        virtual vector<Component*> getListDeletedFile() = 0;
        void setState(const char&);
        void setExt(const string&);
        string getName();
        string getExt();
        char getState();
        char getType();
        uint32_t getIndexClusterBegin();
        uint32_t getSize();
        uint32_t getRank();
};

#endif