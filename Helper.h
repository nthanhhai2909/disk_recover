#ifndef __HELPER_H__
#define __HELPER_H__

#include<iostream>
#include<map>
#include<fstream>
#include<vector>
#include<iomanip>

class Helper{
    public:
        Helper();
        ~Helper();
    public:
        void set_code_mapping_type_fs(std::map<uint8_t, std::string> &code_mapping_type_fs, const std::vector<uint8_t> &code, const std::vector<std::string> &type_fs);
        void show_hex_data_dump(const std::vector<char> data,const int &sector_range);
        int dump_sector(std::ifstream &f, std::vector<char> &data,const int &sector_range);
        int dump_random_data(std::ifstream &f, std::vector<char> &data, const int&sector_range, const int&num_bytes);
        long int get_size_of_file(std::ifstream &f);
        bool covert_char_vec_to_uint8_vec(const std::vector<char> &src, std::vector<uint8_t> &des);
        void show_hex_data_sector_uint8(const std::vector<uint8_t> &sector_data);
};

#endif // !__HELPER_H__