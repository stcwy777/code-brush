/* 006_zigzag_conversion.cc
 *
 * leetcode problem 005:
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 * of rows like this: 
 *      P   A   H   N
 *      A P L S I I G
 *      Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR".
 * Write the code that will take a string and make this conversion given a 
 * number of rows: convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 * 
 * History: 
 *  04/03/2016: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

string zigzag_convert(string s, int num_rows) {
    
    if (num_rows <= 1) {        // Boundary condition: no need to zigzag
        return s;
    }
    
    string zigzag;
    string* pattern_rows = new string[num_rows];
    int mov_dir = 1;
    
    pattern_rows[0] += s[0];    // Assign first character
    int cur_row = 0;
    // Create zigzag string is a process of assigning original characters to the
    // three rows. There are two directions: "forward" (add row number) and
    // "backward" (reduce row number). After oberservation, the direction needs
    // to change every (num_rows - 1) assigns.
    for (int i = 1; i < s.length(); i++) {
        cur_row += mov_dir;
        pattern_rows[cur_row] += s[i];
        
        // Change direction every (num_rows -1 ) moves
        if ( !(i % (num_rows - 1))) {       
            mov_dir *= (-1);
        }
    }
    
    for (int i = 0; i < num_rows; i++ ) {   // Concate all rows
        zigzag += pattern_rows[i];
    }
    delete[] pattern_rows;       // Clear heap       
    return zigzag;
}

int main(int argc, char *argv[]) {
    // Test: Initialize two number lists
    string s = "PAYPALISHIRING"; 
    cout << zigzag_convert(s, 2) << endl;
    return 0;
}
