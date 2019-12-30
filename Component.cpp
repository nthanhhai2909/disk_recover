#include"Component.h"

Component::Component(){
    
}
Component::~Component(){

}
Component::Component(const string &name_, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_){
    this->name = name_;
    this->type = type_;
    this->indexClusterBegin = clusterBegin;
    this->size = size_;
}
Component::Component(const string &name_, const char& type_,const uint32_t& clusterBegin, const uint32_t &size_, const uint32_t& rank_){
    this->name = name_;
    this->type = type_;
    this->indexClusterBegin = clusterBegin;
    this->size = size_;
    this->rank = rank_;
}
char Component::getType(){
    return this->type;
}
string Component::getName(){
    return this->name;
}
void Component::setState(const char& state_){
    this->state = state_;
}
char Component::getState(){
    return this->state;
}
void Component::setExt(const string& ext_){
    this->ext = ext_;
}
string Component::getExt(){
    return this->ext;
}
uint32_t Component::getIndexClusterBegin(){
    return this->indexClusterBegin;
}
uint32_t Component::getSize(){
    return this->size;
}
uint32_t Component::getRank(){
    return this->rank;
}