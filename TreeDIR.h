#ifndef __TREEDIR_H__
#define __TREEDIR_H__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <stack>

#include "Helper.h"

#include"Component.h"
#include "File.h"


using namespace std;


class TreeDIR: public Component {
    private:
        std::vector<Component*> files;
        uint32_t numItems;
        Helper *helper;
    public:
        TreeDIR();
        ~TreeDIR();
        TreeDIR(const uint32_t&);
        TreeDIR(const vector<char> &rDET);
        TreeDIR(const string &name, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_);
        TreeDIR(const string &name, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_, 
            const uint32_t& rank_, std::ifstream &f, const uint32_t& idxSector, const uint32_t& bytesPerSector, 
            const uint32_t& beginSectorArea, const uint32_t& sectorPerCluster);
    public:
        void show();
        void add(Component*);
        bool vectorIsEmpty(const vector<char>&);
        int getNumItems();
        bool entryIsEmpty(const vector<char>&);
        void listFile();
        vector<Component*> getListFileWithExt(const std::string&);
        vector<Component*> getListDeletedFileWithExt(const std::string&);
        vector<Component*> getAllFiles();
        vector<Component*> getListDeletedFile();
    public:
        string getExtFromName(const string&);
        void printListFile(const vector<Component*>&);
};

#endif