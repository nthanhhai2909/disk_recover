#include <iostream>
#include <curses.h>
#include <fstream>
#include "Helper.h"
#include "Fat.h"
#include <stdlib.h>
#include <cstdlib>

using namespace std;

const int BYTE_PER_BOOT_SECTOR = 512;
const int BYTE_PER_RDET_ENTRY = 32;

int main()
{
    Helper *helper = new Helper();

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
    // goToSectorOfFile(file, initData, 0, BYTE_PER_BOOT_SECTOR);
    helper->dump_random_data(file, initData, 0, BYTE_PER_BOOT_SECTOR);
    vector<uint8_t> bootSector(BYTE_PER_BOOT_SECTOR);
    // convertCharToUint8InVector(initData, bootSector);
    helper->covert_char_vec_to_uint8_vec(initData, bootSector);

    Fat *fat = new Fat(bootSector, file);

    // vector<char> RDETHex(fat->getEntriesOfRDET() * BYTE_PER_RDET_ENTRY);
    // goToSectorOfFile(file, RDETHex, fat->getBeginSectorRDET(), fat->getEntriesOfRDET() * BYTE_PER_RDET_ENTRY);

    // Sb: SO SECTOR TRUOC BAN FAT
    // Sf: So sector cua mot bang FAT
    // Nf: so luong ban FAT
    // Srdet: Kich thuoc ROOT DIRECT ENTRY TABLE (SECTOR)
    // K :
    // S = Sb + Sf*Nf * + [Srdet] + (k-2)*Sc
    // K indxex cluter bat dau cua file (2: cluster duoc danh index tu 2 tro di)
    // Sc: So sector tren mot cluster

    // file.seekg((fat->getBeginSectorDataArea()+(16-2)*fat->getSectorsPerCluster())*fat->getBytesPerSector());
    // ofstream f("record.pdf", std::ios::binary|std::ios::out);
    // char hexbyte;
    // int sizeFile = 257553;
    // for (int i=0;i<sizeFile;++i){
    //     file.read(&hexbyte, 1);
    //     f.write(&hexbyte, 1);
    // }
    // f.close();

    std::string ext;
    char option;

    const int dir_err = system("mkdir -p recoverFolder");
    if (-1 == dir_err)
    {
        printf("Error creating directory!n");
        exit(1);
    }

    while (true)
    {
        cout << "***************** OPTION *****************" << endl;
        cout << "***************** 1: Recover all *********" << endl;
        cout << "***************** 2: Recover file with ext *******" << endl;
        cout << "***************** 3: show tree *******" << endl;
        cout << "***************** 4: Exist: **************" << endl;

        std::cout << "Choose option: ";
        std::cin >> option;
        switch (option)
        {
        case '1':
            fat->recoverAllFile(file, "recoverFolder");
            break;
        case '2':
            std::cout << "Nhap ten file mo rong: ";
            std::cin >> ext;
            fat->recoverFileWithExt(file, "recoverFolder", ext);
            break;
        case '3':
            fat->tree();
            break;
        case '4':
            exit(EXIT_SUCCESS);
            break;
        default:
            std::cout << "Lua chon khong hop le!" << std::endl;
            break;
        }
    }

    std::cout << std::endl;
    file.close();

    delete fat;
    delete helper;

    return 0;
}
