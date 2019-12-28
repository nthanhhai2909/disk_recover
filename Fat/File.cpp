#include"File.h"

File::File(){}
File::~File(){}
File::File(const string &name_, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_)
    :Component(name_, type_, clusterBegin, size_){}
File::File(const string &name_, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_, const uint32_t& rank_)
    :Component(name_, type_, clusterBegin, size_, rank_){}
void File::show(){
    if (int(this->state) == 0xffffffe5)
        cout << std::setw(this->rank*3) << "" << "|--" << this->name << " (Deleted)" << " - Size: " << this->size << endl;
    else
        cout << std::setw(this->rank*3) << "" << "|--" << this->name << " - Size: " << this->size << endl;
    //cout << std::setw(this->rank*3) << "|-" << std::setw(2) << this->type << std::setw(15) << this->size  << std::setw(15) << this->indexClusterBegin << "   " <<this->name << endl;
}

void File::listFile(){
    cout << "Type: " << "File" << " - Size: " << this->size  << " - Cluster begin: " << this->indexClusterBegin << " - File name: " <<this->name << endl;
}
vector<Component*> File::getListFileWithExt(const std::string& ext_){
    vector<Component*> res;
    return res;
}
vector<Component*> File::getListDeletedFileWithExt(const std::string& ext_){
        vector<Component*> res;
    return res;
}
vector<Component*> File::getAllFiles(){    
    vector<Component*> res;
    return res;
}
vector<Component*> File::getListDeletedFile(){
    vector<Component*> res;
    return res;
}