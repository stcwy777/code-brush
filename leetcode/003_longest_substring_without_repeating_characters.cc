/* 003_longest_substring_without_repeating_characters.cc
 *
 * leetcode problem 003:
 * Given a string, find the length of the longest substring without repeating 
 * characters. For example, the longest substring without repeating letters for
 * "abcabcbb" is "abc", which the length is 3. For "bbbbb" the longest 
 * substring is "b", with the length of 1.
 *
 * History: 
 *  03/30/2016: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

int length_of_longest_substring(string s) {
    
    if (s.size() == 0) {    // Boundary case
        return 0;
    }
     
    // Examine characters from left to right. Use max_left to store the length
    // of non-repeating substring to the left of the character being examined.
    // When a character is repeated (non-negative value in the look up array.
    // Update max_left and max_len (if needed). Otherwise, increase max_left by
    // 1 and scan next char.
    
    size_t max_len = 1;      // current longest substring
    size_t max_left = 1;
    
    // Look up array (-1 means not met, or non-negative means the index of the 
    // last scanned character. use char ASCII value as the index
    int found_indices[MAX_CHAR]; 

    for (size_t i = 0; i < MAX_CHAR; i++) {
        found_indices[i] = -1;
    }
    found_indices[size_t(s[0])] = 0;
    
    for (size_t i = 1; i < s.size(); i++) {  // First char ignored
        int exist_index = found_indices[size_t(s[i])];
        
        // If the char has appeared within the max_left range
        if ((exist_index != -1) && ((i - exist_index) <= max_left)) {
            max_left = i - exist_index;
        } else {
            max_left += 1;
        }
        
        found_indices[size_t(s[i])] = i;    // Update array with the new index
        if (max_left > max_len) {   // Update max_len
            max_len = max_left;
        }
    }
    return max_len; 
}

int main(int argc, char *argv[]) {
    // Some test cases
    string s[6] = {"eeydgwdykpv", "cdd", "aaaaa", "a", "", "anviaj"};
    for (int i = 0; i < 6; i++) {
        cout << length_of_longest_substring(s[i]) << endl;
    }
    return 0;
}
