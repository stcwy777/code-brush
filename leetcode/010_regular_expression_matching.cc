/* 010_regular_expression_matching.cc
 *
 * leetcode problem 010:
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 *
 * The matching should cover the entire input string (not partial).
 *
 * Some examples:
 *  isMatch("aa","a") → false
 *  isMatch("aa","aa") → true
 *  isMatch("aaa","aa") → false
 *  isMatch("aa", "a*") → true
 *  isMatch("aa", ".*") → true
 *  isMatch("ab", ".*") → true
 *  isMatch("aab", "c*a*b") → true
 *
 * History: 
 *  04/11/2016: file created
 *  04/15/2016: added dp implementation
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

bool is_match_dp(string s, string p) {
    int len_p = p.length();
    int len_s = s.length();
    bool matched = false;
    
    // dp[i][j]: if s[i:] matches p[j:] including '\0'
    bool dp[len_s + 1][len_p + 1];
    
    // if pattern is empty set false unless input string is empty too
    for (int i = 0; i < len_s; i++) { 
        dp[i][len_p] = false;
    }
    dp[len_s][len_p] = true;
    
    // for the special symbol '*' the solution is:
    // try to match as many procedding letter as possible and check if left 
    // input string can be matched
    for (int i = len_s; i >= 0; i--) {
        for (int j = len_p - 1; j >= 0; j--) { // skip dp[x][len_p] already set
            if (p[j + 1] == '*') {             // next symbol is *
                if (dp[i][j + 2] == true) {    // * matches zero 
                    dp[i][j] = true;
                } else {
                    dp[i][j] = false;          // by default set this dp false
                    for (int k = i; k < len_s; k++) { // * matches 1 to len_s
                        if (s[k] == p[j] || p[j] == '.') {
                            // Check if left input string matches
                            if (dp[k + 1][j + 2] == true) {
                                dp[i][j] = true;
                                break;
                            }
                        } else { // if a letter doesn't match set false
                            dp[i][j] = false;
                            break;
                        }
                    }
                }
            } else if (s[i] == p[j] || (p[j] == '.' && s[i] != '\0')) {
                dp[i][j] = dp[i + 1][j + 1];
            } else {
                dp[i][j] = false;
            }
        }
    }
    matched = dp[0][0];
    return matched;
}
bool is_match_rec(string s, string p) {
    
    size_t len_p = p.length();
    size_t len_s = s.length();
    bool matched = false;
    
    // boundary check
    if (len_p == 0) {
        if (len_s == 0) {
            return true;
        } else {
            return false;
        }
    }

    // for the special symbol '*' the solution is:
    // try to match as many procedding letter as possible and check if left 
    // input string can be matched
    if (len_p > 1 && p[1] == '*') {         // next symbol in pattern is '*'
        if (is_match_rec(s, p.substr(2))) { // '*' matches zero
            return true;
        } else {
            for (size_t i = 0; i < len_s; i++) {    // '*' matches 1 to len_s
                if ((s[i] == p[0] || p[0] == '.')) {
                    if (is_match_rec(s.substr(i+1), p.substr(2))) {
                        return true;
                    }
                } else {
                    return false;
                }
            }
        }
    } else if ((p[0] == '.' && len_s > 0) || p[0] == s[0]){ // next isn't '*'
        matched = is_match_rec(s.substr(1), p.substr(1));
    } 
    
    return matched;
}


int main(int argc, char *argv[]) {
    // Test
    //string s = "aaaaaaaaaaaaab";
    //string p="a*a*a*a*a*a*a*a*a*a*c";
    //string s = "acaabbaccbbacaabbbb";
    //string p = "a*.*b*.*a*aa*a*";
    //string s = "abcd";
    string s = "aa";
    string p = "a*";
    cout << is_match_dp(s, p) << endl;
    return 0;
}

