#include"FIle.h"

File::File(){}
File::~File(){}
File::File(const string &name, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_){
    this->filename = name;
    this->indexClusterBegin = clusterBegin;
    this->size= size_;
}