#include <iostream>
#include <curses.h>
#include <fstream>
#include "Hepler.h"
#include "Fat.h"

using namespace std;

const int BYTE_PER_BOOT_SECTOR = 512;
const int BYTE_PER_RDET_ENTRY = 32;

int main()
{
    cout << "DISK RECOVER FAT16" << endl;
    cout << "ENTER DISK TO RECOVER: " << ends;
    string diskname;
    cin >> diskname;
    cout << "Diskname: " << diskname << endl;

    ifstream file(diskname.c_str(), ios::binary | ios::in);
    if (!file)
    {
        std::cerr << diskname << " Exiting..." << '\n';
        return 1;
    }

    vector<char> initData(BYTE_PER_BOOT_SECTOR);
    goToSectorOfFile(file, initData, 0, BYTE_PER_BOOT_SECTOR);
    vector<uint8_t> bootSector(BYTE_PER_BOOT_SECTOR);
    convertCharToUint8InVector(initData, bootSector);

    Fat *fat = new Fat(bootSector);
    
    vector<char> RDETHex(fat->getEntriesOfRDET() * BYTE_PER_RDET_ENTRY);
    goToSectorOfFile(file, RDETHex, fat->getBeginSectorRDET(), fat->getEntriesOfRDET() * BYTE_PER_RDET_ENTRY);

    // Sb: SO SECTOR TRUOC BAN FAT
    // Sf: So sector cua mot bang FAT
    // Nf: so luong ban FAT
    // Srdet: Kich thuoc ROOT DIRECT ENTRY TABLE (SECTOR)
    // K :
    // S = Sb + Sf*Nf * + [Srdet] + (k-2)*Sc 
    // K indxex cluter bat dau cua file (2: cluster duoc danh index tu 2 tro di)
    // Sc: So sector tren mot cluster

    file.seekg((fat->getBeginSectorDataArea()+(16-2)*fat->getSectorsPerCluster())*fat->getBytesPerSector()); 

    ofstream f("record.pdf", std::ios::binary|std::ios::out);
    char hexbyte;
    int sizeFile = 257553;
    for (int i=0;i<sizeFile;++i){
        file.read(&hexbyte, 1);
        f.write(&hexbyte, 1);
    }
    f.close();

    std::cout << std::endl;
    file.close();

    return 0;
    
    char option;
    while (true)
    {
        cout << "***************** OPTION *****************" << endl;
        cout << "***************** 1: Recover all *****************" << endl;
        cout << "***************** 2: Recover file: *****************" << endl;
        cout << "***************** 3: Exist: *****************" << endl;
        option = getchar();

        cout << option << endl;
        if (option == '3')
        {
            break;
        }
        else if (option == 1)
        {
            cout << "haha";
            break;
        }
    }

    file.close();
    return 0;
}