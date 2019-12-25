#ifndef __VOLUME_FAT__
#define __VOLUME_FAT__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "Hepler.h"

/*
        ** Chu y: thu tu cluster cua vung data bat dau tu 2
        ** Sector bat dau cua file/thu muc
        ** S = Sb + Sf*Nf * + [Srdet] + (k-2)*Sc 
        ** hoac S = begin_sector_data_area + (k-2)*sectors_per_cluster
        ** voi k la cluster bat dau cua file/directory
        */

class Fat
{
private:
    uint32_t posBeginLBA;
    char jumpInstruction[3];
    char OEM_ID[8];
    uint16_t bytePerSector;
    uint8_t sectorPerCluter;
    uint16_t sectorBeforeFATTable;
    uint8_t numFatTable;
    uint16_t entrieOfRDET;
    uint16_t sectorOfVolume;
    uint8_t volumeSignature;
    uint16_t sectorOfFat;
    uint16_t sectorPerTrack;
    uint16_t numberOfHead;
    uint32_t distanceVolDescribeToVolBegin;
    uint32_t volumeSize;
    uint8_t diskPhysicalSignature;
    uint8_t OSSignature;
    uint32_t volumeSerialNumber;
    char volumeLabel;
    char fatType[8];
    uint16_t endSectorMarker;

public:
    Fat();
    ~Fat();
    Fat(const vector<uint8_t> &bootSector);
    void setAttrsFromBootSector(const vector<uint8_t> &bootSector);
    void showREETTRee(const vector<uint8_t> &rDET);
    // int indexOfFile();

public:
    uint32_t getBeginSectorRDET();
    uint16_t getSectorsBeforeFATTable();
    uint16_t getSectorsOfFAT();
    uint8_t getNumFATTable();
    uint32_t getBeginSectorDataArea();
    uint32_t getRDETSize();
    uint16_t getEntriesOfRDET();
    uint16_t getBytesPerSector();
    uint8_t getSectorsPerCluster();
    uint16_t getBytesPerSector();
    
};

#endif