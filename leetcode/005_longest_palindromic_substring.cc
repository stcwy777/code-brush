/* 005_longest_palindromic_substring.cc
 *
 * leetcode problem 005:
 * Given a string S, find the longest palindromic substring in S. You may assume
 * that the maximum length of S is 1000, and there exists one unique longest 
 * palindromic substring.
 *
 * History: 
 *  04/02/2016: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

string find_longest_palindromic_substring(string s) {
    string palindrome;
    size_t plndm_len = 0;
    size_t anchor = 0;
    size_t s_len = s.length();
    bool dp[s_len][s_len];              // Stores if s[i to j] is a palindrome
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < s_len; i++) {   // Each char is palindrome
        dp[i][i] = true;
        plndm_len = 1;
        anchor = i;
    }
    
    for (int i = 0; i < s_len - 1; i++) { // If two nearby chars are the same
        if (s[i] == s[i + 1]) {
            dp[i][i+1] = true;
            plndm_len = 2;
            anchor = i;
        }
    }
    
    for (int i = 3; i <= s_len; i++) {  // For substr length > 3
        for (int j = 0; j <= (s_len - i); j++) {
            // Check table dp to see if can extend palindrome from substring
            if ((s[j] == s[j + i - 1]) && (dp[j + 1][j + i - 2] == true)) {
                dp[j][j + i - 1] = true;
                plndm_len = i;
                anchor = j;
            } else {
                dp[j][j + i - 1] = false;
            }
        }
    }
    
    palindrome = s.substr(anchor, plndm_len);
    return palindrome;
}

int main(int argc, char *argv[]) {
    // Test: Initialize two number lists
    string s = "aaabaaaa"; 
    cout << find_longest_palindromic_substring(s) << endl;
    return 0;
}

