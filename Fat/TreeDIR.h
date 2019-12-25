#ifndef __FILE_H__
#define __FILE_H__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include"Component.h"

using namespace std;


class TReeDIR: public Component {
    private:
        vector<Component*> files;
    public:
        TReeDIR(const vector<char> &rDET);
        void show();
        
};