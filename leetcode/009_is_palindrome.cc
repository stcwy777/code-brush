/* 009_is_palindrome.cc
 *
 * leetcode problem 009:
 * Determine whether an integer is a palindrome. Do this without extra space.
 *
 * History: 
 *  04/04/2016: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

bool is_palindrome(int x) {
    int tmp = x;
    int rev = 0;
    
    if (x < 0) {        // Negative number doesn't count as palindrome
        return false;
    }

    while (tmp) {       // Reverse the integer 
        rev = rev * 10 + tmp % 10;
        tmp /= 10;
    }

    if (rev == x) {     // True for a palindrome number if num remain the same
        return true;
    } else {
        return false;
    }
}

int main(int argc, char *argv[]) {
    // Test
    vector<int> nums = {1, 11, 121, 1211, 1221, -1};
    
    for (auto num : nums) {
        cout << num << ':' << is_palindrome(num) << endl;
    }
    return 0;
}

