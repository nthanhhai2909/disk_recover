#include "TreeDIR.h"



TreeDIR::TreeDIR(){
    this->helper = new Helper();
    this->numItems = 0;
}
TreeDIR::~TreeDIR(){
    delete this->helper;
}
TreeDIR::TreeDIR(const vector<char> &rDET){
    this->helper = new Helper();
    this->numItems = 0;
}
TreeDIR::TreeDIR(const uint32_t& beginCluster){
    this->helper = new Helper();
    this->numItems = 0;
}
TreeDIR::TreeDIR(const string &name, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_)
    :Component(name, type_, clusterBegin, size_){
        this->helper = new Helper();
}
TreeDIR::TreeDIR(const string &name, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_, 
    const uint32_t &rank_, std::ifstream &f, const uint32_t& idxSector, const uint32_t& bytesPerSector, 
    const uint32_t& beginSectorArea, const uint32_t& sectorPerCluster)
        :Component(name, type_, clusterBegin, size_, rank_){
    
    this->helper = new Helper();

    std::string name_temp = "";
    char type_temp = 0x10;
    uint32_t indexClusterBegin_temp = 0;
    uint32_t size_temp = 0;
    uint32_t rank_temp = 0;
    uint32_t idxBytes_temp = idxSector*bytesPerSector;
    uint32_t idxSector_temp = 0;
    std::string ext_temp = "";
    char state_temp = 0xe5;

    std::vector<char> ext_entries;
    std::vector<char> entry(32);
    f.seekg(idxBytes_temp);
    f.read(&entry[0], 32);
    int i, j;
    // int count = 0;
    while (this->entryIsEmpty(entry)==false)
    {
        if (entry[11]==0x0f){//Entry phu
            for (i=1;i<32;++i) //offset dau moi entry khong dung vi no dung de chi trang thai (xoa, con,...)
                ext_entries.push_back(entry[i]);
            // std::cout << "Vao: " << ext_entries.size() << std::endl;
        }
        else // Entry chinh
        {
            state_temp = entry[0];
            name_temp = "";
            if (ext_entries.size() == 0){ //Khong co entry phu
                for (i=0;i<6;++i){ // 2byte 6,7 la ~1
                    if (isgraph(entry[i]))
                        name_temp += entry[i];
                }
                if (entry[11]!=0x10){
                    name_temp += '.';
                    for (i=8;i<11;++i){
                    if (isgraph(entry[i]))
                        name_temp += entry[i];
                        ext_temp += entry[i];
                    }
                }
            }
            else //co entry phu
            {
                for (i=ext_entries.size()/31-1;i>=0;--i){
                    for (j=0;j<31;++j){
                        if (j!=12 && isgraph(ext_entries[31*i+j]))
                            name_temp += ext_entries[31*i+j];
                    }
                }
                ext_entries.clear();
            }
            type_temp = entry[11];
            rank_temp = rank + 1;
            indexClusterBegin_temp = uint32_t((((((uint8_t(entry[21])<<8)|uint8_t(entry[20]))<<8)|uint8_t(entry[27]))<<8)|uint8_t(entry[26]));
            size_temp = uint32_t((((((uint8_t(entry[31])<<8))|uint8_t(entry[30]))<<8)|uint8_t(entry[29]))<<8)|uint8_t(entry[28]);
            idxSector_temp = beginSectorArea + (indexClusterBegin_temp - 2)*sectorPerCluster;

            if (type_temp == 0x10){
                if (name_temp == ".." || name_temp == "."){
                    Component* file = new File(name_temp, type_temp, indexClusterBegin_temp, size_temp, rank_temp);
                    file->setState(entry[0]);
                    // cout << "Create folder - " << file->getName() << " - with type " << std::hex << int(file->getType()) << std::endl;
                    this->files.push_back(file);
                }
                else{
                    Component* folder = new TreeDIR(name_temp, type_temp, indexClusterBegin_temp, size_temp, rank_temp, f, idxSector_temp, bytesPerSector, beginSectorArea, sectorPerCluster);
                    folder->setState(entry[0]);
                    // cout << "Create folder - " << folder->getName() << " - with type " << std::hex << int(folder->getType()) << std::endl;
                    this->files.push_back(folder);
                }
            }
            else{
                // std::cout << "New file\n";
                type_temp = entry[11];
                Component* file = new File(name_temp, type_temp, indexClusterBegin_temp, size_temp, rank_temp);
                file->setState(entry[0]);
                ext_temp = this->getExtFromName(name_temp);
                file->setExt(ext_temp);
                this->files.push_back(file);
            }
        }
        idxBytes_temp += 32;
        f.seekg(idxBytes_temp);
        f.read(&entry[0], 32);
        
        // ++count;
        // if (count == 50) // Max 512 -> so entry cua RDET
        //     return;
    }
    
}
void TreeDIR::show(){
    if (int(this->state) != 0xffffffe5)
        cout << std::setw(this->rank*3) << "" << "|--" << this->name  << endl;
    else
    {
        cout << std::setw(this->rank*3) << "" << "|--" << this->name << " (Deleted)" << endl;
    }
    
    //cout << std::setw(this->rank*3) << "|-" << std::setw(2) << this->type << std::setw(15) << this->size  << std::setw(15) << this->indexClusterBegin << "   " <<this->name << endl;
    for (int i=0;i<this->files.size();++i){
        this->files[i]->show();
    }
}
void TreeDIR::add(Component* items){
    this->files.push_back(items);
}
bool TreeDIR::vectorIsEmpty(const vector<char>&entry){
    for (int i=0;i<entry.size();++i){
        if (entry[i] != 0x00)
            return false;
    }
    return true;
}
bool TreeDIR::entryIsEmpty(const vector<char>&enrty){
    return enrty[0]==0x00;
}
int TreeDIR::getNumItems(){
    return this->files.size();
}
void TreeDIR::listFile(){
    for (int i=0;i<this->files.size();++i){
        if (this->files[i]->getType() != 0x10){
            std::cout << "Size: " << std::hex << uint32_t(files[i]->getSize()) << " - File name: " << files[i]->getName() << std::endl;
        }
        else{
            if (this->files[i]->getName() != "." && this->files[i]->getName() != ".."){
                this->listFile();
            }
        }
    }
}
vector<Component*> TreeDIR::getListFileWithExt(const std::string& ext_){
    vector<Component*> res;
    for (int i=0;i<this->files.size();++i){
        if (this->files[i]->getType() != 0x10){
            if (this->files[i]->getExt() == ext_)
                res.push_back(this->files[i]);
        }
        else{
            if (this->files[i]->getName() != "." && this->files[i]->getName() != ".."){
                vector<Component*> subFiles = this->files[i]->getListFileWithExt(ext_);
                res.insert(res.end(), subFiles.begin(), subFiles.end());
            }
        }
    }
    return res; 
}
vector<Component*> TreeDIR::getAllFiles(){
    vector<Component*> res;
    for (int i=0;i<this->files.size();++i){
        if (this->files[i]->getType() != 0x10){
            res.push_back(this->files[i]);
        }
        else{
            if (this->files[i]->getName() != "." && this->files[i]->getName() != ".."){
                vector<Component*> subFiles = this->files[i]->getAllFiles();
                res.insert(res.end(), subFiles.begin(), subFiles.end());
            }
        }
    }
    return res; 
}
vector<Component*> TreeDIR::getListDeletedFileWithExt(const std::string& ext_){
    vector<Component*> res;
    if (int(this->getState()) == 0xffffffe5){
        for (int i=0;i<this->files.size();++i){
            // cout << "File name: " << this->files[i]->getName() << " - Type: " << std::hex << int(this->files[i]->getType()) << std::endl;
            if (this->files[i]->getType() != 0x10){
                if (this->files[i]->getExt() == ext_)
                    res.push_back(this->files[i]);
            }
            else{
                // cout << "Vao de quy\n";
                if (this->files[i]->getName() != "." && this->files[i]->getName() != ".."){
                    vector<Component*> subFiles = this->files[i]->getListDeletedFileWithExt(ext_);
                    res.insert(res.end(), subFiles.begin(), subFiles.end());
                }
            }
        }
    }
    else{
        for (int i=0;i<this->files.size();++i){
            // cout << "File name: " << this->files[i]->getName() << " - Type: " << std::hex << int(this->files[i]->getType()) << std::endl;
            if (this->files[i]->getType() != 0x10){
                if (this->files[i]->getExt() == ext_ && int(this->files[i]->getState()) == 0xffffffe5)
                    res.push_back(this->files[i]);
            }
            else{
                // cout << "Vao de quy\n";
                if (this->files[i]->getName() != "." && this->files[i]->getName() != ".."){
                    vector<Component*> subFiles = this->files[i]->getListDeletedFileWithExt(ext_);
                    res.insert(res.end(), subFiles.begin(), subFiles.end());
                }
            }
        }
    }
    return res; 
}
vector<Component*> TreeDIR::getListDeletedFile(){
    vector<Component*> res;
    if(int(this->getState()) == 0xffffffe5){
        for (int i=0;i<this->files.size();++i){
            // cout << "File name: " << this->files[i]->getName() << " - Type: " << std::hex << int(this->files[i]->getType()) << std::endl;
            if (this->files[i]->getType() != 0x10){
                res.push_back(this->files[i]);
            }
            else{
                // cout << "Vao de quy\n";
                if (this->files[i]->getName() != "." && this->files[i]->getName() != ".."){
                    vector<Component*> subFiles = this->files[i]->getListDeletedFile();
                    res.insert(res.end(), subFiles.begin(), subFiles.end());
                }
            }
        }
    }
    else{
        for (int i=0;i<this->files.size();++i){
            if (this->files[i]->getType() != 0x10){
                if (int(this->files[i]->getState()) == 0xffffffe5)
                    res.push_back(this->files[i]);
            }
            else{
                if (this->files[i]->getName() != "." && this->files[i]->getName() != ".."){
                    vector<Component*> subFiles = this->files[i]->getListDeletedFile();
                    res.insert(res.end(), subFiles.begin(), subFiles.end());
                }
            }
        }
    }
    return res; 
}

string TreeDIR::getExtFromName(const string& name){
    string res = "";
    int pos = name.find_last_of('.');
    if (pos != -1){
        res = name.substr(pos+1);
    }
    return res;
}
void TreeDIR::printListFile(const vector<Component*>&listFile){
    for (int i=0;i<listFile.size();++i)
        cout << "Type: " << "File" << " - Size: " << listFile[i]->getSize()  << " - Cluster begin: " << listFile[i]->getIndexClusterBegin() << " - File name: " << listFile[i]->getName() << endl;
}