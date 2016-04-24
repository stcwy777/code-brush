/* 013_roman_to_integer.cc
 *
 * leetcode problem 013:
 * Given a roman numeral, convert it to an integer.
 * Input is guaranteed to be within the range from 1 to 3999.
 * History: 
 *  04/22/2016: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"


int roman_to_int(string s) {
    
    int value = 0;
    size_t str_len = s.length();
    map<char, int> roman_value( {{'M', 1000}, {'D', 500}, {'C', 100},
                                 {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}} );
    
    // If a current roman char value is less than next roman char value
    // subtract the value (like 4, 9), otherwise add this value
    int cur_roman_value = roman_value[s[0]];
    for (size_t i = 1; i < str_len; i++) {
        int nxt_roman_value = roman_value[s[i]];
        
        if (cur_roman_value < nxt_roman_value) {
            value -= cur_roman_value;
        } else {
            value += cur_roman_value;
        }

        cur_roman_value = nxt_roman_value;
    }
    value += roman_value[s[str_len - 1]];       // Add last roman char

    return value;  
}


int main(int argc, char *argv[]) {
    // Test
    vector<string> romans = {"MCMXCVI", "XV", "DCCC", "MCMLXXXIV", "DCXXI"};
    for (auto i : romans) {
        cout << roman_to_int(i) << endl;
    }
    return 0;
}

