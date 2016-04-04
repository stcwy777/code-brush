/* 008_string_to_integer.cc
 *
 * leetcode problem 008:
 * Implement atoi to convert a string to an integer.
 * Hint: Carefully consider all possible input cases. If you want a challenge, 
 * please do not see below and ask yourself what are the possible input cases.
 * C/C++ atoi:
 * 1) Allow leading 0's
 * 2) Allow plus/mius sign before digits
 * 3) Conversion stops at non-digits character and return converted results or 
 *    stoi::no_conversion
 * History: 
 *  04/03/2016: file created
 *   
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

int str_to_int(string str) {
    long converted = 0;      // Return 0 for any invalid situation in below
    int base = 10;    
    // bool no_conversion = true;
    
    // String to integer rules:
    // 1. Skip leading zeros
    // 2. At most one plus/mius sign (-/+) allowed right before numbers
    // 3. Numbers won't overflow. Max 10 digtis (2,147,483,648)
    
    int num_digits = 0;     
    const int MAX_INT_LEN = 10;
    int str_len = str.length();
    int cursor = 0;
    int sign = 1;    
    
    if (str_len == 0) {         // Boundary condition: empty input
        return 0;
    }
    while (str[cursor] == ' ') { // Skip leading zeros
        cursor++;
    }
    
    if (str[cursor] == '-' or str[cursor] == '+') {  // Handle plus/mimus sign
        sign = (str[cursor++] == '-')? -1:1;
    }
    
    while (cursor < str_len) { // Scan string, quit at any invalid character
        
        if ( (str[cursor] < '0') || (str[cursor] > '9') ) {
            break;
        } else {
            converted = converted * base + (str[cursor] - '0');
            if (converted > 0) {
                if (++num_digits > MAX_INT_LEN) {   // Check overflow   
                    break;
                }
            }
        }
        cursor++;
    }
    
    // Reduce to boundary if overflowed accomodating Leetcode online judge
    // Otherwise should return error
    converted *= sign;
    if (converted < INT_MIN) {
        converted = INT_MIN;
    } else if (converted > INT_MAX) {
        converted = INT_MAX;
    }
    
    // if (num_digits > 0) {
    //     no_conversion = false;
    // }
    
    return converted;
}

int main(int argc, char *argv[]) {
    // Test
    string test = "+1";
    cout << str_to_int(test) << endl;
    stoi(test);
    return 0;
}
