#ifndef __VOLUME_FAT__
#define __VOLUME_FAT__

#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <string>

#include"Helper.h"
#include"Component.h"
#include"TreeDIR.h"

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

    TreeDIR *treeDir;
    Helper *helper;

public:
    Fat();
    ~Fat();
    Fat(const vector<uint8_t> &bootSector, std::ifstream &);
    void setAttrsFromBootSector(const vector<uint8_t> &bootSector);

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
    public:
        void recoverAllFile(std::ifstream &f,const string&);
        void recoverFileWithExt(std::ifstream &f, const string&, const std::string&);
        void readDataAndWriteToFile(std::ifstream & fi, std::ofstream &fo, const uint32_t&, char*, const int &blockSize);
        void listFile();
        void tree();
};

#endif