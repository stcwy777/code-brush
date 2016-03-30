/* common.h
 *
 * This header include common header files and defines useful macros and inline
 * functions.
 *
 * History: 
 *  03/18/2010: file created
 *  03/28/2016: modified for code-brush project
 *  03/29/2016: added template function for cleaning up a linked list
 *  03/30/2016: added const value MAX_CHAR and PI
 *    
 *  Author: Yun Wang <yunw@email.arizona.edu>
 */
#ifndef COMMON_H
#define COMMON_H

// Linux C header file
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <regex.h>
#include <string.h>
#include <math.h>
#include <limits.h>
// C++ header file
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Const values
const int MAX_CHAR = 256;       // Maximum number of chars in ASCII
const double PI = 3.1415926     // Value of PI

// Check whether character is a number or not
inline int isNumber(char charValue)
{
    if (charValue <= 0x39 && charValue >= 0x30)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Transform hex string to integer
inline int hex2int(const char* hexStr)
{
    int intVar;
    sscanf(hexStr, "%x", &intVar);
    /*
    if (intVar == 1082 || intVar == 20070 || intVar == 36710)
    {
        fstream ftest;
        ftest.open("code.txt", ios::out | ios::app);
        ftest << hexStr << endl;
        ftest.close();
    }
    */
    return intVar;
}

// Transform integer to string
inline string int2str(int num)
{
    stringstream ostream;
    ostream << num;
    return ostream.str();
}

// File size in byte
inline u_int fileSize(ifstream& file)
{
    u_int size;

    file.seekg(0, ios::end);
    size = file.tellg();
    file.seekg(0, ios::beg);

    return size;
}

// String split
inline vector<string>& split(string& str, char delim, vector<string>& elems)
{
    stringstream ss(str);
    string item;
    elems.clear();
    
    while(getline(ss, item, delim)) 
    {
        elems.push_back(item);
    }
    return elems;
}

// Transfomr UCS2 to UTF-8
inline u_int ucs2utf(char* utfCode, u_short ucsCode)
{
    u_int   size;           // Tranformed code size
    /* Conversion Rules   
    (1)if UCS < 0x007F(00000000 - 01111111), tranlated to ASCII； 
    (2)if UCS < 0x07FF, tranlate to 2 bytes, 11 bits from right side insert into 110xxxxx 10yyyyyy
       etc. 00000aaa bbbbbbbb ==> 110aaabb 10bbbbbb 
    (3)else translate to 3 bytes, 16 bits from right sied insert blank space
       etc. aaaaaaaa bbbbbbbb ==> 1110aaaa 10aaaabb 10bbbbbb 
    */
    if (ucsCode <= 0x007F)
    {
        utfCode[0] = ucsCode;
        size = 1;
    }
    else if (ucsCode <= 0x07FF)
    {
        utfCode[0] = 0xC0 + (ucsCode >> 6);
        utfCode[1] = 0x80 + (ucsCode & 0x003F); 
        size = 2;
    }
    else
    {
        utfCode[0] = 0xE0 + (ucsCode >> 12);
        utfCode[1] = 0x80 + ((ucsCode & 0x0FC0) >> 6);
        utfCode[2] = 0x80 + (ucsCode & 0x003F);
        size = 3;
    }   
    return size;
}

// Clean up a singly linked list
template<typename T>
void clear_list(T* list_head)
{
    T* tmp_p = list_head;
    while (list_head) {
	list_head = tmp_p->next;
    	delete tmp_p;
	tmp_p = list_head;
    }
}
#endif 
