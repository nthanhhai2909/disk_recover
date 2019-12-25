#include "Hepler.h"

const int BYTE_PER_BOOT_SECTOR = 512;


void goToSectorOfFile(ifstream &f, vector<char> &data,const int &sectorRange, const int&numBytes) {
    f.seekg(sectorRange * numBytes);
    f.read(&data[0], numBytes);
}


bool convertCharToUint8InVector(const vector<char> &src, std::vector<uint8_t> &tar){
    if (src.size() != tar.size) {
        return false;
    }
    for (int i=0; i < src.size(); ++i){
        tar[i] = src[i];
    }
    return true;
}