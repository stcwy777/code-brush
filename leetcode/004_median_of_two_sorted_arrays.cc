/* 004 median_of_two_sorted_arrays.cc
 *
 * leetcode problem 004:
 * There are two sorted arrays nums_m and nums_n of size m and n respectively.
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 *
 * History: 
 *  03/31/2016: file created
 *  03/31/2016: tried iterator and index visit, the former is 10% solower.
 *
 * Author: Yun Wang <yunw@email.arizona.edu>
 */

#include "common.h"

double find_median_of_two_sorted_arrays(vector<int>& nums_m, 
                                        vector<int>& nums_n) {
    double median;
    size_t len_m = nums_m.size();
    size_t len_n = nums_n.size();    
    
    // Odd number: median_type = 1, median is middle
    // Even number: median_type = 0, median is the mean of two number in middle
    const size_t ODD = 1;
    const size_t EVEN = 2;
    size_t num_for_median = ((len_m + len_n) % 2) ? ODD : EVEN;
    
    // Move two cursors of the two number lists once a time to select top 
    // (m + n) / 2 + 1 smallest numbers
    vector<int>::iterator it_m = nums_m.begin();
    vector<int>::iterator it_n = nums_n.begin();
    size_t num_movs = (len_m + len_n) / 2 + 1;
    
    // Temprorally store selected number by only the last two (ODD) or 
    // one (Even) will be used for median
    int fetch_num = 0;         
    float sum = 0.0;
     
    while (num_movs) {
        if (it_m == nums_m.end()) { // Fetched all numbers in m, scan n only
            fetch_num = *it_n++;
        } else if (it_n == nums_n.end()) { // Simlar but scan m only
            fetch_num = *it_m++;
        } else {    // Otherwise compare two cursors and move on the small
            if (*it_m <= *it_n) {
                fetch_num = *it_m++;
            } else {
                fetch_num = *it_n++;
            }        
        }
        num_movs--;

        // Accumate laste one/two numbers to calculate median
        if (num_movs < num_for_median) {
            sum += fetch_num;
        }
    }
    
    median = sum / num_for_median;
    return median;
}

int main(int argc, char *argv[]) {
    // Test: Initialize two number lists 
    vector<int> nums_m = {2};
    vector<int> nums_n;
    cout << find_median_of_two_sorted_arrays(nums_m, nums_n) << endl;
    return 0;
}

