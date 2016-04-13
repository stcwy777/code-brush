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
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"


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

    if (len_p > 1 && p[1] == '*') {     // next symbol in pattern is '*'
        if (is_match_rec(s, p.substr(2))) { // use '*' as zero
            return true;
        } else {
            for (size_t i = 0; i < len_s; i++) {    // use '*' as 1 to len_s
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
    string s = "aaaaaaaaaaaaab";
    string p="a*a*a*a*a*a*a*a*a*a*c";
    //string s = "abcd";
    //string p = "d*";
    cout << is_match_rec(s, p) << endl;
    return 0;
}

