#include"Helper.h"


Helper::Helper(){}
Helper::~Helper(){}

void Helper::set_code_mapping_type_fs(std::map<uint8_t, std::string> &code_mapping_type_fs, const std::vector<uint8_t> &code, const std::vector<std::string> &type_fs){
    for (int i=0;i< code.size();++i){
        code_mapping_type_fs[code[i]] = type_fs[i]; 
    }
}

void Helper::show_hex_data_dump(const std::vector<char> data,const int &sector_range){
    int count = 0;

    std::cout << "_________________|__";
    for (int i=0;i<16;++i){
        std::cout << std::setfill('0') << std::setw(2) << std::hex << i << " ";
    }
    std::cout << "_|________________" << std::endl;
    std::cout << "=================|===================================================|=================" << std::endl;
    std::cout << "0x" << std::setfill('0') << std::setw(13) << std::hex << 512*sector_range << "  |  ";
    while (count < data.size()){
        ++count;
        printf("%02hhx ", data[count-1]);
        if (count % 16 == 0){
            std::cout << " | ";
            for (int i=count-16;i<count;++i){
                if (isgraph(data[i])){
                    std::cout << data[i];
                }
                else{
                    std::cout << ".";
                }
            }
            std::cout << '\n';
            std::cout << "0x" << std::setfill('0') << std::setw(13) << std::hex << 512*sector_range+count << "  |  ";
        }
    }
}

int Helper::dump_sector(std::ifstream &f, std::vector<char> &data,const int &sector_range){
    if (!f){
        std::cout << "File error! Dump sector error.\n";
        return -1;
    }
    f.seekg(sector_range*512);
    f.read(&data[0], 512);
    return 1;
}

int Helper::dump_random_data(std::ifstream &f, std::vector<char> &data, const int&sector_range, const int&num_bytes){
    if (!f){
        std::cout << "File error! Dump sector error.\n";
        return -1;
    }
    f.seekg(sector_range*512);
    f.read(&data[0], num_bytes);
    return 1;
}

long int Helper::get_size_of_file(std::ifstream &f){
    if (!f){
        std::cout << "File error! Could not get size of file.\n";
        return -1;
    }
    long int size;
    long int seek_cur = f.tellg();
    f.seekg(0, std::ios::end);
    size = f.tellg();
    f.seekg(seek_cur);
    return size;
}

bool Helper::covert_char_vec_to_uint8_vec(const std::vector<char> &src, std::vector<uint8_t> &des){
    if (src.size() != des.size()) return false;
    for (int i=0;i<src.size();++i){
        des[i] = src[i];
    }
    return true;
}

void Helper::show_hex_data_sector_uint8(const std::vector<uint8_t> &sector_data){
    for(int i=0;i<sector_data.size();++i){
        if (i%16 == 0) std::cout <<std::endl;
        std::cout << std::hex << sector_data[i] << " ";
    }
}