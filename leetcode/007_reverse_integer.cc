/* 007_reverse_integer.cc
 *
 * leetcode problem 007:
 * Reverse digits of an integer.
 *     Example1: x = 123, return 321
 *     Example2: x = -123, return -321
 * 
 * History: 
 *  04/03/2016: file created
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

int reverse_integer(int x) {
    long reversed = 0;      // Use long type to check overflow
    int base = 10;
    int residue = x;
    
    // In each step, move reversed number left by one digit (x 10) and
    // then add unit digit of current residue
    while (residue) {       
        int unit_digit = residue % base;
        reversed = base * reversed + unit_digit;
        residue /= base;
    }
    
    // Check if result still in integer range
    if (reversed > INT_MAX || reversed < INT_MIN) {
        reversed = 0;
    }
    return (int)reversed;
}

int main(int argc, char *argv[]) {
    // Test: a case of overflow
    int test = 1534236469;
    cout << reverse_integer(test) << endl;
    return 0;
}
