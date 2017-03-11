/* 014_longest_common_prefix.cc
 *
 * leetcode problem 014:
 * Write a function to find the longest common prefix string amongst an array of 
 * strings
 *
 * History: 
 *  03/10/2017: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

string find_longest_prefix(vector<string> strs) {
    if (strs.size() == 0) {
        return "";
    }
    string prefix = strs[0];
    int prefix_len = 0;
    // vector<string>::iterator  = next(strs.begin(), 1);

    while (prefix_len < prefix.length()) {
        bool match = true;
        for (int i = 1; i < strs.size(); i++) {
            if (strs[i][prefix_len] != prefix[prefix_len]) {
                match = false;
                break;
            }
        }

        if (match) {
            prefix_len++;
        } else {
            break;
        }
    }
    return prefix.substr(0, prefix_len);
}

int main(int argc, char *argv[]) {
    // Test: Initialize two number lists
    const char* args[] = {"123", "12221", "12"};
    std::vector<string> strs(args, args + 3);    
    cout << find_longest_prefix(strs) << endl;
    return 0;
}

