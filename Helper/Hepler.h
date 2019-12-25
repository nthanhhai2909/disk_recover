
#ifndef __HELPER_H__
#define __HELPER_H__

#include<iostream>
#include<map>
#include<fstream>
#include<vector>
#include<iomanip>
#include <stdint.h>

using namespace std;

/*
 *  Go to sector of file(can be disk)
 *  param 1: file
 *  param 2: data to store byte
 *  param 3: sector_range
 */
void goToSectorOfFile(ifstream &, vector<char> &, const int&, const int&numBytes);

/**
 * Convert vector char to Uint8
 */ 
bool convertCharToUint8InVector(const vector<char> &src, vector<uint8_t> &);
