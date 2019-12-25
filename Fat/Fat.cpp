
#include "Fat.h"

Fat::Fat(){}
Fat::~Fat(){}


const int BYTE_PER_BOOT_SECTOR = 512;


Fat::Fat(const vector<uint8_t> &bootSector){
    this->setAttrsFromBootSector(bootSector);
}

uint16_t Fat::getSectorsOfFAT(){
    return this->sectorOfFat;
}

uint16_t Fat::getSectorsBeforeFATTable(){
    return this->sectorBeforeFATTable;
}

uint32_t Fat::getBeginSectorRDET(){
    return this->getSectorsBeforeFATTable() + this->getSectorsOfFAT()*this->getNumFATTable();
}

uint8_t Fat::getNumFATTable(){
    return this->numFatTable
}

uint32_t Fat::getBeginSectorDataArea(){
    return this->getBeginSectorRDET()+this->getRDETSize();
}

uint16_t Fat::getEntriesOfRDET(){
    return this->entrieOfRDET;
}
uint16_t Fat::getBytesPerSector(){
    return this->bytePerSector;
}

uint32_t Fat::getRDETSize() //sector
{
    return (this->getEntriesOfRDET()* 32) /this->getBytesPerSector();
}

uint8_t Fat::getSectorsPerCluster(){
    return this->sectorPerCluter;
}

uint16_t Fat::getBytesPerSector(){
    return this->bytePerSector;
}



void Fat::setAttrsFromBootSector(const vector<uint8_t> &bootSector){
    int i;
    if (bootSector.size() != BYTE_PER_BOOT_SECTOR) {
        return;
    }

    for (i=0;i<3;++i){
        this->jumpInstruction[i] = char(bootSector[i]);
    }
    for (i=0;i<8;++i){
        this->OEM_ID[i] = char(bootSector[3+i]);
    }

    // volume infor
    this->OSSignature = uint8_t(bootSector[38]);
    this->volumeSerialNumber = uint32_t((((((bootSector[42]<<8)|bootSector[41])<<8)|bootSector[40])<<8)|bootSector[39]);
    this->volumeSize = uint32_t((((((bootSector[35]<<8)|bootSector[34])<<8)|bootSector[33])<<8)|bootSector[32]);
    this->volumeSignature = uint8_t(bootSector[21]);
    this->diskPhysicalSignature = uint8_t(bootSector[36]);
    this->volumeLabel = char(bootSector[43]);
    this->sectorOfVolume = uint16_t((bootSector[20]<<8)|bootSector[19]);

    // FAT 16 information 
    this->bytePerSector = uint16_t((bootSector[12]<<8)|bootSector[11]);
    this->sectorBeforeFATTable = uint16_t((bootSector[15]<<8)|bootSector[14]);
    this->sectorPerCluter = uint8_t(bootSector[13]);
    this->numFatTable = uint8_t(bootSector[16]);
    this->entrieOfRDET = uint16_t((bootSector[18]<<8)|bootSector[17]);
    this->sectorOfFat = uint16_t((bootSector[23]<<8)|bootSector[22]);
    this->sectorPerTrack = uint16_t((bootSector[25]<<8)|bootSector[24]);
    this->numberOfHead = uint16_t((bootSector[27]<<8)|bootSector[26]);
    this->distanceVolDescribeToVolBegin = uint32_t((((((bootSector[31]<<8)|bootSector[30])<<8)|bootSector[29])<<8)|bootSector[28]);
    for (i=0;i<8;++i){
        this->fatType[i] = char(bootSector[54+i]);
    }
    this->endSectorMarker = uint16_t((bootSector[510]<<8)|bootSector[511]);
}

void Fat::showREETTRee(const vector<uint8_t> &rDET) {
    
}