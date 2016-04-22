/* 012_integer_to_roman.cc
 *
 * leetcode problem 012:
 * Given an integer, convert it to a roman numeral.
 * Input is guaranteed to be within the range from 1 to 3999.
 *
 * History: 
 *  04/22/2016: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"


string int_to_roman(int num) {
    
    string roman;
    int base[7] = {1000, 500, 100, 50, 10, 5, 1};
    const char roman_chars[7] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};

    // Examine thousands, hundreds tens and ones
    for (int i = 0; i < 7; i += 2) {    
        int num_char = num / base[i];

        if (num_char == 4) {                    // '4': use '1' + '5' 
            roman += roman_chars[i];
            roman += roman_chars[i - 1];
        } else if (num_char == 9) {             // '9': use '1' + '10'
            roman += roman_chars[i];
            roman += roman_chars[i - 2];
        } else {
            if (num_char >= 5) {                // if larger than 5
                roman += roman_chars[i - 1];
                num_char -= 5;
            } 
            for (int j = 0; j < num_char; j++) {
                roman += roman_chars[i];
            }
        }
        num %= base[i];

        if (!num) { // no nums left need to convert
            break;
        }
    }
    return roman;
}


int main(int argc, char *argv[]) {
    // Test
    vector<int> num= {4, 9, 40, 90, 400, 900, 3999};
    for (auto i : num) {
        cout << int_to_roman(i) << endl;
    }
    return 0;
}

