/* two_sum.cc
 *
 * leetcode problem 001:
 * Given an array of integers, return indices of the two numbers such that they
 * add up to a specific target. You may assume that each input would have only
 * one solution
 *
 * History: 
 *  03/29/2016: file created
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"
typedef unordered_map<int, int> NumHash;                
typedef vector<int> IntVector;

// Use the same function definition from leetcode
vector<int> two_sum(vector<int>& nums, int target) {
    
    NumHash num_indices;        
    IntVector solution;
     
    // Scan all numbers and store its index in a hash table
    for (size_t i = 0; i < nums.size(); i++) {
        
        int num = nums[i];
        // If the number already in the hash table, simply add its index to 
        // existing value.Since there is exactly one solution. At most two same
        // number will be in the input list
        if(num_indices.find(num) != num_indices.end()) {
            num_indices[num] += i;
        } else {
            num_indices.insert(make_pair(num, i));
        }
    }
    // Get the solution by minus a number from the target
    for (size_t i = 0; i < nums.size(); i++) {
        int num_look_for = target - nums[i];
        
        if(num_indices.find(num_look_for) != num_indices.end()) { 
            // Same number: check more
            if (num_look_for == nums[i]) {
                // check if the input dose have two same numbers
                if ((num_indices[num_look_for] - i) > 0) {            
                    solution.push_back(i);
                    solution.push_back(num_indices[i] - i);
                    break;
                }
            } else {  // Not the same number: get solution
                solution.push_back(i);
                solution.push_back(num_indices[num_look_for]);
                break;
            }
        }
    }
    return solution; 
}

int main(int argc, char *argv[]) {
    // Test 
    vector<int> nums = {3,2,4};
    int target = 6;
    vector<int> solution = two_sum(nums, target);
    for (auto i : rslt) {
        cout << i << endl;
    }
    return 0;
}

